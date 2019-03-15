#ifndef DEFAULT_SETTINGS_H
#define DEFAULT_SETTINGS_H

#include "const.h"
#include <QVariantList>

struct S_Display {
    QString ampPalette;
    uint bright;
    bool cursor;
    QString depthPalette;
    QVariantList groups;
    uint language;
    uint layout;
    uint opacity;
    QString tofdPalette;
};

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
    double range;
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
    bool autoCalPW;
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

enum ScanType {
    OneLine,
    RasterScan,
    HelicoidalScan
};

struct S_Probe {
    ArrayMode arrayMode;
    double freq;
    QString model;
    QString serial;
    uint priElemQty;
    uint secElemQty;
    double priPitch;
    double secPitch;
    double refPoint;
    double scanOffset;
    double indexOffset;
    uint skew;
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
    double angle;
    double fstElemHeight;
    double length;
    double width;
    double height;
    double velocity;
    double priOffset;
    double secOffset;
    Orientation orientation;
    double rootAngle;
    uint delay;
    double clampOffset;

    WaveType waveType;
    uint refPoint;
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

struct S_WeldI {
    uint orientation;
    bool symmetry;
    double width;
};

struct S_WeldV {
    uint orientation;
    bool symmetry;
    double width;
    double height;
};

struct S_WeldU {
    uint orientation;
    bool symmetry;
    double width;
    double height;
    double radius;
};

struct S_Weld {
    bool enable;
    WeldType type;
    bool isSymmetry;
    WeldOrientation orientation;
    S_WeldI I;
    S_WeldV V;
    S_WeldU U;
    S_WeldI MidI;
    S_WeldI BtmI;
    S_WeldU BtmU;
    S_WeldU TopU;
    S_WeldV BtmV;
    S_WeldV MidV;
    S_WeldV TopV;
};

struct S_Plane {
    double width;
    double height;
    double length;
};

struct S_Cylinder {
    double length;
    double angle;
    double inside;
    double outside;
    double probePos;
};

struct S_Nozzle {
    double angle;
    double inside;
    double outside;
    S_Cylinder cylinder1;
    S_Cylinder cylinder2;
};

struct S_Geometry {
    S_Plane plane;
    S_Cylinder cylinder;
    S_Nozzle nozzle;
};

struct S_Specimen {
    Shape shape;
    double LV;
    double SV;
    Material material;
    double density;
    WeldType weldType;
    S_Geometry geometry;
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
    double radius;
    /* FOCUS_TRUE_DEPTH */
    double depth;
    /* FOCUS_PROJECTION */
    double offset;
    /* FOCUS_FOCAL_PLANE */
    double beginOffset;
    double endOffset;
    double beginDepth;
    double endDepth;
};

struct S_BeamsInfo {
    float delay[setup_MAX_GROUP_LAW_QTY];
    float fieldDistance[setup_MAX_GROUP_LAW_QTY];
};

struct S_Scan {
    double refractAngle;
    double screwAngle;

    double refractStartAngle;
    double refractStopAngle;
    double refractStepAngle;

    double screwStartAngle;
    double screwStopAngle;
    double screwStepAngle;

    uint secApe;
    uint secStartElem;
    uint secElemStep;
    uint secStopElem;

    uint priApe;
    uint priStartElem;
    uint priElemStep;
    uint priStopElem;
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
    uint height;
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

enum CScanMode {
    ANGLE,
    TOPC
};

enum SourceType {
    GATE_A,
    GATE_B,
    GATE_I,
    THICKNESS
};

struct S_CScan {
    CScanMode mode;
    SourceType sourceType;
    double topCWidth;
};

struct S_Cursor {
    double ampMeas;
    double ampRef;
    double depthMeas;
    double depthRef;
    double indexMeas;
    double indexRef;
    double scanMeas;
    double scanRef;
    double ultraMeas;
    double ultraRef;
};

struct S_Groups{
    GroupMode mode;
    UtUnit utUnit;
    bool highestTrack;
    S_Sample sample;
    S_Transceiver transceiver;
    S_Focallawer focallawer;
    S_Gate gateA;
    S_Gate gateB;
    S_Gate gateI;
    S_CScan cScan;
    S_Cursor cursor;

    S_Probe probe;
    S_Wedge wedge;
    S_Specimen specimen;
    S_Thickness thickness;
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
    ScanType scanType;
    uint rate;
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

enum Damping {
    R50  = 0b00,
    R100 = 0b01,
    R200 = 0b10,
    R500 = 0b11
};

struct S_GlobalTransceiver {
    Voltage paVoltage;
    Voltage utVoltage;
    Damping ut1TxDamping;
    Damping ut2TxDamping;
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
    S_Display display;
    S_GlobalTransceiver transceiver;
    S_Scanner scanner;
    S_Alarm alarm[3];
    SoundMode sound;
    uint groupQty;
    PrfMode prfMode;
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
#define DEFAULT_NOZZLE_OUTSIDE      0
#define DEFAULT_NOZZLE_INSIDE       0
#define DEFAULT_NOZZLE_ANGLE        90

/* Weld */
#define DEFAULT_WELD_ORIENTATION  AXIAL
#define DEFAULT_WELD_SYMMETRY     true

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
#define DEFAULT_WEDGE_CLAMP_OFFSET      0

/* Transceiver */
#define DEFAULT_TRANSCEIVER_AVERAGE      0
#define DEFAULT_TRANSCEIVER_FILTER       1
#define DEFAULT_TRANSCEIVER_TXRXMODE     0
#define DEFAULT_TRANSCEIVER_PW           100
#define DEFAULT_TRANSCEIVER_PULSER       0
#define DEFAULT_TRANSCEIVER_RECEIVER     0
#define DEFAULT_TRANSCEIVER_RECTIFIER    FULL_WAVE
#define DEFAULT_TRANSCEIVER_VIDEO_FILTER true

/* Axis */
#define DEFAULT_AXIS_DRIVING    TIMER
#define DEFAULT_AXIS_START      0
#define DEFAULT_AXIS_END        800
#define DEFAULT_AXIS_RESOLUTION 1

/* Encoder */
#define DEFAULT_ENCODER_STATUS      OFF
#define DEFAULT_ENCODER_POLARITY    NORMAL
#define DEFAULT_ENCODER_MODE        QUAD
#define DEFAULT_ENCODER_RESOLUTION  48
#define DEFAULT_ENCODER_ORIGIN      0

/* global */
#define DEFAULT_PRF_MODE OPTIMUM

#define DEFAULT_REF  10
#define DEFAULT_MEAS 20


#define ALARM_COUNT 3
/*  */

#endif // DEFAULT_SETTINGS_H
