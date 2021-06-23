#include "DopplerDrawScan.h"
#include "string.h"
#include <QImage>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <assert.h>
#include <qmath.h>
DopplerDrawScan::DopplerDrawScan(QObject *parent) :
    QObject(parent)
{
	m_pConfig = DopplerConfigure::Instance() ;
    zoomflag = 0;
    srcscanstart = 0;
    srcscanstop = 0;
    curscanstart = 0;
    curscanstop = 0;
    srcCstart = 0;
    srcCend = 0;
    srcBstart = 0;
    srcBend = 0;
    srclawstart = 0;
    srclawstop = 0;
    curlawstart = 0;
    curlawstop = 0;
    currangestart = 0;
    currangestop = 0;
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

void DopplerDrawScan::TransformImage(int x1,int y1,U8 src[2048][2048],int x2,int y2,QImage* pImage)
{
    double widthscale = (double)x1/x2;
    double hightscale = (double)y1/y2;
    int srcx = 0;
    int srcy = 0;
    float transx = 0.0;
    float transy = 0.0;
    float diffx = 0.0;
    float diffy = 0.0;
    //float midy1,midy2;
    int midy3;
    int i;
    int j;
    U8* _pImageTmp;
    U8* _pImageBits = pImage->bits() ;
    int _nWidthStep   = pImage->bytesPerLine() ;
    for(i=0;i<x2;i++)
    {
        transx = (i+0.5)*widthscale-0.5;
        srcx = qFloor(transx);
        diffx = transx - srcx;
        srcx += 1;
        if(srcx >= 2046)
        {
            srcx = 2046;
        }
       for(j=0;j<y2;j++)
       {           
           _pImageTmp = _pImageBits + j * _nWidthStep + i * 3 ;
           transy = (j+0.5)*hightscale-0.5;
           srcy = qFloor(transy);
           diffy = transy -srcy;
           srcy+=1;
           //midy1 = (src[srcx][srcy+1]-src[srcx][srcy])*diffy + src[srcx][srcy];
           //midy2 = (src[srcx+1][srcy+1]-src[srcx+1][srcy])*diffy + src[srcx+1][srcy];
           midy3 = (1-diffx)*(1-diffy)*src[srcx][srcy] + (1-diffx)*(diffy)*src[srcx][srcy+1]+diffx*(1-diffy)*src[srcx+1][srcy]+diffx*diffy*src[srcx+1][srcy+1];
           memcpy(_pImageTmp,&m_pColor[midy3],3);
       }
    }
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
    else
    {
        m_PosStop = m_PosStart + nRangle_ - 1 ;
    }
    emit signalScanRangeMove(nType_, m_PosStart, m_PosStop) ;
}

void DopplerDrawScan::UpdateIndexRange(int nType_, int nRangle_ , int nPos_)
{
    if(nPos_ < 0) nPos_ = 0;

    if( nPos_ <= m_indexStartIndex){
        m_indexStartIndex = nPos_;
        m_indexStopIndex  = m_indexStartIndex + nRangle_ - 1;
        if( m_indexStopIndex > MAX_SCAN_INDEX){
            m_indexStartIndex = MAX_SCAN_INDEX -  nRangle_ + 1;
            m_indexStopIndex  = MAX_SCAN_INDEX;
        }
    }else if(nPos_ >= m_indexStopIndex){
        m_indexStopIndex = nPos_;
        m_indexStartIndex = m_indexStopIndex - nRangle_ + 1;
        if(m_indexStartIndex < 0){
            m_indexStartIndex = 0;
            m_indexStopIndex = nRangle_ - 1;
        }
    }else{
        m_indexStopIndex = m_indexStartIndex + nRangle_ - 1;
    }
    emit signalIndexRangeMove( nType_, 0, m_indexStartIndex, m_indexStopIndex);
}
