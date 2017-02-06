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
