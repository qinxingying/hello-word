#ifndef DOPPLERTOFDOPP_H
#define DOPPLERTOFDOPP_H

#include <QObject>
#include <QRectF>
#include <configure/DopplerConfigure.h>
#include "../process/ParameterProcess.h"


class DopplerTofdOpp : public QObject
{
    Q_OBJECT
public:
    explicit DopplerTofdOpp(QObject *parent = 0);
    void SetGroupId(int nGroupId_);
    TOFD_PRO_STATUS TofdDragProStatus(int nGroupId_);

private:
    int TofdSearchPos(WDATA* pSource_, int iStart, int iMax, int iMin, int iEdge_);
public:
    int TofdDragProStart(int nGroupId_, TOFD_PRO_STATUS proSt_);
	int TofdDataProStart(int nGroupId_, TOFD_PRO_STATUS proSt_, GYRECT* pRect_);
    int TofdDragProcess(int nGroupId_, AREAF rcArea_);
    int TofdDataToShadow(int nGroupId_);
    int TofdDataProRepeal(int nGroupId_);
    int TofdDataProRedo(int nGroupId_);
    void TofdClearDragStatus(int nGroupId_);
    int TofdProStr(int nGroupId_, char* pStr_);
    int TofdDragProStr(int nGroupId_, char* pStr_);
private:
    int TofdDataProcess(int nGroupId_, TOFD_PRO_INFO* pInfo, WDATA* pSource_, WDATA* pDest_);
    int TofdLwStraitening(int nGroupId_, TOFD_PRO_INFO* pInfo_, WDATA* pSource_, WDATA* pDest_);
    int TofdBwStraitening(int nGroupId_, TOFD_PRO_INFO* pInfo_, WDATA* pSource_, WDATA* pDest_);
    int TofdDifference(int nGroupId_, TOFD_PRO_INFO* pInfo_, WDATA* pSource_, WDATA* pDest_);
    int TofdSaft(int nGroupId_, TOFD_PRO_INFO* pInfo_, WDATA* pSource_, WDATA* pDest_);

    int TofdSAFTInit(int nGroupId_, TOFD_PRO_INFO* pInfo_, int* pCurveBuf);
	void TofdWavAlign(int iBase_, int iDot_, WDATA* pSource_, WDATA* pDest_, GYRECT rect_);


    DopplerConfigure* m_pConfig;
    ParameterProcess* m_process;
    GROUP_CONFIG*     m_pGroup;
    SCANNER*          m_pScanner;
	//int               m_iPosMax;
    TOFD_PARA*        m_pTofd ;
    int               m_nGroupId ;

signals:

public slots:

};

#endif // DOPPLERTOFDOPP_H
