/************************************
  Name:  INSTRUMENT_H
  Description:   配制参数的定义
*************************************/

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "const.h"


enum setup_UNIT_TYPE
{
	setup_UNIT_MM,
	setup_UNIT_INCH ,
	setup_UNIT_NS   ,
	setup_UNIT_10NS
} ;

enum setup_DISPLAY_MODE
{
	setup_DISPLAY_MODE_A_H = 0 ,
	setup_DISPLAY_MODE_A_V	 ,
	setup_DISPLAY_MODE_B_H	 ,
	setup_DISPLAY_MODE_B_V	 ,
	setup_DISPLAY_MODE_C_H	 ,
	setup_DISPLAY_MODE_C_V	 ,
	setup_DISPLAY_MODE_CC_H	,
	setup_DISPLAY_MODE_CC_V	,
	setup_DISPLAY_MODE_S	   ,
	setup_DISPLAY_MODE_S_SOUNDPATH ,
	setup_DISPLAY_MODE_S_ATHUMIZ   ,
	setup_DISPLAY_MODE_S_LINEAR
}  ;

enum setup_DISPLAY_CSCAN_SOURCE	 //C扫的数据显示类型
{
	setup_DISPLAY_CSCAN_A  = 0	,
	setup_DISPLAY_CSCAN_B		 ,
	setup_DISPLAY_CSCAN_THICKNESS ,
	setup_DISPLAY_CSCAN_OFF
}  ;

//######################################################################
enum setup_GATE_NAME   //闸门类型
{
	setup_GATE_A = 0 ,
	setup_GATE_B	 ,
	setup_GATE_I	 ,
	setup_GATE_MAX
}  ;

enum setup_GATE_AYNC_TYPE   //闸门跟踪方式
{
	setup_GATE_AYNC_PUL = 0 ,
	setup_GATE_AYNC_I,
	setup_GATE_AYNC_A
};

typedef struct
{
	float fStart  ;	 // gate start position
	float fWidth  ;	 // gate width
	unsigned int nThreshold  ; // gate height
	//unsigned int eSynChro	 ; // setup_GATE_SYN_MODE
	setup_GATE_AYNC_TYPE eSynChro;
	unsigned int eMeasure	 ; // setup_GATE_MEASURE_MODE
} GATE_CONFIG;

typedef struct
{
	int iX;
	int iY;
	int iXEdge;
	int iYEdge;
	float fGs;
	float fGw;
	float fGh;

	float fSEdge ;
	float fHEdge ;
	float fLEdge ;
	float fDEdge ;

	float fS ;
	float fH ;
	float fL ;
	float fD ;

	float fAmp;
	float fXdXA; // AdBA / BdBB
} PEAK_CONFIG;

//######################################################################
/*探头(PROBE)*/

struct PROBE_CONFIG
{
	char	 strName[64];
	char	 strSerial[64];

	int	  nElementPri;		//主轴阵元数
	int	  nElementSec;		//副轴阵元数
	int	  nLocationPolicy ;   // 二维探头，排列顺序

	float	fFrequency ;		//MHz
	float	fPitchPri  ;		//主轴间距
	float	fPitchSec  ;
	float	fSizePri   ;
	float	fSizeSec   ;

	float	fReferencePoint ;

} ;
//######################################################################

enum setup_WEDGE_TYPE
{
	setup_WEDGE_TYPE_PA  = 0 ,
	setup_WEDGE_TYPE_UT
} ;

enum setup_WEDGE_ORIENTATION
{
	setup_WEDGE_ORIENTATION_REVERSE = 0 ,
	setup_WEDGE_ORIENTATION_NORMAL
} ;


/*楔块(Wedge)*/
struct WEDGE_CONFIG
{
	char	 strName[64];
	char	 strSerial[64];

	setup_WEDGE_TYPE eType ;
	setup_WEDGE_ORIENTATION eDirection ;

	float	fWedgeAngle; /* 楔块角 */
	float	fRoofAngle ; /* 顶角 */

	float	fVelocityLon;/*纵波声速*/
	float	fVelocityTra;/*横波声速*/

	float	fHeigtFirst ;  /*第一阵元高度*/
	float	fOffsetFir;	/*主轴阵元偏移*/
	float	fOffsetSec;	/*次轴阵元偏移*/
	float	fPriAxisRef;   /*主轴楔块参考位置*/
	float	fSecAxisRef;   /*次轴楔块参考位置*/

