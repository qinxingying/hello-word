#ifndef DOPPLERGATEITEM_H
#define DOPPLERGATEITEM_H

#include "DopplerGraphicsItem.h"
#include <QColor>
//#include <QRectF>

enum GATE_DRAW_MODE
{
	GATE_MODE_GATE_HORIZENTAL  = 0 ,
	GATE_MODE_GATE_VERTICAL   ,
	GATE_MODE_LINE_HORIZENTAL ,
	GATE_MODE_LINE_VERTICAL ,
    GATE_MODE_S_TRUEDEPTH,
    GATE_MODE_S_SOUNDPATH,
	GATE_DRAW_MODE_MAX
};

class DopplerGateItem : public DopplerGraphicsItem
{
public:
	DopplerGateItem(const QColor& cColor_);
	void SetDrawMode(GATE_DRAW_MODE eMode_);
    void setCurveGate(QVector<QPointF> start, QVector<QPointF> end);
    void clearCurveGate(){
        m_gateStart.clear();
        m_gateEnd.clear();
    }
    GATE_DRAW_MODE GetDrawMode() {
        return m_eMode;
    }

protected:
	QRectF boundingRect() const;
	QPainterPath shape() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
	virtual void SetItemGeometry (QRectF& rect_);
	void DrawLabel(QPainter *painter, QColor& cColor_, bool bSel_);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) ;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent  *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent  *event);

	GATE_DRAW_MODE	m_eMode ;
	QColor			m_cColor ;
    QVector<QPointF> m_gateStart;
    QVector<QPointF> m_gateEnd;
    QPointF  m_mouseDownPos;
};

#endif // DOPPLERGATEITEM_H
