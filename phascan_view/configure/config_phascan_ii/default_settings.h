#ifndef DEFAULT_SETTINGS_H
#define DEFAULT_SETTINGS_H

#include "const.h"

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
    bool refGainStatus;
    double refGain;
    double start;
    double maxGain;
    int pointQty;
    bool autoCalcPointQty;
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
    FULL_WAVE,
};

enum Averaging {
    AVERAGING_1,
    AVERAGING_2,
    AVERAGING_4,
    AVERAGING_8,
    AVERAGING_16
};

struct S_Transceiver {
    Averaging average;
    uint filter;
    TxRxMode txRxMode;
    float pw;
    uint pulser;
    uint receiver;
    Rectifier rectifier;
    bool videoFilter;
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

struct S_Probe {
    ArrayMode arrayMode;
    double freq;
    QString model;
    QString serial;
    int priElemQty;
    int secElemQty;
    float priPitch;
    float secPitch;
    float refPoint;
    double scanOffset;
    double indexOffset;
    int skew;
    ProbeType type;
};

enum Orientation {
    Reversal,
    Normal
};

enum WaveType {
    Longitudinal,
    Shear
};

struct S_Wedge {
    QString serial;
    QString model;
    float angle;
    float fstElemHeight;
    float length;
    float width;
    float height;
    unsigned int velocity;
    WaveType waveType;
    float priOffset;
    float secOffset;
    Orientation orientation;
    uint refPoint;

    float rootAngle;
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
    NONE_TYPE,
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

enum MaxGain {
    PA_MAX_GAIN = 80,
    UT_MAX_GAIN = 110
};

struct S_Weld {
    bool enable;
    WeldType type;
    bool isSymmetry;
    WeldOrientation orientation;
    double w0;
    double h0;
    double r0;

    double w1;
    double h1;
    double r1;

