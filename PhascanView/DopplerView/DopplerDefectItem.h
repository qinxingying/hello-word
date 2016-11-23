#ifndef DOPPLERDEFECTITEM_H
#define DOPPLERDEFECTITEM_H

#include "DopplerGraphicsItem.h"
#include <QColor>
//#include <QRectF>

class DopplerDefectItem : public DopplerGraphicsItem
{
public:
    DopplerDefectItem(const QColor& cColor_);
    void SetLineStyle(Qt::PenStyle eStype_) ;
    void SetScenceSize(QSize);
    virtual void SetItemGeometry (QRectF& rect_);

protected:
    //void DrawLabel(QPainter* painter);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    void DrawLabel(QPainter *painter, QColor& cColor_, bool bSel_);
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event) ;
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QRectF         m_rect   ;
    QColor         m_cColor ;
    Qt::PenStyle   m_eStype ;
    QSize          m_cSize ;};

#endif // DOPPLERDEFECTITEM_H
