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
    void setGroupId(int groupId){m_groupId = groupId;}

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
    void  DrawWeldI(QPainter& painter);//绘制I型缺陷
    void  DrawWeldV(QPainter& painter);//绘制V型缺陷
    void  DrawWeldDV(QPainter& painter);
    void  DrawWeldU (QPainter& painter);
    void  DrawWeldDiffDV(QPainter& painter);
    void  DrawWeldJ(QPainter& painter);
    void  DrawWeldVY(QPainter& painter);
    void  DrawWeldTKY(QPainter& painter);
    void  UpdateDisplayRangle();//角度？？
    void  PositionTransfer(QPointF& pos_);

    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

	PART_CONFIG* m_pPart;
    RANGE_INFO m_cRange;
    float m_fThickness;

private:
    QPoint m_startPoint;//起点坐标
    QPoint m_endPoint;//终点坐标
    QPoint m_lastPoint;//
    int    m_groupId;

public slots:
    void do_zoom_change(double value);

signals:
    void zoom(double v);
};

#endif // QWELDSHOWWIDGET_H
