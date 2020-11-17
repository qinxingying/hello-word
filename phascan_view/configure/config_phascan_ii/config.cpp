#include "config.h"
#include "msgpack/msgpack.h"
#include <QDebug>
#include <QList>
#include <QDataStream>
#include "../DopplerDataFileOperateor.h"
#include "mercury_paramters/group_paramters.h"

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

    m_global.m_groupQty = dst.value("GroupQty").toUInt();
    m_global.m_prfMode = static_cast<Paramters::Global::PrfMode> (dst.value("PrfMode").toUInt());

    unpack_version();
    unpack_display();
    unpack_scanner();
    unpack_global_transceiver();

    convert_other_to_phascan_config();

    for(uint i = 0; i < m_global.m_groupQty; ++i) {
        unpack_group(i);
        convert_to_phascan_config(i);
    }

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
    if(m_global.m_scanner.m_scanAxis.m_driving == Paramters::Axis::TIMER){
        m_pDataFile->m_cDrawInfoPack.nScanEnd = m_pDataFile->m_cDrawInfoPack.nScanStart +
                                                len*1000.0;
    }

    /* 不拷贝到bScanMark，直接拷贝m_dataMark到common.nRecMark */
//    memset(m_pDataFile->m_cDrawInfoPack.bScanMark, 0, sizeof(unsigned char) * 1024 * 256);
//    memcpy(m_pDataFile->m_cDrawInfoPack.bScanMark, m_dataMark.data(), len);

    file.read((char *)&len, sizeof(len));
    m_dataSource.clear();
    m_dataSource.resize(len);
    if (len <= 0 || len != file.read(m_dataSource.data(), len) ) {
        qWarning("%s(%s[%d]): Read Data(%d) failed", __FILE__, __func__, __LINE__, len);
        set_is_phascan_ii(false);
        return false;
    }

    m_pDataFile->m_pBeamData = (unsigned char *)m_dataSource.data();
    m_pDataFile->m_mapdataSize = len;

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << " Read Phascan II Data Success!!";
    set_is_phascan_ii(true);
    return true;
}

Config::Config(QObject *parent)
    : QSettings(parent),
      m_pDataFile(NULL),
      s_alarmCount(ALARM_COUNT),
      m_isPhascanII(false),
      m_currentGroupID(0)
{
}

void Config::unpack_group(int groupId)
{
    m_currentGroupID = groupId;
    QVariantMap map = value(QString("Group%1").arg(groupId)).toMap();

    m_groups[m_currentGroupID].m_mode         = static_cast<Paramters::Group::GroupMode> (map["Mode"].toUInt());
    m_groups[m_currentGroupID].m_utUnit       = static_cast<Paramters::Group::UtUnit> (map["UtUnit"].toUInt());
    m_groups[m_currentGroupID].m_highestTrack = map["HighestTrack"].toBool();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " mode " << m_groups[m_currentGroupID].m_mode
             << " ut unit " << m_groups[m_currentGroupID].m_utUnit
             << " highestTrack " << m_groups[m_currentGroupID].m_highestTrack;

    unpack_focallawer(map["Focallawer"].toMap());
    unpack_gate(map["GateA"].toMap(), m_groups[m_currentGroupID].m_gateA);
    unpack_gate(map["GateB"].toMap(), m_groups[m_currentGroupID].m_gateB);
    unpack_gate(map["GateI"].toMap(), m_groups[m_currentGroupID].m_gateI);
    unpack_transceiver(map["Transceiver"].toMap());
    unpack_cursor(map["Cursor"].toMap());
    unpack_sample(map["Sample"].toMap());
    unpack_c_scan(map["CScan"].toMap());
    unpack_sizing(map["Sizing"].toMap());
    unpack_thickness(map["Thickness"].toMap());
    unpack_tofd(map["Tofd"].toMap());
}

void Config::unpack_version()
{
    Paramters::Version &version = m_global.m_version;
    version.m_phascanVersion = value("Version").toString();
    version.m_FpgaCpuVersion = value("FpgaCpuVersion").toString();
    version.m_FpgaPaVersion  = value("FpgaPaVersion").toString();
    if(!value("DxfData").isNull()){
        version.m_dxfExist = true;
        version.m_dxfData = value("DxfData").toByteArray();
    }else{
        version.m_dxfExist = false;
    }

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " version " << version.m_phascanVersion
             << " fpgaCpuVersion " << version.m_FpgaCpuVersion
             << " fpgaPaVersion " << version.m_FpgaPaVersion
             << " DxfDataExist " << version.m_dxfExist << version.m_dxfData.size();
}

void Config::unpack_display()
{
    Paramters::Display &display = m_global.m_display;

    QVariantMap displayMap= value("Display").toMap();

    display.m_ampPalette   = displayMap["AmpPalette"].toString();
    display.m_bright       = displayMap["Bright"].toUInt();
    display.m_cursor       = displayMap["Cursor"].toBool();
    display.m_depthPalette = displayMap["DepthPalette"].toString();
    display.m_groups       = displayMap["Groups"].toList();
    display.m_language     = displayMap["Language"].toUInt();
    display.m_layout       = displayMap["Layout"].toUInt();
    display.m_opacity      = displayMap["Opacity"].toUInt();
    display.m_tofdPalette  = displayMap["TofdPalette"].toString();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " ampPalette " << display.m_ampPalette
             << " bright " << display.m_bright
             << " cursor " << display.m_cursor
             << " depthPalette " << display.m_depthPalette
             << " groups " << display.m_groups
             << " language " << display.m_language
             << " layout " << display.m_layout
             << " opacity " << display.m_opacity
             << " tofdPalette " << display.m_tofdPalette;
}

void Config::unpack_sample(const QVariantMap &map)
{
    Paramters::Sample &sample = m_groups[m_currentGroupID].m_sample;
    sample.m_gain          = map["Gain"].toDouble();
    sample.m_start         = map["Start"].toDouble();
    sample.m_range         = map["Range"].toDouble();
    sample.m_maxGain       = map["MaxGain"].toUInt();
    sample.m_refGainStatus = map["RefGainStatus"].toUInt();
    sample.m_refGain       = map["RefGain"].toDouble();
    sample.m_pointQty      = map["PointQty"].toInt();
    sample.m_autoCalcPointQty= map["AutoCalcPointQty"].toBool();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " gain " << sample.m_gain
             << " refGainStatus " << sample.m_refGainStatus
             << " ref gain " << sample.m_refGain
             << " start " << sample.m_start
             << " range " << sample.m_range
             << " maxGain " << sample.m_maxGain
             << " point_qty " << sample.m_pointQty
             << " autoCalcPointQty " << sample.m_autoCalcPointQty;
}

void Config::unpack_c_scan(const QVariantMap &map)
{
    Paramters::CScan &cScan = m_groups[m_currentGroupID].m_cScan;
    cScan.m_mode = static_cast<Paramters::CScan::CScanMode> (map["Mode"].toUInt());
    cScan.m_sourceType = static_cast<Paramters::CScan::SourceType> (map["SourceType"].toUInt());
    cScan.m_topCWidth = map["TopCWidth"].toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " mode " << cScan.m_mode
             << " sourceType " << cScan.m_sourceType
             << " topCWidth " << cScan.m_topCWidth;
}

void Config::unpack_transceiver(const QVariantMap &map)
{
    Paramters::Transceiver &transceiver = m_groups[m_currentGroupID].m_transceiver;
    transceiver.m_autoCalPW  = map["AutoCalPW"].toBool();
    transceiver.m_average    = static_cast<Paramters::Transceiver::Averaging> (map["Average"].toUInt());
    transceiver.m_filter     = map["Filter"].toUInt();
    transceiver.m_txRxMode   = static_cast<Paramters::Transceiver::TxRxMode> (map["Mode"].toUInt());
    transceiver.m_pw         = map["PW"].toFloat();
    transceiver.m_pulser     = map["Pulser"].toUInt();
    transceiver.m_receiver   = map["Receiver"].toUInt();
    transceiver.m_rectifier  = static_cast<Paramters::Transceiver::Rectifier> (map["Rectifier"].toUInt());
    transceiver.m_videoFilter= map["VideoFilter"].toBool();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " autoCalPW " << transceiver.m_autoCalPW
             << " tx_rx mode " << transceiver.m_txRxMode
             << " pulser width " << transceiver.m_pw
             << " filter " << transceiver.m_filter
             << " rectifier " << transceiver.m_rectifier
             << " video filter " << transceiver.m_videoFilter
             << " averaging " << transceiver.m_average
             << " pulser " << transceiver.m_pulser
             << " receiver " << transceiver.m_receiver;
}

