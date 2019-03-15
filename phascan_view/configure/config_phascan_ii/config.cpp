#include "config.h"
#include "msgpack/msgpack.h"
#include <QDebug>
#include <QList>
#include "../DopplerDataFileOperateor.h"

Config *Config::m_instance = NULL;

Config *Config::instance()
{
    if(NULL == m_instance) {
        m_instance = new Config;
    }
    return m_instance;
}

bool Config::load(const QString &filename, DopplerDataFileOperateor *dataFile)
{   
    m_pDataFile = dataFile;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("%s[%d]:Open %s failed",__func__, __LINE__,
                 filename.toUtf8().data());
        set_is_phascan_ii(false);
        return false;
    }

    if(!is_phascan_ii_file(file)) {
        qWarning("%s[%d]: %s is not phascan ii file!",__func__, __LINE__,
                 filename.toUtf8().data());
        set_is_phascan_ii(false);
        return false;
    }

    int totalSize = file.size();
    quint64 len = 0;

    file.read((char *)&len, sizeof(len));
    if (len <= 0 || len > totalSize) {
        qWarning("%s(%s[%d]): Read Configuare Data failed", __FILE__, __func__, __LINE__);
        set_is_phascan_ii(false);
        return false;
    }
    QByteArray data = file.read(len);

    QFile tmp("mercury.cfg");
    if (!tmp.open(QIODevice::WriteOnly|QIODevice::Truncate)) {
        qWarning("%s(%s)[%d]", __FILE__, __func__, __LINE__);
        set_is_phascan_ii(false);
        return false;
    }
    tmp.write(data);
    tmp.close();
    QSettings src("mercury.cfg", QSettings::defaultFormat());
    QSettings dst;
    dst.clear();
    QStringList keys = src.allKeys();
    QVariantMap childMap;
    foreach (QString key, keys) {
        dst.setValue(key, src.value(key));

        childMap.clear();
        childMap = src.value(key).toMap();
        qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                 << " ******** key " << key << " *****************"
                 << " value " << src.value(key)
                 << " \n ";
        print_all_key(0, childMap);
    }
    QFile::remove("mercury.cfg");

    m_global.groupQty = dst.value("GroupQty").toUInt();
    m_global.prfMode = static_cast<PrfMode> (dst.value("PrfMode").toUInt());

    unpack_display();
    unpack_scanner();
    unpack_global_transceiver();

    for(int i = 0; i < m_global.groupQty; ++i) {
        unpack_group(i);
        convert_to_phascan_config(i);
    }

    convert_other_to_phascan_config();

    if (file.atEnd()) {
        set_is_phascan_ii(true);
        return true;
    }

    file.read((char *)&len, sizeof(len));
    m_dataMark.resize(len);
    if (len <= 0 || len != file.read(m_dataMark.data(), len)) {
        qWarning("%s(%s[%d]): Read Mark Failed", __FILE__, __func__, __LINE__);
        set_is_phascan_ii(false);
        return false;
    }
    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " len " << len
             << " mark len " << m_dataMark.length();

    memset(m_pDataFile->m_cDrawInfoPack.bScanMark, 0, sizeof(unsigned char) * 1024 * 256);
    memcpy(m_pDataFile->m_cDrawInfoPack.bScanMark, m_dataMark.data(), len);

    file.read((char *)&len, sizeof(len));
    m_dataSource.resize(len);
    if (len <= 0 || len != file.read(m_dataSource.data(), len) ) {
        qWarning("%s(%s[%d]): Read Data(%d) failed", __FILE__, __func__, __LINE__, len);
        set_is_phascan_ii(false);
        return false;
    }

    m_pDataFile->m_pBeamData = (unsigned char *)m_dataSource.data();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << " Read Phascan II Data Success!!";
    set_is_phascan_ii(true);
    return true;
}

Config::Config(QObject *parent)
    : QSettings(parent),
      m_pDataFile(NULL),
      m_currentGroup(m_groups[0]),
      s_alarmCount(ALARM_COUNT),
      m_isPhascanII(false)
{
}

void Config::unpack_group(int groupId)
{
    m_currentGroup = m_groups[groupId];

    QVariantMap map = value(QString("Group%1").arg(groupId)).toMap();

    m_currentGroup.mode         = static_cast<GroupMode> (map["Mode"].toUInt());
    m_currentGroup.utUnit       = static_cast<UtUnit> (map["UtUnit"].toUInt());
    m_currentGroup.highestTrack = map["HighestTrack"].toBool();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " mode " << m_currentGroup.mode
             << " ut unit " << m_currentGroup.utUnit
             << " highestTrack " << m_currentGroup.highestTrack;

    unpack_focallawer(map["Focallawer"].toMap());
    unpack_gate(map["GateA"].toMap(), m_currentGroup.gateA);
    unpack_gate(map["GateB"].toMap(), m_currentGroup.gateB);
    unpack_gate(map["GateI"].toMap(), m_currentGroup.gateI);
    unpack_transceiver(map["Transceiver"].toMap());
    unpack_cursor(map["Cursor"].toMap());
    unpack_sample(map["Sample"].toMap());
    unpack_c_scan(map["CScan"].toMap());

    /* has not added.*/
    unpack_curves();
    unpack_thickness();
}

void Config::unpack_display()
{
    S_Display &display = m_global.display;

    QVariantMap displayMap= value("Display").toMap();

    display.ampPalette   = displayMap["AmpPalette"].toString();
    display.bright       = displayMap["Bright"].toUInt();
    display.cursor       = displayMap["Cursor"].toBool();
    display.depthPalette = displayMap["DepthPalette"].toString();
    display.groups       = displayMap["Groups"].toList();
    display.language     = displayMap["Language"].toUInt();
    display.layout       = displayMap["Layout"].toUInt();
    display.opacity      = displayMap["Opacity"].toUInt();
    display.tofdPalette  = displayMap["TofdPalette"].toString();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " ampPalette " << display.ampPalette
             << " bright " << display.bright
             << " cursor " << display.cursor
             << " depthPalette " << display.depthPalette
             << " groups " << display.groups
             << " language " << display.language
             << " layout " << display.layout
             << " opacity " << display.opacity
             << " tofdPalette " << display.tofdPalette;
}

void Config::unpack_sample(const QVariantMap &map)
{
    m_currentGroup.sample.gain          = map["Gain"].toDouble();
    m_currentGroup.sample.start         = map["Start"].toDouble();
    m_currentGroup.sample.range         = map["Range"].toDouble();
    m_currentGroup.sample.maxGain       = map["MaxGain"].toUInt();
    m_currentGroup.sample.refGainStatus = map["RefGainStatus"].toUInt();
    m_currentGroup.sample.refGain       = map["RefGain"].toDouble();
    m_currentGroup.sample.pointQty      = map["PointQty"].toInt();
    m_currentGroup.sample.autoCalcPointQty= map["AutoCalcPointQty"].toBool();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " gain " << m_currentGroup.sample.gain
             << " refGainStatus " << m_currentGroup.sample.refGainStatus
             << " ref gain " << m_currentGroup.sample.refGain
             << " start " << m_currentGroup.sample.start
             << " range " << m_currentGroup.sample.range
             << " maxGain " << m_currentGroup.sample.maxGain
             << " point_qty " << m_currentGroup.sample.pointQty
             << " autoCalcPointQty " << m_currentGroup.sample.autoCalcPointQty;
}