	float	fLength;/*楔块长度*/
	float	fWidth ;/*楔块宽度*/
	float	fHeight;/*楔块高度*/

	//ut 探头参数
    float		fRefPoint;
    unsigned int nWedgeDelay;
};

struct MATERIAL
{
    char   strName[4][64];
	float  fVelocityLon;
	float  fVelocityTran;
    float  fDensity;
};

enum setup_WELD_TYPE
{
	setup_WELD_I = 0 ,
	setup_WELD_V ,
	setup_WELD_DV,
	setup_WELD_U,
    setup_WELD_DIFF_DV,
    setup_WELD_J,
    setup_WELD_VY,
//	setup_WELD_NCC,
    setup_WELD_TKY,
    setup_WELD_DXF,
	setup_WELD_MAX
};

enum setup_WELD_SYMMETRY_TYPE
{
	setup_WELD_SYMMETRY = 0 ,
	setup_WELD_LEFT ,
	setup_WELD_RIGHT
} ;

struct WELD
{
	setup_WELD_TYPE   				 eType	;		/* 焊缝 */
	setup_WELD_SYMMETRY_TYPE		 eSymmetry;		/* 对称 */

    float	weland_height;
    float	weland_offset;
	float	fizone_height;
	float	fizone_angle ;
	float	fizone_radius;
	float	weldtype_pos ;
    float   fizone_down_height;
    float	fizone_down_angle ;
    float   Diameter;
} ;

enum setup_PART_GEOMETRY
{
	setup_PART_GEOMETRY_FLAT = 0 ,
	setup_PART_GEOMETRY_OD ,
	setup_PART_GEOMETRY_ID ,
	setup_PART_GEOMETRY_BALL
} ;


enum FLAT_PART_SIZE
{
	FLAT_PART_SIZE_THICKNESS = 0,
	FLAT_PART_SIZE_LENGTH ,
	FLAT_PART_SIZE_WIDTH
} ;

enum CYLINDRICAL_PART_SIZE
{
	CYLINDRICAL_PART_INNER_DIAMETER = 0,
	CYLINDRICAL_PART_OUTTER_DIAMETER ,
	CYLINDRICAL_PART_SIZE_LENGTH
} ;

struct PART_CONFIG
{
	setup_PART_GEOMETRY	eGeometry;				/* 几何形状 FLAT/ID/OD/BALL */

	//geometry parameter
	float				afSize[4];				// sizes if necceray , part height , width , diameter
	MATERIAL			material;				/* 材料 */
	WELD				weld;					// weld
	char				strPartFile[256];		// Name of part file , *.ncc
};

enum setup_LAW_TYPE
{
	setup_LAW_TYPE_AZIMUTHAL = 0 ,
	setup_LAW_TYPE_LINEAR
} ;

enum setup_FOCAL_TYPE
{
	setup_FOCAL_TYPE_HALF_PATH = 0 ,
	setup_FOCAL_TYPE_TRUE_DEPTH  ,
	setup_FOCAL_TYPE_PROJECTION  ,
	setup_FOCAL_TYPE_FOCAL_PLANE
} ;

enum setup_ANGLE_TYPE
{
	setup_ANGLE_TYPE_PRI_SEC_STEERING = 0 ,
	setup_ANGLE_TYPE_PRI_SEC_SKEW  =1,
	setup_ANGLE_TYPE_PRI_SEC_REFRACT = 2,
	setup_ANGLE_TYPE_PRI_BEAM_SKEW = 3,
	setup_ANGLE_TYPE_REFRACT = 0 ,
	setup_ANGLE_TYPE_PRI_STEERING = 1 ,
	setup_ANGLE_TYPE_SKEW = 2
} ;


struct LAW_CONFIG
{
    setup_LAW_TYPE	 eLawType;				//  setup_LAW_TYPE

	setup_ANGLE_TYPE   eAngleType ;
	// refract angle
	int nAngleStartRefract;						  // 0.1 degree
	int nAngleStopRefract ; 				 // focal law  angle setting
	int nAngleStepRefract ;		 					 //
	// beam skew angle
	int nAngleStartBeamSkew;
	int nAngleStopBeamSkew ;
	int nAngleStepBeamSkew ;
	// primary axis steering angle
	int nAngleStartPriSteer;
	int nAngleStopPriSteer ;
	int nAngleStepPriSteer ;
	// primary axis steering angle
	int nAngleStartSecSteer;
	int nAngleStopSecSteer ;
	int nAngleStepSecSteer ;

