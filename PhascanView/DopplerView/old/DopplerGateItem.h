/***************************
  Name:  DopplerGateItem
  Copyright: Sheng Shen
  Date : 2013-08-26
  Description:   数据显示窗口　闸门
************************************/
#ifndef DOPPLER_GATE_H
#define DOPPLER_GATE_H

#include <QColor>
#include <QGraphicsItem>
#include "DopplerGraphicsItem.h"

enum GATE_DRAW_MODE
{
    GATE_MODE_GATE_HORIZENTAL  = 0 ,
    GATE_MODE_GATE_VERTICAL   ,
    GATE_MODE_LINE_HORIZENTAL ,
    GATE_MODE_LINE_VERTICAL ,
    GATE_DRAW_MODE_MAX
};

class DopplerGateItem : public DopplerGraphicsItem
{
public:
    DopplerGateItem(const QColor& cColor_);
    void SetDrawMode(GATE_DRAW_MODE eMode_);

    QRectF boundingRect() const;
    QPainterPath shape() const;
protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void SetItemGeometry(QRectF& rect_);
private:
    QColor m_cColor;
    GATE_DRAW_MODE m_eMode ;
};

#endif	//DOPPLER_GATE_H