void Config::unpack_c_scan(const QVariantMap &map)
{
    S_CScan &cScan = m_currentGroup.cScan;
    cScan.mode = static_cast<CScanMode> (map["Mode"].toUInt());
    cScan.sourceType = static_cast<SourceType> (map["SourceType"].toUInt());
    cScan.topCWidth = map["TopCWidth"].toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " mode " << cScan.mode
             << " sourceType " << cScan.sourceType
             << " topCWidth " << cScan.topCWidth;
}

void Config::unpack_transceiver(const QVariantMap &map)
{
    m_currentGroup.transceiver.autoCalPW  = map["AutoCalPW"].toBool();
    m_currentGroup.transceiver.average    = static_cast<Averaging> (map["Average"].toUInt());
    m_currentGroup.transceiver.filter     = map["Filter"].toUInt();
    m_currentGroup.transceiver.txRxMode   = static_cast<TxRxMode> (map["Mode"].toUInt());
    m_currentGroup.transceiver.pw         = map["PW"].toFloat();
    m_currentGroup.transceiver.pulser     = map["Pulser"].toUInt();
    m_currentGroup.transceiver.receiver   = map["Receiver"].toUInt();
    m_currentGroup.transceiver.rectifier  = static_cast<Rectifier> (map["Rectifier"].toUInt());
    m_currentGroup.transceiver.videoFilter= map["VideoFilter"].toBool();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " autoCalPW " << m_currentGroup.transceiver.autoCalPW
             << " tx_rx mode " << m_currentGroup.transceiver.txRxMode
             << " pulser width " << m_currentGroup.transceiver.pw
             << " filter " << m_currentGroup.transceiver.filter
             << " rectifier " << m_currentGroup.transceiver.rectifier
             << " video filter " << m_currentGroup.transceiver.videoFilter
             << " averaging " << m_currentGroup.transceiver.average
             << " pulser " << m_currentGroup.transceiver.pulser
             << " receiver " << m_currentGroup.transceiver.receiver;
}

void Config::unpack_focallawer(const QVariantMap &map)
{
    m_currentGroup.focallawer.focusMode = static_cast<FocusMode> (map["FocusMode"].toUInt());
    m_currentGroup.focallawer.scanMode  = static_cast<ScanMode> (map["ScanMode"].toUInt());
    m_currentGroup.focallawer.waveType = static_cast<WaveType> (map["WaveType"].toInt());

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " wave type " << m_currentGroup.focallawer.waveType
             << " focus mode " << m_currentGroup.focallawer.focusMode
             << " scan mode " << m_currentGroup.focallawer.scanMode;

    unpack_scan(map["Scan"].toMap());

    unpack_focus(map["Focus"].toMap());

    unpack_wedge(map["Wedge"].toMap());

    unpack_probe(map["Probe"].toMap());

    unpack_specimen(map["Specimen"].toMap());

    unpack_beams_info();
}

void Config::unpack_scan(const QVariantMap &map)
{
    S_Scan &scan = m_currentGroup.focallawer.scan;

    if(Linear == m_currentGroup.focallawer.scanMode) {
        scan.refractAngle   = map["RefractAngle"].toDouble();
        scan.screwAngle     = map["ScrewAngle"].toDouble();

        scan.secApe         = map["SecApe"].toUInt();
        scan.secElemStep    = map["SecElemStep"].toUInt();
        scan.secStartElem   = map["SecStartElem"].toUInt();
        scan.secStopElem    = map["SecStopElem"].toUInt();

        scan.priApe         = map["PriApe"].toUInt();
        scan.priElemStep    = map["PriElemStep"].toUInt();
        scan.priStartElem   = map["PriStartElem"].toUInt();
        scan.priStopElem    = map["PriStopElem"].toUInt();

        qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                 << " refractAngle " << scan.refractAngle
                 << " screwAngle " << scan.screwAngle
                 << " priApe " << scan.priApe
                 << " priStartElem " << scan.priStartElem
                 << " priElemStep " << scan.priElemStep
                 << " priStopElem " << scan.priStopElem
                 << " secApe " << scan.secApe
                 << " secStartElem " << scan.secStartElem
                 << " secElemStep " << scan.secElemStep
                 << " secStopElem " << scan.secStopElem;
    } else {

        scan.refractStartAngle = map["RefractStartAngle"].toDouble();
        scan.refractStopAngle  = map["RefractStopAngle"].toDouble();
        scan.refractStepAngle  = map["RefractStepAngle"].toDouble();

        scan.screwStartAngle   = map["ScrewStartAngle"].toDouble();
        scan.screwStopAngle    = map["ScrewStopAngle"].toDouble();
        scan.screwStepAngle    = map["ScrewStepAngle"].toDouble();

        scan.priApe         = map["PriApe"].toUInt();
        scan.priStartElem   = map["PriStartElem"].toUInt();
        scan.secApe         = map["SecApe"].toUInt();
        scan.secStartElem   = map["SecStartElem"].toUInt();

        qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                 << " refractStartAngle " << scan.refractStartAngle
                 << " refractStopAngle " << scan.refractStopAngle
                 << " refractStepAngle " << scan.refractStepAngle
                 << " screwStartAngle " << scan.screwStartAngle
                 << " screwStopAngle " << scan.screwStopAngle
                 << " screwStepAngle " << scan.screwStepAngle
                 << " priApe " << scan.priApe
                 << " priStartElem " << scan.priStartElem
                 << " secApe " << scan.secApe
                 << " secStartElem " << scan.secStartElem;
    }
}

void Config::unpack_probe(const QVariantMap &map)
{
    S_Probe &probe = m_currentGroup.probe;

    probe.arrayMode     = static_cast<ArrayMode> (map.value("ArrayMode", DEFAULT_ARRAY_MODE).toUInt());
    probe.freq          = map.value("Freq", DEFAULT_PROBE_FREQ).toDouble();
    probe.model         = map.value("Model", DEFAULT_PROBE_MODEL).toString();
    probe.serial        = map.value("Serial", DEFAULT_PROBE_SERIAL).toString();
    probe.priElemQty    = map.value("PriElemQty", DEFAULT_ELEMQTY).toUInt();
    probe.secElemQty    = map.value("SecElemQty", DEFAULT_ELEMQTY).toUInt();
    probe.priPitch      = map.value("PriPitch", DEFAULT_PRI_PITCH).toFloat();
    probe.secPitch      = map.value("SecPitch", DEFAULT_SEC_PITCH).toFloat();
    probe.refPoint      = map.value("RefPoint", DEFAULT_REFPOINT).toFloat();
    probe.scanOffset    = map.value("ScanOffset", DEFAULT_OFFSET).toDouble();
    probe.indexOffset   = map.value("IndexOffset", DEFAULT_OFFSET).toDouble();
    probe.type          = static_cast<ProbeType> (map.value("Type", DEFAULT_PROBE_TYPE).toUInt());
    probe.skew          = map.value("Skew", DEFAULT_SKEW).toUInt();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " Serial " << probe.serial
             << " Model " << probe.model
             << " freq " << probe.freq
             << " scanOffset " << probe.scanOffset
             << " indexOffset " << probe.indexOffset
             << " skew " << probe.skew
             << " type " << probe.type
             << "\n[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " arrayMode " << probe.arrayMode
             << " priElemQty " << probe.priElemQty
             << " secElemQty " << probe.secElemQty
             << " priPitch " << probe.priPitch
             << " secPitch " << probe.secPitch
             << " refPoint " << probe.refPoint;
}

