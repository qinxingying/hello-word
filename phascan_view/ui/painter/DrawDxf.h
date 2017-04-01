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
    enum AxisOrientation {
        Axis_Normal,
        Axis_Vertical_Flip,
        Axis_Horizontal_Flip
    };

    explicit DrawDxf(QWidget *parent = 0);
    ~DrawDxf();
    static   DrawDxf* Instance();
    void SetInfo(DRAW_DXF_INFO info_) {m_Info = info_;}
    int setPart(PART_CONFIG* pInfo_);
    void draw_dxf_part(QPainter& painter);
    void set(double width, double height, double centerX, double centerY, double scaleX, double scaleY);
    void draw_dxf_part(QPainterPath& path);
    void set_axis_orientation(DrawDxf::AxisOrientation value);

    DRAW_DXF_INFO m_Info;
    PART_CONFIG* m_pPart;
    float m_fThickness;
    DplDxf::DrawDxf::AxisOrientation m_axis;

private:
    void draw_line(QPainterPath& path);
    void draw_polyLine(QPainterPath& path);
    void draw_arc(QPainterPath& path);
    void draw_circle(QPainterPath& path);
    void draw_ellipse(QPainterPath& path);

    void paint_point(QPainter& painter);
    void paint_line(QPainter& painter);
    void paint_polyLine(QPainter& painter);
    void paint_text(QPainter& painter);
    void paint_arc(QPainter& painter);
    void paint_circle(QPainter& painter);
    void paint_ellipse(QPainter& painter);

    void rotate(QPainter& painter, QPointF point, double angle);
    void create_ellipse(QPolygonF& pa, const RVector& cp, double radius1, double radius2,
                        double angle, double angle1, double angle2, int factor);
    double get_span_angle(double angle1, double angle2, bool isRad);
    double calc_rotateAngle(double mx, double my);
    double get_magnitude2D(double x, double y);
    QString format_text(QString str);

    Qt::AlignmentFlag get_v_flag(int flag);
    Qt::AlignmentFlag get_h_flag(int flag);
    int getDxfData();
    QPointF coordinate_trans(float x_, float y_, bool isRadius);

    DrawDxfPrivate *d;

};

}

#endif // DrawDxf_H
