#ifndef DOPPLERPARABOLAITEM_H
#define DOPPLERPARABOLAITEM_H


#include <QColor>
#include <QGraphicsItem>
#include "DopplerGraphicsItem.h"
#include <configure/DopplerConfigure.h>

class DopplerParabolaItem : public DopplerGraphicsItem
{
public:
    DopplerParabolaItem();
    void SetPoint(QPointF pos_ ) ;
    void Set_Scale(float scaleH, float scaleV);

protected:
    void   GetPrecInfo(float* precX_, float* precY_, float* pTX0_);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

    QColor  m_cColor     ;
    QPointF m_cPos       ;
    int     m_nDisp      ;
    int     m_nGroup     ;
    TOFD_PARA* m_pTofd   ;
    float  m_scaleH;
    float  m_scaleV;
};

#endif // DOPPLERPARABOLAITEM_H
