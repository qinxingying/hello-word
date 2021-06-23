#ifndef DOPPLERFOCALLAW_H
#define DOPPLERFOCALLAW_H

#define DOPPLER_EXPORT __declspec(dllexport)

#include <string.h>
#include <math.h>
#include <malloc.h>

typedef struct _GYRECT
{
	int left;
	int top;
	int right;
	int bottom;
}GYRECT;

enum TOFD_PRO_STATUS
{
	TOFD_PRO_NONE = 0 ,
	TOFD_PRO_STRAIGHT,
	TOFD_PRO_BOTTOM,
	TOFD_PRO_DIFFERENC,
	TOFD_PRO_SAFT,
	TOFD_PRO_REPEAL,
	TOFD_PRO_REDO
};

struct TOFD_PRO_INFO
{
	TOFD_PRO_STATUS	eType;
	GYRECT			rcArea;
	float			fX;
	float			fY;
	int				iDots;
};

struct TOFD_PARA
{
	float fLayerStart;
	float fLayerEnd;
	float fArcH;

	float fRefPoint;
	float fWedgeSep;
	float fPCS;

	float fZeroOff;
	float fDepthCal;

	float fZero;
	float fD;
	float fC;
	float fTb;
	float fTa;
	float fT0;

	float fPcs;

	TOFD_PRO_STATUS eProingST;
	TOFD_PRO_INFO   proInfo[9];
	int iProCnt;
	int iSaftBuf[8192*40];
};


extern "C" DOPPLER_EXPORT void sleep(unsigned int msec);
extern "C" DOPPLER_EXPORT float GetDepth(float h_, float ply_);
extern "C" DOPPLER_EXPORT float GateHeight(int nThreshold_, int nRectify_);
extern "C" DOPPLER_EXPORT float CalPeakAmp(float nPeak_, int nRectify_);
extern "C" DOPPLER_EXPORT void CharFilter(char* source, char* rule);
extern "C" DOPPLER_EXPORT void CheckLockFlag(const char *FormatStr);
extern "C" DOPPLER_EXPORT void LockRegStr(char *input,char *output,int len);
extern "C" DOPPLER_EXPORT bool UnLockRegStr(char *input, char *output, const char *FormatStr, int len);
extern "C" DOPPLER_EXPORT float FittedCurveDTX(float dY_, float C_, float TX0_, float T0_ );
extern "C" DOPPLER_EXPORT float FittedCurveDTXParallel(float dY_, float C_, float TX0_, float T0_, float fPcs_);

extern "C" DOPPLER_EXPORT void TofdProbeDelay(TOFD_PARA* pTofd_);
extern "C" DOPPLER_EXPORT void TofdPcs(TOFD_PARA* pTofd_);
extern "C" DOPPLER_EXPORT float TofdDepth(TOFD_PARA* pTofd_, float T_, float fCursorPos_);

#endif // DOPPLERFOCALLAW_H
