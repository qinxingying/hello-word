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


    virtual void Draw(QImage* pImage_) = 0;
    virtual void UpdateDrawInfo () = 0;
protected:
	unsigned char		(*m_pColor)[3];
	DrawInfo			m_cInfo   ;
	DopplerConfigure*	m_pConfig;
	GROUP_CONFIG*		m_pGroup;
	QMutex				m_hMutex;

signals:
	void signalScanRangeMove(int nType_, int nStart_, int nStop_) ;
};

#endif // DPLDRAWSCAN_H
