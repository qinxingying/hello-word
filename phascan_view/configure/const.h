/*********************************
  Name:  const.h
  Description:   ������ֳ���
*********************************/

#include <QString>
#include <qdatetime.h>
#include <QColor>

#include "process/dopplerfocallaw.h"

#define __DPL_DEBUG__

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
#define WAVE_HALF		256

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

extern const char* g_strMeasureFildName[][4];
extern const char* g_strMeasureFildUnit[][4];
extern const char* g_strThicknessStandard[];
extern const double g_ValuedbStandard[4][3][3];
extern QString GetExePathName2(char* dir);
extern void GetExePathName1(char* dir, char* _strPathName);

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
    FEILD_APos_DEC_IPos,
    FEILD_BPos_DEC_IPos,
    FEILD_RL,
    FEILD_EL,
    FEILD_SL,
    FEILD_VALUE_INDEX_MAX,
};
#endif // CONST_H