void Config::unpack_focallawer(const QVariantMap &map)
{
    m_groups[m_currentGroupID].m_focallawer.m_focusMode = static_cast<Paramters::Focallawer::FocusMode> (map["FocusMode"].toUInt());
    m_groups[m_currentGroupID].m_focallawer.m_scanMode  = static_cast<Paramters::Focallawer::ScanMode> (map["ScanMode"].toUInt());
    m_groups[m_currentGroupID].m_focallawer.m_waveType = static_cast<Paramters::Focallawer::WaveType> (map["WaveType"].toInt());
    m_groups[m_currentGroupID].m_focallawer.m_coupling = map["Coupling"].toBool();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " wave type " << m_groups[m_currentGroupID].m_focallawer.m_waveType
             << " focus mode " << m_groups[m_currentGroupID].m_focallawer.m_focusMode
             << " scan mode " << m_groups[m_currentGroupID].m_focallawer.m_scanMode;

    unpack_scan(map["Scan"].toMap());

    unpack_focus(map["Focus"].toMap());

    unpack_wedge(map["Wedge"].toMap());

    unpack_probe(map["Probe"].toMap());

    unpack_specimen(map["Specimen"].toMap());

    unpack_delays(map["Delays"].toList());

    unpack_fields(map["Fields"].toList());

    unpack_gains(map["Gains"].toList());
}

void Config::unpack_scan(const QVariantMap &map)
{
    Paramters::Scan &scan = m_groups[m_currentGroupID].m_focallawer.m_scan;

    if(Paramters::Focallawer::Linear == m_groups[m_currentGroupID].m_focallawer.m_scanMode) {
        scan.m_refractAngle   = map["RefractAngle"].toDouble();
        scan.m_screwAngle     = map["ScrewAngle"].toDouble();

        scan.m_secApe         = map["SecApe"].toUInt();
        scan.m_secElemStep    = map["SecElemStep"].toUInt();
        scan.m_secStartElem   = map["SecStartElem"].toUInt();
        scan.m_secStopElem    = map["SecStopElem"].toUInt();

        scan.m_priApe         = map["PriApe"].toUInt();
        scan.m_priElemStep    = map["PriElemStep"].toUInt();
        scan.m_priStartElem   = map["PriStartElem"].toUInt();
        scan.m_priStopElem    = map["PriStopElem"].toUInt();

        qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                 << " refractAngle " << scan.m_refractAngle
                 << " screwAngle " << scan.m_screwAngle
                 << " priApe " << scan.m_priApe
                 << " priStartElem " << scan.m_priStartElem
                 << " priElemStep " << scan.m_priElemStep
                 << " priStopElem " << scan.m_priStopElem
                 << " secApe " << scan.m_secApe
                 << " secStartElem " << scan.m_secStartElem
                 << " secElemStep " << scan.m_secElemStep
                 << " secStopElem " << scan.m_secStopElem;
    } else if(Paramters::Focallawer::Sectorial == m_groups[m_currentGroupID].m_focallawer.m_scanMode){

        scan.m_refractStartAngle = map["RefractStartAngle"].toDouble();
        scan.m_refractStopAngle  = map["RefractStopAngle"].toDouble();
        scan.m_refractStepAngle  = map["RefractStepAngle"].toDouble();

        scan.m_screwStartAngle   = map["ScrewStartAngle"].toDouble();
        scan.m_screwStopAngle    = map["ScrewStopAngle"].toDouble();
        scan.m_screwStepAngle    = map["ScrewStepAngle"].toDouble();

        scan.m_priApe         = map["PriApe"].toUInt();
        scan.m_priStartElem   = map["PriStartElem"].toUInt();
        scan.m_secApe         = map["SecApe"].toUInt();
        scan.m_secStartElem   = map["SecStartElem"].toUInt();

        qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                 << " refractStartAngle " << scan.m_refractStartAngle
                 << " refractStopAngle " << scan.m_refractStopAngle
                 << " refractStepAngle " << scan.m_refractStepAngle
                 << " screwStartAngle " << scan.m_screwStartAngle
                 << " screwStopAngle " << scan.m_screwStopAngle
                 << " screwStepAngle " << scan.m_screwStepAngle
                 << " priApe " << scan.m_priApe
                 << " priStartElem " << scan.m_priStartElem
                 << " secApe " << scan.m_secApe
                 << " secStartElem " << scan.m_secStartElem;
    }else{
        scan.m_colOffset = map["ColOffset"].toDouble();
        scan.m_colRes    = map["ColRes"].toDouble();
        scan.m_rowOffset = map["RowOffset"].toDouble();
        scan.m_rowRes    = map["RowRes"].toDouble();

        scan.m_colQty = map["ColQty"].toInt();
        scan.m_rowQty = map["RowQty"].toInt();

        scan.m_priApe       = 1;
        scan.m_priStartElem = map["PriStartElem"].toUInt();
        scan.m_secApe         = map["SecApe"].toUInt();
        scan.m_secStartElem   = map["SecStartElem"].toUInt();

        qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                 << " colOffset " << scan.m_colOffset
                 << " colRes " << scan.m_colRes
                 << " rowOffset " << scan.m_rowOffset
                 << " rowRes " << scan.m_rowRes
                 << " colQty " << scan.m_colQty
                 << " rowQty " << scan.m_rowQty
                 << " priApe " << scan.m_priApe
                 << " priStartElem " << scan.m_priStartElem
                 << " secApe " << scan.m_secApe
                 << " secStartElem " << scan.m_secStartElem;
    }
}

void Config::unpack_probe(const QVariantMap &map)
{
    Paramters::Probe &probe = m_groups[m_currentGroupID].m_probe;

    probe.m_arrayMode     = static_cast<Paramters::Probe::ArrayMode> (map.value("ArrayMode", DEFAULT_ARRAY_MODE).toUInt());
    probe.m_freq          = map.value("Freq", DEFAULT_PROBE_FREQ).toDouble();
    probe.m_model         = map.value("Model", DEFAULT_PROBE_MODEL).toString();
    probe.m_serial        = map.value("Serial", DEFAULT_PROBE_SERIAL).toString();
    probe.m_priElemQty    = map.value("PriElemQty", DEFAULT_ELEMQTY).toUInt();
    probe.m_secElemQty    = map.value("SecElemQty", DEFAULT_ELEMQTY).toUInt();
    probe.m_priPitch      = map.value("PriPitch", DEFAULT_PRI_PITCH).toFloat();
    probe.m_secPitch      = map.value("SecPitch", DEFAULT_SEC_PITCH).toFloat();
    probe.m_refPoint      = map.value("RefPoint", DEFAULT_REFPOINT).toFloat();
    probe.m_scanOffset    = map.value("ScanOffset", DEFAULT_OFFSET).toDouble();
    probe.m_indexOffset   = map.value("IndexOffset", DEFAULT_OFFSET).toDouble();
    probe.m_type          = static_cast<Paramters::Probe::ProbeType> (map.value("Type", DEFAULT_PROBE_TYPE).toUInt());
    probe.m_skew          = map.value("Skew", DEFAULT_SKEW).toUInt();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " Serial " << probe.m_serial
             << " Model " << probe.m_model
             << " freq " << probe.m_freq
             << " scanOffset " << probe.m_scanOffset
             << " indexOffset " << probe.m_indexOffset
             << " skew " << probe.m_skew
             << " type " << probe.m_type
             << "\n[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " arrayMode " << probe.m_arrayMode
             << " priElemQty " << probe.m_priElemQty
             << " secElemQty " << probe.m_secElemQty
             << " priPitch " << probe.m_priPitch
             << " secPitch " << probe.m_secPitch
             << " refPoint " << probe.m_refPoint;
}

void Config::unpack_wedge(const QVariantMap &map)
{
    Paramters::Wedge &wedge = m_groups[m_currentGroupID].m_wedge;

    wedge.m_serial        = map.value("Serial", DEFAULT_WEDGE_SERIAL).toString();
    wedge.m_model         = map.value("Model", DEFAULT_WEDGE_MODEL).toString();
    wedge.m_angle         = map.value("Angle", DEFAULT_WEDGE_ANGLE).toDouble();
    wedge.m_fstElemHeight = map.value("FstElemHeight", DEFAULT_WEDGE_FIRST_ELEM_HEIGHT).toDouble();
    wedge.m_length        = map.value("Length", DEFAULT_WEDGE_LENGTH).toDouble();
    wedge.m_width         = map.value("Width", DEFAULT_WEDGE_WIDTH).toDouble();
    wedge.m_height        = map.value("Height", DEFAULT_WEDGE_HEIGHT).toDouble();
    wedge.m_velocity      = map.value("Velocity", DEFAULT_WEDGE_VELOCITY).toDouble();
    wedge.m_priOffset     = map.value("PriOffset").toDouble();
    wedge.m_secOffset     = map.value("SecOffset").toDouble();
    wedge.m_orientation   = static_cast<Paramters::Wedge::Orientation> (map.value("Orientation", DEFAULT_WEDGE_ORIENTATION).toUInt());
    wedge.m_rootAngle     = map.value("RootAngle", DEFAULT_WEDGE_ROOT_ANGLE).toDouble();
    wedge.m_delay         = map.value("Delay", DEFAULT_WEDGE_DELAY).toUInt();
    wedge.m_clampOffset   = map.value("Delay", DEFAULT_WEDGE_CLAMP_OFFSET).toDouble();
    /* 以下键值暂不清楚是否存在 */
    wedge.m_waveType      = static_cast<Paramters::Wedge::WaveType> (map.value("WaveType", DEFAULT_WEDGE_WAVE_TYPE).toUInt());
    wedge.m_refPoint      = map.value("RefPoint", DEFAULT_WEDGE_REF_POINT).toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " serial " << wedge.m_serial
             << " model " << wedge.m_model
             << " angle " << wedge.m_angle
             << " rootAngle " << wedge.m_rootAngle
             << " velocity " << wedge.m_velocity
             << " primaryOffset " << wedge.m_priOffset
             << " secondaryOffset " << wedge.m_secOffset
             << " firstElementHeight " << wedge.m_fstElemHeight
             << " length " << wedge.m_length
             << " width " << wedge.m_width
             << " height " << wedge.m_height
             << " orientation " << wedge.m_orientation
             << " delay " << wedge.m_delay
             << " clampOffset " << wedge.m_clampOffset
             << " wave type " << wedge.m_waveType
             << " ref pint " << wedge.m_refPoint;
}

