#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <QVariantList>
#include <QFile>
#include "../DopplerConfigure.h"

class DopplerDataFileOperateor;

class Config
{
public:
    static bool save(const QString &filename, bool saveData = false);
    static bool load(const QString &filename, DopplerDataFileOperateor *dataFile);

    static void set_is_phascan_ii(bool flag);
    static bool is_phascan_ii();

    enum FocalPointMode {
        HALF_PATH,  /* 半声程 */
        TRUE_DEPTH, /* 真实深度 */
        PROJECTION, /* 投影 */
        FOCAL_PLANE,/* 任意面 */
        DDF         /* 动态聚焦 */
    };

    enum GroupMode {
        UT,
        PA,
        UT1,
        UT2
    };

    enum UtUnit {
        Time,       /* 时间 */
        SoundPath,  /* 声程 */
        TruePath    /* 真实深度 */
    };

    struct S_Sample {
        double gain;
        bool refGainEnabled;
        double refGain;
        double start;
        double range;
        int pointQty;
        bool autoPointQty;
    };

    enum TxRxMode {
        PE,
        PC,
        TT,
        TOFD
    };

    enum Rectifier {
        RF,
        POSITIVE_HW,
        NEGATIVE_HW,
        FULL_WAVE
    };

    enum Averaging {
        AVERAGING_1,
        AVERAGING_2,
        AVERAGING_4,
        AVERAGING_8,
        AVERAGING_16
    };

    struct S_Transceiver {
        TxRxMode txRxMode;
        float pw;
        int filter;
        Rectifier rectifier;
        bool videoFilter;
        Averaging averaging;
    };

    /**
     * @brief The Type enum 探头类型
     */
    enum ProbeType {
        CONTACT,    /* 直接接触式类型 */
        DELAY,      /* 延迟块式 */
        IMMERSION,  /* 水浸式 */
        ANGLE_BEAM, /* 角度声速类型 */
        DUAL,       /* 双晶探头，UT专有 */
        UT_TOFD     /* Tofd探头，UT专有 */
    };

    enum ArrayMode {
        CURVED,         /* 曲型 */
        DUAL_LINEAR,    /* 双线性，一发一收 */
        DUAL_MATRIX,    /* 双矩阵，一发一收 */
        LINEAR,         /* 线性，自发自收 */
        MATRIX          /* 矩阵，自发自收 */
    };

    enum ScanMode {
        Linear,     /* 线性扫查 */
        Sectorial   /* 扇性扫查 */
    };

    struct S_PA_Scan {
        ScanMode scanMode;
        int aperture;
        int firstElement;
        /* UT */
        int lastElement;
        int elementStep;
        float angle;
        /* PA */
        float firstAngle;
        float lastAngle;
        float angleStep;
    };

    struct S_Probe {
        bool isPA;
        QString serial;
        QString model;
        ProbeType type;
        double frequency;
        int pulserIndex;
        int receiverIndex;
        double scanOffset;
        double indexOffset;
        int skew;
        /* PA */
        ArrayMode arrayMode;
        int primaryElementQty;
        int secondaryElementQty;
        float primaryPitch;
        float secondaryPitch;
        S_PA_Scan paScan;
    };

    enum Orientation {
        Reversal,
        Normal
    };

    struct S_Wedge {
        QString serial;
        QString model;
        float angle;
        float rootAngle;
        unsigned int velocity;
        float primaryOffset;
        float secondaryOffset;
        float firstElementHeight;
        float length;
        float width;
        float height;
        Orientation orientation;
        int delay;
    };

    enum Shape {
        PLANE,
        CYLINDER,
        NOZZLE,
        FILLET
    };

    enum ProbePosition {
        CID,
        COD
    };

    enum Material {
        ALUMINUM,
        STEEL_COMMON,
        STEEL_STAINLESS,
        BRASS,
        COPPER,
        IRON,
        LEAD,
        NYLON,
        SILVER,
        GOLD,
        ZINC,
        TITANIUM,
        TIN,
        EPOXY_RESIN,
        ICE,
        NICKEL,
        PLEXIGLASS,
        POLYSTYRENE,
        ORCELAIN,
        PVC,
        QUARTZ_GLASS,
        RUBBER_VULCANIZED,
        TEFLON,
        WATER
    };

    enum WeldType {
        I,
        V,
        U,
        VY,
        VV,
        UU,
        UV
    };

    enum WeldOrientation {
        AXIAL,
        CIRC
    };

    struct S_Weld {
        bool enable;
        WeldType type;
        bool isSymmetry;
        WeldOrientation orientation;
        qreal w;
        qreal h;
        qreal r;
        qreal w1;
        qreal w2;
        qreal w3;
        qreal h1;
        qreal h2;
        qreal r1;
        qreal r2;
    };

    struct S_Specimen {
        Shape shape;
        int logitudinalVelocity;
        int shearVelocity;
        S_Weld weld;
        Material material;
        double thickness;
        float length; /* PLANE & CYLINDER共有属性 */
        /* PLANE */
        float height;
        float width;
        /* CYLINDER */
        ProbePosition probePosition;
        float inside;
        float outside;
        double angle;
    };

