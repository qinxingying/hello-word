/************************************
  Name:  INSTRUMENT_H
  Description:   配制参数的定义
*************************************/

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "const.h"

enum setup_LANG
{
    setup_LANG_ENGLISH = 0,
    setup_LANG_CHINESE,
    setup_LANG_JAPANESE,
    setup_LANG_KOREAN
};

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

enum setup_GATE_TRAVEL_MODE
{
    setup_GATE_DEPTH,       //深度闸门
    setup_GATE_SOUND_PATH   //半声程闸门
};

typedef struct
{
	float fStart  ;	 // gate start position
	float fWidth  ;	 // gate width
    unsigned int nThreshold  ; // gate height (0-100)
    setup_GATE_AYNC_TYPE eSynChro; // setup_GATE_SYN_MODE
	unsigned int eMeasure	 ; // setup_GATE_MEASURE_MODE
    setup_GATE_TRAVEL_MODE gTravelMode;
} GATE_CONFIG;

typedef struct
{
    int iX; // 闸门峰值beam上相应的点的位置，第几个点 ?
    int iY; // 闸门峰值
    int iXEdge; // 闸门前沿beam上相应的点的位置，第几个点 ?
    int iYEdge; // 前沿
    float fGs;  // gate start ? mm
    float fGw;  // gate width ? mm
    float fGh;  // gate height ? mm

    float fSEdge ; // 前沿iXEdge dot pos to mm， DistDotPosToMm
    float fHEdge ; // fSEdge * Cos
    float fLEdge ; // fSEdge * Sin
    float fDEdge ; // GetDepth

    float fS ;  // 峰值点沿半声程方向的值,等于sa
    float fH ;  // 表示峰值垂直方向位置值
    float fL ;  // 峰值点水平方向的位置值
    float fD ;  // 峰值点深度值, 通过fH和工件厚度确定

    float fAmp; // CalPeakAmp
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

enum VIEW_ORIENT
{
    ORIENT_HORIZONTAL = 0,
    ORIENT_VERTICAL
};

enum setup_WELD_TYPE_II
{
    NONE_TYPE = 0,
    I,
    V,
    U,
    VY,
    VV,
    UU,
    UV,
    TKY,
    ASYMMETRIC,
    DXF
};

enum setup_WELD_SYMMETRY_TYPE
{
	setup_WELD_SYMMETRY = 0 ,
    setup_WELD_RIGHT ,
    setup_WELD_LEFT
} ;

enum setup_PLANE_ALIGN_TYPE//板的对齐方式
{
    setup_PLANE_TOP=0,
    setup_PLANE_CENTER,
    setup_PLANE_BOTTOM,
};


struct WELD
{
	setup_WELD_TYPE   				 eType	;		/* 焊缝 */
	setup_WELD_SYMMETRY_TYPE		 eSymmetry;		/* 对称 */

    float	weland_height;
    float	weland_offset;              //???
	float	fizone_height;
	float	fizone_angle ;
	float	fizone_radius;
	float	weldtype_pos ;
    float   fizone_down_height;
    float	fizone_down_angle ;
    float   Diameter;
};

struct WELD_FORMAT_I
{
    double w;
};

struct WELD_FORMAT_V
{
    double w1;
    double h;
    double w2;
};

struct WELD_FORMAT_U
{
    double w1;
    double h;
    double w2;
    double fill1;
    double fill2;
    double r;
};

struct WELD_FORMAT_VY
{
    double w1;
    double h1;
    double w2;
    double h2;
    double w3;
};

struct WELD_FORMAT_VV
{
    double w1;
    double h1;
    double w2;
    double h2;
    double w3;
};

struct WELD_FORMAT_UU
{
    double w1;
    double h1;    
    double w2;
    double h2;    
    double w3;
    double r1;
    double r2;
};

struct WELD_FORMAT_UV
{
    double w1;
    double h1;    
    double w2;
    double h2;
    double w3;
    double r;
};

struct WELD_FORMAT_TKY
{
    double w1;
    double h1;
    double w2;
    double h2;
    double fill1;
    double a1;
    double a2;
};

//二代数据不等厚焊缝数据
struct WELD_FORMAT_ASY
{

    bool m_symmetry;
    double W1;
    double H1;
    double W2;
    double H2;
    double W3;
    double m_thickness;//主板厚度
    double s_thickness;

};

enum KTY_ProbePosition {
    KTY_WED_1,
    KTY_WED_2,
    KTY_WING_1,
    KTY_WING_2,
    KTY_WING_3,
    KTY_WING_4
};

enum Cylinder_WeldDir {
    AXIAL,
    CIRC
};

struct WELD_II
{
    setup_WELD_TYPE_II       eType;		  /* 焊缝 */
    setup_WELD_SYMMETRY_TYPE eSymmetry;	  /* 对称 */
    KTY_ProbePosition eProbePos;         //TKY探头位置
    double eAngle;                       //TKY腹板与翼板夹角
    double eTopThinkness;                //TKY腹板厚度
    double eBottomThinkness;             //TKY翼板厚度
    double eHAZ;                         //焊缝热影响区
    float bottomCapHeight;
    float bottomCapOverlap;
    float topCapHeight;
    float topCapOverlap;
    Cylinder_WeldDir eWeldDir;          // 管道焊缝方向

    double l1;                          // 不等厚焊缝削边信息
    double h1;
    double l2;
    double h2;
    double a1;
    double a2;
    setup_PLANE_ALIGN_TYPE align;  //不等厚板对齐

    union{
        WELD_FORMAT_I  I;
        WELD_FORMAT_V  V;
        WELD_FORMAT_U  U;
        WELD_FORMAT_VY VY;
        WELD_FORMAT_VV VV;
        WELD_FORMAT_UU UU;
        WELD_FORMAT_UV UV;
        WELD_FORMAT_TKY TKY;
        WELD_FORMAT_ASY ASY;

    };
};

enum setup_PART_GEOMETRY
{
	setup_PART_GEOMETRY_FLAT = 0 ,
	setup_PART_GEOMETRY_OD ,
	setup_PART_GEOMETRY_ID ,
    setup_PART_GEOMETRY_BALL,
    setup_PART_GEOMETRY_ASYMMETRIC
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

enum WELD_FORMAT
{
    PHASCAN_I_FORMAT = 0,   //一代焊缝格式，解析weld
    PHASCAN_II_FORMAT       //二代焊缝格式，解析weld_ii
};

struct PART_CONFIG
{
	setup_PART_GEOMETRY	eGeometry;				/* 几何形状 FLAT/ID/OD/BALL */

	//geometry parameter
	float				afSize[4];				// sizes if necceray , part height , width , diameter
	MATERIAL			material;				/* 材料 */
    WELD_FORMAT         weldFormat;
	WELD				weld;					// weld
    WELD_II             weld_ii;
    float               weld_border;
    bool                CADFresh;
	char				strPartFile[256];		// Name of part file , *.ncc
};

enum setup_LAW_TYPE
{
    setup_LAW_TYPE_AZIMUTHAL = 0 ,   //角度
    setup_LAW_TYPE_LINEAR,           //线扫
    setup_LAW_TYPE_TFM               //全聚焦
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

struct CURVE_RL_EL_SL
{
    int CurRL[setup_MAX_GROUP_QTY];
    int CurEL[setup_MAX_GROUP_QTY];
    int CurSL[setup_MAX_GROUP_QTY];
    int bShowRL;
    int bShowEL;
    int bShowSL;
    float REF_Gain[setup_MAX_GROUP_QTY];
    float Com_Gain[setup_MAX_GROUP_QTY];
    float Couple_Com_Gain[setup_MAX_GROUP_QTY]; // 耦合监控增益补偿
    int CurSS[setup_MAX_GROUP_QTY];      //保存扫查灵敏度
    int Standard[setup_MAX_GROUP_QTY];   //tcg曲线标准的index
    int Thickness[setup_MAX_GROUP_QTY];  //tcg曲线厚度
    float Ref_Amp[setup_MAX_GROUP_QTY];  //二代数据加载标准后读取值，其它默认80
};

extern CURVE_RL_EL_SL CUR_RES;
enum setup_TRAVEL_MODE
{
    setup_TRAVEL_MODE_TRUE_DEPTH = 0,  //真实深度
    setup_TRAVEL_MODE_HALF_PATH,       //半声程
    setup_TRAVEL_MODE_TIME             //时间
} ;

enum DAC_MODE
{
    setup_DAC = 0,
    setup_TCG,
    setup_RL,
    setup_EL,
    setup_SL
};

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

//S扫反射类型显示
enum setup_REFLECT_TYPE
{
    CLOSE = 0,
    FIRST   ,
    LAST    ,
    OVERLAY

};

//S扫1:1显示
enum setup_REFLECT_SHOWS
{
    OFF = 0,
    ON

};

//S扫模式
enum setup_SSCANF_MODE
{
    S_MODE = 0,
    D_MODE

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
    setup_CURSOR_C_ANGLE ,
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

struct TOPC_INFO
{
    bool   TOPCValid;    //是否有topc
    bool   TOPCStatus;   //true开启  false关闭
    double TOPCWidth;
    float  startX;
    float  stopX;
    float  startY;
    float  stopY;
    int    pixelWidth;  //对应像素长度
    int    pixelHeigh;  //对应像素高度
    int    TOPCMergeStatus; //融合的状态 0 off 1 on
    int    TOPCMergeRefer; //融合关联的组Id
    int*   pDataIndex;  //通过坐标索引得到A扫数据的位置
};

struct TOPC_DATA
{
    int startX;
    int stopX;
    int startY;
    int stopY;
    int direction;
    WDATA *topcData;
};

enum RASTER_MODE
{
    raster_AMP = 0,
    raster_POS_ONE,
    raster_POS_TWO
};

struct RASTER_DATA
{
    float fStart1;	 // gate start position
    float fWidth1;	 // gate width
    unsigned int threshold1;
    float fStart2;
    float fWidth2;
    unsigned int threshold2;
    float fMinThickness;
    float fMaxThickness;
    RASTER_MODE rasterMode;
    WDATA *rasterData;
};

struct STORE_SCAN_LAWID
{
    bool  status;
    float scanPos;
    float depth;
    int   lawId;
    int   ZA;
    int   maxValue; // 当前缺陷在beam上的最高点值
};

typedef struct _Group
{
	setup_GROUP_MODE		eGroupMode;				/* 组工作模式  0 UT or 1 PA*/
    setup_TRAVEL_MODE		eTravelMode;            /*声轴单位*/
    setup_TX_RX_MODE		eTxRxMode;              /*收发模式*/
	/* 基本设置 */
	int						nWedgeDelay;			/* 楔款延时 单位 ns */
	int 					nTimeStart;				/* 时间起点 单位 ns */
	int						nTimeRange;				/* 时间范围 单位 ns */
    float					fSampleStart;			/* 扫描延时 单位 mm */
    float					fSampleRange;			/* 显示范围 单位 mm */
	int						nPointQty;				/* 点个数(采样深度) */
	float					fVelocity;				/* 声速 单位 m/s*/
	float					fGain;					/* 增益 0 - 80 db  _STEP 0.01dB */
    float					fRefGain;               // 调节增益增加，判定线不动
    float                   RefGain;                // 调节增益增加,判定线增加
    float                   CoupleGain;         //耦合补偿
    float                   CoupleMonitoringGain;         //耦合监控补偿

    int                     on_off_status;
    float					fSumGain ;                /* 总增益 */
	int						bPointQtyAuto;
	int						bSumGainAuto;
    bool                    coupleMonitoringState;     /* 耦合监控状态 true 开启  false 关闭 */
    int                     coupleMonitoringVelocity;  /* 耦合监控声速 单位 m/s*/
    bool                    bShowCoupleInAScan;        // A扫中显示耦合监控曲线
	/* 发射接收 */
    unsigned int			nTrigeStart;			/* 1~128 - elem_qty(聚焦阵元数最大为32) + 1 指定发射阵元与机器配置
                                                    相关我们是128阵元最大,值与connect P 一样 */
	unsigned int			nReceiveStart;			/* 接收阵元 必须是 PR 模式才能调节 */

	setup_FILTER_MODE		eFileter;		/* 滤波 */
	setup_RECTIFIER_MODE	eRectifier;		/* 检波 */
	setup_AVERAGE_MODE		eAveraging;		/* 平均 */
    int						bVedioFilter;   /* 视频滤波 */

	// 设置的探头频率，和对应的脉宽
	float					fTriFrequency;		/* Mhz*/
	unsigned int			nPulserWidth;		/* ns */

	/* 参考光标 */
	float					afCursor[setup_CURSOR_MAX] ;

	// thickness range for c scan display
	setup_CSCAN_SOURCE_MODE	eCScanSource[2] ;
	float					fMinThickness;		/* Measurements->Thickness->min */
	float					fMaxThickness;		/* Measurements->Thickness->max */
    int                     DisplayMode;        //显示模式
    bool                    CScanShowAll;       //C扫完整显示标志位，false 关闭，true开启。开启后加入扫查帧数大于C扫横向像素点
                                                //会压缩帧数
	// wedge position
	float					fScanOffset;		/*mm*/
	float					fIndexOffset;		/*mm*/
    setup_PROBE_ANGLE		eSkew;              /* 探头角度 */

    setup_REFLECT_TYPE      m_Retype; //S扫反射类型
    setup_REFLECT_SHOWS     m_Shows; //S扫1:1显示
    setup_SSCANF_MODE       m_mode;//S扫模式
    float zoomFactor;               //S扫1:1缩放因子-扫查轴坐标
    bool lawMove;                   //D扫的扫查轴移动标志

    int currentGroupId;             //D扫绘制组ID
    bool viewDragflage;             //视图拖拽切换显示标志位
    bool DrawCviewflage;            //绘制C视图标志
    bool LawMarker;                 //扫查轴标志位


	/*  校准状态  */
	int						bVelocityCalib;
	int						bWedgeDelayCalib;
	int						bSensationCalib;

	float					afGainOffset[setup_MAX_GROUP_LAW_QTY];
	unsigned int			anBeamDelay[setup_MAX_GROUP_LAW_QTY];
    float					afBeamPos[setup_MAX_GROUP_LAW_QTY];     // beam入射点的位置

    int                     aeMeasureIndex; //表示参数种类， 0 扇扫 1 线扫  2 tofd
    int						aeMeasureType[setup_MAX_MEASURE_QTY];
	int						bShowMeasure;
    bool                    bShowAScanMeasure;
    bool                    bShowBScanMeasure;
    bool                    bShowCScanMeasure;
    bool                    bShowSScanMeasure;
	int						bShowCursor;
	int						bShowWeldPart;
    int                     measuregateType[setup_MAX_MEASURE_QTY]; //测量闸门类型，measureGateStatus为true时读取显示此
    bool                    measureGateStatus; //测量闸门状态，开启将测量值前三个换成B闸门
    bool                    loadCurveData;

    //int						bShowGate;
    int                     bShowGateA;
    int                     bShowGateB;
    int                     bShowGateI;
	int						bShowThickness;
	int						bShowCurve;
	int						bShowLwBw;
    int						bShowDefect;
    bool                    bWeldRemainingHeight;
    bool                    bShowCurrentDefect;

	LAW_CONFIG				law;
	GATE_CONFIG				gate[setup_GATE_MAX] ;
	PART_CONFIG				part;
	WEDGE_CONFIG			wedge[2];
	PROBE_CONFIG			probe[2];
	CURVES					curve;
	GROUP_COLOR				color;
    int						ThicknessType[8];
    TOPC_INFO               TopCInfo;
    TOPC_DATA               TopCData;
    RASTER_DATA             RasterData;
    STORE_SCAN_LAWID        storeScanLawId;


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
    setup_ENCODER_TYPE_NONE,
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
    setup_SCAN_TYPE_RASTER,
    setup_SCAN_TYPE_HELICOIDAL
} ;

enum setup_SCAN_MODE
{
	setup_SCAN_NORMAL = 0 ,
	setup_SCAN_PARALLEL   ,
}  ;

/*scanner*/
/*
由于文档缺失，根据个人理解，scanner有时间编码和编码器编码，两种编码有几个变量的意义是不一样的：
在编码器编码情况下：
fScanPos     单位mm 表示扫查线当前位置
fIndexPos    单位mm 表示步进轴当前位置 适用于二维扫查,二维扫查无时间编码情况
fScanStart   单位mm 表示扫查的起点
fScanStop    单位mm 表示扫查的终点
fScanStart2  单位mm 值和fScanStart一样
fScanend     单位mm 值和fScanStop一样
在时间编码情况下：
fScanPos     单位秒 表示扫查线当前位置
fScanStart   表示扫查起始对应的index 值为 fScanStart2 * fPrf 取数据的索引值 工具栏的slider范围与此数据关联
fScanStop    表示扫查终点对应的index 值为 fScanend * fPrf    取数据的索引值 工具栏的slider范围与此数据关联
fScanStart2  单位秒 表示时间扫查的起点 和显示的坐标轴对应
fScanend     单位秒 表示时间扫查的终点 和显示的坐标轴对应
代码都是按此逻辑进行的debug，里面可能还有没有修改的逻辑，都需按照此逻辑进行修复。
*/
struct SCANNER
{

    setup_ENCODER_TYPE eScanEncoderType;
    setup_ENCODER_TYPE eIndexEncoderType;
	setup_SCAN_TYPE	eScanType	 ;
	setup_SCAN_MODE	eScanMode	 ;
	// scan pos
	float fScanPos	 ;
	float fIndexPos	;
	// scan speed
	float fPrf		 ;
	// scan range
	float fScanStart   ;
    float fIndexStart  ; //步进轴起点
	float fScanStop	;
    float fIndexStop   ; //步进轴终点
	float fScanStep	;
	float fIndexStep   ;
    float fScanStart2;
    float fScanend;
    int fLawStart ;
    int fLawStop;
    int fLawQty;
	// encoder
    ENCODER_CONFIG  encoder[setup_MAX_ENCODER_QTY];
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

struct AIDED_ANALYSIS
{
    int aidedGroupId;   //辅助分析的组
    bool aidedStatus;   //辅助分析的状态，true开启，false关闭
    int  aidedBeamId;   //分析得到的beamId
    int  aidedMethodId; //0 半波长  1 绝对灵敏度
};

struct COMMON_CONFIG
{
    int					nGroupQty	;         //总的组数量
	int					bUnifiedPart ;
    bool                dataModeStatus; //数据模式状态
	SONIC_AXIS_UNIT		eUAxisUnit   ;
	INSTRUMENT_CONFIG	instrument   ;
	ALARM_CONFIG		alarm   ;
	SCANNER				scanner ;
	//----------------------------
    int					nRecMax;    // 最大帧数 ?
	int					nDataSize;
    int					nScanOffMax; // 最大扫查偏置 ?
    int					nScanOff[setup_MAX_GROUP_QTY];//每组的扫查偏置
    U8					nRecMark[setup_MAX_REC_LEN];//保存帧数据的标志位，标志位非零表示该帧数据有效，值为0表示该帧数据无效，用于绘制C扫或者查找最近的有效帧
    bool                TOPCMergeValid;          //是否支持topc融合
    int                 TOPCMergeQty;            //topc融合的组总数，等于PA组数
    int                 TOPCMergeGroupId[setup_MAX_GROUP_QTY]; //可以融合的组的Id
    AIDED_ANALYSIS      aidedAnalysis;
    bool                bDefectIdentifyStatus;      // 在分析状态
    bool                bDefectIdentifyStatusDone;  // 分析完成
    bool                bMarkDefectNotIdentifyArea;  // 标记是否在框选缺陷不识别区域
} ;

struct DISPLAY_CONFIG
{    
    bool bShowRL;                                                                                   //11.是否显示RL,SL,EL,线
    bool bShowSL;
    bool bShowEL;
    bool bShowDAC[setup_MAX_GROUP_QTY];                                                             //16.DAC曲线
    bool bShowThickness[setup_MAX_GROUP_QTY];                                                       //7.是否开启厚度显示
    bool bShowWeld[setup_MAX_GROUP_QTY];                                                            //8.是否开启焊缝显示
    bool bShowMeasure[setup_MAX_GROUP_QTY];                                                         // 2.是否显示测量参数
    bool bShowCursor[setup_MAX_GROUP_QTY];                                                          // 5.是否显示测量光标
    int  anMeasureSelection[setup_MAX_GROUP_QTY][setup_MAX_MEASURE_QTY];                            // 4.测量参数的种类
    int  DisplayMode[setup_MAX_GROUP_QTY];                                                          //17.显示模式
    int  CScanSource[setup_MAX_GROUP_QTY][2];                                                       //14.C扫描1/C扫描2数据源
    float MinThickness[setup_MAX_GROUP_QTY];                                                        // 15.C扫最小厚度和最大厚度
    float MaxThickness[setup_MAX_GROUP_QTY];
    int   Standard[setup_MAX_GROUP_QTY];                                                            //10.标准
    bool bShowAScanMeasure[setup_MAX_GROUP_QTY];                                                    //3.测量参数的显示位置（A、B、C、S）
    bool bShowBScanMeasure[setup_MAX_GROUP_QTY];
    bool bShowCScanMeasure[setup_MAX_GROUP_QTY];
    bool bShowSScanMeasure[setup_MAX_GROUP_QTY];
    int   Thickness[setup_MAX_GROUP_QTY];                                                           // 曲线->标准->厚度

    setup_LANG       eLanguage;                                                                     // 1.中/英文模式
    bool bSAxisCursorSync;                                                                          //6.是否开启光标同步
    int bShowGateA[setup_MAX_GROUP_QTY];                                                            //9.表示A闸门可见性
    int bShowGateB[setup_MAX_GROUP_QTY];                                                            //表示B闸门可见性
    int bShowGateI[setup_MAX_GROUP_QTY];                                                            //表示I闸门可见性
    bool  bTOPCStatus[setup_MAX_GROUP_QTY];                                                         //12.C扫描模式（false=角度C,true=投影C）
    float TOPCWidth[setup_MAX_GROUP_QTY];                                                           //13. 如选择为投影C，需保存投影C扫描宽度的设置
};


#endif // INSTRUMENT_H





