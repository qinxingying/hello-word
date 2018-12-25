#include "config.h"
#include "msgpack/msgpack.h"
#include <QFile>
#include <QDebug>
#include "../DopplerDataFileOperateor.h"

DopplerDataFileOperateor *Config::m_pDataFile = NULL;
QByteArray Config::m_dataMark = QByteArray();
QByteArray Config::m_dataSource = QByteArray();
Config::S_Groups Config::m_groups[setup_MAX_GROUP_QTY];
Config::S_Scanner Config::m_scanner;
Config::S_Global Config::m_global;
int Config::s_alarmCount = 3;
bool Config::m_isPhascanII = false;

bool Config::save(const QString &filename, bool saveData)
{
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate)) {
        qWarning("Open %s failed", filename.toUtf8().data());
        return false;
    }

    save_config(file);

    if (saveData) {
        save_data(file);
    }

    file.waitForBytesWritten(-1);
    file.close();

    return true;
}

bool Config::load(const QString &filename, DopplerDataFileOperateor *dataFile)
{   
    m_pDataFile = dataFile;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("%s[%d]:Open %s failed",__func__, __LINE__,
                 filename.toUtf8().data());
        m_isPhascanII = false;
        return false;
    }

    if(!is_phascan_ii_file(file)) {
        qWarning("%s[%d]: %s is not phascan ii file!",__func__, __LINE__,
                 filename.toUtf8().data());
        m_isPhascanII = false;
        return false;
    }

    int totalSize = file.size();
    int len = 0;

    file.read((char *)&len, sizeof(len));
    if (len <= 0 || len > totalSize) {
        qWarning("%s(%s[%d]): Read Configuare Data failed", __FILE__, __func__, __LINE__);
        m_isPhascanII = false;
        return false;
    }

    QByteArray cnf = file.read(len);
    QVariantMap map = MsgPack::unpack(cnf).toMap();
    if (map.isEmpty() || map.value("Groups").isNull()) {
        qWarning("%s(%s[%d]): no configuration", __FILE__, __func__, __LINE__);
        m_isPhascanII = false;
        return false;
    }

    unpack_groups(map["Groups"].toList());
    unpack_scanner(map["Scanner"].toMap());
    unpack_global(map["Global"].toMap());

    convert_other_to_phascan_config();

    if (file.atEnd()) {
        m_isPhascanII = true;
        return true;
    }

    int frameQty = 0;
    file.read((char *)&frameQty, sizeof(int));
    m_dataMark.resize(frameQty);
    if (frameQty <= 0 || frameQty != file.read(m_dataMark.data(), frameQty)) {
        qWarning("%s(%s[%d]): Read Mark Failed", __FILE__, __func__, __LINE__);
        m_isPhascanII = false;
        return false;
    }

    memset(m_pDataFile->m_cDrawInfoPack.bScanMark, 0, sizeof(unsigned char) * 1024 * 256);
    memcpy(m_pDataFile->m_cDrawInfoPack.bScanMark, m_dataMark.data(), frameQty);

    file.read((char *)&len, sizeof(len));
    m_dataSource.resize(len);
    if (len <= 0 || len != file.read(m_dataSource.data(), len) ) {
        qWarning("%s(%s[%d]): Read Data(%d) failed", __FILE__, __func__, __LINE__, len);
        m_isPhascanII = false;
        return false;
    }

    m_pDataFile->m_pBeamData = (unsigned char *)m_dataSource.data();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << " Read Phascan II Data Success!!";
    m_isPhascanII = true;
    return true;
}

Config::Config()
{

}

QVariantList Config::pack_groups()
{
    QVariantList list;
    return list;
}

void Config::unpack_groups(const QVariantList &list)
{
    int groupId = 0;
    foreach (QVariant v, list) {
        unpack_group(v.toMap(), groupId);
        convert_to_phascan_config(groupId);
        ++groupId;
    }

    m_pDataFile->m_cDrawInfoPack.nGroupNum = groupId;
}

QVariantMap Config::pack_group()
{
    QVariantMap map;
    return map;
}