    enum FocusMode {
        FOCUS_HALF_PATH,  /* 半声程 */
        FOCUS_TRUE_DEPTH, /* 真实深度 */
        FOCUS_PROJECTION, /* 投影 */
        FOCUS_FOCAL_PLANE,/* 任意面 */
        FOCUS_DDF         /* 动态聚焦 */
    };

    struct S_Focus {
        FocusMode focusMode;
        /* FOCUS_HALF_PATH */
        float radius;
        /* FOCUS_TRUE_DEPTH */
        float depth;
        /* FOCUS_PROJECTION */
        float offset;
        /* FOCUS_FOCAL_PLANE */
        float beginOffset;
        float endOffset;
        float beginDepth;
        float endDepth;
    };

    enum WaveType {
        Longitudinal,
        Shear
    };

    struct S_BeamsInfo {
        float delay[setup_MAX_GROUP_LAW_QTY];
        float fieldDistance[setup_MAX_GROUP_LAW_QTY];
    };

    struct S_Focallawer {
        S_Probe probe;
        S_Wedge wedge;
        WaveType waveType;
        S_Specimen specimen;
        S_Focus focus;
        S_BeamsInfo beamsInfo;
    };

    struct S_Thickness {
        double min;
        double max;
    };

    /**
     * @brief The MeasureMode enum  闸门测量模式
     */
    enum MeasureMode {
        EDGE,
        PEAK
    };

    /**
     * @brief The SynchroMode enum  闸门同步模式
     */
    enum SynchroMode {
        SYNCHRO_PULSER,
        SYNCHRO_I,
        SYNCHRO_A,
        SYNCHRO_B,
    };

    enum GateMode {
        DEPTH,
        SOUND_PATH
    };

    struct S_Gate {
        MeasureMode measureMode;
        GateMode gateMode;
        SynchroMode synchroMode;
        bool visible;
        double start;
        double width;
        double height;
        unsigned color;
    };

    enum SizingType {
        SizingNONE,
        DAC,
        LINEAR_DAC,
        TCG
    };

    enum Compliance {
        CUSTOM,
        JIC,
        ASME
    };

    struct S_CurveOffset {
        double offset[setup_DAC_POINT_QTY];
    };

    enum CurveType {
        STRAIGHT,
        LOGARITHMIC,
        POLYNOMIAL
    };

    struct S_DAC {
        CurveType curveType;
        bool applyAllBeams; /* 二代默认应用到所有beam？？  */
        int pointCount;
        double position[setup_DAC_POINT_QTY];
        double amplitude[setup_DAC_POINT_QTY];
        int currentPoint;
        int currentBeamIndex;
    };

    struct S_LinearDAC {
        double matAttenuation;
        double delay;
    };

    struct S_TCG {
        int currentPointIndex;
        int currentBeamIndex;
        int pointCount;
        double position[setup_DAC_POINT_QTY];
        double gain[setup_DAC_POINT_QTY];
    };

    struct S_Curves {
        SizingType type;
        Compliance compliance;
        double gain;
        double refAmplitude;
        int curveQty;
        int currentCurve;
        S_CurveOffset curveOffset;
        S_DAC dac;
        S_LinearDAC linearDAC;
        S_TCG tcg;
    };

    struct S_Groups{
        GroupMode mode;
        UtUnit utUnit;
        S_Sample sample;
        S_Transceiver transceiver;
        S_Focallawer focallawer;
        S_Thickness thickness;
        S_Gate gateA;
        S_Gate gateB;
        S_Gate gateI;
        S_Curves curves;
    };

    enum Driving {
        TIMER,
        ENCODER_X,
        ENCODER_Y,
        NONE
    };

    struct S_Axis {
        Driving driving;
        double start;
        double end;
        double resolution;
    };

    enum EncoderMode {
        DOWN,
        UP,
        QUAD
    };

    enum Status {
        OFF,
        ON
    };

    enum Polarity {
        NORMAL,
        INVERSE
    };

    struct S_Encoder {
        Status status;
        Polarity polarity;
        EncoderMode mode;
        double resolution;
        double origin;
    };

    struct S_Scanner {
        ScanMode scanMode;
        int speed;
        S_Axis scanAxis;
        S_Axis indexAxis;
        S_Encoder encoderX;
        S_Encoder encoderY;
    };

    enum Voltage {
        V50     = 50,
        V100    = 100,
        V200    = 200,
        V400    = 400
    };

    enum PrfMode {
        MAX,
        MAX_HALF,
        OPTIMUM,
        USER_DEF
    };

    struct S_GlobalTransceiver {
        Voltage paVoltage;
        Voltage utVoltage;
        PrfMode prfMode;
        int acquisitionRate;
    };

