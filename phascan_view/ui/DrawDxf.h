#ifndef DrawDxf_H
#define DrawDxf_H

#include "dl_creationadapter.h"
#include "test_creationclass.h"

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

    QList<DL_LineData> getLineList() const;
    void setLineList(const QList<DL_LineData> &lineList);

    QList<DL_ArcData> getArcList() const;
    void setArcList(const QList<DL_ArcData> &arcList);

    QList<DL_MTextData> getTextList() const;
    void setTextList(const QList<DL_MTextData> &textList);

    QList<DL_EllipseData> getEllipseList() const;
    void setEllipseList(const QList<DL_EllipseData> &ellipseList);

    QList<DL_CircleData> getCircleList() const;
    void setCircleList(const QList<DL_CircleData> &circleList);

    QList<DL_TextData> getTextDataList() const;
    void setTextDataList(const QList<DL_TextData> &textDataList);

    QList<DL_VertexData> getVertexList() const;
    void setVertexList(const QList<DL_VertexData> &vertexList);

    QList<DL_SplineData> getSplineList() const;
    void setSplineList(const QList<DL_SplineData> &splineList);

    QList<DL_ControlPointData> getControlPointList() const;
    void setControlPointList(const QList<DL_ControlPointData> &controlPointList);

    QList<DL_PointData> getPointList() const;
    void setPointList(const QList<DL_PointData> &pointList);

    QList<DL_PolylineData> getPolyLineList() const;
    void setPolyLineList(const QList<DL_PolylineData> &polyLineList);

private:
    Test_CreationClass* creationClass;

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

protected:
    void paintEvent(QPaintEvent * event);
    void paint_point(QPainter& painter);
    void paint_line(QPainter& painter);
    void paint_polyLine_0(QPainter& painter);
    void paint_polyLine_1(QPainter& painter);
    void paint_text(QPainter& painter);
    void paint_arc(QPainter& painter);
    void paint_circle(QPainter& painter);
    void paint_ellipse(QPainter& painter);
    void wheelEvent(QWheelEvent *event);

signals:
    void zoom(double v);
};

#endif // DrawDxf_H