void Config::unpack_specimen(const QVariantMap &map)
{
    Paramters::Specimen &specimen = m_groups[m_currentGroupID].m_specimen;

    specimen.m_shape      = static_cast<Paramters::Specimen::Shape> (map.value("Shape", DEFAULT_SHAPE).toUInt());
    specimen.m_LV         = map.value("LV", DEFAULT_LV).toDouble();
    specimen.m_SV         = map.value("SV", DEFAULT_SV).toDouble();
    specimen.m_material   = static_cast<Paramters::Specimen::Material> (map.value("Material", DEFAULT_MATERIAL).toUInt());
    specimen.m_density    = map.value("Density", DEFAULT_DENSITY).toDouble();
    specimen.m_weldType   = static_cast<Paramters::Specimen::WeldType> (map.value("WeldType", DEFAULT_WELD_TYPE).toUInt());
    specimen.m_weld.m_type  = static_cast<Paramters::Weld::WeldType> (specimen.m_weldType);

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " shape " << specimen.m_shape
             << " logitudinalVelocity " << specimen.m_LV
             << " shearVelocity " << specimen.m_SV
             << " material " << specimen.m_material
             << " density " << specimen.m_density
             << " weldType " << specimen.m_weldType;

    unpack_geometry(map.value("Geometry").toMap());

    unpack_weld(map.value("Weld").toMap());
}

void Config::unpack_delays(const QVariantList &list)
{
    QList<float> &delays = m_groups[m_currentGroupID].m_focallawer.m_delays;
    delays.clear();
    foreach (QVariant value, list) {
        delays.append(value.toFloat());
    }
}

void Config::unpack_fields(const QVariantList &list)
{
    QList<float> &fields = m_groups[m_currentGroupID].m_focallawer.m_fieldDistance;
    fields.clear();
    foreach (QVariant value, list) {
        fields.append(value.toFloat());
    }
}

void Config::unpack_gains(const QVariantList &list)
{
    QList<float> &gains = m_groups[m_currentGroupID].m_focallawer.m_gains;
    gains.clear();
    foreach (QVariant value, list) {
        gains.append(value.toFloat());
    }
}

void Config::unpack_geometry(const QVariantMap &map)
{
    if(Paramters::Specimen::PLANE == m_groups[m_currentGroupID].m_specimen.m_shape) {
        unpack_geometry_plane(map, m_groups[m_currentGroupID].m_specimen.m_geometry.m_plane);
    } else if(Paramters::Specimen::CYLINDER == m_groups[m_currentGroupID].m_specimen.m_shape) {
        unpack_geometry_cylinder(map, m_groups[m_currentGroupID].m_specimen.m_geometry.m_cylinder);
    } else if(Paramters::Specimen::NOZZLE == m_groups[m_currentGroupID].m_specimen.m_shape) {
        unpack_geometry_nozzle(map);
    } else if(Paramters::Specimen::FILLET == m_groups[m_currentGroupID].m_specimen.m_shape) {
        unpack_geometry_fillet(map);
    } else {
        qWarning("%s(%s[%d]): unimplement", __FILE__, __func__, __LINE__);
    }
}

void Config::unpack_geometry_plane(const QVariantMap &map, Paramters::Plane &plane)
{
    //Paramters::Plane &plane = m_groups[m_currentGroupID].m_specimen.m_geometry.m_plane;
    plane.m_height = map.value("Height", DEFAULT_PLANE_HEIGHT).toDouble();
    plane.m_length = map.value("Length", DEFAULT_PLANE_LENGTH).toDouble();
    plane.m_width  = map.value("Width", DEFAULT_PLANE_WIDTH).toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " height " << plane.m_height
             << " length " << plane.m_length
             << " width " << plane.m_width;
}

void Config::unpack_geometry_cylinder(const QVariantMap &map, Paramters::Cylinder &cylinder)
{
    cylinder.m_probePos = static_cast<Paramters::Cylinder::ProbePosition> (map.value("ProbePos",
                                                               DEFAULT_CYLINDER_PROBE_POS).toUInt());
    cylinder.m_inside  = map.value("Inside", DEFAULT_CYLINDER_INSIDE).toDouble();
    cylinder.m_outside = map.value("Outside", DEFAULT_CYLINDER_OUTSIDE).toDouble();
    cylinder.m_angle   = map.value("Angle", DEFAULT_CYLINDER_ANGLE).toDouble();
    cylinder.m_length  = map.value("Length", DEFAULT_CYLINDER_LENGHT).toDouble();
    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " probePos " << cylinder.m_probePos
             << " inside " << cylinder.m_inside
             << " outside " << cylinder.m_outside
             << " angle " << cylinder.m_angle
             << " length " << cylinder.m_length;
}

void Config::unpack_geometry_nozzle(const QVariantMap &map)
{
    Paramters::Nozzle &nozzle = m_groups[m_currentGroupID].m_specimen.m_geometry.m_nozzle;
    nozzle.m_inside  = map.value("Inside", DEFAULT_NOZZLE_INSIDE).toDouble();
    nozzle.m_outside = map.value("Outside", DEFAULT_NOZZLE_OUTSIDE).toDouble();
    nozzle.m_angle   = map.value("Angle", DEFAULT_NOZZLE_ANGLE).toDouble();

    unpack_geometry_cylinder(map.value("Cylinder1").toMap(), nozzle.m_cylinder1);
    unpack_geometry_cylinder(map.value("Cylinder2").toMap(), nozzle.m_cylinder2);
}

void Config::unpack_geometry_fillet(const QVariantMap &map)
{
    Paramters::Fillet &fillet = m_groups[m_currentGroupID].m_specimen.m_geometry.m_fillet;
    fillet.m_angle = map.value("Angle", DEFAULT_FILLET_ANGLE).toDouble();
    fillet.m_probePos = static_cast<Paramters::Fillet::ProbePosition> (map.value("ProbePosition",
                                                                        DEFAULT_FILLET_PROBE_POS).toUInt());
    unpack_geometry_plane(map.value("BottomPlane").toMap(), fillet.m_bottomPlane);
    unpack_geometry_plane(map.value("TopPlane").toMap(), fillet.m_topPlane);
}

void Config::unpack_weld(const QVariantMap &map)
{
    Paramters::Weld &weld = m_groups[m_currentGroupID].m_specimen.m_weld;

    if(m_groups[m_currentGroupID].m_specimen.m_weldType == Paramters::Weld::NONE_TYPE) {
        return;
    }

    weld.m_orientation = static_cast<Paramters::Weld::WeldOrientation> (map.value("Orientation", DEFAULT_WELD_ORIENTATION).toUInt());
    weld.m_isSymmetry  = static_cast<Paramters::Weld::Symmetry> (map.value("Symmetry", DEFAULT_WELD_SYMMETRY).toUInt());
    weld.HAZ = map.value("HAZ", DEFAULT_WELD_HAZ).toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " orientation " << weld.m_orientation
             << " symmetry " << weld.m_isSymmetry
             << " HAZ " << weld.HAZ;

    if(Paramters::Weld::I == weld.m_type) {
        unpack_I_weld(map.value("I").toMap(), weld.m_I);
    } else if(Paramters::Weld::V == weld.m_type) {
        unpack_I_weld(map.value("I").toMap(), weld.m_I);
        unpack_V_weld(map.value("V").toMap(), weld.m_V);
    } else if(Paramters::Weld::U == weld.m_type) {
        unpack_I_weld(map.value("I").toMap(), weld.m_I);
        unpack_U_weld(map.value("U").toMap(), weld.m_U);
    }else if(Paramters::Weld::VY == weld.m_type) {
        unpack_I_weld(map.value("BtmI").toMap(), weld.m_BtmI);
        unpack_V_weld(map.value("MidV").toMap(), weld.m_MidV);
        unpack_V_weld(map.value("TopV").toMap(), weld.m_TopV);
    } else if(Paramters::Weld::VV == weld.m_type) {
        unpack_V_weld(map.value("BtmV").toMap(), weld.m_BtmV);
        unpack_I_weld(map.value("MidI").toMap(), weld.m_MidI);
        unpack_V_weld(map.value("TopV").toMap(), weld.m_TopV);
    } else if(Paramters::Weld::UU == weld.m_type) {
        unpack_U_weld(map.value("BtmU").toMap(), weld.m_BtmU);
        unpack_I_weld(map.value("MidI").toMap(), weld.m_MidI);
        unpack_U_weld(map.value("TopU").toMap(), weld.m_TopU);
    } else if(Paramters::Weld::UV == weld.m_type) {
        unpack_U_weld(map.value("U").toMap(), weld.m_U);
        unpack_I_weld(map.value("I").toMap(), weld.m_I);
        unpack_V_weld(map.value("V").toMap(), weld.m_V);
    } else if(Paramters::Weld::TKY == weld.m_type) {
        weld.m_TKY.m_a1 = map.value("a1").toDouble();
        weld.m_TKY.m_a2 = map.value("a2").toDouble();
        weld.m_TKY.m_h1 = map.value("h1").toDouble();
        weld.m_TKY.m_h2 = map.value("h2").toDouble();
        weld.m_TKY.m_l1 = map.value("l1").toDouble();
        weld.m_TKY.m_l2 = map.value("l2").toDouble();
    } else {
        qWarning("%s(%s[%d]): unimplement", __FILE__, __func__, __LINE__);
    }
}

