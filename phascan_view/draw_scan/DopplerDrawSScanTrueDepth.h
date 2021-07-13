#ifndef DOPPLERDRAWSSCANAZIMUTHAL_H
#define DOPPLERDRAWSSCANAZIMUTHAL_H

#include <configure/const.h>
#include "DopplerDrawScan.h"

//#define FLOAT_ZERO_GATE 0.00001
//#define COLOR_STEP  32     /*    4  8  16  32  64*/
//#define COLOR_SHIFT 5      /*    2  3   4   5   6*/

//#define BUFF_MAX_WIDTH   2048
//#define BUFF_MAX_HEIGHT  2048
//#define BUFF_MAX_SIZE   (BUFF_MAX_WIDTH * BUFF_MAX_HEIGHT)

 const int OFFSET_Y=15;
//#define OFFSET_Y 25
struct FAN_SCAN_INFO
{
    int      nStartElement ;
    int      nStopElement  ;
    int      nStepElement  ;
    int      nElementQty   ;

    float   fStartAngle;
    float   fStopAngle ;
    float   fStepAngle ;

    float   fSampleStart ;
    float   fSampleRange ;
    float*   pExitPoint   ;     // beam入射点的位置
    int      nPointQty    ;
    int      width ;
    int      height ;
    int      group  ;
    int      direction  ;

    int eType ;
}  ;


class DopplerDrawSScanTrueDepth : public DopplerDrawScan
{
    Q_OBJECT
public:
    explicit DopplerDrawSScanTrueDepth();
    ~DopplerDrawSScanTrueDepth();
    void UpdateDrawInfo() ;
    virtual void Draw (QImage *pImage_) ;


protected:
    void CalcMatrix();
    void CreateMatrixBuff();
    void ReleaseMatrixBuff();
    bool MatrixBuffValid();
    void CalcMatrixAzimuthal(FAN_SCAN_INFO* pInfo_) ;
    void CalcMatrixLinear(FAN_SCAN_INFO* pInfo_);
    void DrawPixbuff(QImage* pImage_) ;

    int m_PosStart ;
    int m_PosStop  ;
    int m_nScanPos ;
    int m_nGroupOffset ;
    int m_nFrameOffset ;

    FAN_SCAN_INFO m_SScaninfo  ;
    float _nStepX , _nStepY;

    float thickness;
    int m_nWidth , m_nHeight ;
    U8*  m_pAngleZoom;
    U8*  m_pDraw;
    U8*  m_pDrawRate;
    U8*  m_pColRate;
    int* m_pDataNo;
    bool m_bClear;
    bool m_bWeldRemainingHeightAffect {false};
};

#endif // DOPPLERDRAWSSCANAZIMUTHAL_H
