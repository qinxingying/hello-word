#include "DrawDxfHeader.h"
#include "dxf_header.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

namespace DplDxf {
class DrawDxfHeaderPrivate : public Dxf_HeaderAdapter
{
public:
    DrawDxfHeaderPrivate();

    virtual void add_version(const DXF_HEADER_ACADVER& data);
    virtual void add_angle_dir(const DXF_HEADER_ANGDIR& data);
    virtual void add_unit(const DXF_HEADER_INSUNITS& data);

    virtual void add_PUCS_name(const DXF_HEADER_PUCSNAME& data);
    virtual void add_point_PUCSORG(const DXF_HEADER_PUCSORG& data);
    virtual void add_point_PUCSXDIR(const DXF_HEADER_PUCSXDIR& data);
    virtual void add_point_PUCSYDIR(const DXF_HEADER_PUCSYDIR& data);

    virtual void add_UCS_name(const DXF_HEADER_UCSNAME& data);
    virtual void add_point_UCSORG(const DXF_HEADER_UCSORG& data);
    virtual void add_point_UCSXDIR(const DXF_HEADER_UCSXDIR& data);
    virtual void add_point_UCSYDIR(const DXF_HEADER_UCSYDIR& data);

    virtual void add_line_scale(const DXF_HEADER_LTSCALE& data);
    void clear();

    QList<DXF_HEADER_ACADVER> m_dataACadVer;
    QList<DXF_HEADER_ANGDIR> m_dataAngDir;
    QList<DXF_HEADER_INSUNITS> m_dataInsUnits;
    QList<DXF_HEADER_PUCSNAME> m_dataPUCSName;
    QList<DXF_HEADER_PUCSORG> m_dataPUCSOrg;
    QList<DXF_HEADER_PUCSXDIR> m_dataPUCSXDir;
    QList<DXF_HEADER_PUCSYDIR> m_dataPUCSYDir;
    QList<DXF_HEADER_UCSNAME> m_dataUCSName;
    QList<DXF_HEADER_UCSORG> m_dataUCSOrg;
    QList<DXF_HEADER_UCSXDIR> m_dataUCSXDir;
    QList<DXF_HEADER_UCSYDIR> m_dataUCSYDir;
    QList<DXF_HEADER_LTSCALE> m_dataLtScale;