void Config::unpack_group(const QVariantMap &map, int groupId)
{
    S_Groups &currentGroup = m_groups[groupId];

    currentGroup.mode   = static_cast<GroupMode> (map["Mode"].toInt());
    currentGroup.utUnit = static_cast<UtUnit> (map["UtUnit"].toInt());

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " mode " << currentGroup.mode
             << " ut unit " << currentGroup.utUnit;

    unpack_sample(map["Sample"].toMap(), currentGroup);
    unpack_transceiver(map["Transceiver"].toMap(), currentGroup);
    unpack_focallawer(map["Focallawer"].toMap(), currentGroup);
    unpack_thickness(map["Thickness"].toMap(), currentGroup);
    unpack_gate(map["GateA"].toMap(), currentGroup.gateA);
    unpack_gate(map["GateB"].toMap(), currentGroup.gateB);
    unpack_gate(map["GateI"].toMap(), currentGroup.gateI);
    unpack_curves(map["Curves"].toMap(), currentGroup.curves);
}

QVariantMap Config::pack_sample()
{
    QVariantMap map;
    return map;
}

void Config::unpack_sample(const QVariantMap &map, S_Groups &group)
{
    group.sample.gain          = map["Gain"].toDouble();
    group.sample.start         = map["Start"].toDouble();
    group.sample.range         = map["Range"].toFloat();
    group.sample.refGainEnabled= map["RefGainEnabled"].toBool();
    if(group.sample.refGainEnabled) {
        group.sample.refGain = map["RefGain"].toDouble();
    }
    group.sample.pointQty      = map["PointQty"].toInt();
    group.sample.autoPointQty  = map["AutoPointQty"].toBool();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " gain " << group.sample.gain
             << " refGainEnabled " << group.sample.refGainEnabled
             << " ref gain " << group.sample.refGain
             << " start " << group.sample.start
             << " range " << group.sample.range
             << " point_qty " << group.sample.pointQty
             << " autoPointQty " << group.sample.autoPointQty;
}

QVariantMap Config::pack_transceiver()
{
    QVariantMap map;
    return map;
}

void Config::unpack_transceiver(const QVariantMap &map, S_Groups &group)
{
    group.transceiver.txRxMode   = static_cast<TxRxMode> (map["Mode"].toInt());
    group.transceiver.pw         = map["PW"].toFloat();
    group.transceiver.filter     = map["Filter"].toInt();
    group.transceiver.rectifier  = static_cast<Rectifier> (map["Rectifier"].toInt());
    group.transceiver.videoFilter= map["VideoFilter"].toBool();
    group.transceiver.averaging   = static_cast<Averaging> (map["Averaging"].toInt());

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " tx_rx mode " << group.transceiver.txRxMode
             << " pulser width " << group.transceiver.pw
             << " filter " << group.transceiver.filter
             << " rectifier " << group.transceiver.rectifier
             << " video filter " << group.transceiver.videoFilter
             << " averaging " << group.transceiver.averaging;
}

QVariantMap Config::pack_focallawer()
{
    QVariantMap map;
    return map;
}

void Config::unpack_focallawer(const QVariantMap &map, S_Groups &group)
{
    unpack_probe(map["Probe"].toMap(), group);

    unpack_wedge(map["Wedge"].toMap(), group);

    group.focallawer.waveType = static_cast<WaveType> (map["WaveType"].toInt());

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " wave type " << group.focallawer.waveType;

    unpack_specimen(map["Specimen"].toMap(), group);

    unpack_focus(map["Focus"].toMap(), group);

    unpack_beams_info(map["BeamsInfo"].toMap(), group);
}

QVariantMap Config::pack_probe()
{
    QVariantMap map;
    return map;
}

