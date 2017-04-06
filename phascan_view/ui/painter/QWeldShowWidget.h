#ifndef QWELDSHOWWIDGET_H
#define QWELDSHOWWIDGET_H

#include <QWidget>
#include "Instrument.h"

class QWeldShowWidget : public QWidget
{
	Q_OBJECT

public:
	explicit QWeldShowWidget(QWidget *parent = 0);
	void SerPart(PART_CONFIG* pInfo_);
    void clear_point();

    double m_zoom;

protected:
	struct RANGE_INFO
	{
        double fWidth;
        double fHeight;
        double fStartY;
        double fStopY;
        double fPixelSize;
    };

    void  paintEvent (QPaintEvent * event);
    void  DrawWeld(QPainter& painter);
	void  DrawWeldI(QPainter& painter);
	void  DrawWeldV(QPainter& painter);
    void  DrawWeldDV(QPainter& painter);
    void  DrawWeldU (QPainter& painter);
    void  DrawWeldDiffDV(QPainter& painter);
    void  DrawWeldJ(QPainter& painter);
    void  DrawWeldVY(QPainter& painter);
    void  UpdateDisplayRangle();
    void  PositionTransfer(QPointF& pos_);

    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

	PART_CONFIG* m_pPart;
    RANGE_INFO m_cRange;
    float m_fThickness;

private:
    QPoint m_startPoint;
    QPoint m_endPoint;
    QPoint m_lastPoint;

public slots:
    void do_zoom_change(double value);

signals:
    void zoom(double v);
};

#endif // QWELDSHOWWIDGET_H
