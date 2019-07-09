#ifndef DPLDRAWSCAN_H
#define DPLDRAWSCAN_H

#include <QObject>
#include <configure/DopplerConfigure.h>
#include <QMutex>

class QImage ;

enum DRAW_TYPE
{
    NO_DRAW = -1,
    A_SCAN  = 0 ,
    B_SCAN      ,
    C_SCAN      ,
    S_SCAN      ,
    S_ASCAN     ,
    S_LSCAN
};

struct DrawInfo
{
    DRAW_TYPE nDrawType ;
    int       nGroupId  ;
    int       nBeamId   ;
    int       nPointQty ;
    //volatile unsigned char*  pData ;

    DrawInfo()
    {
        nDrawType = NO_DRAW  ;
        nGroupId  = 0        ;
        nBeamId   = 0        ;
        nPointQty = 600      ;
    }
};
class DopplerDrawScan : public QObject
{
    Q_OBJECT
public:
    explicit DopplerDrawScan(QObject *parent = 0);
    void SetDrawInfo(DrawInfo* cInfo_)  ;
    DrawInfo* GetDrawInfo();
    void SetColorIndex(void* pColor_) ;
    void TransformImage(int x1,int y1,U8 src[2048][2048],int x2,int y2,QImage* pImage);

    virtual void Draw(QImage* pImage_) = 0;
    virtual void UpdateDrawInfo () = 0;
    int                 zoomflag;      //视图缩放标志位  0：无缩放 1：有放大 2：右键恢复无缩放视图
    float               srcscanstart;
    float               srcscanstop;
    float               curscanstart;
    float               curscanstop;
    float               curIndexStartPos;  //用于栅格扫查
    float               curIndexStopPos;   //用于栅格扫查
    float               srcCstart;
    float               srcCend;
    float               srcCIndexStartPos; //用于栅格扫查
    float               srcCIndexEndPos;   //用于栅格扫查
    float               srcBstart;
    float               srcBend;
    int                 srclawstart;
    int                 srclawstop;
    double              curlawstart;
    double              curlawstop;
    int                 currangestart;
    int                 currangestop;
protected:
    virtual void UpdateDisplayRange(int nType_, int nRangle_ , int nPos_);
    virtual void UpdateIndexRange(int nType_, int nRangle_ , int nPos_);
protected:
	unsigned char		(*m_pColor)[3];
	DrawInfo			m_cInfo   ;
	DopplerConfigure*	m_pConfig;
	GROUP_CONFIG*		m_pGroup;
	QMutex				m_hMutex;
    int                 m_PosStart ;
    int                 m_PosStop  ;
    int m_indexStartIndex;
    int m_indexStopIndex;


signals:
	void signalScanRangeMove(int nType_, int nStart_, int nStop_) ;
    void signalIndexRangeMove(int nType_, int nStart_, int nStop_);
};

#endif // DPLDRAWSCAN_H