void Config::unpack_probe(const QVariantMap &map, S_Groups &group)
{
    S_Probe &probe = group.focallawer.probe;
    probe.isPA         = map["PA"].toBool();
    probe.serial       = map["Serial"].toString();
    probe.model        = map["Model"].toString();
    probe.type         = static_cast<ProbeType> (map["Type"].toInt());
    probe.frequency    = map["Freq"].toDouble();
    probe.pulserIndex  = map["PulserIndex"].toInt();
    probe.receiverIndex= map["ReceiverIndex"].toInt();
    probe.scanOffset   = map["ScanOffset"].toDouble();
    probe.indexOffset  = map["IndexOffset"].toDouble();
    probe.skew         = map["Skew"].toInt();

    if(group.focallawer.probe.isPA) {
        probe.arrayMode             = static_cast<ArrayMode> (map["ArrayMode"].toInt());
        probe.primaryElementQty     = map["PrimaryElementQty"].toInt();
        probe.secondaryElementQty   = map["SecondaryElementQty"].toInt();
        probe.primaryPitch          = map["PrimaryPitch"].toFloat();
        probe.secondaryPitch        = map["SecondaryPitch"].toFloat();

        unpack_pa_probe_scan(map["Scan"].toMap(), group);
    }

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " is pa " << probe.isPA
             << " Serial " << probe.serial
             << " Model " << probe.model
             << " Type " << probe.type
             << " Frequency " << probe.frequency
             << " pulserIndex " << probe.pulserIndex
             << " receiverIndex " << probe.receiverIndex
             << " scanOffset " << probe.scanOffset
             << " indexOffset " << probe.indexOffset
             << " skew " << probe.skew
             << "\n[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " arrayMode " << probe.arrayMode
             << " primaryElementQty " << probe.primaryElementQty
             << " secondaryElementQty " << probe.secondaryElementQty
             << " primaryPitch " << probe.primaryPitch
             << " secondaryPitch " << probe.secondaryPitch;
}

QVariantMap Config::pack_pa_probe_scan()
{
    QVariantMap map;
    return map;
}

void Config::unpack_pa_probe_scan(const QVariantMap &map, S_Groups &group)
{
    S_PA_Scan &paScan = group.focallawer.probe.paScan;
    paScan.scanMode = static_cast<ScanMode> (map["Mode"].toInt());
    paScan.aperture = map["Aperture"].toInt();
    paScan.firstElement = map["FirstElement"].toInt();

    if(Linear == paScan.scanMode) {
        paScan.lastElement = map["LastElement"].toInt();
        paScan.elementStep = map["ElementStep"].toInt();
        paScan.angle       = map["Angle"].toFloat();
    } else if(Sectorial == paScan.scanMode) {
        paScan.firstAngle  = map["FirstAngle"].toFloat();
        paScan.lastAngle   = map["LastAngle"].toFloat();
        paScan.angleStep   = map["AngleStep"].toFloat();
    }

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " scanMode " << paScan.scanMode
             << " aperture " << paScan.aperture
             << " firstElement " << paScan.firstElement
             << " lastElement " << paScan.lastElement
             << " elementStep " << paScan.elementStep
             << " angle " << paScan.angle
             << " firsAngle " << paScan.firstAngle
             << " lastAngle " << paScan.lastAngle
             << " angleStep " << paScan.angleStep;
}

QVariantMap Config::pack_wedge()
{
    QVariantMap map;
    return map;
}

void Config::unpack_wedge(const QVariantMap &map, S_Groups &group)
{
    S_Wedge &wedge = group.focallawer.wedge;
    wedge.serial             = map["Serial"].toString();
    wedge.model              = map["Model"].toString();
    wedge.angle              = map["Angle"].toFloat();
    wedge.rootAngle          = map["RootAngle"].toFloat();
    wedge.velocity           = map["Velocity"].toUInt();
    wedge.primaryOffset      = map["PrimaryOffset"].toFloat();
    wedge.secondaryOffset    = map["SecondaryOffset"].toFloat();
    wedge.firstElementHeight = map["FirstElementHeight"].toFloat();
    wedge.length             = map["Length"].toFloat();
    wedge.width              = map["Width"].toFloat();
    wedge.height             = map["Height"].toFloat();
    wedge.orientation        = static_cast<Orientation> (map["Orientation"].toInt());
    wedge.delay              = map["Delay"].toInt();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " serial " << wedge.serial
             << " model " << wedge.model
             << " angle " << wedge.angle
             << " rootAngle " << wedge.rootAngle
             << " velocity " << wedge.velocity
             << " primaryOffset " << wedge.primaryOffset
             << " secondaryOffset " << wedge.secondaryOffset
             << " firstElementHeight " << wedge.firstElementHeight
             << " length " << wedge.length
             << " width " << wedge.width
             << " height " << wedge.height
             << " orientation " << wedge.orientation
             << " delay " << wedge.delay;
}

QVariantMap Config::pack_specimen()
{
    QVariantMap map;
    return map;
}