    double m_width;
    double m_height;
    double m_centerX;
    double m_centerY;
    double m_scaleX;
    double m_scaleY;

};

DrawDxfHeaderPrivate::DrawDxfHeaderPrivate()
{
    m_centerX = 0;
    m_centerY = 0;
    m_scaleX = 1;
    m_scaleY = 1;
}

void DrawDxfHeaderPrivate::add_version(const DXF_HEADER_ACADVER& data)
{
    m_dataACadVer.append(data);
    qDebug()<<"\n *****ACADVER(1)*****\n --- version = "<<data.version.c_str();
}

void DrawDxfHeaderPrivate::add_angle_dir(const DXF_HEADER_ANGDIR& data)
{
    m_dataAngDir.append(data);
    qDebug()<<"\n *****ANGDIR(2)*****\n --- flag = "<<data.flags;
}

void DrawDxfHeaderPrivate::add_unit(const DXF_HEADER_INSUNITS& data)
{
    m_dataInsUnits.append(data);
    qDebug()<<"\n *****INSUNITS(3)*****\n --- flag = ("<<data.flags;
}

void DrawDxfHeaderPrivate::add_PUCS_name(const DXF_HEADER_PUCSNAME& data)
{
    m_dataPUCSName.append(data);
    qDebug()<<"\n *******PUCSNAME(4)********\n --- name = ("<<data.name.c_str();
}

void DrawDxfHeaderPrivate::add_point_PUCSORG(const DXF_HEADER_PUCSORG& data)
{
    m_dataPUCSOrg.append(data);
    qDebug()<<"\n *******PUCSORG(5)********\n --- x, y, z ="<<data.x<<data.y<<data.z;
}

void DrawDxfHeaderPrivate::add_point_PUCSXDIR(const DXF_HEADER_PUCSXDIR& data)
{
    m_dataPUCSXDir.append(data);
    qDebug()<<"\n *******PUCSXDIR(6)********\n ---x, y, z ="<<data.x<<data.y<<data.z;
}

void DrawDxfHeaderPrivate::add_point_PUCSYDIR(const DXF_HEADER_PUCSYDIR& data)
{
    m_dataPUCSYDir.append(data);
    qDebug()<<"\n *******PUCSYDIR(7)********\n ---x, y, z ="<<data.x<<data.y<<data.z;
}

void DrawDxfHeaderPrivate::add_UCS_name(const DXF_HEADER_UCSNAME& data)
{
    m_dataUCSName.append(data);
    qDebug()<<"\n *******UCSNAME(8)********\n ---name ="<<data.name.c_str();
}

void DrawDxfHeaderPrivate::add_point_UCSORG(const DXF_HEADER_UCSORG& data)
{
    m_dataUCSOrg.append(data);
    qDebug()<<"\n *****UCSORG(9)****\n ---x, y, z ="<<data.x<<data.y<<data.z;
}

void DrawDxfHeaderPrivate::add_point_UCSXDIR(const DXF_HEADER_UCSXDIR& data)
{
    m_dataUCSXDir.append(data);
    qDebug()<<"\n *****UCSXDIR(10)****\n ---x, y, z ="<<data.x<<data.y<<data.z;
}

void DrawDxfHeaderPrivate::add_point_UCSYDIR(const DXF_HEADER_UCSYDIR& data)
{
    m_dataUCSYDir.append(data);
    qDebug()<<"\n *****UCSYDIR(11)****\n ---x,y,z,w ="<<data.x<<data.y<<data.z;
}

void DrawDxfHeaderPrivate::add_line_scale(const DXF_HEADER_LTSCALE& data)
{
    m_dataLtScale.append(data);
    qDebug()<<"\n *****LTSCALE***\n ---lineScale ="<<data.lineScale;
}

void DrawDxfHeaderPrivate::clear()
{
    m_dataACadVer.clear();
    m_dataAngDir.clear();
    m_dataInsUnits.clear();
    m_dataPUCSName.clear();
    m_dataPUCSOrg.clear();
    m_dataPUCSXDir.clear();
    m_dataPUCSYDir.clear();
    m_dataUCSName.clear();
    m_dataUCSOrg.clear();
    m_dataUCSXDir.clear();
    m_dataUCSYDir.clear();
    m_dataLtScale.clear();
}

DrawDxfHeader * g_pDrawDxfHeader = NULL;
DrawDxfHeader *DrawDxfHeader::Instance()
{
    if(!g_pDrawDxfHeader){
        g_pDrawDxfHeader = new DrawDxfHeader();
    }
    return g_pDrawDxfHeader;
}

DrawDxfHeader::DrawDxfHeader(QWidget *parent) :
    QWidget(parent),
    d(new DrawDxfHeaderPrivate())
{
    m_pPart = NULL;
    m_fThickness = 20;
}

DrawDxfHeader::~DrawDxfHeader()
{
    delete d;
}

int DrawDxfHeader::get_dxf_header()
{
    if(m_pPart == NULL)
        return -1;

    DxfHeader header;

    QString dxfFile = m_pPart->strPartFile;
    if (!header.in(dxfFile.toLatin1().data(), d)) {
        qDebug()<<"could not be opened";
        return -1;
    }

    return 0;
}

void DrawDxfHeader::draw_dxf_header(QPainter &painter)
{

    paint_wcs_axis(painter);

    paint_ucs_axis(painter);
}

void DrawDxfHeader::paint_wcs_axis(QPainter &painter)
{
    if(!d->m_dataPUCSOrg.isEmpty()) {
        for(int i = 0; i < d->m_dataPUCSOrg.count(); i ++) {
            double x0 = d->m_dataPUCSOrg.at(i).x;
            double y0 = d->m_dataPUCSOrg.at(i).y;
            double x1 = x0 + 100 * d->m_dataPUCSXDir.at(i).x;
            double y1 = y0 + 100 * d->m_dataPUCSXDir.at(i).y;
            double x2 = x0 + 100 * d->m_dataPUCSYDir.at(i).x;
            double y2 = y0 + 100 * d->m_dataPUCSYDir.at(i).y;

            QPointF _point1 = coordinate_trans(x0, y0, false);
            QPointF _point2 = coordinate_trans(x1, y1, false);
            QPointF _point3 = coordinate_trans(x2, y2, false);

            painter.drawLine(_point1, _point2); // X Axis
            painter.drawLine(_point1, _point3); // Y Axis

            painter.drawLine(coordinate_trans(x1 - 5, y1 + 5, false), _point2);
            painter.drawLine(coordinate_trans(x1 - 5, y1 - 5, false), _point2);

            painter.drawLine(coordinate_trans(x2 - 5, y2 - 5, false), _point3);
            painter.drawLine(coordinate_trans(x2 + 5, y2 - 5, false), _point3);
        }
    }
}

void DrawDxfHeader::paint_ucs_axis(QPainter &painter)
{
    if(!d->m_dataUCSOrg.isEmpty()) {
        for(int i = 0; i < d->m_dataUCSOrg.count(); i ++) {
            double x0 = d->m_dataUCSOrg.at(i).x;
            double y0 = d->m_dataUCSOrg.at(i).y;
            double x1 = x0 + 100 * d->m_dataUCSXDir.at(i).x;
            double y1 = y0 + 100 * d->m_dataUCSXDir.at(i).y;
            double x2 = x0 + 100 * d->m_dataUCSYDir.at(i).x;
            double y2 = y0 + 100 * d->m_dataUCSYDir.at(i).y;

            QPointF _point1 = coordinate_trans(x0, y0, false);
            QPointF _point2 = coordinate_trans(x1, y1, false);
            QPointF _point3 = coordinate_trans(x2, y2, false);

            painter.drawLine(_point1, _point2); // X Axis
            painter.drawLine(_point1, _point3); // Y Axis

            /* X Axis Arrow */
            painter.drawLine(coordinate_trans(x1 - 5, y1 + 5, false), _point2);
            painter.drawLine(coordinate_trans(x1 - 5, y1 - 5, false), _point2);

            /* Y Axis Arrow */
            if(d->m_dataPUCSYDir.at(i).y * d->m_dataUCSYDir.at(i).y < 0) {
                painter.drawLine(coordinate_trans(x2 - 5, y2 + 5, false), _point3);
                painter.drawLine(coordinate_trans(x2 + 5, y2 + 5, false), _point3);
            } else {
                painter.drawLine(coordinate_trans(x2 - 5, y2 - 5, false), _point3);
                painter.drawLine(coordinate_trans(x2 + 5, y2 - 5, false), _point3);
            }

            /* Text */
            painter.drawText(coordinate_trans(x1, y0 - 10, false), "X");
            painter.drawText(coordinate_trans(x0 + 10, y2, false), "Y");
            painter.drawText(coordinate_trans(x0 + 5, y0 - 10, false), "UCS");
        }
    }
}

int DrawDxfHeader::set_part(PART_CONFIG *pInfo_)
{
    m_pPart = pInfo_;
    m_fThickness = m_pPart->afSize[0];
    int ret = get_dxf_header();
    return ret;
}

void DrawDxfHeader::draw_dxf_header(QPainterPath &path)
{
    draw_wcs_axis(path);

    draw_ucs_axis(path);
}

void DrawDxfHeader::draw_wcs_axis(QPainterPath &path)
{
    if(!d->m_dataPUCSOrg.isEmpty()) {
        for(int i = 0; i < d->m_dataPUCSOrg.count(); i ++) {
            double x0 = d->m_dataPUCSOrg.at(i).x;
            double y0 = d->m_dataPUCSOrg.at(i).y;
            double x1 = x0 + 100 * d->m_dataPUCSXDir.at(i).x;
            double y1 = y0 + 100 * d->m_dataPUCSXDir.at(i).y;
            double x2 = x0 + 100 * d->m_dataPUCSYDir.at(i).x;
            double y2 = y0 + 100 * d->m_dataPUCSYDir.at(i).y;

            QPointF _point1 = coordinate_trans(x0, y0, false);
            QPointF _point2 = coordinate_trans(x1, y1, false);
            QPointF _point3 = coordinate_trans(x2, y2, false);

            path.moveTo(_point1);
            path.lineTo(_point2); // X Axis
            path.moveTo(_point1);
            path.lineTo(_point3); // Y Axis

            path.moveTo(coordinate_trans(x1 - 5, y1 + 5, false));
            path.lineTo(_point2);
            path.lineTo(coordinate_trans(x1 - 5, y1 - 5, false));

            path.moveTo(coordinate_trans(x2 - 5, y2 - 5, false));
            path.lineTo(_point3);
            path.lineTo(coordinate_trans(x2 + 5, y2 - 5, false));

        }
    }
}

void DrawDxfHeader::draw_ucs_axis(QPainterPath &path)
{
    if(!d->m_dataUCSOrg.isEmpty()) {
        for(int i = 0; i < d->m_dataUCSOrg.count(); i ++) {
            double x0 = d->m_dataUCSOrg.at(i).x;
            double y0 = d->m_dataUCSOrg.at(i).y;
            double x1 = x0 + 100 * d->m_dataUCSXDir.at(i).x;
            double y1 = y0 + 100 * d->m_dataUCSXDir.at(i).y;
            double x2 = x0 + 100 * d->m_dataUCSYDir.at(i).x;
            double y2 = y0 + 100 * d->m_dataUCSYDir.at(i).y;

            QPointF _point1 = coordinate_trans(x0, y0, false);
            QPointF _point2 = coordinate_trans(x1, y1, false);
            QPointF _point3 = coordinate_trans(x2, y2, false);

            path.moveTo(_point1);
            path.lineTo(_point2);// X Axis
            path.moveTo(_point1);
            path.lineTo( _point3);// Y Axis

            path.moveTo(coordinate_trans(x1 - 5, y1 + 5, false));
            path.lineTo(_point2);
            path.lineTo(coordinate_trans(x1 - 5, y1 - 5, false));

            if(d->m_dataPUCSYDir.at(i).y * d->m_dataUCSYDir.at(i).y < 0) {
                path.moveTo(coordinate_trans(x2 - 5, y2 + 5, false));
                path.lineTo(_point3);
                path.lineTo(coordinate_trans(x2 + 5, y2 + 5, false));
            } else {
                path.moveTo(coordinate_trans(x2 - 5, y2 - 5, false));
                path.lineTo(_point3);
                path.lineTo(coordinate_trans(x2 + 5, y2 - 5, false));
            }
        }
    }
}

QPointF DrawDxfHeader::coordinate_trans(float x_, float y_, bool isRadius)
{
    float _fX;
    float _fY;

    float _fScaleX = d->m_scaleX;
    float _fScaleY = d->m_scaleY;
    float     _fX0 = d->m_centerX;
    float     _fY0 = d->m_centerY;

    if(isRadius) {
        _fX = x_ * _fScaleX;
        _fY = y_ * _fScaleY;
    } else {
        //QPainter中坐标系统的第一象限相当于数学坐标中的第四象限
        if(m_axis == Axis_Normal) {
            _fX = x_ * _fScaleX + _fX0;
            _fY = - y_ * _fScaleY + _fY0;//x不变，y轴上下翻转
        } else if(m_axis == Axis_Vertical_Flip){
            _fX = x_ * _fScaleX + _fX0;
            _fY = y_ * _fScaleY + _fY0;//x不变，y不变
        } else {
            _fX = - x_ * _fScaleX + _fX0;
            _fY = - y_ * _fScaleY + _fY0;//x轴左右翻转，y轴上下翻转
        }
    }

    QPointF _point;
    _point.setX(_fX);
    _point.setY(_fY);

    return _point;
}

void DrawDxfHeader::set(double width, double height, double centerX, double centerY, double scaleX, double scaleY)
{
    d->m_width = width;
    d->m_height = height;
    d->m_centerX = centerX;
    d->m_centerY = centerY;
    d->m_scaleX = scaleX;
    d->m_scaleY = scaleY;
}

void DrawDxfHeader::set_axis_orientation(DrawDxfHeader::AxisOrientation value)
{
    m_axis = value;
}

}
