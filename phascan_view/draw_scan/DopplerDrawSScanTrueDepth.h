#ifndef DOPPLERDRAWSSCANAZIMUTHAL_H
#define DOPPLERDRAWSSCANAZIMUTHAL_H

#include <configure/const.h>
#include "DopplerDrawScan.h"
#include "DopplerDataView.h"
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
    void DrawPixbuff(QImage* pImage_) ;
    void CalcDscanDate(WDATA* _pData,QImage* pImage_,int num);
    void CalcDscanDateReflect(WDATA* _pData,QImage* pImage_,int num);

protected:
    void CalcMatrix();
    void CreateMatrixBuff();
    void ReleaseMatrixBuff();
    bool MatrixBuffValid();
    void CalcMatrixAzimuthal(FAN_SCAN_INFO* pInfo_) ;
    void CalcMatrixLinear(FAN_SCAN_INFO* pInfo_);

    int m_PosStart ;
    int m_PosStop  ;
    int m_nScanPos ;
    int m_nGroupOffset ;
    int m_nFrameOffset ;

    FAN_SCAN_INFO m_SScaninfo  ;
    float _nStepX , _nStepY;
    int m_nWidth , m_nHeight ;
    float m_thickness {0.0};
    int m_reType {0};
    int m_Shows{0};

    U8*  m_pAngleZoom;
    U8*  m_pDraw;
    U8*  m_pDrawRate;
    U8*  m_pColRate;
    int* m_pDataNo;
    bool m_bClear;
    bool m_bWeldRemainingHeightAffect {false}; 
    float m_zoomFactor;
    int m_xoffset; //180/270°中 x(像素)的偏移量
    int m_width;
    int m_cursorOffset;
    QVector <QVector<int>>m_tempdata;
    QVector <QVector<int>>m_RefTempdata;
};

#endif // DOPPLERDRAWSSCANAZIMUTHAL_H
