void Config::getWeldData( int groupId, WELD_II & weld_ii)
{
    Paramters::Weld &weld = m_groups[groupId].m_specimen.m_weld;
    Paramters::Fillet &fillet = m_groups[groupId].m_specimen.m_geometry.m_fillet;
    weld_ii.eType = static_cast<setup_WELD_TYPE_II>(weld.m_type);
    weld_ii.eSymmetry = static_cast<setup_WELD_SYMMETRY_TYPE>(weld.m_isSymmetry);
    weld_ii.eHAZ = weld.HAZ;
    //if(Paramters::Weld::I == weld.m_type)
    switch (weld.m_type) {
    case Paramters::Weld::I:
        weld_ii.I.w = weld.m_I.m_width;
        break;
    case Paramters::Weld::V:
        weld_ii.V.w1 = weld.m_V.m_width;
        weld_ii.V.h  = weld.m_V.m_height;
        weld_ii.V.w2 = weld.m_I.m_width;
        break;
    case Paramters::Weld::U:
        weld_ii.U.w1 = weld.m_U.m_width;
        weld_ii.U.h  = weld.m_U.m_height;
        weld_ii.U.r  = weld.m_U.m_radius;
        weld_ii.U.w2 = weld.m_I.m_width;
        break;
    case Paramters::Weld::VY:
        weld_ii.VY.w1 = weld.m_TopV.m_width;
        weld_ii.VY.h1 = weld.m_TopV.m_height;
        weld_ii.VY.w2 = weld.m_MidV.m_width;
        weld_ii.VY.h2 = weld.m_MidV.m_height;
        weld_ii.VY.w3 = weld.m_BtmI.m_width;
        break;
    case Paramters::Weld::VV:
        weld_ii.VV.w1 = weld.m_TopV.m_width;
        weld_ii.VV.h1 = weld.m_TopV.m_height;
        weld_ii.VV.w2 = weld.m_MidI.m_width;
        weld_ii.VV.w3 = weld.m_BtmV.m_width;
        weld_ii.VV.h2 = weld.m_BtmV.m_height;
        break;
    case Paramters::Weld::UU:
        weld_ii.UU.w1 = weld.m_TopU.m_width;
        weld_ii.UU.h1 = weld.m_TopU.m_height;
        weld_ii.UU.r1 = weld.m_TopU.m_radius;
        weld_ii.UU.w2 = weld.m_MidI.m_width;
        weld_ii.UU.w3 = weld.m_BtmU.m_width;
        weld_ii.UU.h2 = weld.m_BtmU.m_height;
        weld_ii.UU.r2 = weld.m_BtmU.m_radius;
        break;
    case Paramters::Weld::UV:
        weld_ii.UV.w1 = weld.m_U.m_width;
        weld_ii.UV.h1 = weld.m_U.m_height;
        weld_ii.UV.r  = weld.m_U.m_radius;
        weld_ii.UV.w2 = weld.m_I.m_width;
        weld_ii.UV.w3 = weld.m_V.m_width;
        weld_ii.UV.h2 = weld.m_V.m_height;
        break;
    case Paramters::Weld::TKY:
        weld_ii.TKY.w1 = weld.m_TKY.m_l1;
        weld_ii.TKY.w2 = weld.m_TKY.m_l2;
        weld_ii.TKY.h1 = weld.m_TKY.m_h1;
        weld_ii.TKY.h2 = weld.m_TKY.m_h2;
        weld_ii.TKY.a1 = weld.m_TKY.m_a1;
        weld_ii.TKY.a2 = weld.m_TKY.m_a2;
        break;
    default:
        break;
    }
    if(Paramters::Weld::TKY == weld.m_type){
        weld_ii.eProbePos = static_cast<KTY_ProbePosition>(fillet.m_probePos);
        weld_ii.eAngle    = fillet.m_angle;
        //weld_ii.eAngle    = 60;
        weld_ii.eTopThinkness    = fillet.m_topPlane.m_height;
        weld_ii.eBottomThinkness = fillet.m_bottomPlane.m_height;
    }else{
        weld_ii.eProbePos = static_cast<KTY_ProbePosition>(DEFAULT_FILLET_PROBE_POS);
        weld_ii.eAngle    = DEFAULT_FILLET_ANGLE;
        weld_ii.eTopThinkness    = DEFAULT_PLANE_HEIGHT;
        weld_ii.eBottomThinkness = DEFAULT_PLANE_HEIGHT;
    }
    if(m_global.m_version.m_dxfExist){
        weld_ii.eType = DXF;
    }
}

void Config::getTOPCWidth( int groupId, double &topcWidth)
{
    topcWidth = m_groups[groupId].m_cScan.m_topCWidth;
}

void Config::getApertureSec( int groupId, unsigned int * apertureData)
{
    apertureData[0] = m_groups[groupId].m_focallawer.m_scan.m_secApe;
    apertureData[1] = m_groups[groupId].m_focallawer.m_scan.m_secStartElem;
    apertureData[2] = m_groups[groupId].m_focallawer.m_scan.m_secStopElem;
    apertureData[3] = m_groups[groupId].m_focallawer.m_scan.m_secElemStep;
}

void Config::getTofdData( int groupId, float *PCS, float *RefPoint)
{
    *PCS = m_groups[groupId].m_tofd.m_PCS;
    *RefPoint = m_groups[groupId].m_tofd.m_RefPosition;
}

void Config::getTMFRange(int groupId, float *start, float *range, int *pointQty)
{
    *start = m_groups[groupId].m_focallawer.m_scan.m_rowOffset;
    *range = (m_groups[groupId].m_focallawer.m_scan.m_rowQty - 1) * m_groups[groupId].m_focallawer.m_scan.m_rowRes;
    *pointQty = m_groups[groupId].m_focallawer.m_scan.m_rowQty;
}

void Config::getScannerData( SCANNER &scanner)
{
    scanner.eScanEncoderType = (setup_ENCODER_TYPE)m_global.m_scanner.m_scanAxis.m_driving;
    scanner.eIndexEncoderType = (setup_ENCODER_TYPE)m_global.m_scanner.m_indexAxis.m_driving;
    scanner.eScanType = (setup_SCAN_TYPE)m_global.m_scanner.m_scanType;

    scanner.encoder[0].eEncoderMode = (setup_ENCODER_MODE)m_global.m_scanner.m_encoderX.m_mode;
    scanner.encoder[0].ePolarity    = (setup_ENCODER_POLARITY)m_global.m_scanner.m_encoderX.m_polarity;
    scanner.encoder[0].fResulotion  = m_global.m_scanner.m_encoderX.m_resolution;
    scanner.encoder[0].fOrigin      = m_global.m_scanner.m_encoderX.m_origin;

    scanner.encoder[1].eEncoderMode = (setup_ENCODER_MODE)m_global.m_scanner.m_encoderY.m_mode;
    scanner.encoder[1].ePolarity    = (setup_ENCODER_POLARITY)m_global.m_scanner.m_encoderY.m_polarity;
    scanner.encoder[1].fResulotion  = m_global.m_scanner.m_encoderY.m_resolution;
    scanner.encoder[1].fOrigin      = m_global.m_scanner.m_encoderY.m_origin;
}

void Config::unpack_I_weld(const QVariantMap &map, Paramters::WeldI &I)
{
    I.m_width       = map.value("W").toDouble();
    I.m_orientation = static_cast<Paramters::Weld::WeldOrientation> (map.value("Orientation").toUInt());
    I.m_symmetry    = map.value("Symmetry").toBool();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " width " << I.m_width
             << " orientation " << I.m_orientation
             << " symmetry " << I.m_symmetry;
}

void Config::unpack_V_weld(const QVariantMap &map, Paramters::WeldV &V)
{
    V.m_width       = map.value("W").toDouble();
    V.m_orientation = static_cast<Paramters::Weld::WeldOrientation> (map.value("Orientation").toUInt());
    V.m_symmetry    = map.value("Symmetry").toBool();
    V.m_height      = map.value("H").toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " width " << V.m_width
             << " orientation " << V.m_orientation
             << " symmetry " << V.m_symmetry
             << " height " << V.m_height;
}