void Config::unpack_wedge(const QVariantMap &map)
{
    S_Wedge &wedge = m_currentGroup.wedge;

    wedge.serial        = map.value("Serial", DEFAULT_WEDGE_SERIAL).toString();
    wedge.model         = map.value("Model", DEFAULT_WEDGE_MODEL).toString();
    wedge.angle         = map.value("Angle", DEFAULT_WEDGE_ANGLE).toDouble();
    wedge.fstElemHeight = map.value("FstElemHeight", DEFAULT_WEDGE_FIRST_ELEM_HEIGHT).toDouble();
    wedge.length        = map.value("Length", DEFAULT_WEDGE_LENGTH).toDouble();
    wedge.width         = map.value("Width", DEFAULT_WEDGE_WIDTH).toDouble();
    wedge.height        = map.value("Height", DEFAULT_WEDGE_HEIGHT).toDouble();
    wedge.velocity      = map.value("Velocity", DEFAULT_WEDGE_VELOCITY).toDouble();
    wedge.priOffset     = map.value("PriOffset").toDouble();
    wedge.secOffset     = map.value("SecOffset").toDouble();
    wedge.orientation   = static_cast<Orientation> (map.value("Orientation", DEFAULT_WEDGE_ORIENTATION).toUInt());
    wedge.rootAngle     = map.value("RootAngle", DEFAULT_WEDGE_ROOT_ANGLE).toDouble();
    wedge.delay         = map.value("Delay", DEFAULT_WEDGE_DELAY).toUInt();
    wedge.clampOffset   = map.value("Delay", DEFAULT_WEDGE_CLAMP_OFFSET).toDouble();
    /* 以下键值暂不清楚是否存在 */
    wedge.waveType      = static_cast<WaveType> (map.value("WaveType", DEFAULT_WEDGE_WAVE_TYPE).toUInt());
    wedge.refPoint      = map.value("RefPoint", DEFAULT_WEDGE_REF_POINT).toUInt();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " serial " << wedge.serial
             << " model " << wedge.model
             << " angle " << wedge.angle
             << " rootAngle " << wedge.rootAngle
             << " velocity " << wedge.velocity
             << " primaryOffset " << wedge.priOffset
             << " secondaryOffset " << wedge.secOffset
             << " firstElementHeight " << wedge.fstElemHeight
             << " length " << wedge.length
             << " width " << wedge.width
             << " height " << wedge.height
             << " orientation " << wedge.orientation
             << " delay " << wedge.delay
             << " clampOffset " << wedge.clampOffset
             << " wave type " << wedge.waveType
             << " ref pint " << wedge.refPoint;
}

void Config::unpack_specimen(const QVariantMap &map)
{
    S_Specimen &specimen = m_currentGroup.specimen;

    specimen.shape      = static_cast<Shape> (map.value("Shape", DEFAULT_SHAPE).toUInt());
    specimen.LV         = map.value("LV", DEFAULT_LV).toDouble();
    specimen.SV         = map.value("SV", DEFAULT_SV).toDouble();
    specimen.material   = static_cast<Material> (map.value("Material", DEFAULT_MATERIAL).toUInt());
    specimen.density    = map.value("Density", DEFAULT_DENSITY).toDouble();
    specimen.weldType   = static_cast<WeldType> (map.value("WeldType", DEFAULT_WELD_TYPE).toUInt());
    specimen.weld.type  = specimen.weldType;

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " shape " << specimen.shape
             << " logitudinalVelocity " << specimen.LV
             << " shearVelocity " << specimen.SV
             << " material " << specimen.material
             << " density " << specimen.density
             << " weldType " << specimen.weldType;

    unpack_geometry(map.value("Geometry").toMap());

    unpack_weld(map.value("Weld").toMap());
}

void Config::unpack_geometry(const QVariantMap &map)
{
    if(PLANE == m_currentGroup.specimen.shape) {
        unpack_geometry_plane(map);
    } else if(CYLINDER == m_currentGroup.specimen.shape) {
        unpack_geometry_cylinder(map, m_currentGroup.specimen.geometry.cylinder);
    } else if(NOZZLE == m_currentGroup.specimen.shape) {
        unpack_geometry_nozzle(map);
    } else {
        qWarning("%s(%s[%d]): unimplement", __FILE__, __func__, __LINE__);
    }
}

void Config::unpack_geometry_plane(const QVariantMap &map)
{
    S_Plane &plane = m_currentGroup.specimen.geometry.plane;
    plane.height = map.value("Height", DEFAULT_PLANE_HEIGHT).toDouble();
    plane.length = map.value("Height", DEFAULT_PLANE_LENGTH).toDouble();
    plane.width  = map.value("Height", DEFAULT_PLANE_WIDTH).toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " height " << plane.height
             << " length " << plane.length
             << " width " << plane.width;
}

void Config::unpack_geometry_cylinder(const QVariantMap &map, S_Cylinder &cylinder)
{
    cylinder.probePos = static_cast<ProbePosition> (map.value("ProbePos",
                                                               DEFAULT_CYLINDER_PROBE_POS).toUInt());
    cylinder.inside  = map.value("Inside", DEFAULT_CYLINDER_INSIDE).toDouble();
    cylinder.outside = map.value("Outside", DEFAULT_CYLINDER_OUTSIDE).toDouble();
    cylinder.angle   = map.value("Angle", DEFAULT_CYLINDER_ANGLE).toDouble();
    cylinder.length  = map.value("Length", DEFAULT_CYLINDER_LENGHT).toDouble();
    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " probePos " << cylinder.probePos
             << " inside " << cylinder.inside
             << " outside " << cylinder.outside
             << " angle " << cylinder.angle
             << " length " << cylinder.length;
}

void Config::unpack_geometry_nozzle(const QVariantMap &map)
{
    S_Nozzle &nozzle = m_currentGroup.specimen.geometry.nozzle;
    nozzle.inside  = map.value("Inside", DEFAULT_NOZZLE_INSIDE).toDouble();
    nozzle.outside = map.value("Outside", DEFAULT_NOZZLE_OUTSIDE).toDouble();
    nozzle.angle   = map.value("Angle", DEFAULT_NOZZLE_ANGLE).toDouble();

    unpack_geometry_cylinder(map.value("Cylinder1").toMap(), nozzle.cylinder1);
    unpack_geometry_cylinder(map.value("Cylinder2").toMap(), nozzle.cylinder2);
}

