#ifndef DrawDxfHeader_H
#define DrawDxfHeader_H

#include "dxf_headeradapter.h"
#include "Instrument.h"

#include <QWidget>
#include <QPaintEvent>

namespace DplDxf {

class DrawDxfHeaderPrivate;

class DrawDxfHeader : public QWidget, public Dxf_HeaderAdapter
{
    Q_OBJECT

public:
    enum AxisOrientation {
        Axis_Normal,
        Axis_Vertical_Flip,
        Axis_Horizontal_Flip
    };

    explicit DrawDxfHeader(QWidget *parent = 0);
    ~DrawDxfHeader();
    static   DrawDxfHeader* Instance();
    int set_part(PART_CONFIG* pInfo_);
    void draw_dxf_header(QPainter& painter);
    void set(double width, double height, double centerX, double centerY, double scaleX, double scaleY);
    void draw_dxf_header(QPainterPath& path);
    void set_axis_orientation(DrawDxfHeader::AxisOrientation value);

    PART_CONFIG* m_pPart;
    float m_fThickness;
    DplDxf::DrawDxfHeader::AxisOrientation m_axis;

private:
    void draw_wcs_axis(QPainterPath& path);
    void draw_ucs_axis(QPainterPath& path);

    void paint_wcs_axis(QPainter& painter);
    void paint_ucs_axis(QPainter& painter);

    int get_dxf_header();
    QPointF coordinate_trans(float x_, float y_, bool isRadius);

    DrawDxfHeaderPrivate *d;
};

}

#endif // DrawDxfHeader_H