void Config::unpack_specimen(const QVariantMap &map, S_Groups &group)
{
    S_Specimen &specimen = group.focallawer.specimen;

    specimen.shape               = static_cast<Shape> (map["Shape"].toInt());
    specimen.logitudinalVelocity = map["LogitudinalVelocity"].toInt();
    specimen.shearVelocity       = map["ShearVelocity"].toInt();
    specimen.length              = map["Length"].toFloat();
    specimen.material            = static_cast<Material> (map["Material"].toInt());
    specimen.thickness           = map["Thickness"].toDouble();

    if(PLANE == specimen.shape) {
        specimen.height = map["Height"].toFloat();
        specimen.width  = map["Width"].toFloat();
    } else if(CYLINDER == specimen.shape) {
        specimen.probePosition = static_cast<ProbePosition> (map["ProbePosition"].toInt());
        specimen.inside = map["Inside"].toFloat();
        specimen.outside= map["Outside"].toFloat();
        specimen.probePosition = static_cast<ProbePosition> (map["ProbePosition"].toInt());
        specimen.angle  = map["Angle"].toDouble();
    }

    unpack_weld(map["Weld"].toMap(), group);

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " shape " << specimen.shape
             << " logitudinalVelocity " << specimen.logitudinalVelocity
             << " shearVelocity " << specimen.shearVelocity
             << " length " << specimen.length
             << " material " << specimen.material
             << " thickness " << specimen.thickness
             << " height " << specimen.height
             << " width " << specimen.width
             << " probePosition " << specimen.probePosition
             << " inside " << specimen.inside
             << " outside " << specimen.outside;
}

QVariantMap Config::pack_weld()
{
    QVariantMap map;
    return map;
}

void Config::unpack_weld(const QVariantMap &map, S_Groups &group)
{
    S_Weld &weld = group.focallawer.specimen.weld;

    if(!map["Enable"].toBool()) {
        return;
    }

    weld.type        = static_cast<WeldType> (map["Type"].toInt());
    weld.orientation = static_cast<WeldOrientation> (map["Orientation"].toInt());
    weld.isSymmetry  = map["Symmetry"].toBool();

    if(I == weld.type) {
        weld.w = map["W"].toReal();
    } else if(V == weld.type) {
        weld.w1 = map["W1"].toReal();
        weld.w2 = map["W2"].toReal();
        weld.h  = map["H"].toReal();
    } else if(U == weld.type) {
        weld.w1 = map["W1"].toReal();
        weld.w2 = map["W2"].toReal();
        weld.h  = map["H"].toReal();
        weld.r  = map["R"].toReal();
    }else if(VY == weld.type || VV == weld.type) {
        weld.w1 = map["W1"].toReal();
        weld.w2 = map["W2"].toReal();
        weld.w3 = map["W3"].toReal();
        weld.h1 = map["H1"].toReal();
        weld.h2 = map["H2"].toReal();
    } else if(UU == weld.type) {
        weld.w1 = map["W1"].toReal();
        weld.w2 = map["W2"].toReal();
        weld.w3 = map["W3"].toReal();
        weld.h1 = map["H1"].toReal();
        weld.h2 = map["H2"].toReal();
        weld.r1 = map["R1"].toReal();
        weld.r2 = map["R2"].toReal();
    } else if(UV == weld.type) {
        weld.w1 = map["W1"].toReal();
        weld.w2 = map["W2"].toReal();
        weld.w3 = map["W3"].toReal();
        weld.h1 = map["H1"].toReal();
        weld.h2 = map["H2"].toReal();
        weld.r  = map["R"].toReal();
    } else {
        qWarning("%s(%s[%d]): unimplement", __FILE__, __func__, __LINE__);
    }
}

QVariantMap Config::pack_focus()
{
    QVariantMap map;
    return map;
}

