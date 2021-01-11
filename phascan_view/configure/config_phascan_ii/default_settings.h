#ifndef DEFAULT_SETTINGS_H
#define DEFAULT_SETTINGS_H

#include "const.h"
#include <QVariantList>

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
#define DEFAULT_MAX_GAIN        80
#define DEFAULT_POINT_QTY       640
#define DEFAULT_AUTO_CAL_POINT_QTY  true

/* Probe */
#define DEFAULT_ARRAY_MODE   0
#define DEFAULT_PROBE_FREQ   5
#define DEFAULT_PROBE_MODEL  ""
#define DEFAULT_PROBE_SERIAL ""
#define DEFAULT_ELEMQTY      1
#define DEFAULT_PRI_PITCH    500
#define DEFAULT_SEC_PITCH    0
#define DEFAULT_REFPOINT     0
#define DEFAULT_OFFSET       0
#define DEFAULT_PROBE_TYPE   3
#define DEFAULT_SKEW         90

/* Specimen */
#define DEFAULT_SHAPE     0
#define DEFAULT_LV        5890
#define DEFAULT_SV        3240
#define DEFAULT_DENSITY   7.8
#define DEFAULT_MATERIAL  1
#define DEFAULT_WELD_TYPE 0

#define DEFAULT_PLANE_LENGTH 250
#define DEFAULT_PLANE_WIDTH  250
#define DEFAULT_PLANE_HEIGHT  50

#define DEFAULT_CYLINDER_ANGLE   180
#define DEFAULT_CYLINDER_LENGHT  250
#define DEFAULT_CYLINDER_INSIDE  200
#define DEFAULT_CYLINDER_OUTSIDE 300
#define DEFAULT_CYLINDER_PROBE_POS 0
/* outside - inside = thickness; UI显示thickness
 * 配置保存Inside信息
 */
#define DEFAULT_NOZZLE_OUTSIDE      0
#define DEFAULT_NOZZLE_INSIDE       0
#define DEFAULT_NOZZLE_ANGLE        90

#define DEFAULT_FILLET_ANGLE        90
#define DEFAULT_FILLET_PROBE_POS    4
/* Weld */
#define DEFAULT_WELD_ORIENTATION  0
#define DEFAULT_WELD_SYMMETRY     true
#define DEFAULT_WELD_HAZ          5.0

/* Wedge */
#define DEFAULT_WEDGE_SERIAL            ""
#define DEFAULT_WEDGE_MODEL             ""
#define DEFAULT_WEDGE_ANGLE             0
#define DEFAULT_WEDGE_FIRST_ELEM_HEIGHT 0
#define DEFAULT_WEDGE_LENGTH            0
#define DEFAULT_WEDGE_WIDTH             0
#define DEFAULT_WEDGE_HEIGHT            0
#define DEFAULT_WEDGE_VELOCITY          2337
#define DEFAULT_WEDGE_WAVE_TYPE         1
#define DEFAULT_WEDGE_PRI_OFFSET        0
#define DEFAULT_WEDGE_SEC_OFFSET        0
#define DEFAULT_WEDGE_ORIENTATION       1
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

#define DEFAULT_REFAMP  70

#endif // DEFAULT_SETTINGS_H
