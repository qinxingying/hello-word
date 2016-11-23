#include <QString>
#include <qdatetime.h>
#include <QColor>

#include "process/dopplerfocallaw.h"

#define __DPL_DEBUG__

/****************************************************************************
  Name:  const.h
  Copyright: Sheng Shen
  Date : 2013-08-26
  Description:   ������ֳ���
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

typedef U8				WDATA;	//	���岨������λ�� 8λ

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
//��������β�ĳ���
#define setup_DATA_PENDIX_LENGTH			32

#define setup_MAX_TOFD_PRO_N				8


#define setup_DATA_ALIAN					1024
#define setup_DATA_OFFSET					2
// ��ɨͼ
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

extern const U8 g_iToolSeparator[];
extern const char* g_strToolBarIconName[];

extern const char* g_strLanguageName[];
extern const char* g_strToolBarName[][4];
extern const char* g_strTravelMode[][4];
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
	FEILD_A100,				// "A%			բ��A�ڷ�ֵ����",
	FEILD_AdBA,				// "AdBA		բ��A�ڷ�ֵ������բ����ֵ����֮�dB��",
	FEILD_AdBr,				// "AdBr		բ��A�ڷ�ֵ������ο��źŷ���֮�dB��",
	FEILD_B100,				// "B%			բ��B�ڷ�ֵ����",
	FEILD_BdBB,				// "BdBB		բ��B�ڷ�ֵ������բ����ֵ����֮�dB��",
	FEILD_BdBr,				// "BdBr		բ��B�ڷ�ֵ������ο��źŷ���֮�dB��",
	FEILD_APos,				// "A^			բ��A�ڷ�ֵλ��",
	FEILD_BPos,				// "B^			բ��B�ڷ�ֵλ��",
	FEILD_IEdge,			// "I/			բ��I��ǰ��λ��",
	FEILD_IEdgeInWater,		// "I(w)/		Position in gate I in water",
	FEILD_ThicknessAPos,	// "T(A^)		���",
	FEILD_ML,				// "ML			������ʧ�ٷֱ�",
	FEILD_r100,				// "%(r)		�ο����λ�õķ���ֵ",
	FEILD_m100,				// "%(m)		�������λ�õķ���ֵ",
	FEILD_mr100,			// "%(m-r)		�������ķ���ֵ��ȥ�ο��źŵķ���ֵ)",
	FEILD_Ur,				// "U(r)		�ο�����ڳ������ϵ�λ��",
	FEILD_Um,				// "U(m)		��������ڳ������ϵ�λ��",
	FEILD_Umr,				// "U(m-r)		�������ϲ������λ����ο����λ��֮��",
	FEILD_Pr,				// "P(r)		����ڲο�����̽ͷλ��",
	FEILD_Pm,				// "P(m)		����ڲ�������̽ͷλ��",
	FEILD_Pmr,				// "P(m-r)		̽ͷ����ڲ��������ο�����ֵ��λ��",
	FEILD_Sr,				// "S(r)		ɨ�����ϲο�����λ��",
	FEILD_Sm,				// "S(m)		ɨ�����ϲ�������λ��",
	FEILD_Smr,				// "S(m-r)		ɨ�����ϲ��������ο����ľ���",
	FEILD_Ir,				// "I(r)		�������ϲο�����λ��",
	FEILD_Im,				// "I(m)		�������ϲ�������λ��",
	FEILD_Imr,				// "I(m-r)		�������ϲ��������ο����ľ���",
	FEILD_RA,				// "RA^			�����������բ��A�ڼ�⵽��ȱ��֮��ľ���",
	FEILD_RB,				// "RB^			�����������բ��B�ڼ�⵽��ȱ��֮��ľ���",
	FEILD_PA,				// "PA^			̽ͷǰ������բ��A�ڼ�⵽��ȱ�ݵľ���",
	FEILD_PB,				// "PB^			̽ͷǰ������բ��B�ڼ�⵽��ȱ�ݵľ���",
	FEILD_DA,				// "DA^			բ��A�ڼ�⵽��ȱ���ڹ����е����",
	FEILD_DB,				// "DB^			բ��B�ڼ�⵽��ȱ���ڹ����е����",
	FEILD_SA,				// "SA^			��������㵽բ��A�ڼ�⵽��ȱ��֮�������",
	FEILD_SB,				// "SB^			��������㵽բ��B�ڼ�⵽��ȱ��֮�������",
	FEILD_ViA,				// "ViA^		բ��A�ڼ�⵽��ȱ������ڲ�����������λ",
	FEILD_ViB,				// "ViB^		բ��B�ڼ�⵽��ȱ������ڲ�����������λ",
	FEILD_VsA,				// "VsA^		բ��A�ڼ�⵽��ȱ�������ɨ����������λ",
	FEILD_VsB,				// "VsB^		բ��B�ڼ�⵽��ȱ�������ɨ����������λ",
	FEILD_LA,				// "LA^			������̽ͷ��բ��A̽�⵽��ȱ���ڲ����е�·���ı����",
	FEILD_LB,				// "LB^			������̽ͷ��բ��B̽�⵽��ȱ���ڲ����е�·���ı����",
	FEILD_TofdDepth1 ,
	FEILD_TofdDepth2 ,
	FEILD_TofdLength ,
	FEILD_TofdHeight ,
	FEILD_VALUE_INDEX_MAX
};


extern const char* g_strPartDir;


#endif // CONST_H