    double w2;
    double h2;
    double r2;
};

struct S_Specimen {
    Shape shape;
    double LV;
    double SV;
    Material material;
    double density;
    WeldType weldType;
    /* PLANE & CYLINDER */
    double width0;
    double height0;
    double length0;
    double angle0;
    double inside0;
    double outside0;
    double clampOffset0;
    /* CYLINDER特有 */
    ProbePosition probePosition;
    /* Nozzle */
    double length1;
    double inside1;
    double outside1;
    double length2;
    double inside2;
    double outside2;
    double angle2;
    S_Weld weld;
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

struct S_BeamsInfo {
    float delay[setup_MAX_GROUP_LAW_QTY];
    float fieldDistance[setup_MAX_GROUP_LAW_QTY];
};

struct S_Scan {
    double refractStartAngle;
    double refractStepAngle;
    double refractStopAngle;
    uint priApe;
    uint priStartElem;
    uint priElemStep;
    uint priStopElem;
    double refractAngle;
};

struct S_Focallawer {
    ScanMode scanMode;
    FocusMode focusMode;
    WaveType waveType;
    S_Scan scan;
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
    float start;
    float width;
    int height;
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
    S_Probe probe;
    S_Wedge wedge;
    S_Specimen specimen;
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

enum EncoderStatus {
    OFF,
    ON
};

enum Polarity {
    NORMAL,
    INVERSE
};

struct S_Encoder {
    EncoderStatus status;
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
    V50  = 50,
    V100 = 100,
    V200 = 200,
    V400 = 400
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

enum GateType {
    GateA,
    GateB,
    GateI
};

/* Group */
#define DEFAULT_GROUP_MODE  PA
#define DEFAULT_UT_UNIT     TruePath

/* focallawer */
#define DEFAULT_FOCUS_MODE FOCUS_HALF_PATH
#define DEFAULT_SCAN_MODE  Linear
#define DEFAULT_WAVE_TYPE  Shear

/* Gate */
#define DEFAULT_MEASURE_MODE DEPTH
#define DEFAULT_GATE_MODE    PEAK
#define DEFAULT_SYNCHRO_MODE SYNCHRO_PULSER
#define DEFAULT_GATE_VISIBLE false
#define DEFAULT_GATE_START   0.0
#define DEFAULT_GATE_WIDTH   5000.0
#define DEFAULT_GATE_HEIGHT  25

/* Focus */
#define DEFAULT_BEGIN_OFFSET 0
#define DEFAULT_END_OFFSET   30

/* Scan */
#define DEFAULT_REFRACT_START_ANGLE 40
#define DEFAULT_REFRACT_STEP_ANGLE  1
#define DEFAULT_REFRACT_STOP_ANGLE  70
#define DEFAULT_PRIAPE              1
#define DEFAULT_PRI_START_ELEM      1
#define DEFAULT_PRI_ELEM_STEP       1
#define DEFAULT_PRI_STOP_ELEM       1
#define REFRACT_ANGLE               0

/* Sample */

#define DEFAULT_SAMPLE_GAIN     20.0
#define DEFAULT_REF_GAIN_STATUS  false
#define DEFAULT_REF_GAIN        0.0
#define DEFAULT_SAMPLE_START    0.0
#define DEFAULT_MAX_GAIN        PA_MAX_GAIN
#define DEFAULT_POINT_QTY       640
#define DEFAULT_AUTO_CAL_POINT_QTY  true

/* Probe */
#define DEFAULT_ARRAY_MODE   LINEAR
#define DEFAULT_PROBE_FREQ   5
#define DEFAULT_PROBE_MODEL  ""
#define DEFAULT_PROBE_SERIAL ""
#define DEFAULT_ELEMQTY      1
#define DEFAULT_PRI_PITCH    500
#define DEFAULT_SEC_PITCH    0
#define DEFAULT_REFPOINT     0
#define DEFAULT_OFFSET       0
#define DEFAULT_PROBE_TYPE   ANGLE_BEAM
#define DEFAULT_SKEW         90

/* Specimen */
#define DEFAULT_SHAPE     PLANE
#define DEFAULT_LV        5890
#define DEFAULT_SV        3240
#define DEFAULT_DENSITY   7.8
#define DEFAULT_MATERIAL  STEEL_COMMON
#define DEFAULT_WELD_TYPE NONE_TYPE

#define DEFAULT_PLANE_LENGTH 250
#define DEFAULT_PLANE_WIDTH  250
#define DEFAULT_PLANE_HEIGHT  50

#define DEFAULT_CYLINDER_ANGLE   180
#define DEFAULT_CYLINDER_LENGHT  250
#define DEFAULT_CYLINDER_INSIDE  200
#define DEFAULT_CYLINDER_OUTSIDE 300
#define DEFAULT_CYLINDER_PROBE_POS CID
/* outside - inside = thickness; UI显示thickness
 * 配置保存Inside信息
 */
#define DEFAULT_NOZZLE_0_OUTSIDE      0
#define DEFAULT_NOZZLE_0_INSIDE       0
#define DEFAULT_NOZZLE_0_ANGLE        90
#define DEFAULT_NOZZLE_0_CLAMP_OFFSET 0
#define DEFAULT_NOZZLE_1_OUTSIDE      84
#define DEFAULT_NOZZLE_1_INSIDE       74
#define DEFAULT_NOZZLE_1_LENGTH       2000
#define DEFAULT_NOZZLE_2_OUTSIDE      610
#define DEFAULT_NOZZLE_2_INSIDE       584
#define DEFAULT_NOZZLE_2_LENGTH       600
#define DEFAULT_NOZZLE_2_ANGLE        180

/* Weld */
#define DEFAULT_WELD_ORIENTATION  AXIAL
#define DEFAULT_WELD_SYMMETRY     true

#define DEFAULT_I_W_0   5

#define DEFAULT_V_W_0   10
#define DEFAULT_V_W_1   5
#define DEFAULT_V_H_0   10

#define DEFAULT_U_W_0   10
#define DEFAULT_U_W_1   5
#define DEFAULT_U_R_0   6
#define DEFAULT_U_H_0   20

#define DEFAULT_VY_W_0   10
#define DEFAULT_VY_W_1   10
#define DEFAULT_VY_W_2   5
#define DEFAULT_VY_H_0   10
#define DEFAULT_VY_H_1   10

#define DEFAULT_VV_W_0   10
#define DEFAULT_VV_W_1   5
#define DEFAULT_VV_W_2   10
#define DEFAULT_VV_H_0   10
#define DEFAULT_VV_H_1   10

#define DEFAULT_UU_W_0   10
#define DEFAULT_UU_W_1   5
#define DEFAULT_UU_W_2   10
#define DEFAULT_UU_R_0   6
#define DEFAULT_UU_R_1   6
#define DEFAULT_UU_H_0   20
#define DEFAULT_UU_H_1   20

#define DEFAULT_UV_W_0   10
#define DEFAULT_UV_W_1   5
#define DEFAULT_UV_W_2   10
#define DEFAULT_UV_R_0   6
#define DEFAULT_UV_H_0   20
#define DEFAULT_UV_H_1   10

/* Wedge */
#define DEFAULT_WEDGE_SERIAL            ""
#define DEFAULT_WEDGE_MODEL             ""
#define DEFAULT_WEDGE_ANGLE             0
#define DEFAULT_WEDGE_FIRST_ELEM_HEIGHT 0
#define DEFAULT_WEDGE_LENGTH            0
#define DEFAULT_WEDGE_WIDTH             0
#define DEFAULT_WEDGE_HEIGHT            0
#define DEFAULT_WEDGE_VELOCITY          2337
#define DEFAULT_WEDGE_WAVE_TYPE         Shear
#define DEFAULT_WEDGE_PRI_OFFSET        0
#define DEFAULT_WEDGE_SEC_OFFSET        0
#define DEFAULT_WEDGE_ORIENTATION       Normal
#define DEFAULT_WEDGE_REF_POINT         0
#define DEFAULT_WEDGE_ROOT_ANGLE        0
#define DEFAULT_WEDGE_DELAY             0

/* Transceiver */
#define DEFAULT_TRANSCEIVER_AVERAGE      0
#define DEFAULT_TRANSCEIVER_FILTER       1
#define DEFAULT_TRANSCEIVER_TXRXMODE     0
#define DEFAULT_TRANSCEIVER_PW           100
#define DEFAULT_TRANSCEIVER_PULSER       0
#define DEFAULT_TRANSCEIVER_RECEIVER     0
#define DEFAULT_TRANSCEIVER_RECTIFIER    FULL_WAVE
#define DEFAULT_TRANSCEIVER_VIDEO_FILTER true


#define ALARM_COUNT 3
/*  */

#endif // DEFAULT_SETTINGS_H