void Config::unpack_weld(const QVariantMap &map)
{
    S_Weld &weld = m_currentGroup.specimen.weld;

    if(m_currentGroup.specimen.weldType == NONE_TYPE) {
        return;
    }

    weld.orientation = static_cast<WeldOrientation> (value("Orientation", DEFAULT_WELD_ORIENTATION).toUInt());
    weld.isSymmetry  = value("Symmetry", DEFAULT_WELD_SYMMETRY).toBool();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " orientation " << weld.orientation
             << " symmetry " << weld.isSymmetry;

    if(I == weld.type) {
        unpack_I_weld(map.value("I").toMap(), weld.I);
    } else if(V == weld.type) {
        unpack_I_weld(map.value("I").toMap(), weld.I);
        unpack_V_weld(map.value("V").toMap(), weld.V);
    } else if(U == weld.type) {
        unpack_I_weld(map.value("I").toMap(), weld.I);
        unpack_U_weld(map.value("U").toMap(), weld.U);
    }else if(VY == weld.type) {
        unpack_I_weld(map.value("BtmI").toMap(), weld.BtmI);
        unpack_V_weld(map.value("MidV").toMap(), weld.MidV);
        unpack_V_weld(map.value("TopV").toMap(), weld.TopV);
    } else if(VV == weld.type) {
        unpack_V_weld(map.value("BtmV").toMap(), weld.BtmV);
        unpack_I_weld(map.value("MidI").toMap(), weld.MidI);
        unpack_V_weld(map.value("TopV").toMap(), weld.TopV);
    } else if(UU == weld.type) {
        unpack_U_weld(map.value("BtmU").toMap(), weld.BtmU);
        unpack_I_weld(map.value("MidI").toMap(), weld.MidI);
        unpack_U_weld(map.value("TopU").toMap(), weld.TopU);
    } else if(UV == weld.type) {
        unpack_U_weld(map.value("U").toMap(), weld.U);
        unpack_I_weld(map.value("I").toMap(), weld.I);
        unpack_V_weld(map.value("V").toMap(), weld.V);
    } else {
        qWarning("%s(%s[%d]): unimplement", __FILE__, __func__, __LINE__);
    }
}

void Config::unpack_I_weld(const QVariantMap &map, S_WeldI &I)
{
    I.width       = map.value("W").toDouble();
    I.orientation = static_cast<WeldOrientation> (map.value("Orientation").toUInt());
    I.symmetry    = map.value("Symmetry").toBool();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " width " << I.width
             << " orientation " << I.orientation
             << " symmetry " << I.symmetry;
}

void Config::unpack_V_weld(const QVariantMap &map, S_WeldV &V)
{
    V.width       = map.value("W").toDouble();
    V.orientation = static_cast<WeldOrientation> (map.value("Orientation").toUInt());
    V.symmetry    = map.value("Symmetry").toBool();
    V.height      = map.value("H").toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " width " << V.width
             << " orientation " << V.orientation
             << " symmetry " << V.symmetry
             << " height " << V.height;
}

void Config::unpack_U_weld(const QVariantMap &map, S_WeldU &U)
{
    U.width       = map.value("W").toDouble();
    U.orientation = static_cast<WeldOrientation> (map.value("Orientation").toUInt());
    U.symmetry    = map.value("Symmetry").toBool();
    U.height      = map.value("H").toDouble();
    U.radius      = map.value("R").toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " width " << U.width
             << " orientation " << U.orientation
             << " symmetry " << U.symmetry
             << " height " << U.height
             << " radius " << U.radius;
}

void Config::unpack_focus(const QVariantMap &map)
{
    S_Focus &focus = m_currentGroup.focallawer.focus;

    focus.radius      = map.value("Radius", DEFAULT_END_OFFSET).toDouble();
    focus.depth       = map.value("Depth", DEFAULT_END_OFFSET).toDouble();
    focus.offset      = map.value("Offset", DEFAULT_END_OFFSET).toDouble();
    focus.beginOffset = map.value("BeginOffset", DEFAULT_BEGIN_OFFSET).toDouble();
    focus.endOffset   = map.value("EndOffset", DEFAULT_END_OFFSET).toDouble();
    focus.beginDepth  = map.value("BeginDepth", DEFAULT_BEGIN_OFFSET).toDouble();
    focus.endDepth    = map.value("EndDepth", DEFAULT_END_OFFSET).toDouble();
    focus.focusMode   = m_currentGroup.focallawer.focusMode;

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " radius " << focus.radius
             << " depth " << focus.depth
             << " offset " << focus.offset
             << " beginOffset " << focus.beginOffset
             << " endOffset " << focus.endOffset
             << " beginDepth " << focus.beginDepth
             << " endDepth " << focus.endDepth;
}

void Config::unpack_beams_info()
{
    memset(&m_currentGroup.focallawer.beamsInfo, 0, sizeof(S_BeamsInfo));

//    S_BeamsInfo &beamsInfo = m_currentGroup.focallawer.beamsInfo;
//    QVariantMap tmp = map["Delay"].toMap();
//    if(tmp.count() <= setup_MAX_GROUP_LAW_QTY) {
//        for(int i = 0; i < tmp.count(); ++i) {
//            beamsInfo.delay[i] = tmp[QString::number(i)].toFloat();
//            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//                     << " delay " << beamsInfo.delay[i];
//        }
//    }

//    tmp.clear();
//    tmp = map["FieldDistance"].toMap();
//    if(tmp.count() <= setup_MAX_GROUP_LAW_QTY) {
//        for(int i = 0; i < tmp.count(); ++i) {
//            beamsInfo.fieldDistance[i] = tmp[QString::number(i)].toFloat();
//            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//                     << " fieldDistance " << beamsInfo.fieldDistance[i];
//        }
//    }
}

void Config::unpack_thickness()
{
//    m_currentGroup.thickness.min = map["Min"].toDouble();
//    m_currentGroup.thickness.max = map["Max"].toDouble();
//    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//             << " thickness min " << m_currentGroup.thickness.min
    //             << " thickness max " << m_currentGroup.thickness.max;
}