void Config::unpack_focus(const QVariantMap &map, S_Groups &group)
{
    S_Focus &focus = group.focallawer.focus;
    focus.focusMode = static_cast<FocusMode> (map["Mode"].toInt());
    if(FOCUS_HALF_PATH == focus.focusMode) {
        focus.radius = map["Radius"].toFloat();
    } else if(FOCUS_TRUE_DEPTH == focus.focusMode) {
        focus.depth = map["Depth"].toFloat();
    } else if(FOCUS_PROJECTION == focus.focusMode) {
        focus.offset = map["Offset"].toFloat();
    } else if(FOCUS_FOCAL_PLANE == focus.focusMode) {
        focus.beginOffset = map["BeginOffset"].toFloat();
        focus.endOffset   = map["EndOffset"].toFloat();
        focus.beginDepth  = map["BeginDepth"].toFloat();
        focus.endDepth    = map["EndDepth"].toFloat();
    } else if(FOCUS_DDF == focus.focusMode) {
        qWarning("%s(%s[%d]): DDF unimplement", __FILE__, __func__, __LINE__);
    } else {
        qWarning("%s(%s[%d]): unimplement", __FILE__, __func__, __LINE__);
    }

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " radius " << focus.radius
             << " depth " << focus.depth
             << " offset " << focus.offset
             << " beginOffset " << focus.beginOffset
             << " endOffset " << focus.endOffset
             << " beginDepth " << focus.beginDepth
             << " endDepth " << focus.endDepth;
}

QVariantMap Config::pack_beams_info()
{
    QVariantMap map;
    return map;
}

void Config::unpack_beams_info(const QVariantMap &map, S_Groups &group)
{
    S_BeamsInfo &beamsInfo = group.focallawer.beamsInfo;
    QVariantMap tmp = map["Delay"].toMap();
    if(tmp.count() <= setup_MAX_GROUP_LAW_QTY) {
        for(int i = 0; i < tmp.count(); ++i) {
            beamsInfo.delay[i] = tmp[QString::number(i)].toFloat();
            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                     << " delay " << beamsInfo.delay[i];
        }
    }

    tmp.clear();
    tmp = map["FieldDistance"].toMap();
    if(tmp.count() <= setup_MAX_GROUP_LAW_QTY) {
        for(int i = 0; i < tmp.count(); ++i) {
            beamsInfo.fieldDistance[i] = tmp[QString::number(i)].toFloat();
            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                     << " fieldDistance " << beamsInfo.fieldDistance[i];
        }
    }
}

QVariantMap Config::pack_thickness()
{
    QVariantMap map;
    return map;
}

void Config::unpack_thickness(const QVariantMap &map, S_Groups &group)
{
    group.thickness.min = map["Min"].toDouble();
    group.thickness.max = map["Max"].toDouble();
    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " thickness min " << group.thickness.min
             << " thickness max " << group.thickness.max;
}

QVariantMap Config::pack_gate()
{
    QVariantMap map;
    return map;
}