void Config::unpack_U_weld(const QVariantMap &map, Paramters::WeldU &U)
{
    U.m_width       = map.value("W").toDouble();
    U.m_orientation = static_cast<Paramters::Weld::WeldOrientation> (map.value("Orientation").toUInt());
    U.m_symmetry    = map.value("Symmetry").toBool();
    U.m_height      = map.value("H").toDouble();
    U.m_radius      = map.value("R").toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " width " << U.m_width
             << " orientation " << U.m_orientation
             << " symmetry " << U.m_symmetry
             << " height " << U.m_height
             << " radius " << U.m_radius;
}

void Config::unpack_focus(const QVariantMap &map)
{
    Paramters::Focus &focus = m_groups[m_currentGroupID].m_focallawer.m_focus;

    focus.m_radius      = map.value("Radius", DEFAULT_END_OFFSET).toDouble();
    focus.m_depth       = map.value("Depth", DEFAULT_END_OFFSET).toDouble();
    focus.m_offset      = map.value("Offset", DEFAULT_END_OFFSET).toDouble();
    focus.m_beginOffset = map.value("BeginOffset", DEFAULT_BEGIN_OFFSET).toDouble();
    focus.m_endOffset   = map.value("EndOffset", DEFAULT_END_OFFSET).toDouble();
    focus.m_beginDepth  = map.value("BeginDepth", DEFAULT_BEGIN_OFFSET).toDouble();
    focus.m_endDepth    = map.value("EndDepth", DEFAULT_END_OFFSET).toDouble();
//    focus.m_focusMode   = m_groups[m_currentGroupID].focallawer.focusMode;

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " radius " << focus.m_radius
             << " depth " << focus.m_depth
             << " offset " << focus.m_offset
             << " beginOffset " << focus.m_beginOffset
             << " endOffset " << focus.m_endOffset
             << " beginDepth " << focus.m_beginDepth
             << " endDepth " << focus.m_endDepth;
}

void Config::unpack_beams_info()
{
//    memset(&m_groups[m_currentGroupID].focallawer.beamsInfo, 0, sizeof(S_BeamsInfo));

//    S_BeamsInfo &beamsInfo = m_groups[m_currentGroupID].focallawer.beamsInfo;
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

void Config::unpack_thickness(const QVariantMap &map)
{
    m_groups[m_currentGroupID].m_thickness.m_min = map["Min"].toDouble();
    m_groups[m_currentGroupID].m_thickness.m_max = map["Max"].toDouble();
    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " thickness min " << m_groups[m_currentGroupID].m_thickness.m_min
                 << " thickness max " << m_groups[m_currentGroupID].m_thickness.m_max;
}

void Config::unpack_tofd(const QVariantMap &map)
{
    m_groups[m_currentGroupID].m_tofd.m_PCS = map["PCS"].toFloat();
    m_groups[m_currentGroupID].m_tofd.m_RefPosition = map["RefPosition"].toFloat();
    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " tofd PCS " << m_groups[m_currentGroupID].m_tofd.m_PCS
             << " tofd RefPosition " << m_groups[m_currentGroupID].m_tofd.m_RefPosition;
}

void Config::unpack_cursor(const QVariantMap &map)
{
    Paramters::Cursor &cursor = m_groups[m_currentGroupID].m_cursor;

    cursor.m_ampMeas  = map.value("AmpMeas", DEFAULT_MEAS).toDouble();
    cursor.m_ampRef   = map.value("AmpRef", DEFAULT_REF).toDouble();
    cursor.m_depthMeas= map.value("DepthMeas", DEFAULT_MEAS).toDouble();
    cursor.m_depthRef = map.value("DepthRef", DEFAULT_REF).toDouble();
    cursor.m_indexMeas= map.value("IndexMeas", DEFAULT_MEAS).toDouble();
    cursor.m_indexRef = map.value("IndexRef", DEFAULT_REF).toDouble();
    cursor.m_scanMeas = map.value("ScanMeas", DEFAULT_MEAS).toDouble();
    cursor.m_scanRef  = map.value("ScanRef", DEFAULT_REF).toDouble();
    cursor.m_ultraMeas= map.value("UltraMeas", DEFAULT_MEAS).toDouble();
    cursor.m_ultraRef = map.value("UltraRef", DEFAULT_REF).toDouble();
    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " ampMeas " << cursor.m_ampMeas
             << " ampRef " << cursor.m_ampRef
             << " depthMeas " << cursor.m_depthMeas
             << " depthRef " << cursor.m_depthRef
             << " indexMeas " << cursor.m_indexMeas
             << " indexRef " << cursor.m_indexRef
             << " scanMeas " << cursor.m_scanMeas
             << " scanRef " << cursor.m_scanRef
             << " ultraMeas " << cursor.m_ultraMeas
             << " ultraRef " << cursor.m_ultraRef;
}

void Config::unpack_gate(const QVariantMap &map, Paramters::Gate &gate)
{
    gate.m_measureMode = static_cast<Paramters::Gate::MeasureMode> (map["MeasureMode"].toUInt());
    gate.m_gateMode    = static_cast<Paramters::Gate::GateMode> (map["Mode"].toUInt());
    gate.m_synchroMode = static_cast<Paramters::Gate::SynchroMode> (map["SynchroMode"].toUInt());
    gate.m_visible     = map["Visible"].toBool();
    gate.m_start       = map["Start"].toDouble();
    gate.m_width       = map["Width"].toDouble();;
    gate.m_height      = map["Height"].toUInt();
//    gate.color       = map["Color"].toUInt();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " measureMode " << gate.m_measureMode
             << " gateMode " << gate.m_gateMode
             << " synchroMode " << gate.m_synchroMode
             << " visible " << gate.m_visible
             << " start " << gate.m_start
             << " width " << gate.m_width
             << " height " << gate.m_height
             << " color " << gate.m_color;
}

void Config::unpack_sizing(const QVariantMap &map)
{
    m_groups[m_currentGroupID].m_sizing.m_type = static_cast<Paramters::Sizing::SizingType> (map.value("Type").toUInt());
    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " sizing type " << m_groups[m_currentGroupID].m_sizing.m_type;
    unpack_curves(map.value("Curves").toMap());
}

void Config::unpack_curves(const QVariantMap &map)
{
    if(Paramters::Sizing::SizingNONE == m_groups[m_currentGroupID].m_sizing.m_type) {
        return;
    }

    Paramters::Curves &curves = m_groups[m_currentGroupID].m_sizing.m_curves;
    curves.m_compliance = static_cast<Paramters::Curves::Compliance> (map.value("Compliance").toUInt());
    curves.m_curveQty   = map.value("CurveQty").toUInt();
    curves.m_gain       = map.value("Gain").toDouble();
    curves.m_pointQty   = map.value("PointQty").toUInt();
    curves.m_refAmp     = map.value("RefAmp").toDouble();
    QVariantList offsets = map.value("Offsets").toList();
    //QVariantList offsets = map.value("Gains").toList();
    for(int i = 0; i < offsets.count(); ++i) {
        curves.m_offsets.append(offsets.at(i).toDouble());
        qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]"
                 << " offset db " << offsets.at(i).toDouble();
    }

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " compliance " << curves.m_compliance
             << " curveQty " << curves.m_curveQty
             << " gain " << curves.m_gain
             << " pointQty " << curves.m_pointQty
             << " refAmp " << curves.m_refAmp;

    curves.m_beams.clear();

    if(Paramters::Sizing::TCG == m_groups[m_currentGroupID].m_sizing.m_type) {
        QVariantList beamsList = map.value("Beams").toList();
        QVariantMap beamsMap;
        for(int i = 0; i < beamsList.count(); ++i) {
            beamsMap = beamsList.at(i).toMap();
            QVariantList gainList = beamsMap.value("Gain").toList();
            QVariantList positionList = beamsMap.value("Positions").toList();

            if(gainList.size() != positionList.size()) {
                qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << " TCG error size !!!";
            }

            int count = qMin(gainList.size(), positionList.size());

            QList< QPair< double, double> > list;
            QPair<double, double> value;
            for(int k = 0; k < count; ++k) {
                value.first  = gainList.at(k).toDouble();
                value.second = positionList.at(k).toDouble();
                list.append(value);
                qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                         << " i " << i
                         << " k " << k
                         << " first " << value.first
                         << " second " << value.second;
            }

            curves.m_beams.append(list);
        }
    } else if(Paramters::Sizing::DAC == m_groups[m_currentGroupID].m_sizing.m_type) {
        QVariantList beamsList = map.value("Beams").toList();
        QVariantMap beamsMap;
        for(int i = 0; i < beamsList.count(); ++i) {
            beamsMap = beamsList.at(i).toMap();
            //QVariantList gainList = beamsMap.value("Offsets").toList();
            QVariantList gainList = beamsMap.value("Gains").toList();
            QVariantList positionList = beamsMap.value("Positions").toList();

            if(gainList.size() != positionList.size()) {
                qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << " DAC error size !!!";
            }

            int count = qMin(gainList.size(), positionList.size());

            QList< QPair< double, double> > list;
            QPair<double, double> value;
            for(int k = 0; k < count; ++k) {
                value.first  = gainList.at(k).toDouble();
                value.second = positionList.at(k).toDouble();
                qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                         << " i " << i
                         << " k " << k
                         << " first " << value.first
                         << " second " << value.second;
                list.append(value);
            }

            curves.m_beams.append(list);
        }
    } else if(Paramters::Sizing::LINEAR_DAC == m_groups[m_currentGroupID].m_sizing.m_type) {
        curves.m_attenuation = map.value("Attenuation").toDouble();
        curves.m_delay       = map.value("Delay").toDouble();
        qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                 << " attenuation " << curves.m_attenuation
                 << " delay " << curves.m_delay;
    }
}

