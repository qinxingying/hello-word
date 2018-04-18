/************************************
  Name:  INSTRUMENT_H
  Description:   ���Ʋ����Ķ���
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

enum setup_DISPLAY_CSCAN_SOURCE	 //Cɨ��������ʾ����
{
	setup_DISPLAY_CSCAN_A  = 0	,
	setup_DISPLAY_CSCAN_B		 ,
	setup_DISPLAY_CSCAN_THICKNESS ,
	setup_DISPLAY_CSCAN_OFF
}  ;

//######################################################################
enum setup_GATE_NAME   //բ������
{
	setup_GATE_A = 0 ,
	setup_GATE_B	 ,
	setup_GATE_I	 ,
	setup_GATE_MAX
}  ;

enum setup_GATE_AYNC_TYPE   //բ�Ÿ��ٷ�ʽ
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
/*̽ͷ(PROBE)*/

struct PROBE_CONFIG
{
	char	 strName[64];
	char	 strSerial[64];

	int	  nElementPri;		//������Ԫ��
	int	  nElementSec;		//������Ԫ��
	int	  nLocationPolicy ;   // ��ά̽ͷ������˳��

	float	fFrequency ;		//MHz
	float	fPitchPri  ;		//������
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


/*Ш��(Wedge)*/
struct WEDGE_CONFIG
{
	char	 strName[64];
	char	 strSerial[64];

	setup_WEDGE_TYPE eType ;
	setup_WEDGE_ORIENTATION eDirection ;

	float	fWedgeAngle; /* Ш��� */
	float	fRoofAngle ; /* ���� */

	float	fVelocityLon;/*�ݲ�����*/
	float	fVelocityTra;/*�Შ����*/

	float	fHeigtFirst ;  /*��һ��Ԫ�߶�*/
	float	fOffsetFir;	/*������Ԫƫ��*/
	float	fOffsetSec;	/*������Ԫƫ��*/
	float	fPriAxisRef;   /*����Ш��ο�λ��*/
	float	fSecAxisRef;   /*����Ш��ο�λ��*/

	float	fLength;/*Ш�鳤��*/
	float	fWidth ;/*Ш����*/
	float	fHeight;/*Ш��߶�*/

	//ut ̽ͷ����
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
	setup_WELD_TYPE   				 eType	;		/* ���� */
	setup_WELD_SYMMETRY_TYPE		 eSymmetry;		/* �Գ� */

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
	setup_PART_GEOMETRY	eGeometry;				/* ������״ FLAT/ID/OD/BALL */

	//geometry parameter
	float				afSize[4];				// sizes if necceray , part height , width , diameter
	MATERIAL			material;				/* ���� */
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
/* �����Ϣ */
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

enum setup_FILTER_MODE	 //�˲�ģʽ
{
	setup_FILTER_NONE = 0 ,
	setup_FILTER_AUTO	 ,
	setup_FILTER_1_MHZ	,
	setup_FILTER_2_5MHZ   ,
	setup_FILTER_5_MHZ	,
	setup_FILTER_7_5MHZ   ,
	setup_FILTER_10_MHZ
} ;

enum setup_RECTIFIER_MODE  //�첨ģʽ
{
	setup_RECTIFIER_RF = 0		  ,
	setup_RECTIFIER_HW_POSITIVE	 ,
	setup_RECTIFIER_HW_NEGTIVE	  ,
	setup_RECTIFIER_FW
};

enum setup_AVERAGE_MODE   //ƽ��
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
	setup_CURSOR_LAW = 0 , /* �ο���굱ǰ�۽�����*/
	setup_CURSOR_A_REF   , /* �ο����ĸ߶� */
	setup_CURSOR_A_MES   , /* �������ĸ߶� */
	setup_CURSOR_U_REF   , /* �ο�����ڳ������λ�� */
	setup_CURSOR_U_MES   , /* ��������ڳ������λ�� */
	setup_CURSOR_S_REF   , /* �ο������ɨ�����λ�� */
	setup_CURSOR_S_MES   , /* ���������ɨ�����λ�� */
	setup_CURSOR_I_REF   , /* �ο������ָ�����λ�� */
	setup_CURSOR_I_MES   , /* ���������ָ�����λ�� */
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
	setup_GROUP_MODE		eGroupMode;				/* �鹤��ģʽ  0 UT or 1 PA*/
	setup_TRAVEL_MODE		eTravelMode;
	setup_TX_RX_MODE		eTxRxMode;
	/* �������� */
	int						nWedgeDelay;			/* Ш����ʱ ��λ ns */
	int 					nTimeStart;				/* ʱ����� ��λ ns */
	int						nTimeRange;				/* ʱ�䷶Χ ��λ ns */
	float					fSampleStart;			/* ��ʾ��Χ ��λ mm */
	float					fSampleRange;			/* ɨ����ʱ ��λ mm */
	int						nPointQty;				/* �����(�������) */
	float					fVelocity;				/* ���� ��λ m/s*/
	float					fGain;					/* ���� 0 - 80 db  _STEP 0.01dB */
	float					fRefGain;
	float					fSumGain ;
	int						bPointQtyAuto;
	int						bSumGainAuto;
	/* ������� */
	unsigned int			nTrigeStart;			/* 1~128 - elem_qty(�۽���Ԫ�����Ϊ32) + 1 ָ��������Ԫ������������������128��Ԫ���,ֵ��connect P һ�� */
	unsigned int			nReceiveStart;			/* ������Ԫ ������ PR ģʽ���ܵ��� */

	setup_FILTER_MODE		eFileter;		/* �˲� */
	setup_RECTIFIER_MODE	eRectifier;		/* �첨 */
	setup_AVERAGE_MODE		eAveraging;		/* ƽ�� */
	int						bVedioFilter;

	// ���õ�̽ͷƵ�ʣ��Ͷ�Ӧ������
	float					fTriFrequency;		/* Mhz*/
	unsigned int			nPulserWidth;		/* ns */

	/* �ο���� */
	float					afCursor[setup_CURSOR_MAX] ;

	// thickness range for c scan display
	setup_CSCAN_SOURCE_MODE	eCScanSource[2] ;
	float					fMinThickness;		/* Measurements->Thickness->min */
	float					fMaxThickness;		/* Measurements->Thickness->max */
	// wedge position
	float					fScanOffset;		/*mm*/
	float					fIndexOffset;		/*mm*/
	setup_PROBE_ANGLE		eSkew;

	/*  У׼״̬  */
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
enum setup_ENCODER_TYPE   //ɨ������Դ
{
	setup_ENCODER_TYPE_TIMER = 0,
	setup_ENCODER_TYPE_ENCODER_1,
	setup_ENCODER_TYPE_ENCODER_2,
	setup_ENCODER_TYPE_MAX
};

/*Different counter types for encoder input*/
enum setup_ENCODER_MODE   //����
{
	setup_ENC_MODE_QUADRATURE = 0 ,	//  ����
	setup_ENC_MODE_UP		,		 //  ����
	setup_ENC_MODE_DOWN				//  ����
} ;

enum setup_ENCODER_POLARITY  //����
{
	setup_ENC_POLARITY_NORNAL = 0,	//����
	setup_ENC_POLARITY_REVERSE		//����
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





