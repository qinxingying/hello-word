#ifndef DrawDxf_H
#define DrawDxf_H

#include "dxf_data.h"

#include <QWidget>
#include <QPaintEvent>
#include "Instrument.h"

namespace DplDxf {
    class DrawDxf;
}

typedef struct _DRAW_DXF_INFO
{
//	QPointF	Origin;
    float fX;
    float fY;
    int   fWidth;
    int   fHeight;
    float fScaleX;
    float fScaleY;
}DRAW_DXF_INFO;

class DrawDxf : public QWidget
{
	Q_OBJECT

public:
    explicit DrawDxf(QWidget *parent = 0);

    static   DrawDxf* Instance();
    DRAW_DXF_INFO	m_Info;
    void SetInfo(DRAW_DXF_INFO info_) {m_Info = info_;}
    void DrawDxfPart(QPainter& painter);
    void DrawDxfPart(QPainterPath& path);

    int setPart(PART_CONFIG* pInfo_);
    double m_zoom;

private:
    int getDxfData();
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
    struct RANGE_INFO
    {
        double fWidth;
        double fHeight;
        double fStartY;
        double fStopY;
        double fPixelSize;
    };

    PART_CONFIG* m_pPart;
    RANGE_INFO m_cRange;
    float m_fThickness;

    void paint_point(QPainter& painter);
    void paint_line(QPainter& painter);
    void paint_polyLine_0(QPainter& painter);
    void paint_polyLine_1(QPainter& painter);
    void paint_text(QPainter& painter);
    void paint_arc(QPainter& painter);
    void paint_circle(QPainter& painter);
    double calc_rotateAngle(double cx, double cy, double mx, double my);
    void paint_ellipse(QPainter& painter);
};

#endif // DrawDxf_H