void Config::unpack_scanner()
{
    QVariantMap map = value("Scanner").toMap();

    unpack_axis(map["IndexAxis"].toMap(), m_global.m_scanner.m_indexAxis);

    unpack_axis(map["ScanAxis"].toMap(), m_global.m_scanner.m_scanAxis);

    unpack_encoder(map["Encoder0"].toMap(), m_global.m_scanner.m_encoderX);

    unpack_encoder(map["Encoder1"].toMap(), m_global.m_scanner.m_encoderY);

    m_global.m_scanner.m_scanType = static_cast<Paramters::Scanner::ScanType> (map["Mode"].toUInt());
    m_global.m_scanner.m_rate     = map["Rate"].toUInt();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " scanType " << m_global.m_scanner.m_scanType
             << " rate " << m_global.m_scanner.m_rate;
}

void Config::unpack_axis(const QVariantMap &map, Paramters::Axis &axis)
{
    axis.m_driving    = static_cast<Paramters::Axis::Driving>(map["Driving"].toUInt());
    axis.m_start      = map["Start"].toDouble();
    axis.m_end        = map["End"].toDouble();
    axis.m_resolution = map["Resolution"].toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " driving " << axis.m_driving
             << " start " << axis.m_start
             << " end " << axis.m_end
             << " resolution " << axis.m_resolution;
}

void Config::unpack_encoder(const QVariantMap &map,Paramters::Encoder &encoder)
{
    encoder.m_status      = static_cast<Paramters::Encoder::EncoderStatus> (map["Status"].toUInt());
    encoder.m_polarity    = static_cast<Paramters::Encoder::Polarity> (map["Polarity"].toUInt());
    encoder.m_mode        = static_cast<Paramters::Encoder::EncoderMode> (map["Mode"].toUInt());
    encoder.m_resolution  = map["Resolution"].toDouble();
    encoder.m_origin      = map["Origin"].toDouble();;

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " status " << encoder.m_status
             << " polarity " << encoder.m_polarity
             << " mode " << encoder.m_mode
             << " resolution " << encoder.m_resolution
             << " origin " << encoder.m_origin;
}