void Config::unpack_cursor(const QVariantMap &map)
{
    S_Cursor &cursor = m_currentGroup.cursor;

    cursor.ampMeas  = map.value("AmpMeas", DEFAULT_MEAS).toDouble();
    cursor.ampRef   = map.value("AmpRef", DEFAULT_REF).toDouble();
    cursor.depthMeas= map.value("DepthMeas", DEFAULT_MEAS).toDouble();
    cursor.depthRef = map.value("DepthRef", DEFAULT_REF).toDouble();
    cursor.indexMeas= map.value("IndexMeas", DEFAULT_MEAS).toDouble();
    cursor.indexRef = map.value("IndexRef", DEFAULT_REF).toDouble();
    cursor.scanMeas = map.value("ScanMeas", DEFAULT_MEAS).toDouble();
    cursor.scanRef  = map.value("ScanRef", DEFAULT_REF).toDouble();
    cursor.ultraMeas= map.value("UltraMeas", DEFAULT_MEAS).toDouble();
    cursor.ultraRef = map.value("UltraRef", DEFAULT_REF).toDouble();
    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " ampMeas " << cursor.ampMeas
             << " ampRef " << cursor.ampRef
             << " depthMeas " << cursor.depthMeas
             << " depthRef " << cursor.depthRef
             << " indexMeas " << cursor.indexMeas
             << " indexRef " << cursor.indexRef
             << " scanMeas " << cursor.scanMeas
             << " scanRef " << cursor.scanRef
             << " ultraMeas " << cursor.ultraMeas
             << " ultraRef " << cursor.ultraRef;
}

void Config::unpack_gate(const QVariantMap &map, S_Gate &gate)
{
    gate.measureMode = static_cast<MeasureMode> (map["MeasureMode"].toUInt());
    gate.gateMode    = static_cast<GateMode> (map["Mode"].toUInt());
    gate.synchroMode = static_cast<SynchroMode> (map["SynchroMode"].toUInt());
    gate.visible     = map["Visible"].toBool();
    gate.start       = map["Start"].toDouble();
    gate.width       = map["Width"].toDouble();;
    gate.height      = map["Height"].toUInt();
//    gate.color       = map["Color"].toUInt();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " measureMode " << gate.measureMode
             << " gateMode " << gate.gateMode
             << " synchroMode " << gate.synchroMode
             << " visible " << gate.visible
             << " start " << gate.start
             << " width " << gate.width
             << " height " << gate.height
             << " color " << gate.color;
}

void Config::unpack_curves()
{
    memset(&m_currentGroup.curves, 0, sizeof(m_currentGroup.curves));

//    curves.type = static_cast<SizingType> (map["Type"].toInt());
//    if(SizingNONE == curves.type) {
//        return;
//    }

//    curves.compliance = static_cast<Compliance>(map["Compliance"].toInt());
//    curves.gain       = map["Gain"].toDouble();
//    curves.refAmplitude = map["RefAmplitude"].toDouble();
//    curves.curveQty = map["CurveQty"].toInt();
//    curves.currentCurve = map["CurrentCurve"].toInt();

//    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//             << " compliance " << curves.compliance
//             << " gain " << curves.gain
//             << " refAmplitude " << curves.refAmplitude
//             << " curveQty " << curves.curveQty
//             << " currentCurve " << curves.currentCurve;

//    unpack_curve_offset(map["CurveOffset"].toMap(), curves);

//    if(DAC == curves.type) {
//        unpack_dac(map["DAC"].toMap(), curves);
//    } else if(LINEAR_DAC == curves.type) {
//        unpack_linear_dac(map["LINEAR_DAC"].toMap(), curves);
//    } else if(TCG == curves.type) {
//        unpack_tcg(map["TCG"].toMap(), curves);
//    }
}

void Config::unpack_dac()
{
//    S_DAC &dac = curves.dac;

//    dac.curveType       = static_cast<CurveType> (map["CurveType"].toInt());
//    dac.pointCount      = map["PointCount"].toInt();
//    dac.currentPoint    = map["CurrentPoint"].toInt();
//    dac.currentBeamIndex= map["CurrentBeamIndex"].toInt();

//    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//             << " curveType " << dac.curveType
//             << " pointCount " << dac.pointCount
//             << " currentPoint " << dac.currentPoint
//             << " currentBeamIndex " << dac.currentBeamIndex;

//    QVariantMap positionMap = map["Position"].toMap();
//    QVariantMap amplitudeMap = map["Amplitude"].toMap();
//    if(positionMap.size() <= setup_DAC_POINT_QTY) {
//        for(int i = 0; i < positionMap.count(); ++i) {
//            dac.position[i] = positionMap[QString::number(i)].toDouble();
//            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//                     << " i " << i
//                     << " position " << dac.position[i];
//        }
//    }

//    if(amplitudeMap.size() <= setup_DAC_POINT_QTY) {
//        for(int i = 0; i < amplitudeMap.count(); ++i) {
//            dac.amplitude[i] = amplitudeMap[QString::number(i)].toDouble();
//            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//                     << " i " << i
//                     << " amplitude " << dac.position[i];
//        }
//    }
}

void Config::unpack_linear_dac()
{
//    curves.linearDAC.matAttenuation = map["MatAttenuation"].toDouble();
//    curves.linearDAC.delay          = map["Delay"].toDouble();

//    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//             << " matAttenuation " << curves.linearDAC.matAttenuation
//             << " delay " << curves.linearDAC.delay;
}

void Config::unpack_tcg()
{
//    S_TCG &tcg = curves.tcg;

//    tcg.pointCount        = map["PointCount"].toInt();
//    tcg.currentPointIndex = map["CurrentPointIndex"].toInt();
//    tcg.currentBeamIndex  = map["CurrentBeamIndex"].toInt();

//    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//             << " pointCount " << tcg.pointCount
//             << " currentPointIndex " << tcg.currentPointIndex
//             << " currentBeamIndex " << tcg.currentBeamIndex;

//    QVariantMap positionMap = map["Position"].toMap();
//    QVariantMap gainMap = map["GainMap"].toMap();

//    if(positionMap.count() <= setup_DAC_POINT_QTY) {
//        for(int i = 0; i < positionMap.count(); ++i) {
//            tcg.position[i] = positionMap[QString::number(i)].toDouble();
//            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//                     << " i " << i
//                     << " position " << tcg.position[i];
//        }
//    }

//    if(gainMap.count() <= setup_DAC_POINT_QTY) {
//        for(int i = 0; i < gainMap.count(); ++i) {
//            tcg.gain[i] = gainMap[QString::number(i)].toDouble();
//            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//                     << " i " << i
//                     << " gain " << tcg.gain[i];
//        }
//    }
}

void Config::unpack_curve_offset()
{
//    if(map.count() <= setup_DAC_POINT_QTY) {
//        for(int i = 0; i < map.count(); ++i) {
//            curves.curveOffset.offset[i] = map[QString::number(i)].toDouble();
//            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//                     << " i " << i << " offset " << curves.curveOffset.offset[i];
//        }
//    }
}

void Config::unpack_scanner()
{
    QVariantMap map = value("Scanner").toMap();

    unpack_axis(map["IndexAxis"].toMap(), m_global.scanner.indexAxis);

    unpack_axis(map["ScanAxis"].toMap(), m_global.scanner.scanAxis);

    unpack_encoder(map["Encoder0"].toMap(), m_global.scanner.encoderX);

    unpack_encoder(map["Encoder1"].toMap(), m_global.scanner.encoderY);

    m_global.scanner.scanType = static_cast<ScanType> (map["Mode"].toUInt());
    m_global.scanner.rate     = map["Rate"].toUInt();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " scanType " << m_global.scanner.scanType
             << " rate " << m_global.scanner.rate;
}

