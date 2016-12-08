#include <QString>
#include <qdatetime.h>
#include <QColor>

#include "process/dopplerfocallaw.h"

#define __DPL_DEBUG__

/****************************************************************************
  Name:  const.h
  Copyright: Sheng Shen
  Date : 2013-08-26
  Description:   定义各种常量
		 .............
*****************************************************************************/
////////////////////////////////////////////////////////////////

typedef char			S8;
typedef unsigned char	U8;

typedef short			S16;
typedef unsigned short	U16;

typedef int				S32;
typedef unsigned int	U32;


typedef float			F32;
typedef double			F64;

typedef U8				WDATA;	//	定义波形数据位宽 8位

#define WAVE_MAX		255
#define WAVE_HALF		128

#define DEFECT_SIGN_MAX	40
////////////////////////////////////////////////////////////////


#define setup_MAX_GROUP_QTY					8

#define setup_MAX_CHANNEL_TRIGGER			32
#define setup_MAX_CHANNEL_RECIEVE			128

#define setup_MAX_GROUP_LAW_QTY				256
#define setup_MAX_LAW_QTY					1024
#define setup_MAX_PROBE_ELEMENT_ACTIVE		32
#define setup_MAX_PROBE_ELEMENT				128

#define setup_MAX_REC_LEN					1024 * 256

#define setup_MAX_FRAME_SIZE				192*1024
//波形数据尾的长度
#define setup_DATA_PENDIX_LENGTH			32

#define setup_MAX_TOFD_PRO_N				8


#define setup_DATA_ALIAN					1024
#define setup_DATA_OFFSET					2
// 扇扫图
#define FLOAT_ZERO_GATE						0.00001
#define COLOR_STEP							32		/*	4	8	16	32	64*/
#define COLOR_SHIFT							5		/*	2	3	4	5	6*/
#define SYSTEM_TIME_ERROR					-365000

#define LAW_1_COLOR							QColor(200 , 0  ,200)
#define LAW_2_COLOR							QColor(200 , 200,  0)
#define LAW_3_COLOR							QColor(200 , 0  ,  0)
//#################################################################
extern const char* g_strMeasureFildName[][4] ;
extern const char* g_strMeasureFildUnit[][4] ;

extern const char* g_strLanguageName[];
extern const char* g_strTxRxMode[][4];
extern const char* g_strScanMode[][4];
extern const char* g_strGeometry[][4];
extern const char* g_strRectifier[][4];
extern const char* g_strTofdScanMode[][4];
extern const char* g_strTofdProMode[][4];
extern const char* g_strWeldType[][4];
extern const char* g_strSymmetry[][4];
extern const char* g_strLawType[][4];
extern const char* g_strAngleType[][4];
extern const char* g_strFocalType[][4];
extern const char* g_strSkewAngle[][4];
extern const char* g_strGateSelect[][4];
extern const char* g_strGateSync[][4];
extern const char* g_strGateMeasure[][4];
extern const char* g_strSizingCurve[][4];
extern const char* g_strColorLineColor[][4];
extern const char* g_strCScanSource[][4];
extern const char* g_strWeldPartSel[][4];
extern const char* g_strScanType[][4];
extern const char* g_strEncoderType[][4];
extern const char* g_strPolarity[][4];
extern const char* g_strDirection[][4];

extern const char* g_strReportName[4];
extern const char* g_strTofdReportHead[][4];
extern const char* g_strReportHead[][4];
extern const char* g_strReportPath[][4];
extern const char* g_strLawConfig[][4];
extern const char* g_strMaterial[][4];
extern const char* g_strProbe[][4];
extern const char* g_strGroupSetup[][4];
extern const char* g_strCalculator[][4];
extern const char* g_strGroupPart[][4];
extern const char* g_strSignature[][4];
extern const char* g_strOnOff[][4];
extern const char* g_strDefect[][4];
extern const char* g_strReportSetGroupParamMode[][4];

extern int ToolBarCnt();
extern QString GetExePathName2(char* dir);
extern void GetExePathName1(char* dir, char* _strPathName);
extern bool VerRegInfo(char* strRegInfo_, char* strCpuID_);
extern int GetRegDays(char* strRegInfo_, QDate last_);
extern QDate GetSysTime(void);
extern void GetHardwareInfo(char* strInfo_);
//#################################################################
#ifndef CONST_H
#define CONST_H



