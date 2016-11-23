#include "DopplerGraphicsItem.h"
#include <QGraphicsScene>

DopplerGraphicsItem::DopplerGraphicsItem()
{
    //m_eType = DOPPLER_GRAPHICS_ITEM_GATE  ;
    m_Geometry = QRect( 0 , 0 , 1 , 1);
    m_pDataView = NULL ;
}


int DopplerGraphicsItem::GetItemType()  const
{
    return m_eType  ;
}


void DopplerGraphicsItem::SetItemType(DOPPLER_GRAPHICS_ITEM_TYPE eType_)
{
    if(eType_ < DOPPLER_GRAPHICS_ITEM_TYPE_MAX)
        m_eType = eType_ ;
}


int DopplerGraphicsItem::GetItemId() const
{
    return m_nId ;
}

void DopplerGraphicsItem::SetItemId(int nId_)
{
    m_nId = nId_  ;
}

void DopplerGraphicsItem::SetDataView(DopplerDataView* pDataView_)
{
    m_pDataView = pDataView_ ;
}

QPointF DopplerGraphicsItem::GetItemScenePos()
{
    return scenePos() ;
}


void DopplerGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* /*event*/)
{
    //*************************************************
    //############  确保只有一个 item 被选中
    QList<QGraphicsItem*> ItemList =scene()->selectedItems();
    DopplerGraphicsItem* item ;
    int _iCnt = ItemList.count();
    for(int i = 0 ; i < _iCnt; i++)
    {
        item = (DopplerGraphicsItem*)ItemList.at(i) ;
        item->setSelected(false);
    }
    setSelected(true);
    //***************************************************
}

//void DopplerGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//
//}
//
void DopplerGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setSelected(false);
}

void DopplerGraphicsItem::SetItemGeometry(QRectF& rect_)
{
    m_nWidth  = rect_.width();
    m_nHeight = rect_.height();
    this->setPos(rect_.topLeft());
    //update();
}
void DopplerGraphicsItem::SetItemGeometryReal(QRectF& rect_)
{
    m_Geometry = rect_ ;
}

QRectF DopplerGraphicsItem::GetItemGeometryReal() const
{
    return m_Geometry ;
}