void Config::unpack_axis(const QVariantMap &map, S_Axis &axis)
{
    axis.driving    = static_cast<Driving>(map["Driving"].toUInt());
    axis.start      = map["Start"].toDouble();
    axis.end        = map["End"].toDouble();
    axis.resolution = map["Resolution"].toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " driving " << axis.driving
             << " start " << axis.start
             << " end " << axis.end
             << " resolution " << axis.resolution;
}

void Config::unpack_encoder(const QVariantMap &map,S_Encoder &encoder)
{
    encoder.status      = static_cast<EncoderStatus> (map["Status"].toUInt());
    encoder.polarity    = static_cast<Polarity> (map["Polarity"].toUInt());
    encoder.mode        = static_cast<EncoderMode> (map["Mode"].toUInt());
    encoder.resolution  = map["Resolution"].toDouble();
    encoder.origin      = map["Origin"].toDouble();;

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " status " << encoder.status
             << " polarity " << encoder.polarity
             << " mode " << encoder.mode
             << " resolution " << encoder.resolution
             << " origin " << encoder.origin;
}

void Config::unpack_global()
{
//    unpack_global_transceiver(map["Transceiver"].toMap());
//    unpack_alarm(map["Alarm"].toMap());
}

void Config::unpack_global_transceiver()
{
    S_GlobalTransceiver &transceiver = m_global.transceiver;
    QVariantMap map = value("GlobalTransceiver").toMap();

    transceiver.paVoltage      = static_cast<Voltage> (map["PaVoltage"].toUInt());
    transceiver.ut1TxDamping   = static_cast<Damping> (map["Ut1TxDamping"].toUInt());
    transceiver.ut2TxDamping   = static_cast<Damping> (map["Ut2TxDamping"].toUInt());
    transceiver.utVoltage      = static_cast<Voltage> (map["UtVoltage"].toUInt());

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " PA Voltage " << transceiver.paVoltage
             << " UT Voltage " << transceiver.utVoltage
             << " ut1TxDamping " << transceiver.ut1TxDamping
             << " ut2TxDamping " << transceiver.ut2TxDamping;
}

void Config::unpack_alarm()
{
//    for(int i = 0; i < s_alarmCount; ++i) {
//        unpack_one_alarm_setting(i, map[QString::number(i)].toMap());
//    }

//    m_global.sound = static_cast<SoundMode> (map["Sound"].toInt());
}

void Config::unpack_one_alarm_setting(int index)
{
//    S_Alarm &alarm = m_global.alarm[index];
//    alarm.enable = map["Enable"].toBool();
//    if(!alarm.enable){
//        return;
//    }

//    alarm.logicGroup     = static_cast<quint16> (map["Group"].toUInt());
//    alarm.firstCondition = static_cast<Condition> (map["FirstCondition"].toInt());
//    alarm.secondCondition= static_cast<Condition> (map["SecondCondition"].toInt());
//    alarm.opt            = static_cast<Operator> (map["Operator"].toInt());
//    alarm.count          = map["Count"].toUInt();
//    alarm.delay          = map["Delay"].toInt();
//    alarm.holdTime       = map["HoldTime"].toInt();
}

int Config::set_bit_value(int val, int bit, int val1)
{
    Q_ASSERT(bit < 32);
    Q_ASSERT(bit >= 0);
    return ((val & ~(0x1 << bit)) | (val1 << bit));
}

int Config::get_bit_value(int val, int bit)
{
    Q_ASSERT(bit < 32);
    Q_ASSERT(bit >= 0);
    return ((val & (0x01 << bit)) != 0);
}

