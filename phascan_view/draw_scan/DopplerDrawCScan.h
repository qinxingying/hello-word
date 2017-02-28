#ifndef DOPPLERDRAWCSCAN_H
#define DOPPLERDRAWCSCAN_H

#include <configure/const.h>
#include "DopplerDrawScan.h"


enum CSCAN_TYPE
{
    CSCAN_AMP_A = 0,
    CSCAN_AMP_B ,
    CSCAN_POS_I ,
    CSCAN_POS_A ,
    CSCAN_POS_B ,
    CSCAN_POS_AI ,
    CSCAN_POS_BI ,
    CSCAN_POS_BA ,
    CSCAN_TYPE_MAX
} ;


struct C_SCAN_DRAW_INFO
{
    CSCAN_TYPE eType ;
    int   bRFmode    ;
    int   nGateHeight1;
    int   nGateHeight2;
    int   nThicknessStart ;
    int   nThicknessStop  ;

    int nLawQty      ;
    int nPointQty    ;
    int nFrameSize   ;
    int nGroupOffset ;

    int nWedgeDelay  ;
    int nPulserWidth ;
    unsigned char* pData ;
    U32*  pBeamDelay ;
} ;

class DopplerDrawCScanH : public DopplerDrawScan
{
    Q_OBJECT
public:
    explicit DopplerDrawCScanH(QObject *parent = 0);
    void UpdateDrawInfo();

    void SetCScanType(CSCAN_TYPE eType_);
    float* GetAngleScaleRate();

    virtual void Draw (QImage* pImage_);
private:
	void UpdateDrawInfo_private();
protected:
    enum GATE_TYPE
    {
        GATE_NONE = 0 ,
        GATE_A = 4 ,
        GATE_B = 8 ,
        GATE_I = 12
    };
	void UpdateScanPos(int nType_, int nRange_ , int nPos_);

    inline void GetPixValueInfo(int nScanPos_, GATE_TYPE eGate_, U32* pBuff_);
    inline void GetPixValuePos(U32* pBuff_);
    inline void GetPixValueDistance(U32* pBuff1_ , U32* pBuff2_);

	virtual void DrawGateAmplitude (QImage* pImage_ , GATE_TYPE eGate_) ;
    virtual void DrawGatePos (QImage* pImage_ , GATE_TYPE eGate1_ , GATE_TYPE eGate2_);
    int m_PosStart ;
    int m_PosStop  ;
    float m_afScale[256]  ;

    C_SCAN_DRAW_INFO m_CScanInfo ;
};

class DopplerDrawCScanV : public DopplerDrawCScanH
{
    Q_OBJECT
public:
    explicit DopplerDrawCScanV(QObject *parent = 0);

protected:
    virtual void DrawGateAmplitude (QImage* pImage_ , GATE_TYPE eGate_) ;
    virtual void DrawGatePos (QImage* pImage_ , GATE_TYPE eGate1_ , GATE_TYPE eGate2_);
} ;

#endif // DOPPLERDRAWCSCAN_H