	setup_FOCAL_TYPE   eFocalType ;			   //  setup_FOCAL_TYPE
	//###################################################
	double	fPositionStart;					// focal depth
	double	fPositionStop;					// not available currently
	double	fPositionStep;					// not available currently
	//###################################################
	double	fOffsetStart;					// focal plane
	double	fDepthStart;					//
	double	fOffsetStop;				//
	double	fDepthStop ;				//

	/*element selection*/
	unsigned int	nElemQtyFir;		// aperture setting
	unsigned int	nFirstElemFir;		// first trigger element
	unsigned int	nLastElemFir;			// last  trigger element
	unsigned int	nElemStepFir;			// element step (linear scan)

	unsigned int	nElemQtySec;			// aperture setting
	unsigned int	nFirstElemSec ;		// first trigger element
	unsigned int	nLastElemSec;			// last  trigger element
	unsigned int	nElemStepSec;			// element step (linear scan)

} ;
//######################################################################
enum setup_CURVE_TYPE
{
	setup_CURVE_TYPE_NULL = 0 ,
	setup_CURVE_TYPE_DAC,
	setup_CURVE_TYPE_LINEAR_DAC,
	setup_CURVE_TYPE_TCG,
	setup_CURVE_TYPE_MAX
};
/* 光标信息 */
#define setup_DAC_POINT_QTY   16
struct CURVES
{
		int bTcgCalibrated;
		int bApplyToAllLaws ;

		setup_CURVE_TYPE	eType;
		int					nPointPos;
		int					nPointQty;
		float				fCurStep ;
		float				fMatAtten;
		float				fAmpOffsetAmp ;
		float				fAmpOffsetLinear;
		float				nLinearDelay;

		float				faAmpLinear[setup_DAC_POINT_QTY] ;
		float				faAmpPosition [setup_DAC_POINT_QTY] ;
		float				faAmpRef[setup_MAX_GROUP_LAW_QTY] ;
		float				faAmp[setup_MAX_GROUP_LAW_QTY][setup_DAC_POINT_QTY];
		float				faPosition[setup_MAX_GROUP_LAW_QTY][setup_DAC_POINT_QTY];

} ;
//######################################################################
//######################################################################
enum setup_TRAVEL_MODE
{
	setup_TRAVEL_MODE_TRUE_DEPTH = 0,
	setup_TRAVEL_MODE_HALF_PATH
} ;

enum setup_GROUP_MODE
{
	setup_GROUP_MODE_PAUT = 0 ,
	setup_GROUP_MODE_PA ,
	setup_GROUP_MODE_UT1,
	setup_GROUP_MODE_UT2
};

enum setup_FILTER_MODE	 //滤波模式
{
	setup_FILTER_NONE = 0 ,
	setup_FILTER_AUTO	 ,
	setup_FILTER_1_MHZ	,
	setup_FILTER_2_5MHZ   ,
	setup_FILTER_5_MHZ	,
	setup_FILTER_7_5MHZ   ,
	setup_FILTER_10_MHZ
} ;

enum setup_RECTIFIER_MODE  //检波模式
{
	setup_RECTIFIER_RF = 0		  ,
	setup_RECTIFIER_HW_POSITIVE	 ,
	setup_RECTIFIER_HW_NEGTIVE	  ,
	setup_RECTIFIER_FW
};

enum setup_AVERAGE_MODE   //平均
{
	setup_AVERAGE_1 = 0  ,
	setup_AVERAGE_2	  ,
	setup_AVERAGE_4	  ,
	setup_AVERAGE_8	  ,
	setup_AVERAGE_16
} ;

enum setup_PROBE_ANGLE
{
	setup_PROBE_PART_SKEW_0 = 0 ,
	setup_PROBE_PART_SKEW_90  ,
	setup_PROBE_PART_SKEW_180 ,
	setup_PROBE_PART_SKEW_270
};