void Config::convert_to_phascan_config(int groupId)
{
    if(groupId < 0 || groupId >= setup_MAX_GROUP_QTY) {
        return;
    }

    S_Groups &currentGroup = m_groups[groupId];
    S_Probe &currentProbe = currentGroup.probe;
    S_Wedge &currentWedge = currentGroup.wedge;
    S_Focus &currentFocus = currentGroup.focallawer.focus;
    S_Scan &currentScan= currentGroup.focallawer.scan;
    S_Specimen &currentSpecimen = currentGroup.specimen;

    GROUP_INFO &targetGroup = m_pDataFile->m_cGroupInfo[groupId];
    LAW_INFO &targetLawInfo = targetGroup.law_info;
    WEDGE &targetWedge = targetGroup.wedge;
    PROBE &targetProbe = targetGroup.probe;

    targetGroup.group_mode  = currentGroup.mode;
    targetGroup.ut_unit     = currentGroup.utUnit;

    /* Sample */
    targetGroup.gain          = currentGroup.sample.gain * 100.0;
    targetGroup.start         = currentGroup.sample.start;
    targetGroup.range         = currentGroup.sample.range;
    targetGroup.on_off_status = set_bit_value(targetGroup.on_off_status, 0, currentGroup.sample.refGainStatus);
    if(get_bit_value(targetGroup.on_off_status, 0)) {
        targetGroup.gainr = currentGroup.sample.refGain;
    }
    targetGroup.point_qty     = currentGroup.sample.pointQty;

    /* Transceiver */
    targetGroup.tx_rxmode1    = currentGroup.transceiver.txRxMode;
    targetGroup.pulser_width1 = currentGroup.transceiver.pw;
    targetGroup.filter_pos1   = currentGroup.transceiver.filter;
    targetGroup.rectifier1    = currentGroup.transceiver.rectifier;
    targetGroup.on_off_status = set_bit_value(targetGroup.on_off_status, 1, currentGroup.transceiver.videoFilter);
    targetGroup.averaging1    = currentGroup.transceiver.average;

    /* Probe */
    memset(targetProbe.Serial, 0, 20);
    memset(targetProbe.Model, 0, 20);

    strncpy(targetProbe.Serial,
            currentProbe.serial.toLocal8Bit().data(),
            currentProbe.serial.toLocal8Bit().size());
    strncpy(targetProbe.Model,
            currentProbe.model.toLocal8Bit().data(),
            currentProbe.model.toLocal8Bit().size());
    targetProbe.Frequency = currentProbe.freq * 1000.0;
    targetProbe.Pitch     = 0; /* TODO：UT模式，也需要用到Pitch？ */
    targetProbe.Reference_Point = 0; /* TODO: */

    targetGroup.scan_offset  = currentProbe.scanOffset * 1000.0;
    targetGroup.index_offset = currentProbe.indexOffset * 1000.0;
    if(0 == currentProbe.skew) {
        targetGroup.skew_pos = 0;
    } else if(90 == currentProbe.skew) {
        targetGroup.skew_pos = 1;
    } else if(180 == currentProbe.skew) {
        targetGroup.skew_pos = 2;
    } else if(270 == currentProbe.skew) {
        targetGroup.skew_pos = 3;
    }

    if (currentGroup.mode == PA) {
        targetProbe.Elem_qty  = currentProbe.priElemQty;
        targetProbe.Pitch     = currentProbe.priPitch * 1000.0;

        /* PA Scan */
        targetLawInfo.Focal_type      = !currentGroup.focallawer.scanMode;
        targetLawInfo.Elem_qty        = currentScan.priApe;
        targetLawInfo.First_tx_elem   = currentScan.priStartElem;

        /* 二代：0：Linear；1：Sectorial 故在赋值Focal_type时候取反
         * 一代：1：Linear；0：Sectorial         */
        if(Linear == currentGroup.focallawer.scanMode) {
            /* Linear */
            targetLawInfo.Last_tx_elem = currentScan.priStopElem;
            targetLawInfo.Elem_step    = currentScan.priElemStep;
            targetLawInfo.Angle_min    = currentScan.refractAngle;

            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << " LLLLLLLLLLL "
                     << " Last_tx_elem " << targetLawInfo.Last_tx_elem
                     << " Elem_step " << targetLawInfo.Elem_step
                     << " first elem " << targetLawInfo.First_tx_elem
                     << " Angle_min " << targetLawInfo.Angle_min;

        } else if(Sectorial == currentGroup.focallawer.scanMode) {
            /* Azimuthal */
            targetLawInfo.Angle_min   = currentScan.refractStartAngle * 100.0;
            targetLawInfo.Angle_max   = currentScan.refractStopAngle * 100.0;
            targetLawInfo.Angle_step  = currentScan.refractStepAngle * 100.0;

            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << " AAAAAAAAAAA "
                     << " min " << targetLawInfo.Angle_min
                     << " max " << targetLawInfo.Angle_max
                     << " step " << targetLawInfo.Angle_step;
        } else {
            qWarning("%s(%s[%d]): unimplement", __FILE__, __func__, __LINE__);
        }
    }

    /* Wedge */
    memset(targetWedge.Serial, 0, 20);
    memset(targetWedge.Model, 0, 20);

    strncpy(targetWedge.Serial,
            currentWedge.serial.toLocal8Bit().data(),
            currentWedge.serial.toLocal8Bit().size());
    strncpy(targetWedge.Model,
            currentWedge.model.toLocal8Bit().data(),
            currentWedge.model.toLocal8Bit().size());
    targetWedge.Angle             = currentWedge.angle * 10.0;
    /* TODO:
         * 一代默认rootAngle = 0；
         * 二代：rootAngle涉及到成像、聚焦法则？ */
    targetWedge.Velocity_PA       = currentWedge.velocity * 1000.0;
    targetWedge.Velocity_UT       = currentWedge.velocity * 1000.0;
    targetWedge.Primary_offset    = currentWedge.priOffset * 1000.0;
    targetWedge.Secondary_offset  = currentWedge.secOffset * 1000.0;
    targetWedge.Height            = currentWedge.fstElemHeight * 1000.0;
    targetWedge.Orientation       = currentWedge.orientation;
    targetWedge.Wave_type         = currentWedge.waveType;
    targetWedge.Ref_point         = currentWedge.refPoint;
    targetWedge.Probe_delay       = currentWedge.delay;

    /* Specimen */
    targetGroup.part.Geometry     = currentSpecimen.shape;
    targetGroup.part.Material_pos = currentSpecimen.material;

    if(currentSpecimen.weldType != NONE_TYPE) {
        targetGroup.part.symmetry = currentSpecimen.weld.isSymmetry;
        /* TODO: fill weld info */
    }

    /* TODO */
    if(PLANE == currentSpecimen.shape) {
        targetGroup.part.Thickness    = currentSpecimen.geometry.plane.height * 1000.0;
    } else if(CYLINDER == currentSpecimen.shape) {

    }

    if(Longitudinal == currentGroup.focallawer.waveType) {
         targetGroup.velocity = currentSpecimen.LV * 100.0;
    } else if(Shear == currentGroup.focallawer.waveType){
        targetGroup.velocity = currentSpecimen.SV * 100.0;
    }

    /* Focus */
    targetLawInfo.Focal_point_type = currentFocus.focusMode;
    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " focus Mode " << currentFocus.focusMode;

    if (HALF_PATH == currentFocus.focusMode) {
        targetLawInfo.Position_start = currentFocus.radius * 1000.0;
    } else if (TRUE_DEPTH == currentFocus.focusMode) {
        targetLawInfo.Position_start = currentFocus.depth * 1000.0;
    } else if (PROJECTION == currentFocus.focusMode) {
        targetLawInfo.Offset_start = currentFocus.offset * 1000.0;
    } else if (FOCAL_PLANE == currentFocus.focusMode) {
        targetLawInfo.Offset_start = currentFocus.beginOffset * 1000.0;
        targetLawInfo.Offset_end   = currentFocus.endOffset * 1000.0;
        targetLawInfo.Depth_start  = currentFocus.beginDepth * 1000.0;
        targetLawInfo.Depth_end    = currentFocus.endDepth * 1000.0;
    } else if (DDF == currentFocus.focusMode) {
        qWarning("%s(%s[%d]): DDF unimplement", __FILE__, __func__, __LINE__);
    } else {
        qWarning("%s(%s[%d]): unimplement", __FILE__, __func__, __LINE__);
    }

    /* BeamsInfo */
    for(int i = 0; i < setup_MAX_GROUP_LAW_QTY; i++) {
        targetGroup.beam_delay[i]     = currentGroup.focallawer.beamsInfo.delay[i];
        targetGroup.field_distance[i] = currentGroup.focallawer.beamsInfo.fieldDistance[i];
    }

    /* Thickness */
    targetGroup.min_thickness = currentGroup.thickness.min * 1000.0;
    targetGroup.max_thickness = currentGroup.thickness.max * 1000.0;

    /* Gate */
    targetGroup.gate[0].start   = currentGroup.gateA.start;
    targetGroup.gate[0].width   = currentGroup.gateA.width;
    targetGroup.gate[0].height  = currentGroup.gateA.height;
    targetGroup.gate[0].measure = !currentGroup.gateA.measureMode;
    targetGroup.gate[0].synchro = currentGroup.gateA.synchroMode;

    targetGroup.gate[1].start   = currentGroup.gateA.start;
    targetGroup.gate[1].width   = currentGroup.gateA.width;
    targetGroup.gate[1].height  = currentGroup.gateA.height;
    targetGroup.gate[1].measure = !currentGroup.gateA.measureMode;
    targetGroup.gate[1].synchro = currentGroup.gateA.synchroMode;

    targetGroup.gate[2].start   = currentGroup.gateA.start;
    targetGroup.gate[2].width   = currentGroup.gateA.width;
    targetGroup.gate[2].height  = currentGroup.gateA.height;
    targetGroup.gate[2].measure = !currentGroup.gateA.measureMode;
    targetGroup.gate[2].synchro = currentGroup.gateA.synchroMode;

    S_Curves &currentCurves = currentGroup.curves;
    SIZING_CURVES &targetCurves = targetGroup.SizingCurves;

    targetCurves.bApplyToAllLaws = true;
//    targetCurves.bTcgCalibrated = true;

    if(DAC == currentCurves.type) {
        targetCurves.point_pos      = currentCurves.dac.currentPoint;
        targetCurves.dac_point_qty  = currentCurves.dac.pointCount;
    } else if(LINEAR_DAC == currentCurves.type
              || SizingNONE == currentCurves.type) {
        targetCurves.point_pos = 0;
    } else if(TCG == currentCurves.type) {
        targetCurves.point_pos      = currentCurves.tcg.currentPointIndex;
        targetCurves.dac_point_qty  = currentCurves.tcg.pointCount;
    }

    targetCurves.curve_pos      = currentCurves.type;
    targetCurves.curve_step     = 0;
    targetCurves.ref_ampl_offset= 0;
    targetCurves.linear_ref_ampl= currentCurves.refAmplitude * 1000.0;
    targetCurves.mat_atten      = currentCurves.linearDAC.matAttenuation * 1000.0;
    targetCurves.delay          = currentCurves.linearDAC.delay;


    for(int i = 0; i < setup_DAC_POINT_QTY; ++i) {
        targetCurves.linearamplitude[i] = currentCurves.dac.amplitude[i];
        targetCurves.linearposition[i] = currentCurves.dac.position[i];
    }

    if(TCG == currentCurves.type) {
        /* TCG */
        for(int i = 0; i < setup_MAX_GROUP_LAW_QTY; ++i) {
            targetCurves.dac_ref_ampl[i] = currentCurves.refAmplitude * 10.0;
            for(int j = 0; j < setup_DAC_POINT_QTY; ++j) {
                targetCurves.amplitude[i][j] = currentCurves.refAmplitude * 1000.0
                                                / pow(10.0 , currentCurves.tcg.gain[j] * 100.0 / 2000.0);
                targetCurves.position[i][j]  = currentCurves.tcg.position[j];
            }
        }
    } else if(DAC == currentCurves.type) {
        /* DAC */
        for(int i = 0; i < setup_MAX_GROUP_LAW_QTY; ++i) {
            targetCurves.dac_ref_ampl[i] = currentCurves.refAmplitude * 10.0;
            for(int j = 0; j < setup_DAC_POINT_QTY; ++j) {
                targetCurves.amplitude[i][j] = currentCurves.dac.amplitude[j] * 1000.0;
                targetCurves.position[i][j]  = currentCurves.dac.position[j];
            }
        }
    }
    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << "";
}

