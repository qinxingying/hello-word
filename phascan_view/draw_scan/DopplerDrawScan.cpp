#include "DopplerDrawScan.h"
#include "string.h"
#include <QImage>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <assert.h>

DopplerDrawScan::DopplerDrawScan(QObject *parent) :
    QObject(parent)
{
	m_pConfig = DopplerConfigure::Instance() ;
}

void DopplerDrawScan::SetDrawInfo(DrawInfo* pInfo_)
{
    memcpy((void*)&m_cInfo , (void*)pInfo_ , sizeof(DrawInfo))  ;
	m_pGroup   = &m_pConfig->group[m_cInfo.nGroupId]  ;
}

DrawInfo* DopplerDrawScan::GetDrawInfo()
{
    return &m_cInfo  ;
}

void DopplerDrawScan::SetColorIndex(void* pColor_)
{
    m_pColor = (unsigned char (*)[3])pColor_ ;
}

#define MAX_SCAN_INDEX  10000
void DopplerDrawScan::UpdateDisplayRange(int nType_, int nRangle_, int nPos_)
{
    if(nPos_ < 0) nPos_ = 0;

    if(nPos_<= m_PosStart)
    {
        m_PosStart = nPos_  ;
        m_PosStop  = m_PosStart + nRangle_ - 1 ;
        if(m_PosStop > MAX_SCAN_INDEX)
        {
            m_PosStart = MAX_SCAN_INDEX -  nRangle_ + 1 ;
            m_PosStop  = MAX_SCAN_INDEX;
        }
    }else if(nPos_ >= m_PosStop)
    {
        m_PosStop = nPos_  ;
        m_PosStart  = m_PosStop - nRangle_ + 1 ;
        if(m_PosStart < 0)
        {
            m_PosStart = 0  ;
            m_PosStop  = nRangle_ - 1  ;
        }
    }
    emit signalScanRangeMove(nType_, m_PosStart, m_PosStop) ;
}
