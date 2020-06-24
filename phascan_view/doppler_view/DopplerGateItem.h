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

protected:
	QRectF boundingRect() const;
	QPainterPath shape() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
	virtual void SetItemGeometry (QRectF& rect_);
	void DrawLabel(QPainter *painter, QColor& cColor_, bool bSel_);

	GATE_DRAW_MODE	m_eMode ;
	QColor			m_cColor ;
    QVector<QPointF> m_gateStart;
    QVector<QPointF> m_gateEnd;
};

#endif // DOPPLERGATEITEM_H