void Config::convert_other_to_phascan_config()
{
    DRAW_INFO_PACK &drawInfoPack = m_pDataFile->m_cDrawInfoPack;
    drawInfoPack.nGroupNum = m_global.groupQty;

    /* Scanner */
    drawInfoPack.nScanStart = m_global.scanner.scanAxis.start * 1000.0;
    drawInfoPack.nScanEnd = m_global.scanner.scanAxis.end * 1000.0;
    drawInfoPack.nScanResolution = m_global.scanner.scanAxis.resolution * 1000.0;

    if(ENCODER_X == m_global.scanner.scanAxis.driving) {
        drawInfoPack.nInspecResolution = m_global.scanner.encoderX.origin;
        drawInfoPack.nEncodeType = 1;
    } else if(ENCODER_Y == m_global.scanner.scanAxis.driving) {
        drawInfoPack.nInspecResolution = m_global.scanner.encoderY.origin;
        drawInfoPack.nEncodeType = 1;
    } else if(TIMER == m_global.scanner.scanAxis.driving){
        drawInfoPack.nEncodeType = 0;
    } else {
        qWarning("%s(%s[%d]): unimplement other driving.", __FILE__, __func__, __LINE__);
    }

    /* Global */
    for(int i = 0; i < m_pDataFile->m_cDrawInfoPack.nGroupNum; ++i) {
        m_pDataFile->m_cGroupInfo[i].prf1 = m_global.scanner.rate * 10;
    }  
}

bool Config::is_phascan_ii_file(QFile &file)
{
    qint64 totalSize = file.size();
    qint64 configLen = 0;
    qint64 dataMarkLen = 0;
    qint64 beamDataLen = 0;

    file.read((char *)&configLen, sizeof(configLen));
    if (configLen <= 0 || configLen > totalSize) {
        qWarning("%s(%s[%d]): configLen is ERROR.", __FILE__, __func__, __LINE__);
        return false;
    }

    if(!file.seek(sizeof(configLen) + configLen)) {
        qWarning("%s(%s[%d]): seek faile.", __FILE__, __func__, __LINE__);
        return false;
    }

    if(file.atEnd()) {
        /* phascan config file */
        qWarning("%s(%s[%d]): is phascan config file.", __FILE__, __func__, __LINE__);
        return true;
    }

    file.read((char *)&dataMarkLen, sizeof(dataMarkLen));
    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " dataMakeLen " << dataMarkLen;
    if (dataMarkLen <= 0 || dataMarkLen > totalSize) {
        qWarning("%s(%s[%d]): dataMarkLen is ERROR.", __FILE__, __func__, __LINE__);
        return false;
    }

    if(!file.seek(sizeof(configLen) + configLen + sizeof(dataMarkLen) + dataMarkLen)) {
        qWarning("%s(%s[%d]): seek faile.", __FILE__, __func__, __LINE__);
        return false;
    }

    file.read((char *)&beamDataLen, sizeof(beamDataLen));
    if (beamDataLen <= 0 || beamDataLen > totalSize) {
        qWarning("%s(%s[%d]): beamDataLen is ERROR.", __FILE__, __func__, __LINE__);
        return false;
    }

    qint64 totalLen = configLen + dataMarkLen + beamDataLen + sizeof(quint64) * 3;

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " configlen " << configLen
             << " sizof() * 3 " << (sizeof(quint64) * 3)
             << " dataMakeLen " << dataMarkLen
             << " beamDataLen " << beamDataLen
             << " totalLen " << totalLen
             << " framesize " << beamDataLen / dataMarkLen;

    if(totalLen != totalSize) {
        qWarning("%s(%s[%d]): cal Len is not equal totalSzie.", __FILE__, __func__, __LINE__);
        return false;
    }

    file.seek(0);
    return true;
}

void Config::print_all_key(int depth, const QVariantMap &map)
{
    int count = depth + 1;
    QString tag;
    for(int i = 0; i < count; ++i) {
        tag += QString(" =");
    }

    if(map.count()) {
        QList<QString> keys = map.keys();
        for(int i = 0; i < keys.count(); ++i) {
            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                     << tag
                     << " key " << keys.at(i)
                     << " value " << map.value(keys.at(i));
            print_all_key(count, map.value(keys.at(i)).toMap());
        }
    }
}

void Config::set_is_phascan_ii(bool flag)
{
    m_isPhascanII = flag;
}

bool Config::is_phascan_ii()
{
    return m_isPhascanII;
}