void Config::unpack_global_transceiver()
{
    Paramters::GlobalTransceiver &transceiver = m_global.m_transceiver;
    QVariantMap map = value("GlobalTransceiver").toMap();

    transceiver.m_paVoltage      = static_cast<Paramters::GlobalTransceiver::Voltage> (map["PaVoltage"].toUInt());
    transceiver.m_ut1TxDamping   = static_cast<Paramters::GlobalTransceiver::Damping> (map["Ut1TxDamping"].toUInt());
    transceiver.m_ut2TxDamping   = static_cast<Paramters::GlobalTransceiver::Damping> (map["Ut2TxDamping"].toUInt());
    transceiver.m_utVoltage      = static_cast<Paramters::GlobalTransceiver::Voltage> (map["UtVoltage"].toUInt());

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " PA Voltage " << transceiver.m_paVoltage
             << " UT Voltage " << transceiver.m_utVoltage
             << " ut1TxDamping " << transceiver.m_ut1TxDamping
             << " ut2TxDamping " << transceiver.m_ut2TxDamping;
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
    Q_UNUSED(index);
//    Paramters::Alarm &alarm = m_global.alarm[index];
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

    Paramters::Group &currentGroup = m_groups[groupId];
    Paramters::Probe &currentProbe = currentGroup.m_probe;
    Paramters::Wedge &currentWedge = currentGroup.m_wedge;
    Paramters::Focus &currentFocus = currentGroup.m_focallawer.m_focus;
    Paramters::Scan &currentScan= currentGroup.m_focallawer.m_scan;
    Paramters::Specimen &currentSpecimen = currentGroup.m_specimen;

    GROUP_INFO &targetGroup = m_pDataFile->m_cGroupInfo[groupId];
    LAW_INFO &targetLawInfo = targetGroup.law_info;
    WEDGE &targetWedge = targetGroup.wedge;
    PROBE &targetProbe = targetGroup.probe;

    targetGroup.group_mode  = currentGroup.m_mode;
//    if(Paramters::Group::Time == currentGroup.m_utUnit
//            || Paramters::Group::TruePath == currentGroup.m_utUnit) {
//        targetGroup.ut_unit = 1;
//    } else {
//        targetGroup.ut_unit = 0;
//    }
    switch (currentGroup.m_utUnit) {
    case Paramters::Group::Time:
        targetGroup.ut_unit = 1;
        break;
    case Paramters::Group::SoundPath:
        targetGroup.ut_unit = 0;
        break;
    case Paramters::Group::TruePath:
        targetGroup.ut_unit = 2;
        break;
    default:
        targetGroup.ut_unit = 2;
        break;
    }

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " m_utUnit " << currentGroup.m_utUnit
             << " ut_unit " << targetGroup.ut_unit;

    /* Sample */
    //二代数据在补偿增益开启的情况下 m_refGain 为基础增益对应离线分析的增益栏，m_gain 对应离线分析的补偿增益栏；
    //在补偿增益关闭的情况离线分析软件的增益栏为m_gain,补偿增益为0
    targetGroup.on_off_status = 0;
    targetGroup.gain          = currentGroup.m_sample.m_gain * 100.0;
    targetGroup.start         = currentGroup.m_sample.m_start;
    targetGroup.range         = currentGroup.m_sample.m_range;
    targetGroup.on_off_status = set_bit_value(targetGroup.on_off_status, 0, currentGroup.m_sample.m_refGainStatus);
    if(get_bit_value(targetGroup.on_off_status, 0)) {
        targetGroup.gainr = currentGroup.m_sample.m_refGain * 100.0;
        targetGroup.gain = (currentGroup.m_sample.m_refGain + currentGroup.m_sample.m_gain)*100;
    }
    targetGroup.point_qty     = currentGroup.m_sample.m_pointQty;

    /* Transceiver */
    targetGroup.tx_rxmode1    = currentGroup.m_transceiver.m_txRxMode;
    targetGroup.pulser_width1 = currentGroup.m_transceiver.m_pw;
    targetGroup.filter_pos1   = currentGroup.m_transceiver.m_filter;
    targetGroup.rectifier1    = currentGroup.m_transceiver.m_rectifier;
    targetGroup.on_off_status = set_bit_value(targetGroup.on_off_status, 1, currentGroup.m_transceiver.m_videoFilter);
    targetGroup.averaging1    = currentGroup.m_transceiver.m_average;
    targetGroup.on_off_status = set_bit_value(targetGroup.on_off_status, 2, currentGroup.m_focallawer.m_coupling);
    int couplingVelocity = currentSpecimen.m_LV * 10;
    couplingVelocity = couplingVelocity << 3;
    targetGroup.on_off_status = targetGroup.on_off_status | couplingVelocity;

    /* Probe */
    memset(targetProbe.Serial, 0, 20);
    memset(targetProbe.Model, 0, 20);

    strncpy(targetProbe.Serial,
            currentProbe.m_serial.toLocal8Bit().data(),
            currentProbe.m_serial.toLocal8Bit().size());
    strncpy(targetProbe.Model,
            currentProbe.m_model.toLocal8Bit().data(),
            currentProbe.m_model.toLocal8Bit().size());
    targetProbe.Frequency = currentProbe.m_freq * 1000.0;
    targetProbe.Pitch     = 0; /* TODO：UT模式，也需要用到Pitch？ */
    targetProbe.Reference_Point = 0; /* TODO: */

    targetGroup.scan_offset  = currentProbe.m_scanOffset * 1000.0;
    targetGroup.index_offset = currentProbe.m_indexOffset * 1000.0;
    if(0 == currentProbe.m_skew) {
        targetGroup.skew_pos = 0;
    } else if(90 == currentProbe.m_skew) {
        targetGroup.skew_pos = 1;
    } else if(180 == currentProbe.m_skew) {
        targetGroup.skew_pos = 2;
    } else if(270 == currentProbe.m_skew) {
        targetGroup.skew_pos = 3;
    }

    if (currentGroup.m_mode == Paramters::Group::PA) {
        targetProbe.Elem_qty = currentProbe.m_priElemQty;
        targetProbe.Pitch    = currentProbe.m_priPitch * 1000.0;
        targetProbe.A4       = currentProbe.m_secElemQty;
        targetProbe.A3       = currentProbe.m_secPitch * 1000.0;

        /* PA Scan */
        switch (currentGroup.m_focallawer.m_scanMode) {
        case Paramters::Focallawer::Linear:
            targetLawInfo.Focal_type = 1;
            break;
        case Paramters::Focallawer::Sectorial:
            targetLawInfo.Focal_type = 0;
            break;
        case Paramters::Focallawer::TFM_MODE:
            targetLawInfo.Focal_type = 2;
            break;
        default:
            targetLawInfo.Focal_type = 0;
            break;
        }
        //targetLawInfo.Focal_type      = !currentGroup.m_focallawer.m_scanMode;
        targetLawInfo.Elem_qty        = currentScan.m_priApe;
        targetLawInfo.First_tx_elem   = currentScan.m_priStartElem;

        /* 二代：0：Linear；1：Sectorial 故在赋值Focal_type时候取反
         * 一代：1：Linear；0：Sectorial         */
        if(Paramters::Focallawer::Linear == currentGroup.m_focallawer.m_scanMode) {
            /* Linear */
            targetLawInfo.Last_tx_elem = currentScan.m_priStopElem;
            targetLawInfo.Elem_step    = currentScan.m_priElemStep;
            targetLawInfo.Angle_min    = currentScan.m_refractAngle;

            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << " LLLLLLLLLLL "
                     << " Last_tx_elem " << targetLawInfo.Last_tx_elem
                     << " Elem_step " << targetLawInfo.Elem_step
                     << " first elem " << targetLawInfo.First_tx_elem
                     << " Angle_min " << targetLawInfo.Angle_min;

        } else if(Paramters::Focallawer::Sectorial == currentGroup.m_focallawer.m_scanMode) {
            /* Azimuthal */
            targetLawInfo.Angle_min   = currentScan.m_refractStartAngle * 100.0;
            targetLawInfo.Angle_max   = currentScan.m_refractStopAngle * 100.0;
            targetLawInfo.Angle_step  = currentScan.m_refractStepAngle * 100.0;

            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << " AAAAAAAAAAA "
                     << " min " << targetLawInfo.Angle_min
                     << " max " << targetLawInfo.Angle_max
                     << " step " << targetLawInfo.Angle_step;
        } else {
            targetLawInfo.First_tx_elem = 0;
            targetLawInfo.Last_tx_elem  = currentScan.m_colQty - 1;
            targetLawInfo.Elem_step     = 1;
            targetLawInfo.Angle_min     = 0;
            qWarning("%s(%s[%d]): unimplement", __FILE__, __func__, __LINE__);
        }
    }else{
        targetLawInfo.Focal_type = 0;
        targetProbe.Elem_qty = currentProbe.m_priElemQty;
        targetProbe.Pitch    = 1000.0;
        targetProbe.A4       = 1;
        targetProbe.A3       = 1000.0;
        targetLawInfo.Elem_qty        = currentScan.m_priApe;
        targetLawInfo.First_tx_elem   = currentScan.m_priStartElem;
        targetLawInfo.Angle_min   = 4000;
        targetLawInfo.Angle_max   = 4000;
        targetLawInfo.Angle_step  = 100;

    }

    /* Wedge */
    memset(targetWedge.Serial, 0, 20);
    memset(targetWedge.Model, 0, 20);

    strncpy(targetWedge.Serial,
            currentWedge.m_serial.toLocal8Bit().data(),
            currentWedge.m_serial.toLocal8Bit().size());
    strncpy(targetWedge.Model,
            currentWedge.m_model.toLocal8Bit().data(),
            currentWedge.m_model.toLocal8Bit().size());
    targetWedge.Angle             = currentWedge.m_angle * 10.0;
    /* TODO:
         * 一代默认rootAngle = 0；
         * 二代：rootAngle涉及到成像、聚焦法则？ */
    targetWedge.Velocity_PA       = currentWedge.m_velocity * 1000.0;
    targetWedge.Velocity_UT       = currentWedge.m_velocity * 1000.0;
    targetWedge.Primary_offset    = currentWedge.m_priOffset * 1000.0;
    targetWedge.Secondary_offset  = currentWedge.m_secOffset * 1000.0;
    targetWedge.Height            = currentWedge.m_fstElemHeight * 1000.0;
    targetWedge.Orientation       = currentWedge.m_orientation;
    targetWedge.Wave_type         = currentWedge.m_waveType;
    targetWedge.Ref_point         = currentWedge.m_refPoint * 1000.0;
    targetWedge.Probe_delay       = currentWedge.m_delay;
    targetGroup.wedge_delay       = currentWedge.m_delay;

    /* Specimen */
    targetGroup.part.Geometry     = currentSpecimen.m_shape;
    targetGroup.part.Material_pos = currentSpecimen.m_material;

    if(currentSpecimen.m_weldType != Paramters::Weld::NONE_TYPE) {
        targetGroup.part.symmetry = currentSpecimen.m_weld.m_isSymmetry;
        /* TODO: fill weld info */
    }

    /* TODO */
    if(Paramters::Specimen::PLANE == currentSpecimen.m_shape) {
        targetGroup.part.Thickness    = currentSpecimen.m_geometry.m_plane.m_height * 1000.0;
        targetGroup.part.Diameter     = 0;
    } else if(Paramters::Specimen::CYLINDER == currentSpecimen.m_shape) {
        targetGroup.part.Thickness    = (currentSpecimen.m_geometry.m_cylinder.m_outside -
                                         currentSpecimen.m_geometry.m_cylinder.m_inside) * 1000.0;
    } else if(Paramters::Specimen::NOZZLE == currentSpecimen.m_shape) {
        targetGroup.part.Thickness    = (currentSpecimen.m_geometry.m_nozzle.m_outside -
                                         currentSpecimen.m_geometry.m_nozzle.m_inside) * 1000.0;
    } else if(Paramters::Specimen::FILLET == currentSpecimen.m_shape) {
        if(Paramters::Fillet::WED_1 == currentSpecimen.m_geometry.m_fillet.m_probePos
                || Paramters::Fillet::WED_2 == currentSpecimen.m_geometry.m_fillet.m_probePos){
            targetGroup.part.Thickness = currentSpecimen.m_geometry.m_fillet.m_topPlane.m_height * 1000.0;
        }else{
            targetGroup.part.Thickness = currentSpecimen.m_geometry.m_fillet.m_bottomPlane.m_height * 1000.0;
        }
    }

    if(Paramters::Focallawer::Longitudinal == currentGroup.m_focallawer.m_waveType) {
         targetGroup.velocity = currentSpecimen.m_LV * 100.0;
    } else if(Paramters::Focallawer::Shear == currentGroup.m_focallawer.m_waveType){
        targetGroup.velocity = currentSpecimen.m_SV * 100.0;
    }

    /* Focus */
    targetLawInfo.Focal_point_type = currentGroup.m_focallawer.m_focusMode;
    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " focus Mode " << currentGroup.m_focallawer.m_focusMode;

    if (Paramters::Focallawer::HALF_PATH == currentGroup.m_focallawer.m_focusMode) {
        targetLawInfo.Position_start = currentFocus.m_radius * 1000.0;
    } else if (Paramters::Focallawer::TRUE_DEPTH == currentGroup.m_focallawer.m_focusMode) {
        targetLawInfo.Position_start = currentFocus.m_depth * 1000.0;
    } else if (Paramters::Focallawer::PROJECTION == currentGroup.m_focallawer.m_focusMode) {
        targetLawInfo.Offset_start = currentFocus.m_offset * 1000.0;
    } else if (Paramters::Focallawer::FOCAL_PLANE == currentGroup.m_focallawer.m_focusMode) {
        targetLawInfo.Offset_start = currentFocus.m_beginOffset * 1000.0;
        targetLawInfo.Offset_end   = currentFocus.m_endOffset * 1000.0;
        targetLawInfo.Depth_start  = currentFocus.m_beginDepth * 1000.0;
        targetLawInfo.Depth_end    = currentFocus.m_endDepth * 1000.0;
    } else if (Paramters::Focallawer::DDF == currentGroup.m_focallawer.m_focusMode) {
        qWarning("%s(%s[%d]): DDF unimplement", __FILE__, __func__, __LINE__);
    } else {
        qWarning("%s(%s[%d]): unimplement", __FILE__, __func__, __LINE__);
    }

    /* BeamsInfo */
    memset(targetGroup.beam_delay, 0, sizeof(unsigned int) * setup_MAX_GROUP_LAW_QTY);
    memset(targetGroup.field_distance, 0, sizeof(float) * setup_MAX_GROUP_LAW_QTY);
    memset(targetGroup.gain_offset, 0, sizeof(unsigned short) * setup_MAX_GROUP_LAW_QTY);

    if(Paramters::Focallawer::TFM_MODE == currentGroup.m_focallawer.m_scanMode){
        for(int i = 0; i < currentGroup.m_focallawer.m_delays.count(); ++i) {
            targetGroup.gain_offset[i] = currentGroup.m_focallawer.m_gains[i];
            targetGroup.beam_delay[i] = currentGroup.m_focallawer.m_delays[i];
        }
        int distanceQty = setup_MAX_GROUP_LAW_QTY > currentScan.m_colQty ? currentScan.m_colQty : setup_MAX_GROUP_LAW_QTY;
        float step = currentScan.m_colRes;
        float start = currentScan.m_colOffset;
        for(int i = 0; i < distanceQty; i++){
            targetGroup.field_distance[i] = i * step + start;
        }
    }else{
        for(int i = 0; i < currentGroup.m_focallawer.m_delays.count(); ++i) {
            targetGroup.gain_offset[i] = currentGroup.m_focallawer.m_gains[i];
            targetGroup.beam_delay[i] = currentGroup.m_focallawer.m_delays[i];
            targetGroup.field_distance[i] = currentGroup.m_focallawer.m_fieldDistance[i];
        }
    }

    /* Thickness */
    targetGroup.min_thickness = currentGroup.m_thickness.m_min * 1000.0;
    targetGroup.max_thickness = currentGroup.m_thickness.m_max * 1000.0;

    /* Gate */
    targetGroup.gate[0].start   = currentGroup.m_gateA.m_start;
    targetGroup.gate[0].width   = currentGroup.m_gateA.m_width;
    targetGroup.gate[0].height  = currentGroup.m_gateA.m_height;
    targetGroup.gate[0].measure = !currentGroup.m_gateA.m_measureMode;
    targetGroup.gate[0].synchro = currentGroup.m_gateA.m_synchroMode;
    targetGroup.gate[0].travel_mode = currentGroup.m_gateA.m_gateMode;

    targetGroup.gate[1].start   = currentGroup.m_gateB.m_start;
    targetGroup.gate[1].width   = currentGroup.m_gateB.m_width;
    targetGroup.gate[1].height  = currentGroup.m_gateB.m_height;
    targetGroup.gate[1].measure = !currentGroup.m_gateB.m_measureMode;
    targetGroup.gate[1].synchro = currentGroup.m_gateB.m_synchroMode;
    targetGroup.gate[1].travel_mode = currentGroup.m_gateB.m_gateMode;

    targetGroup.gate[2].start   = currentGroup.m_gateI.m_start;
    targetGroup.gate[2].width   = currentGroup.m_gateI.m_width;
    targetGroup.gate[2].height  = currentGroup.m_gateI.m_height;
    targetGroup.gate[2].measure = !currentGroup.m_gateI.m_measureMode;
    targetGroup.gate[2].synchro = currentGroup.m_gateI.m_synchroMode;
    targetGroup.gate[2].travel_mode = currentGroup.m_gateI.m_gateMode;

    Paramters::Curves &currentCurves = currentGroup.m_sizing.m_curves;
    SIZING_CURVES &targetCurves = targetGroup.SizingCurves;

    targetCurves.bApplyToAllLaws = true;
//  targetCurves.bTcgCalibrated = false;
    targetCurves.point_pos      = 0;
    targetCurves.dac_point_qty  = currentCurves.m_pointQty;
    targetCurves.curve_pos      = currentGroup.m_sizing.m_type;
    targetCurves.curve_step     = 0;
    targetCurves.ref_ampl_offset= 0/*80000*/;
    targetCurves.linear_ref_ampl= currentCurves.m_refAmp * 10.0;

    if(Paramters::Sizing::TCG == currentGroup.m_sizing.m_type) {
        /* TCG */
        qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << " TCG TCG TCG ";
        QList< QPair < double, double> > beamInfo;
        for(int i = 0; i < currentCurves.m_beams.count(); ++i) {
            targetCurves.dac_ref_ampl[i] = currentCurves.m_refAmp * 10.0;
            beamInfo = currentCurves.m_beams.at(i);
            for(int j = 0; j < beamInfo.count(); ++j) {
                targetCurves.amplitude[i][j] = currentCurves.m_refAmp / pow(10.0, beamInfo.at(j).first / 20.0) * 1000.0;
                targetCurves.position[i][j]  = beamInfo.at(j).second;
                qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << " TCG "
                         << " i " << i
                         << " j " << j
                         << " refAmp " << currentCurves.m_refAmp
                         << " first " << beamInfo.at(j).first
                         << " second " << beamInfo.at(j).second
                         << " amplitude " << targetCurves.amplitude[i][j]
                         << " position " << targetCurves.position[i][j];
            }
        }
    } else if(Paramters::Sizing::DAC == currentGroup.m_sizing.m_type) {
        /* DAC */
        qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << " DAC  DAC  DAC ";
        QList< QPair < double, double> > beamInfo;
        for(int i = 0; i < currentCurves.m_beams.count(); ++i) {
            targetCurves.dac_ref_ampl[i] = currentCurves.m_refAmp * 10.0;
            beamInfo = currentCurves.m_beams.at(i);
            for(int j = 0; j < beamInfo.count(); ++j) {
                targetCurves.amplitude[i][j]  = currentCurves.m_refAmp / pow(10.0 , beamInfo.at(j).first / 20.0) * 1000.0;
                targetCurves.position[i][j]  = beamInfo.at(j).second;
                qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << " DAC "
                         << " i " << i
                         << " j " << j
                         << " refAmp " << currentCurves.m_refAmp
                         << " first " << beamInfo.at(j).first
                         << " second " << beamInfo.at(j).second
                         << " amplitude " << targetCurves.amplitude[i][j]
                         << " position " << targetCurves.position[i][j];
            }
        }
    } else if(Paramters::Sizing::LINEAR_DAC == currentGroup.m_sizing.m_type) {
        targetCurves.mat_atten = currentCurves.m_attenuation * 1000.0;
        targetCurves.delay     = currentCurves.m_delay;
        qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << " LINEAR_DAC  LINEAR_DAC  LINEAR_DAC ";
    }
}