enum FEILD_VALUE_INDEX
{
	FEILD_NONE  = 0 ,
	FEILD_A100,				// "A%			闸门A内峰值幅度",
	FEILD_AdBA,				// "AdBA		闸门A内峰值幅度与闸门阈值幅度之差（dB）",
	FEILD_AdBr,				// "AdBr		闸门A内峰值幅度与参考信号幅度之差（dB）",
	FEILD_B100,				// "B%			闸门B内峰值幅度",
	FEILD_BdBB,				// "BdBB		闸门B内峰值幅度与闸门阈值幅度之差（dB）",
	FEILD_BdBr,				// "BdBr		闸门B内峰值幅度与参考信号幅度之差（dB）",
	FEILD_APos,				// "A^			闸门A内峰值位置",
	FEILD_BPos,				// "B^			闸门B内峰值位置",
	FEILD_IEdge,			// "I/			闸门I的前沿位置",
	FEILD_IEdgeInWater,		// "I(w)/		Position in gate I in water",
	FEILD_ThicknessAPos,	// "T(A^)		厚度",
	FEILD_ML,				// "ML			材料损失百分比",
	FEILD_r100,				// "%(r)		参考光标位置的幅度值",
	FEILD_m100,				// "%(m)		测量光标位置的幅度值",
	FEILD_mr100,			// "%(m-r)		测量光标的幅度值减去参考信号的幅度值)",
	FEILD_Ur,				// "U(r)		参考光标在超声轴上的位置",
	FEILD_Um,				// "U(m)		测量光标在超声轴上的位置",
	FEILD_Umr,				// "U(m-r)		超声轴上测量光标位置与参考光标位置之差",
	FEILD_Pr,				// "P(r)		相对于参考光标的探头位置",
	FEILD_Pm,				// "P(m)		相对于测量光标的探头位置",
	FEILD_Pmr,				// "P(m-r)		探头相对于测量光标与参考光标差值的位置",
	FEILD_Sr,				// "S(r)		扫查轴上参考光标的位置",
	FEILD_Sm,				// "S(m)		扫查轴上测量光标的位置",
	FEILD_Smr,				// "S(m-r)		扫查轴上测量光标与参考光标的距离",
	FEILD_Ir,				// "I(r)		步进轴上参考光标的位置",
	FEILD_Im,				// "I(m)		步进轴上测量光标的位置",
	FEILD_Imr,				// "I(m-r)		步进轴上测量光标与参考光标的距离",
	FEILD_RA,				// "RA^			声束出射点与闸门A内检测到的缺陷之间的距离",
	FEILD_RB,				// "RB^			声束出射点与闸门B内检测到的缺陷之间的距离",
	FEILD_PA,				// "PA^			探头前表面与闸门A内检测到的缺陷的距离",
	FEILD_PB,				// "PB^			探头前表面与闸门B内检测到的缺陷的距离",
	FEILD_DA,				// "DA^			闸门A内检测到的缺陷在工件中的深度",
	FEILD_DB,				// "DB^			闸门B内检测到的缺陷在工件中的深度",
	FEILD_SA,				// "SA^			声束出射点到闸门A内检测到的缺陷之间的声程",
	FEILD_SB,				// "SB^			声束出射点到闸门B内检测到的缺陷之间的声程",
	FEILD_ViA,				// "ViA^		闸门A内检测到的缺陷相对于步进轴的体积定位",
	FEILD_ViB,				// "ViB^		闸门B内检测到的缺陷相对于步进轴的体积定位",
	FEILD_VsA,				// "VsA^		闸门A内检测到的缺陷相对于扫查轴的体积定位",
	FEILD_VsB,				// "VsB^		闸门B内检测到的缺陷相对于扫查轴的体积定位",
	FEILD_LA,				// "LA^			声波从探头到闸门A探测到的缺陷在材料中的路径改变次数",
	FEILD_LB,				// "LB^			声波从探头到闸门B探测到的缺陷在材料中的路径改变次数",
	FEILD_TofdDepth1 ,
	FEILD_TofdDepth2 ,
	FEILD_TofdLength ,
	FEILD_TofdHeight ,
	FEILD_VALUE_INDEX_MAX
};


extern const char* g_strPartDir;


#endif // CONST_H


