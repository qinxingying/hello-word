/**********************************
  Description: 显示二代数据的焊缝图示的图像
**********************************/

#ifndef WELDSHOWDATAIIWIDGET_H
#define WELDSHOWDATAIIWIDGET_H

#include <QWidget>
#include "Instrument.h"

class WeldShowDataIIWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WeldShowDataIIWidget(QWidget *parent = 0);
    void SerPart(PART_CONFIG *pInfo_);
    void clear_point();
public slots:
    void do_zoom_change(double value);
protected:
    void paintEvent( QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void zoom(double v);
private:
    void UpdateDisplayRangle();
    void PositionTransfer( QPointF &pos_);
    void DrawWeld( QPainter &painter);
    void DrawWeldI( QPainter &painter);
    void DrawWeldV( QPainter &painter);
    void DrawWeldU( QPainter &painter);
    void DrawWeldVY( QPainter &painter);
    void DrawWeldVV( QPainter &painter);
    void DrawWeldUU( QPainter &painter);
    void DrawWeldUV( QPainter &painter);
    void DrawWeldTKY( QPainter &painter);
    struct RANGE_INFO
    {
        double fWidth;
        double fHeight;
        double fStartY;
        double fStopY;
        double fPixelSize;
    };
    PART_CONFIG *m_pPart;
    RANGE_INFO m_cRange;
    float m_fThickness;
    double m_zoom;
    QPoint m_startPoint;
    QPoint m_endPoint;
    QPoint m_lastPoint;
};

#endif // WELDSHOWDATAIIWIDGET_H