enum setup_CURSOR_TYPE
{
	setup_CURSOR_LAW = 0 , /* 参考光标当前聚焦法则*/
	setup_CURSOR_A_REF   , /* 参考光标的高度 */
	setup_CURSOR_A_MES   , /* 测量光标的高度 */
	setup_CURSOR_U_REF   , /* 参考光标在超声轴的位置 */
	setup_CURSOR_U_MES   , /* 测量光标在超声轴的位置 */
	setup_CURSOR_S_REF   , /* 参考光标在扫描轴的位置 */
	setup_CURSOR_S_MES   , /* 测量光标在扫描轴的位置 */
	setup_CURSOR_I_REF   , /* 参考光标在指数轴的位置 */
	setup_CURSOR_I_MES   , /* 测量光标在指数轴的位置 */
	setup_CURSOR_VPA_REF ,
	setup_CURSOR_VPA_MES ,
	setup_CURSOR_TFOD_LW ,
	setup_CURSOR_TFOD_BW ,
	setup_CURSOR_MAX
} ;

struct GROUP_COLOR
{
	int anColor[8] ;
	unsigned char Amp[256][3] ;
	unsigned char Rf [256][3] ;
	unsigned char Thickness[256][3] ;
} ;

enum setup_CSCAN_SOURCE_MODE
{
	setup_CSCAN_AMP_A = 0,
	setup_CSCAN_AMP_B ,
	setup_CSCAN_POS_I ,
	setup_CSCAN_POS_A ,
	setup_CSCAN_POS_B ,
	setup_CSCAN_POS_AI ,
	setup_CSCAN_POS_BI ,
	setup_CSCAN_POS_BA ,
	setup_CSCAN_TYPE_MAX
} ;

enum setup_TX_RX_MODE
{
	setup_TX_RX_MODE_PC = 0 ,
	setup_TX_RX_MODE_PE ,
	setup_TX_RX_MODE_TT ,
	setup_TX_RX_MODE_TOFD
};

typedef struct _Group
{
	setup_GROUP_MODE		eGroupMode;				/* 组工作模式  0 UT or 1 PA*/
	setup_TRAVEL_MODE		eTravelMode;
	setup_TX_RX_MODE		eTxRxMode;
	/* 基本设置 */
	int						nWedgeDelay;			/* 楔款延时 单位 ns */
	int 					nTimeStart;				/* 时间起点 单位 ns */
	int						nTimeRange;				/* 时间范围 单位 ns */
	float					fSampleStart;			/* 显示范围 单位 mm */
	float					fSampleRange;			/* 扫描延时 单位 mm */
	int						nPointQty;				/* 点个数(采样深度) */
	float					fVelocity;				/* 声速 单位 m/s*/
	float					fGain;					/* 增益 0 - 80 db  _STEP 0.01dB */
	float					fRefGain;
	float					fSumGain ;
	int						bPointQtyAuto;
	int						bSumGainAuto;
	/* 发射接收 */
	unsigned int			nTrigeStart;			/* 1~128 - elem_qty(聚焦阵元数最大为32) + 1 指定发射阵元与机器配置相关我们是128阵元最大,值与connect P 一样 */
	unsigned int			nReceiveStart;			/* 接收阵元 必须是 PR 模式才能调节 */

	setup_FILTER_MODE		eFileter;		/* 滤波 */
	setup_RECTIFIER_MODE	eRectifier;		/* 检波 */
	setup_AVERAGE_MODE		eAveraging;		/* 平均 */
	int						bVedioFilter;

	// 设置的探头频率，和对应的脉宽
	float					fTriFrequency;		/* Mhz*/
	unsigned int			nPulserWidth;		/* ns */

	/* 参考光标 */
	float					afCursor[setup_CURSOR_MAX] ;

	// thickness range for c scan display
	setup_CSCAN_SOURCE_MODE	eCScanSource[2] ;
	float					fMinThickness;		/* Measurements->Thickness->min */
	float					fMaxThickness;		/* Measurements->Thickness->max */
	// wedge position
	float					fScanOffset;		/*mm*/
	float					fIndexOffset;		/*mm*/
	setup_PROBE_ANGLE		eSkew;

	/*  校准状态  */
	int						bVelocityCalib;
	int						bWedgeDelayCalib;
	int						bSensationCalib;

	float					afGainOffset[setup_MAX_GROUP_LAW_QTY];
	unsigned int			anBeamDelay[setup_MAX_GROUP_LAW_QTY];
	float					afBeamPos[setup_MAX_GROUP_LAW_QTY];

	int						aeMeasureType[5];
	int						bShowMeasure;
	int						bShowCursor;
	int						bShowWeldPart;
	int						bShowGate;
    int                     bShowGateA;
    int                     bShowGateB;
    int                     bShowGateI;
	int						bShowThickness;
	int						bShowCurve;
	int						bShowLwBw;
	int						bShowDefect;

	LAW_CONFIG				law;
	GATE_CONFIG				gate[setup_GATE_MAX] ;
	PART_CONFIG				part;
	WEDGE_CONFIG			wedge[2];
	PROBE_CONFIG			probe[2];
	CURVES					curve;
	GROUP_COLOR				color;
}GROUP_CONFIG;
//####################################################################################
//#################				 COMMON DATA			 ######################
//####################################################################################
/*encoder definition.*/
enum setup_ENCODER_TYPE   //扫查数据源
{
	setup_ENCODER_TYPE_TIMER = 0,
	setup_ENCODER_TYPE_ENCODER_1,
	setup_ENCODER_TYPE_ENCODER_2,
	setup_ENCODER_TYPE_MAX
};