    /**
     * @brief The Condition enum    报警条件类型
     */
    enum Condition {
        CONDITION_NONE,
        CONDITION_GATE_A        = 0b0001,
        CONDITION_GATE_B        = 0b0010,
        CONDITION_GATE_I        = 0b0011,
        CONDITION_NOT_GATE_A    = 0b0100,
        CONDITION_NOT_GATE_B    = 0b0101,
        CONDITION_NOT_GATE_I    = 0b0110,
        CONDITION_MAX_THICKNESS = 0b0111,
        CONDITION_MIN_THICKNESS = 0b1000
    };

    /**
     * @brief The SoundMode enum    蜂鸣器工作频率
     */
    enum SoundMode {
        SOUND_OFF   = 0b000,
        SOUND_300HZ = 0b001,
        SOUND_600HZ = 0b010,
        SOUND_1000HZ= 0b011,
        SOUND_5000HZ= 0b100,
    };

    /**
     * @brief The Operator enum 操作类型
     */
    enum Operator {
        AND,
        OR
    };

    struct  S_Alarm {
        bool enable;
        quint16 logicGroup;
        Condition firstCondition;
        Condition secondCondition;
        Operator opt;
        unsigned int count;
        int delay;
        int holdTime;
    };

    struct S_Global {
        S_GlobalTransceiver transceiver;
        S_Alarm alarm[3];
        SoundMode sound;
    };

protected:
    Config();

    static QVariantList pack_groups();
    static void unpack_groups(const QVariantList &list);

    static QVariantMap pack_group();
    static void unpack_group(const QVariantMap &map,int groupId);

    static QVariantMap pack_sample();
    static void unpack_sample(const QVariantMap &map, S_Groups &group);

    static QVariantMap pack_transceiver();
    static void unpack_transceiver(const QVariantMap &map, S_Groups &group);

    static QVariantMap pack_focallawer();
    static void unpack_focallawer(const QVariantMap &map, S_Groups &group);

    static QVariantMap pack_probe();
    static void unpack_probe(const QVariantMap &map, S_Groups &group);

    static QVariantMap pack_pa_probe_scan();
    static void unpack_pa_probe_scan(const QVariantMap &map, S_Groups &group);

    static QVariantMap pack_wedge();
    static void unpack_wedge(const QVariantMap &map, S_Groups &group);

    static QVariantMap pack_specimen();
    static void unpack_specimen(const QVariantMap &map, S_Groups &group);

    static QVariantMap pack_weld();
    static void unpack_weld(const QVariantMap &map, S_Groups &group);

    static QVariantMap pack_focus();
    static void unpack_focus(const QVariantMap &map, S_Groups &group);

    static QVariantMap pack_beams_info();
    static void unpack_beams_info(const QVariantMap &map, S_Groups &group);

    static QVariantMap pack_thickness();
    static void unpack_thickness(const QVariantMap &map, S_Groups &group);

    static QVariantMap pack_gate();
    static void unpack_gate(const QVariantMap &map, S_Gate &gate);

    static QVariantMap pack_curves();
    static void unpack_curves(const QVariantMap &map, S_Curves &curves);

    static QVariantMap pack_dac();
    static void unpack_dac(const QVariantMap &map, S_Curves &curves);

    static QVariantMap pack_linear_dac();
    static void unpack_linear_dac(const QVariantMap &map, S_Curves &curves);

    static QVariantMap pack_tcg();
    static void unpack_tcg(const QVariantMap &map, S_Curves &curves);

    static QVariantMap pack_curve_offset();
    static void unpack_curve_offset(const QVariantMap &map, S_Curves &curves);

    static QVariantMap pack_scanner();
    static void unpack_scanner(const QVariantMap &map);

    static QVariantMap pack_axis();
    static void unpack_axis(const QVariantMap &map, S_Axis &axis);

    static QVariantMap pack_encoder();
    static void unpack_encoder(const QVariantMap &map, S_Encoder &encoder);

    static QVariantMap pack_global();
    static void unpack_global(const QVariantMap &map);

    static QVariantMap pack_global_transceiver();
    static void unpack_global_transceiver(const QVariantMap &map);

    static QVariantMap pack_alarm();
    static void unpack_alarm(const QVariantMap &map);

    static QVariantMap pack_one_alarm_setting(int index);
    static void unpack_one_alarm_setting(int index, const QVariantMap &map);

    static void save_config(QFile &file);
    static void save_data(QFile &file);

    static int set_bit_value(int val, int bit, int val1);
    static int get_bit_value (int val, int bit);

    static void convert_to_phascan_config(int groupId);
    static void convert_other_to_phascan_config();

    static bool is_phascan_ii_file(QFile &file);

    static DopplerDataFileOperateor *m_pDataFile;
    static QByteArray m_dataMark;
    static QByteArray m_dataSource;
    static S_Groups m_groups[setup_MAX_GROUP_QTY];
    static S_Scanner m_scanner;
    static S_Global m_global;
    static int s_alarmCount;
    static bool m_isPhascanII;
};

#endif // __CONFIG_H__
