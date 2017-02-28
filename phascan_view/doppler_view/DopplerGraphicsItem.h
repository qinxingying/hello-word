
/***************************
  Description:   数据显示窗口　闸门
************************************/


#ifndef DOPPLERGRAPHICSITEM_H
#define DOPPLERGRAPHICSITEM_H

#include "DopplerDataView.h"
#include <QGraphicsItem>
#include <QRectF>


enum DOPPLER_GRAPHICS_ITEM_TYPE
{
    DOPPLER_GRAPHICS_ITEM_GATE  = 0  ,
    DOPPLER_GRAPHICS_ITEM_DEFECT     ,
    DOPPLER_GRAPHICS_ITEM_CURSOR     ,
    DOPPLER_GRAPHICS_ITEM_THICKNESS  ,
    DOPPLER_GRAPHICS_ITEM_LAW_MARKER ,
    DOPPLER_GRAPHICS_ITEM_DAC_TCG    ,
    DOPPLER_GRAPHICS_ITEM_PART       ,
    DOPPLER_GRAPHICS_ITEM_SCAN       ,
    DOPPLER_GRAPHICS_ITEM_OTHERS     ,
    DOPPLER_GRAPHICS_ITEM_TYPE_MAX
} ;
class DopplerGraphicsItem : public QGraphicsItem
{
public:

    explicit DopplerGraphicsItem();
    int  GetItemType()  const;
    void SetItemType(DOPPLER_GRAPHICS_ITEM_TYPE eType_) ;
    int  GetItemId() const ;
    void SetItemId(int nId_)  ;
    void SetDataView(DopplerDataView* pDataView_);
    QPointF GetItemScenePos();
    void SetItemGeometryReal(QRectF& rect_);
    QRectF GetItemGeometryReal() const;
    virtual void SetItemGeometry(QRectF& rect_);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QRectF m_Geometry ;
    DOPPLER_GRAPHICS_ITEM_TYPE m_eType ;
    int m_nWidth, m_nHeight;
    int m_nId ;
    DopplerDataView* m_pDataView  ;
};

#endif // DOPPLERGRAPHICSITEM_H
