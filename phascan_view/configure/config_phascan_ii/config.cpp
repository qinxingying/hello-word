#include "config.h"
#include "msgpack/msgpack.h"
#include <QDebug>
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

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << "";

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

    QFile tmp("mercury.cfg");
    if (!tmp.open(QIODevice::WriteOnly|QIODevice::Truncate)) {
        qWarning("%s(%s)[%d]", __FILE__, __func__, __LINE__);
        set_is_phascan_ii(false);
        return false;
    }

    tmp.write(file.read(len));
    tmp.close();
    QSettings src("mercury.cfg", QSettings::defaultFormat());
    QSettings dst;
    dst.clear();
    QStringList keys = src.allKeys();
    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << "";
    foreach (QString key, keys) {
        dst.setValue(key, src.value(key));
        qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                 << " key " << key
                 << " value " << src.value(key);
    }
    QFile::remove("mercury.cfg");

    m_pDataFile->m_cDrawInfoPack.nGroupNum = dst.value("GroupQty").toUInt();
    for(int i = 0; i < m_pDataFile->m_cDrawInfoPack.nGroupNum; ++i) {
        unpack_group(i);
        convert_to_phascan_config(i);
    }

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " start angle " << m_currentGroup.focallawer.scan.refractStartAngle
             << " step angle " << m_currentGroup.focallawer.scan.refractStepAngle
             << " stop angle " << m_currentGroup.focallawer.scan.refractStopAngle
             << " refractAngle " << m_currentGroup.focallawer.scan.refractAngle
             << " priApe " << m_currentGroup.focallawer.scan.priApe
             << " priStartElem " << m_currentGroup.focallawer.scan.priStartElem
             << " priElemStep " << m_currentGroup.focallawer.scan.priElemStep
             << " priStopElem " << m_currentGroup.focallawer.scan.priStopElem;

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

    QSettings::beginGroup(QString("Group%1").arg(groupId));

    m_currentGroup.mode   = static_cast<GroupMode> (value("Mode", DEFAULT_GROUP_MODE).toInt());
    m_currentGroup.utUnit = static_cast<UtUnit> (value("UtUnit", DEFAULT_UT_UNIT).toInt());

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " mode " << m_currentGroup.mode
             << " ut unit " << m_currentGroup.utUnit;

    unpack_display();
    unpack_focallawer();

    unpack_gate(GateA);
    unpack_gate(GateB);
    unpack_gate(GateI);

    unpack_probe();
    unpack_sample();
    unpack_specimen();
    unpack_wedge();
    unpack_transceiver();
    unpack_curves();
    unpack_thickness();
    unpack_cursor();

    /* 以下为全局，非组内配置 */
    unpack_scanner();
    unpack_global_transceiver();

    endGroup();
}

void Config::unpack_display()
{
    beginGroup("Display");
    int language = value("Language", 0).toInt();
    endGroup();
}

void Config::unpack_sample()
{
    beginGroup("Sample");
    m_currentGroup.sample.gain          = value("Gain", DEFAULT_SAMPLE_GAIN).toDouble();
    m_currentGroup.sample.start         = value("Start", DEFAULT_SAMPLE_START).toDouble();
    m_currentGroup.sample.maxGain       = value("MaxGain", DEFAULT_MAX_GAIN).toFloat();
    m_currentGroup.sample.refGainStatus = value("RefGainStatus", DEFAULT_REF_GAIN_STATUS).toUInt();
    if(m_currentGroup.sample.refGainStatus) {
        m_currentGroup.sample.refGain = value("RefGain", DEFAULT_REF_GAIN).toUInt();
    }
    m_currentGroup.sample.pointQty      = value("PointQty", DEFAULT_POINT_QTY).toInt();
    m_currentGroup.sample.autoCalcPointQty= value("AutoCalcPointQty", DEFAULT_AUTO_CAL_POINT_QTY).toBool();

    endGroup();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " gain " << m_currentGroup.sample.gain
             << " refGainStatus " << m_currentGroup.sample.refGainStatus
             << " ref gain " << m_currentGroup.sample.refGain
             << " start " << m_currentGroup.sample.start
             << " maxGain " << m_currentGroup.sample.maxGain
             << " point_qty " << m_currentGroup.sample.pointQty
             << " autoCalcPointQty " << m_currentGroup.sample.autoCalcPointQty;

}