void Config::unpack_gate(const QVariantMap &map, S_Gate &gate)
{
    gate.measureMode = static_cast<MeasureMode> (map["MeasureMode"].toInt());
    gate.gateMode    = static_cast<GateMode> (map["Mode"].toInt());
    gate.synchroMode = static_cast<SynchroMode> (map["SynchroMode"].toInt());
    gate.visible     = map["Visible"].toBool();
    gate.start       = map["Start"].toDouble();
    gate.width       = map["Width"].toDouble();
    gate.height      = map["Height"].toDouble();
    gate.color       = map["Color"].toUInt();

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

QVariantMap Config::pack_curves()
{
    QVariantMap map;
    return map;
}

void Config::unpack_curves(const QVariantMap &map, S_Curves &curves)
{
    curves.type = static_cast<SizingType> (map["Type"].toInt());
    if(SizingNONE == curves.type) {
        return;
    }

    curves.compliance = static_cast<Compliance>(map["Compliance"].toInt());
    curves.gain       = map["Gain"].toDouble();
    curves.refAmplitude = map["RefAmplitude"].toDouble();
    curves.curveQty = map["CurveQty"].toInt();
    curves.currentCurve = map["CurrentCurve"].toInt();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " compliance " << curves.compliance
             << " gain " << curves.gain
             << " refAmplitude " << curves.refAmplitude
             << " curveQty " << curves.curveQty
             << " currentCurve " << curves.currentCurve;

    unpack_curve_offset(map["CurveOffset"].toMap(), curves);

    if(DAC == curves.type) {
        unpack_dac(map["DAC"].toMap(), curves);
    } else if(LINEAR_DAC == curves.type) {
        unpack_linear_dac(map["LINEAR_DAC"].toMap(), curves);
    } else if(TCG == curves.type) {
        unpack_tcg(map["TCG"].toMap(), curves);
    }
}

QVariantMap Config::pack_dac()
{
    QVariantMap map;
    return map;
}

void Config::unpack_dac(const QVariantMap &map, S_Curves &curves)
{
    S_DAC &dac = curves.dac;

    dac.curveType       = static_cast<CurveType> (map["CurveType"].toInt());
    dac.pointCount      = map["PointCount"].toInt();
    dac.currentPoint    = map["CurrentPoint"].toInt();
    dac.currentBeamIndex= map["CurrentBeamIndex"].toInt();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " curveType " << dac.curveType
             << " pointCount " << dac.pointCount
             << " currentPoint " << dac.currentPoint
             << " currentBeamIndex " << dac.currentBeamIndex;

    QVariantMap positionMap = map["Position"].toMap();
    QVariantMap amplitudeMap = map["Amplitude"].toMap();
    if(positionMap.size() <= setup_DAC_POINT_QTY) {
        for(int i = 0; i < positionMap.count(); ++i) {
            dac.position[i] = positionMap[QString::number(i)].toDouble();
            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                     << " i " << i
                     << " position " << dac.position[i];
        }
    }

    if(amplitudeMap.size() <= setup_DAC_POINT_QTY) {
        for(int i = 0; i < amplitudeMap.count(); ++i) {
            dac.amplitude[i] = amplitudeMap[QString::number(i)].toDouble();
            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                     << " i " << i
                     << " amplitude " << dac.position[i];
        }
    }
}

QVariantMap Config::pack_linear_dac()
{
    QVariantMap map;
    return map;
}

void Config::unpack_linear_dac(const QVariantMap &map, S_Curves &curves)
{
    curves.linearDAC.matAttenuation = map["MatAttenuation"].toDouble();
    curves.linearDAC.delay          = map["Delay"].toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " matAttenuation " << curves.linearDAC.matAttenuation
             << " delay " << curves.linearDAC.delay;
}

QVariantMap Config::pack_tcg()
{
    QVariantMap map;
    return map;
}

void Config::unpack_tcg(const QVariantMap &map, S_Curves &curves)
{
    S_TCG &tcg = curves.tcg;

    tcg.pointCount        = map["PointCount"].toInt();
    tcg.currentPointIndex = map["CurrentPointIndex"].toInt();
    tcg.currentBeamIndex  = map["CurrentBeamIndex"].toInt();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " pointCount " << tcg.pointCount
             << " currentPointIndex " << tcg.currentPointIndex
             << " currentBeamIndex " << tcg.currentBeamIndex;

    QVariantMap positionMap = map["Position"].toMap();
    QVariantMap gainMap = map["GainMap"].toMap();

    if(positionMap.count() <= setup_DAC_POINT_QTY) {
        for(int i = 0; i < positionMap.count(); ++i) {
            tcg.position[i] = positionMap[QString::number(i)].toDouble();
            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                     << " i " << i
                     << " position " << tcg.position[i];
        }
    }

    if(gainMap.count() <= setup_DAC_POINT_QTY) {
        for(int i = 0; i < gainMap.count(); ++i) {
            tcg.gain[i] = gainMap[QString::number(i)].toDouble();
            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                     << " i " << i
                     << " gain " << tcg.gain[i];
        }
    }

}

QVariantMap Config::pack_curve_offset()
{
    QVariantMap map;
    return map;
}

void Config::unpack_curve_offset(const QVariantMap &map, S_Curves &curves)
{
    if(map.count() <= setup_DAC_POINT_QTY) {
        for(int i = 0; i < map.count(); ++i) {
            curves.curveOffset.offset[i] = map[QString::number(i)].toDouble();
            qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
                     << " i " << i << " offset " << curves.curveOffset.offset[i];
        }
    }
}

QVariantMap Config::pack_scanner()
{
    QVariantMap map;
    return map;
}

void Config::unpack_scanner(const QVariantMap &map)
{
    m_scanner.scanMode = static_cast<ScanMode> (map["Mode"].toInt());
    m_scanner.speed    = map["Speed"].toInt();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " scanMode " << m_scanner.scanMode
             << " speed " << m_scanner.speed;

    unpack_axis(map["ScanAxis"].toMap(), m_scanner.scanAxis);
    unpack_axis(map["IndexAxis"].toMap(), m_scanner.indexAxis);
    unpack_encoder(map["EncoderX"].toMap(), m_scanner.encoderX);
    unpack_encoder(map["EncoderY"].toMap(), m_scanner.encoderY);
}

QVariantMap Config::pack_axis()
{
    QVariantMap map;
    return map;
}

void Config::unpack_axis(const QVariantMap &map, S_Axis &axis)
{
    axis.driving    = static_cast<Driving> (map["Driving"].toInt());
    axis.start      = map["Start"].toDouble();
    axis.end        = map["End"].toDouble();
    axis.resolution = map["Resolution"].toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " driving " << axis.driving
             << " start " << axis.start
             << " end " << axis.end
             << " resolution " << axis.resolution;
}

QVariantMap Config::pack_encoder()
{
    QVariantMap map;
    return map;
}

void Config::unpack_encoder(const QVariantMap &map, S_Encoder &encoder)
{
    encoder.status      = static_cast<Status> (map["Status"].toInt());
    encoder.polarity    = static_cast<Polarity> (map["Polarity"].toInt());
    encoder.mode        = static_cast<EncoderMode> (map["Mode"].toInt());
    encoder.resolution  = map["Resolution"].toDouble();
    encoder.origin      = map["Origin"].toDouble();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " status " << encoder.status
             << " polarity " << encoder.polarity
             << " mode " << encoder.mode
             << " resolution " << encoder.resolution
             << " origin " << encoder.origin;
}

QVariantMap Config::pack_global()
{
    QVariantMap map;
    map["Transceiver"] = pack_global_transceiver();
    map["Alarm"]       = pack_alarm();
    return map;
}

void Config::unpack_global(const QVariantMap &map)
{
    unpack_global_transceiver(map["Transceiver"].toMap());
    unpack_alarm(map["Alarm"].toMap());
}

QVariantMap Config::pack_global_transceiver()
{
    QVariantMap map;
    return map;
}

void Config::unpack_global_transceiver(const QVariantMap &map)
{
    S_GlobalTransceiver &transceiver = m_global.transceiver;
    transceiver.paVoltage      = static_cast<Voltage> (map["PAVoltage"].toInt());
    transceiver.utVoltage      = static_cast<Voltage> (map["UTVoltage"].toInt());
    transceiver.prfMode        = static_cast<PrfMode> (map["PRFMode"].toInt());
    transceiver.acquisitionRate= map["AcquisitionRate"].toInt();

    qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << ""
             << " PA Voltage " << transceiver.paVoltage
             << " UT Voltage " << transceiver.utVoltage
             << " PRF Mode " << transceiver.prfMode
             << " rate " << transceiver.acquisitionRate;
}

QVariantMap Config::pack_alarm()
{
    QVariantMap map;
    return map;
}

void Config::unpack_alarm(const QVariantMap &map)
{
    for(int i = 0; i < s_alarmCount; ++i) {
        unpack_one_alarm_setting(i, map[QString::number(i)].toMap());
    }

    m_global.sound = static_cast<SoundMode> (map["Sound"].toInt());
}

QVariantMap Config::pack_one_alarm_setting(int index)
{
    QVariantMap map;
    return map;
}

void Config::unpack_one_alarm_setting(int index, const QVariantMap &map)
{
    S_Alarm &alarm = m_global.alarm[index];
    alarm.enable = map["Enable"].toBool();
    if(!alarm.enable){
        return;
    }

    alarm.logicGroup     = static_cast<quint16> (map["Group"].toUInt());
    alarm.firstCondition = static_cast<Condition> (map["FirstCondition"].toInt());
    alarm.secondCondition= static_cast<Condition> (map["SecondCondition"].toInt());
    alarm.opt            = static_cast<Operator> (map["Operator"].toInt());
    alarm.count          = map["Count"].toUInt();
    alarm.delay          = map["Delay"].toInt();
    alarm.holdTime       = map["HoldTime"].toInt();
}

void Config::save_config(QFile &file)
{
    QVariantMap map;
    map["Groups"]   = pack_groups();
    map["Scanner"]  = pack_scanner();
    map["Global"]   = pack_global();

    QByteArray data = MsgPack::pack(map);
    int len = data.size();
    file.write((char *)&len, sizeof(len));
    file.write(data);
}

void Config::save_data(QFile &file)
{
    int len = m_dataMark.size();
    file.write((char *)&len, sizeof(len));
    file.write(m_dataMark);

    len = m_dataSource.size();
    file.write((char *)&len, sizeof(len));
    file.write(m_dataSource);
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
    S_Probe &currentProbe = currentGroup.focallawer.probe;
    S_Wedge &currentWedge = currentGroup.focallawer.wedge;
    S_Focus &currentFocus = currentGroup.focallawer.focus;
    S_Specimen &currentSpecimen = currentGroup.focallawer.specimen;

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
    targetGroup.on_off_status = set_bit_value(targetGroup.on_off_status, 0, currentGroup.sample.refGainEnabled);
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
    targetGroup.averaging1    = currentGroup.transceiver.averaging;

    /* Probe */
    memset(targetProbe.Serial, 0, 20);
    memset(targetProbe.Model, 0, 20);

    strncpy(targetProbe.Serial,
            currentProbe.serial.toLocal8Bit().data(),
            currentProbe.serial.toLocal8Bit().size());
    strncpy(targetProbe.Model,
            currentProbe.model.toLocal8Bit().data(),
            currentProbe.model.toLocal8Bit().size());
    targetProbe.Frequency = currentProbe.frequency * 1000.0;
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

    if (currentProbe.isPA) {
        targetProbe.Elem_qty  = currentProbe.primaryElementQty;
        targetProbe.Pitch     = currentProbe.primaryPitch * 1000.0;

        /* PA Scan */
        targetLawInfo.Focal_type      = !currentProbe.paScan.scanMode;
        targetLawInfo.Elem_qty        = currentProbe.paScan.aperture;
        targetLawInfo.First_tx_elem   = currentProbe.paScan.firstElement;

        /* 二代：0：Linear；1：Sectorial 故在赋值Focal_type时候取反
         * 一代：1：Linear；0：Sectorial         */
        if(Linear == currentProbe.paScan.scanMode) {
            /* Linear */
            targetLawInfo.Last_tx_elem = currentProbe.paScan.lastElement;
            targetLawInfo.Elem_step    = currentProbe.paScan.elementStep;
            targetLawInfo.Angle_min    = currentProbe.paScan.angle;
        } else if(Sectorial == currentProbe.paScan.scanMode) {
            /* Azimuthal */
            targetLawInfo.Angle_min   = currentProbe.paScan.firstAngle * 100.0;
            targetLawInfo.Angle_max   = currentProbe.paScan.lastAngle * 100.0;
            targetLawInfo.Angle_step  = currentProbe.paScan.angleStep * 100.0;
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
    targetWedge.Primary_offset    = currentWedge.primaryOffset * 1000.0;
    targetWedge.Secondary_offset  = currentWedge.secondaryOffset * 1000.0;
    targetWedge.Height            = currentWedge.firstElementHeight * 1000.0;
    targetWedge.Orientation       = currentWedge.orientation;
    //    targetWedge.Ref_point         = ?;
    targetWedge.Probe_delay       = currentWedge.delay;

    targetGroup.wedge.Wave_type = currentGroup.focallawer.waveType;

    /* Specimen */
    targetGroup.part.Geometry     = currentSpecimen.shape;
    targetGroup.part.Material_pos = currentSpecimen.material;
    targetGroup.part.Thickness    = currentSpecimen.thickness * 1000.0;

    if(currentSpecimen.weld.enable) {
        targetGroup.part.symmetry = currentSpecimen.weld.isSymmetry;
        /* TODO: fill weld info */
    }

    if(PLANE == currentSpecimen.shape) {

    } else if(CYLINDER == currentSpecimen.shape) {

    }

    if(Longitudinal == currentGroup.focallawer.waveType) {
         targetGroup.velocity = currentSpecimen.logitudinalVelocity * 100.0;
    } else if(Shear == currentGroup.focallawer.waveType){
        targetGroup.velocity = currentSpecimen.shearVelocity * 100.0;
    }

    /* Focus */
    targetLawInfo.Focal_point_type = currentFocus.focusMode;
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
    int totalSize = file.size();
    int configLen = 0;
    int dataMarkLen = 0;
    int beamDataLen = 0;

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

    int totalLen = configLen + dataMarkLen + beamDataLen + sizeof(int) * 3;

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