void Config::convert_other_to_phascan_config()
{
    DRAW_INFO_PACK &drawInfoPack = m_pDataFile->m_cDrawInfoPack;
    drawInfoPack.nGroupNum = m_global.m_groupQty;
    memset(m_pDataFile->m_cadInfo, 0, 8*sizeof(int));
    if(m_global.m_version.m_dxfExist){
        for(uint i = 0; i < m_global.m_groupQty; i++){
            m_pDataFile->m_cadInfo[i] = 10;
            int caddataSize = m_global.m_version.m_dxfData.size();
            QString g_filePath = QCoreApplication::applicationDirPath() + QString("/temp/%1.dxf").arg(i);
            QFile file(g_filePath);
            file.open(QIODevice::ReadWrite | QIODevice::Truncate);
            QDataStream writer(&file);
            writer.writeRawData(m_global.m_version.m_dxfData.data(), caddataSize);
            file.close();
        }
    }

    /* Scanner */
    drawInfoPack.nScanStart        = m_global.m_scanner.m_scanAxis.m_start * 1000.0;
    drawInfoPack.nScanEnd          = m_global.m_scanner.m_scanAxis.m_end * 1000.0;
    drawInfoPack.nScanResolution   = m_global.m_scanner.m_scanAxis.m_resolution * 1000.0;
    drawInfoPack.nInspecStart      = m_global.m_scanner.m_indexAxis.m_start * 1000.0;
    drawInfoPack.nInspecEnd        = m_global.m_scanner.m_indexAxis.m_end * 1000.0;
    drawInfoPack.nInspecResolution = m_global.m_scanner.m_indexAxis.m_resolution * 1000.0;
    drawInfoPack.nEncodeType       = m_global.m_scanner.m_scanAxis.m_driving;

    /* 当前一代数据文件未保存编码器详细信息，仅分辨率有保存 */
    GROUP_INFO &targetGroup = m_pDataFile->m_cGroupInfo[0];
    if(Paramters::Axis::ENCODER_X == m_global.m_scanner.m_scanAxis.m_driving) {
        targetGroup.cursors_info[0].resolution = m_global.m_scanner.m_encoderX.m_resolution;
    } else if(Paramters::Axis::ENCODER_Y == m_global.m_scanner.m_scanAxis.m_driving) {
        targetGroup.cursors_info[0].resolution = m_global.m_scanner.m_encoderY.m_resolution;
    } else {
        targetGroup.cursors_info[0].resolution = 48;
    }

    /* Global */
    for(int i = 0; i < m_pDataFile->m_cDrawInfoPack.nGroupNum; ++i) {
        m_pDataFile->m_cGroupInfo[i].prf1 = m_global.m_scanner.m_rate * 10;
    }  
}

bool Config::is_phascan_ii_file(QFile &file)
{
    qint64 totalSize = file.size();
    qint64 configLen = 0;
    qint64 dataMarkLen = 0;
    qint64 beamDataLen = 0;

    file.read((char *)&configLen, sizeof(configLen));
    qDebug()<<"configLen"<<configLen<<"totalSize"<<totalSize;
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

    if(totalLen > totalSize) {
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

int Config::getPhascanVersion()
{
//    QString version = m_global.m_version.m_phascanVersion;
//    QStringList list1 = version.split('.');
//    int buffV[3];
//    for(int i = 0; i < list1.size(); i++){
//        QString buffs = list1.at(i);
//        buffV[i] = buffs.toInt();
//    }
//    int buff;
//    if( buffV[0] > 1){
//        buff = 5;
//    }else if( buffV[0] == 1 && buffV[1] > 3){
//        return 5;
//    }else if( buffV[0] == 1 && buffV[1] == 3 && buffV[2] >= 8){
//        return 5;
//    }else{
//        return 4;
//    }
    if(m_global.m_version.m_dxfExist){
        return 7;
    }else{
        return 5;
    }
}

char *Config::data_mark()
{
    return m_dataMark.data();
}

uint Config::data_mark_length()
{
    return m_dataMark.count();
}