/*Different counter types for encoder input*/
enum setup_ENCODER_MODE   //类型
{
	setup_ENC_MODE_QUADRATURE = 0 ,	//  正交
	setup_ENC_MODE_UP		,		 //  正向
	setup_ENC_MODE_DOWN				//  反向
} ;

enum setup_ENCODER_POLARITY  //极性
{
	setup_ENC_POLARITY_NORNAL = 0,	//正向
	setup_ENC_POLARITY_REVERSE		//反向
};

typedef struct
{
	setup_ENCODER_MODE	 eEncoderMode  ;// setup_ENCODER_MODE
	setup_ENCODER_POLARITY ePolarity	 ;// setup_ENCODER_POLARITY

	double fResulotion  ;
	double fOrigin	  ;
} ENCODER_CONFIG ;

enum setup_SCAN_TYPE
{
	//setup_SCAN_TYPE_TIMMER ,
	setup_SCAN_TYPE_ONE_LINE = 0 ,
	setup_SCAN_TYPE_TWO_LINE
} ;

enum setup_SCAN_MODE
{
	setup_SCAN_NORMAL = 0 ,
	setup_SCAN_PARALLEL   ,
}  ;

/*scanner*/
struct SCANNER
{
	setup_ENCODER_TYPE eEncoderType  ;
	setup_SCAN_TYPE	eScanType	 ;
	setup_SCAN_MODE	eScanMode	 ;
	// scan pos
	float fScanPos	 ;
	float fIndexPos	;
	// scan speed
	float fPrf		 ;
	// scan range
	float fScanStart   ;
	float fIndexStart  ;
	float fScanStop	;
	float fIndexStop   ;
	float fScanStep	;
	float fIndexStep   ;
	// encoder
	ENCODER_CONFIG  encoder[setup_ENCODER_TYPE_MAX]  ;
} ;


enum setup_VOLTAGE_MODE
{
	setup_VOLTAGE_50  = 0 ,
	setup_VOLTAGE_100	 ,
	setup_VOLTAGE_200
};

struct INSTRUMENT_CONFIG
{
//	setup_TX_RX_MODE	eTxRxModePA ;
//	setup_TX_RX_MODE	eTxRxModeUT ;
	setup_VOLTAGE_MODE  eVoltagePA  ;
	setup_VOLTAGE_MODE  eVoltageUT  ;
} ;

struct ALARM_SETTING
{
	// alarm
	int nGroupId ;
	int eCondition1 ;
	int eCondition2 ;
	int eOperate ;
} ;
struct ALARM_OUTPUT
{
	// out put
	int bSwitch ;
	int nCount  ;
	int bSoundOn;
	int nDelay  ;
	int nHold   ;
} ;
struct ALARM_CONFIG
{
	ALARM_SETTING  alarm[3] ;
	ALARM_OUTPUT   output[5];
} ;


enum SONIC_AXIS_UNIT
{
	SONIC_AXIS_UNIT_MM = 0,
	SONIC_AXIS_UNIT_INCH  ,
	SONIC_AXIS_UNIT_TIME  ,
	SONIC_AXIS_UNIT_MAX
} ;

struct COMMON_CONFIG
{
	int					nGroupQty	;
	int					bUnifiedPart ;
	SONIC_AXIS_UNIT		eUAxisUnit   ;
	INSTRUMENT_CONFIG	instrument   ;
	ALARM_CONFIG		alarm   ;
	SCANNER				scanner ;
	//----------------------------
	int					nRecMax;
	int					nDataSize;
	int					nScanOffMax;
	int					nScanOff[setup_MAX_GROUP_QTY];
	U8					nRecMark[setup_MAX_REC_LEN];
} ;



#endif // INSTRUMENT_H





