#ifndef DrawDxf_H
#define DrawDxf_H

#include "dl_creationadapter.h"
#include "dxf_data.h"

#include <QWidget>
#include <QPaintEvent>

namespace DplDxf {
    class DrawDxf;
}

class DrawDxf : public QWidget
{
	Q_OBJECT

public:
    explicit DrawDxf(QWidget *parent = 0);

    double m_zoom;

    void getDxfData(QString dxf_file);
    void paint_line();
  //  void paint_ellipse();

private:
    QList<DL_PointData> m_pointList;
    QList<DL_LineData> m_lineList;
    QList<DL_ArcData> m_arcList;
    QList<DL_TextData> m_textDataList;
    QList<DL_MTextData> m_textList;
    QList<DL_EllipseData> m_ellipseList;
    QList<DL_CircleData> m_circleList;
    QList<DL_VertexData> m_vertexList;
    QList<DL_PolylineData> m_polyLineList;
    QList<DL_SplineData> m_splineList;
    QList<DL_ControlPointData> m_controlPointList;

    QPainterPath m_path;
    QPoint lastPoint;
    QPoint endPoint;


protected:
    void paintEvent(QPaintEvent * event);
    void paint_point(QPainter& painter);
    void paint_line(QPainter& painter);
    void paint_polyLine_0(QPainter& painter);
    void paint_polyLine_1(QPainter& painter);
    void paint_text(QPainter& painter);
    void paint_arc(QPainter& painter);
    void paint_circle(QPainter& painter);
    double calc_rotateAngle(double cx, double cy, double mx, double my);
    void paint_ellipse(QPainter& painter);
    void wheelEvent(QWheelEvent *event);

    void mousePressEvent (QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void zoom(double v);
};

#endif // DrawDxf_H