void Config::unpack_transceiver()
{
    beginGroup("Transceiver");

    m_currentGroup.transceiver.average  = static_cast<Averaging> (value("Average", DEFAULT_TRANSCEIVER_AVERAGE).toUInt());
    m_currentGroup.transceiver.filter     = value("Filter", DEFAULT_TRANSCEIVER_FILTER).toUInt();
    m_currentGroup.transceiver.txRxMode   = static_cast<TxRxMode> (value("Mode", DEFAULT_TRANSCEIVER_TXRXMODE).toUInt());
    m_currentGroup.transceiver.pw         = value("PW", DEFAULT_TRANSCEIVER_PW).toFloat();
    m_currentGroup.transceiver.pulser     = value("Pulser", DEFAULT_TRANSCEIVER_PULSER).toUInt();
    m_currentGroup.transceiver.receiver   = value("Receiver", DEFAULT_TRANSCEIVER_RECEIVER).toUInt();
    m_currentGroup.transceiver.rectifier  = static_cast<Rectifier> (value("Rectifier", DEFAULT_TRANSCEIVER_RECTIFIER).toUInt());
    m_currentGroup.transceiver.videoFilter= value("VideoFilter", DEFAULT_TRANSCEIVER_VIDEO_FILTER).toBool();

    endGroup();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " tx_rx mode " << m_currentGroup.transceiver.txRxMode
             << " pulser width " << m_currentGroup.transceiver.pw
             << " filter " << m_currentGroup.transceiver.filter
             << " rectifier " << m_currentGroup.transceiver.rectifier
             << " video filter " << m_currentGroup.transceiver.videoFilter
             << " averaging " << m_currentGroup.transceiver.average
             << " pulser " << m_currentGroup.transceiver.pulser
             << " receiver " << m_currentGroup.transceiver.receiver;
}

void Config::unpack_focallawer()
{
    beginGroup("Focallawer");
    m_currentGroup.focallawer.focusMode = static_cast<FocusMode> (value("FocusMode", DEFAULT_FOCUS_MODE).toUInt());
    m_currentGroup.focallawer.scanMode  = static_cast<ScanMode> (value("ScanMode", DEFAULT_SCAN_MODE).toUInt());
    m_currentGroup.focallawer.waveType = static_cast<WaveType> (value("WaveType", DEFAULT_WAVE_TYPE).toInt());

        qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                 << " wave type " << m_currentGroup.focallawer.waveType
                 << " focus mode " << m_currentGroup.focallawer.focusMode
                 << " scan mode " << m_currentGroup.focallawer.scanMode;

    unpack_scan();

    unpack_focus();

    unpack_beams_info();

    endGroup();
}

void Config::unpack_scan()
{
    beginGroup("Scan");
    S_Scan &scan = m_currentGroup.focallawer.scan;

    scan.refractStartAngle = value("RefractStartAngle", DEFAULT_REFRACT_START_ANGLE).toDouble();
    scan.refractStepAngle  = value("RefractStepAngle", DEFAULT_REFRACT_STEP_ANGLE).toDouble();
    scan.refractStopAngle  = value("RefractStopAngle", DEFAULT_REFRACT_STOP_ANGLE).toDouble();
    scan.refractAngle      = value("RefractAngle", REFRACT_ANGLE).toDouble();

    scan.priApe            = value("PriApe", DEFAULT_PRIAPE).toUInt();
    scan.priStartElem      = value("PriStartElem", DEFAULT_PRI_START_ELEM).toUInt();
    scan.priElemStep      = value("PriElemStep", DEFAULT_PRI_ELEM_STEP).toUInt();
    scan.priStopElem      = value("PriStopElem", DEFAULT_PRI_STOP_ELEM).toUInt();

    endGroup();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " start angle " << scan.refractStartAngle
             << " step angle " << scan.refractStepAngle
             << " stop angle " << scan.refractStopAngle
             << " refractAngle " << scan.refractAngle
             << " priApe " << scan.priApe
             << " priStartElem " << scan.priStartElem
             << " priElemStep " << scan.priElemStep
             << " priStopElem " << scan.priStopElem;
}

