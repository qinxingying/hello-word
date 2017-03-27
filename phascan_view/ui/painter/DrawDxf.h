#ifndef DrawDxf_H
#define DrawDxf_H

//#include "dxf_data.h"
#include "dl_creationadapter.h"
#include "rvector.h"
#include "Instrument.h"

#include <QWidget>
#include <QPaintEvent>

typedef struct _DRAW_DXF_INFO
{
    float fX;
    float fY;
    int   fWidth;
    int   fHeight;
    float fScaleX;
    float fScaleY;
}DRAW_DXF_INFO;

namespace DplDxf {

class DrawDxfPrivate;

class DrawDxf : public QWidget, public DL_CreationAdapter
{
    Q_OBJECT

public:
    explicit DrawDxf(QWidget *parent = 0);
    ~DrawDxf();
    static   DrawDxf* Instance();
    void SetInfo(DRAW_DXF_INFO info_) {m_Info = info_;}
    int setPart(PART_CONFIG* pInfo_);
    void draw_dxfPart(QPainter& painter, double zoom, double centerX, double centerY);
    void DrawDxfPart(QPainterPath& path, double originX, double kx, double ky);

    DRAW_DXF_INFO m_Info;
    PART_CONFIG* m_pPart;
    float m_fThickness;

private:
    void draw_line(QPainterPath& path, double originX, double kx, double ky);
    void draw_arc(QPainterPath& path, double originX, double kx, double ky);
    void draw_circle(QPainterPath& path, double originX, double kx, double ky);
    void draw_ellipse(QPainterPath& path, double originX, double kx, double ky);

    void paint_point(QPainter& painter, double zoom, double centerX, double centerY);
    void paint_line(QPainter& painter, double zoom, double centerX, double centerY);
    void paint_polyLine_0(QPainter& painter, double zoom, double centerX, double centerY);
    void paint_polyLine_1(QPainter& painter, double zoom, double centerX, double centerY);
    void paint_text(QPainter& painter, double zoom, double centerX, double centerY);
    void paint_arc(QPainter& painter, double zoom, double centerX, double centerY);
    void paint_circle(QPainter& painter, double zoom, double centerX, double centerY);
    void paint_ellipse(QPainter& painter, double zoom, double centerX, double centerY);

    void createEllipse(QPolygonF& pa, const RVector& cp, double radius1, double radius2,
                       double angle, double angle1, double angle2, bool reversed);
    double get_span_angle(double angle1, double angle2, bool isRad);
    double calc_rotateAngle(double mx, double my);
    double get_magnitude2D(double x, double y);

    int getDxfData();
    QPointF coordinate_trans(float x_, float y_);

    DrawDxfPrivate *d;
//    QList<DL_PointData> m_pointList;
//    QList<DL_LineData> m_lineList;
//    QList<DL_ArcData> m_arcList;
//    QList<DL_TextData> m_textDataList;
//    QList<DL_MTextData> m_textList;
//    QList<DL_EllipseData> m_ellipseList;
//    QList<DL_CircleData> m_circleList;
//    QList<DL_VertexData> m_vertexList;
//    QList<DL_PolylineData> m_polyLineList;
//    QList<DL_SplineData> m_splineList;
//    QList<DL_ControlPointData> m_controlPointList;

};

}

#endif // DrawDxf_H
