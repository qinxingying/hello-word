#ifndef DrawDxf_H
#define DrawDxf_H

#include "dl_creationadapter.h"
#include "dxf_headeradapter.h"
#include "rvector.h"
#include "Instrument.h"

#include <QWidget>
#include <QPaintEvent>

namespace DplDxf {

class DrawDxfPrivate;

class DrawDxfHeaderPrivate;

class DrawDxf : public QWidget, public DL_CreationAdapter, public Dxf_HeaderAdapter
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
    int set_part(PART_CONFIG* pInfo_);
    void draw_dxf_part(QPainter& painter);
    void draw_dxf_header(QPainter& painter);
    void set(double width, double height, double centerX, double centerY, double scaleX, double scaleY);
    void draw_dxf_header(QPainterPath& path);
    void draw_dxf_part(QPainterPath& path);
    void set_axis_orientation(DrawDxf::AxisOrientation value);

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

//    void draw_wcs_axis(QPainterPath& path);
//    void draw_ucs_axis(QPainterPath& path);

    void paint_wcs_axis(QPainter& painter);
    void paint_ucs_axis(QPainter& painter);

    int get_dxf_header();

    void rotate(QPainter& painter, QPointF point, double angle);
    void create_ellipse(QPolygonF& pa, const RVector& cp, double radius1, double radius2,
                        double angle, double angle1, double angle2, int factor);
    double get_span_angle(double angle1, double angle2, bool isRad);
    double calc_rotate_angle(double mx, double my);
    double get_magnitude2D(double x, double y);
    QString format_text(QString str);

    Qt::AlignmentFlag get_v_flag(int flag);
    Qt::AlignmentFlag get_h_flag(int flag);
    int get_dxf_data();
    QPointF coordinate_trans(float x_, float y_, bool isRadius);

    DrawDxfPrivate *d;
    DrawDxfHeaderPrivate *h;
};

}

#endif // DrawDxf_H