void Config::unpack_probe()
{
    beginGroup("Probe");

    S_Probe &probe = m_currentGroup.probe;

    probe.arrayMode     = static_cast<ArrayMode> (value("ArrayMode", DEFAULT_ARRAY_MODE).toInt());
    probe.freq          = value("Freq", DEFAULT_PROBE_FREQ).toDouble();
    probe.model         = value("Model", DEFAULT_PROBE_MODEL).toString();
    probe.serial        = value("Serial", DEFAULT_PROBE_SERIAL).toString();
    probe.priElemQty    = value("PriElemQty", DEFAULT_ELEMQTY).toInt();
    probe.secElemQty    = value("SecElemQty", DEFAULT_ELEMQTY).toInt();
    probe.priPitch      = value("PriPitch", DEFAULT_PRI_PITCH).toFloat();
    probe.secPitch      = value("SecPitch", DEFAULT_SEC_PITCH).toFloat();
    probe.refPoint      = value("RefPoint", DEFAULT_REFPOINT).toFloat();
    probe.scanOffset    = value("ScanOffset", DEFAULT_OFFSET).toDouble();
    probe.indexOffset   = value("IndexOffset", DEFAULT_OFFSET).toDouble();
    probe.type          = static_cast<ProbeType> (value("Type", DEFAULT_PROBE_TYPE).toInt());
    probe.skew          = value("Skew", DEFAULT_SKEW).toInt();

    endGroup();

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

void Config::unpack_wedge()
{
    S_Wedge &wedge = m_currentGroup.wedge;
    beginGroup("Wedge");
    wedge.serial             = value("Serial", DEFAULT_WEDGE_SERIAL).toString();
    wedge.model              = value("Model", DEFAULT_WEDGE_MODEL).toString();
    wedge.angle              = value("Angle", DEFAULT_WEDGE_ANGLE).toFloat();
    wedge.fstElemHeight      = value("FstElemHeight", DEFAULT_WEDGE_FIRST_ELEM_HEIGHT).toFloat();
    wedge.length             = value("Length", DEFAULT_WEDGE_LENGTH).toFloat();
    wedge.width              = value("Width", DEFAULT_WEDGE_WIDTH).toFloat();
    wedge.height             = value("Height", DEFAULT_WEDGE_HEIGHT).toFloat();
    wedge.velocity           = value("Velocity", DEFAULT_WEDGE_VELOCITY).toUInt();
    wedge.waveType           = static_cast<WaveType> (value("WaveType", DEFAULT_WEDGE_WAVE_TYPE).toUInt());
    wedge.priOffset          = value("PriOffset").toFloat();
    wedge.secOffset          = value("SecOffset").toFloat();
    wedge.orientation        = static_cast<Orientation> (value("Orientation", DEFAULT_WEDGE_ORIENTATION).toUInt());
    wedge.refPoint           = value("RefPoint", DEFAULT_WEDGE_REF_POINT).toUInt();
    /* 待定？？暂在配置信息未发现此key */
    wedge.rootAngle          = value("RootAngle", DEFAULT_WEDGE_ROOT_ANGLE).toFloat();
    wedge.delay              = value("Delay", DEFAULT_WEDGE_DELAY).toInt();

    endGroup();

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
             << " wave type " << wedge.waveType;
}

void Config::unpack_specimen()
{
    S_Specimen &specimen = m_currentGroup.specimen;
    beginGroup("Specimen");
    specimen.shape      = static_cast<Shape> (value("Shape", DEFAULT_SHAPE).toUInt());
    specimen.LV         = value("LV", DEFAULT_LV).toDouble();
    specimen.SV         = value("SV", DEFAULT_SV).toDouble();
    specimen.material   = static_cast<Material> (value("Material", DEFAULT_MATERIAL).toUInt());
    specimen.density    = value("Density", DEFAULT_DENSITY).toDouble();
    specimen.weldType   = static_cast<WeldType> (value("WeldType", DEFAULT_WELD_TYPE).toUInt());
    specimen.weld.type = specimen.weldType;

    if(PLANE == specimen.shape) {
        specimen.height0  = value("0/Height", DEFAULT_PLANE_HEIGHT).toDouble();
        specimen.width0   = value("0/Width", DEFAULT_PLANE_WIDTH).toDouble();
        specimen.length0  = value("0/Length", DEFAULT_PLANE_LENGTH).toDouble();
    } else if(CYLINDER == specimen.shape) {
        specimen.probePosition = static_cast<ProbePosition> (value("0/ProbePosition",
                                                                   DEFAULT_CYLINDER_PROBE_POS).toUInt());
        specimen.inside0  = value("0/Inside", DEFAULT_CYLINDER_INSIDE).toDouble();
        specimen.outside0 = value("0/Outside", DEFAULT_CYLINDER_OUTSIDE).toDouble();
        specimen.angle0   = value("0/Angle", DEFAULT_CYLINDER_ANGLE).toDouble();
        specimen.length0  = value("0/Length", DEFAULT_CYLINDER_LENGHT).toDouble();
    } else if(NOZZLE == specimen.shape) {
        specimen.angle0     = value("0/Angle", DEFAULT_NOZZLE_0_ANGLE).toDouble();
        specimen.inside0    = value("0/Inside", DEFAULT_NOZZLE_0_INSIDE).toDouble();
        specimen.outside0   = value("0/Outside", DEFAULT_NOZZLE_0_OUTSIDE).toDouble();

        specimen.length1    = value("1/Length", DEFAULT_NOZZLE_1_LENGTH).toDouble();
        specimen.inside1    = value("1/Inside", DEFAULT_NOZZLE_1_INSIDE).toDouble();
        specimen.outside1   = value("1/Outside", DEFAULT_NOZZLE_1_OUTSIDE).toDouble();

        specimen.length2    = value("2/Length", DEFAULT_NOZZLE_2_LENGTH).toDouble();
        specimen.inside2    = value("2/Inside", DEFAULT_NOZZLE_2_INSIDE).toDouble();
        specimen.outside2   = value("2/Outside", DEFAULT_NOZZLE_2_OUTSIDE).toDouble();
        specimen.angle2     = value("2/Angle", DEFAULT_NOZZLE_2_LENGTH).toDouble();
    } else {
        qWarning("%s(%s[%d]): unimplement", __FILE__, __func__, __LINE__);
    }

    unpack_weld();

    endGroup();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " shape " << specimen.shape
             << " logitudinalVelocity " << specimen.LV
             << " shearVelocity " << specimen.SV
             << " material " << specimen.material
             << " density " << specimen.density
             << " weldType " << specimen.weldType;
}

void Config::unpack_weld()
{
    S_Weld &weld = m_currentGroup.specimen.weld;

    if(m_currentGroup.specimen.weldType == NONE_TYPE) {
        return;
    }

    beginGroup("Weld");

    weld.orientation = static_cast<WeldOrientation> (value("Orientation", DEFAULT_WELD_ORIENTATION).toUInt());
    weld.isSymmetry  = value("Symmetry", DEFAULT_WELD_SYMMETRY).toBool();

    if(I == weld.type) {
        weld.w0 = value("0/W", DEFAULT_I_W_0).toDouble();
    } else if(V == weld.type) {
        weld.w0 = value("0/W", DEFAULT_V_W_0).toDouble();
        weld.w1 = value("1/W", DEFAULT_V_W_1).toDouble();
        weld.h0  = value("0/H", DEFAULT_V_H_0).toDouble();
    } else if(U == weld.type) {
        weld.w0 = value("0/W", DEFAULT_U_W_0).toDouble();
        weld.w1 = value("1/W", DEFAULT_U_W_1).toDouble();
        weld.h0  = value("0/H", DEFAULT_U_H_0).toDouble();
        weld.r0  = value("0/R", DEFAULT_U_R_0).toDouble();
    }else if(VY == weld.type || VV == weld.type) {
        weld.w0 = value("0/W", DEFAULT_VY_W_0).toDouble();
        weld.w1 = value("1/W", DEFAULT_VY_W_1).toDouble();
        weld.w2 = value("2/W", DEFAULT_VY_W_2).toDouble();
        weld.h0 = value("0/H", DEFAULT_VY_H_0).toDouble();
        weld.h1 = value("1/H", DEFAULT_VY_W_1).toDouble();
    } else if(UU == weld.type) {
        weld.w0 = value("0/W", DEFAULT_UU_W_0).toDouble();
        weld.w1 = value("1/W", DEFAULT_UU_W_1).toDouble();
        weld.w2 = value("2/W", DEFAULT_UU_W_2).toDouble();
        weld.h0 = value("0/H", DEFAULT_UU_H_0).toDouble();
        weld.h1 = value("1/H", DEFAULT_UU_H_1).toDouble();
        weld.r0 = value("0/R", DEFAULT_UU_R_0).toDouble();
        weld.r1 = value("1/R", DEFAULT_UU_R_1).toDouble();
    } else if(UV == weld.type) {
        weld.w0 = value("0/W", DEFAULT_UV_W_0).toDouble();
        weld.w1 = value("1/W", DEFAULT_UV_W_1).toDouble();
        weld.w2 = value("2/W", DEFAULT_UV_W_2).toDouble();
        weld.h0 = value("0/H", DEFAULT_UV_H_0).toDouble();
        weld.h1 = value("1/H", DEFAULT_UV_H_1).toDouble();
        weld.r0 = value("0/R", DEFAULT_UV_R_0).toDouble();
    } else {
        qWarning("%s(%s[%d]): unimplement", __FILE__, __func__, __LINE__);
    }

    endGroup();
}

void Config::unpack_focus()
{
    S_Focus &focus = m_currentGroup.focallawer.focus;
    beginGroup("Focus");
    focus.radius      = value("Radius", DEFAULT_END_OFFSET).toFloat();
    focus.depth       = value("Depth", DEFAULT_END_OFFSET).toFloat();
    focus.offset      = value("Offset", DEFAULT_END_OFFSET).toFloat();
    focus.beginOffset = value("BeginOffset", DEFAULT_BEGIN_OFFSET).toFloat();
    focus.endOffset   = value("EndOffset", DEFAULT_END_OFFSET).toFloat();
    focus.beginDepth  = value("BeginDepth", DEFAULT_BEGIN_OFFSET).toFloat();
    focus.endDepth    = value("EndDepth", DEFAULT_END_OFFSET).toFloat();
    focus.focusMode   = m_currentGroup.focallawer.focusMode;
    endGroup();
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

void Config::unpack_cursor()
{

}

void Config::unpack_gate(GateType gateType)
{
    beginGroup(QString("Gate%1").arg(gateType));
    S_Gate &gate = m_currentGroup.gateA;
    if(GateB == gateType) {
        gate = m_currentGroup.gateB;
    } else if(GateI == gateType) {
        gate = m_currentGroup.gateI;
    }

    gate.measureMode = static_cast<MeasureMode> (value("MeasureMode", DEFAULT_MEASURE_MODE).toInt());
    gate.gateMode    = static_cast<GateMode> (value("Mode", DEFAULT_GATE_MODE).toInt());
    gate.synchroMode = static_cast<SynchroMode> (value("SynchroMode", DEFAULT_SYNCHRO_MODE).toInt());
    gate.visible     = value("Visible", DEFAULT_GATE_VISIBLE).toBool();
    gate.start       = value("Start", DEFAULT_GATE_START).toFloat();
    gate.width       = value("Width", DEFAULT_GATE_WIDTH).toFloat();;
    gate.height      = value("Height", DEFAULT_GATE_HEIGHT).toInt();
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
    endGroup();
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
    unpack_axis(0);
    unpack_axis(1);

    unpack_encoder(0);
    unpack_encoder(1);

//    m_scanner.scanMode = static_cast<ScanMode> (map["Mode"].toInt());
//    m_scanner.speed    = map["Speed"].toInt();

//    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//             << " scanMode " << m_scanner.scanMode
//             << " speed " << m_scanner.speed;

//    unpack_axis(map["ScanAxis"].toMap(), m_scanner.scanAxis);
//    unpack_axis(map["IndexAxis"].toMap(), m_scanner.indexAxis);
//    unpack_encoder(map["EncoderX"].toMap(), m_scanner.encoderX);
//    unpack_encoder(map["EncoderY"].toMap(), m_scanner.encoderY);
}

void Config::unpack_axis(int index)
{
    S_Axis &axis = m_scanner.scanAxis;

    axis.driving    = TIMER;
    axis.start      = 0;
    axis.end        = 800;
    axis.resolution = 1;

//    axis.driving    = static_cast<Driving> (map["Driving"].toInt());
//    axis.start      = map["Start"].toDouble();
//    axis.end        = map["End"].toDouble();
//    axis.resolution = map["Resolution"].toDouble();

//    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//             << " driving " << axis.driving
//             << " start " << axis.start
//             << " end " << axis.end
//             << " resolution " << axis.resolution;
}

void Config::unpack_encoder(int index)
{
    S_Encoder &encoder = m_scanner.encoderX;

    encoder.status      = ON;
    encoder.polarity    = NORMAL;
    encoder.mode        = QUAD;
    encoder.resolution  = 48;
    encoder.origin      = 0;

//    encoder.status      = static_cast<Status> (map["Status"].toInt());
//    encoder.polarity    = static_cast<Polarity> (map["Polarity"].toInt());
//    encoder.mode        = static_cast<EncoderMode> (map["Mode"].toInt());
//    encoder.resolution  = map["Resolution"].toDouble();
//    encoder.origin      = map["Origin"].toDouble();

//    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//             << " status " << encoder.status
//             << " polarity " << encoder.polarity
//             << " mode " << encoder.mode
//             << " resolution " << encoder.resolution
//             << " origin " << encoder.origin;
}

void Config::unpack_global()
{
//    unpack_global_transceiver(map["Transceiver"].toMap());
//    unpack_alarm(map["Alarm"].toMap());
}

void Config::unpack_global_transceiver()
{
    S_GlobalTransceiver &transceiver = m_global.transceiver;
    transceiver.paVoltage      = V50;
    transceiver.utVoltage      = V50;
    transceiver.prfMode        = USER_DEF;
    transceiver.acquisitionRate= 2;


//    S_GlobalTransceiver &transceiver = m_global.transceiver;
//    transceiver.paVoltage      = static_cast<Voltage> (map["PAVoltage"].toInt());
//    transceiver.utVoltage      = static_cast<Voltage> (map["UTVoltage"].toInt());
//    transceiver.prfMode        = static_cast<PrfMode> (map["PRFMode"].toInt());
//    transceiver.acquisitionRate= map["AcquisitionRate"].toInt();

//    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
//             << " PA Voltage " << transceiver.paVoltage
//             << " UT Voltage " << transceiver.utVoltage
//             << " PRF Mode " << transceiver.prfMode
//             << " rate " << transceiver.acquisitionRate;
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
    targetGroup.range         = currentGroup.sample.maxGain;
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
    //    targetWedge.Ref_point         = ?;
    targetWedge.Probe_delay       = currentWedge.delay;

    /* Specimen */
    targetGroup.part.Geometry     = currentSpecimen.shape;
    targetGroup.part.Material_pos = currentSpecimen.material;
    targetGroup.part.Thickness    = currentSpecimen.height0 * 1000.0;

    if(currentSpecimen.weldType != NONE_TYPE) {
        targetGroup.part.symmetry = currentSpecimen.weld.isSymmetry;
        /* TODO: fill weld info */
    }
    /* TODO */
    if(PLANE == currentSpecimen.shape) {

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
    /* Scanner */
    DRAW_INFO_PACK &drawInfoPack = m_pDataFile->m_cDrawInfoPack;

    drawInfoPack.nScanStart = m_scanner.scanAxis.start * 1000.0;
    drawInfoPack.nScanEnd = m_scanner.scanAxis.end * 1000.0;
    drawInfoPack.nScanResolution = m_scanner.scanAxis.resolution * 1000.0;

    if(ENCODER_X == m_scanner.scanAxis.driving) {
        drawInfoPack.nInspecResolution = m_scanner.encoderX.origin;
        drawInfoPack.nEncodeType = 1;
    } else if(ENCODER_Y == m_scanner.scanAxis.driving) {
        drawInfoPack.nInspecResolution = m_scanner.encoderY.origin;
        drawInfoPack.nEncodeType = 1;
    } else if(TIMER == m_scanner.scanAxis.driving){
        drawInfoPack.nEncodeType = 0;
    } else {
        qWarning("%s(%s[%d]): unimplement other driving.", __FILE__, __func__, __LINE__);
    }

    /* Global */
    for(int i = 0; i < m_pDataFile->m_cDrawInfoPack.nGroupNum; ++i) {
        m_pDataFile->m_cGroupInfo[i].prf1 = m_global.transceiver.acquisitionRate * 10;
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

    if(totalLen != totalSize) {
        qWarning("%s(%s[%d]): cal Len is not equal totalSzie.", __FILE__, __func__, __LINE__);
        return false;
    }

    file.seek(0);
    return true;
}

void Config::set_is_phascan_ii(bool flag)
{
    m_isPhascanII = flag;
}

bool Config::is_phascan_ii()
{
    return m_isPhascanII;
}
