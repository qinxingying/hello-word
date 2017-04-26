#include "DrawDxf.h"
#include "dl_dxf.h"
#include "dxf_header.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

namespace DplDxf {
class DrawDxfPrivate : public DL_CreationAdapter
{
public:
    DrawDxfPrivate();

//    virtual void addLayer(const DL_LayerData& data);
    virtual void addBlock(const DL_BlockData& data);
    virtual void endBlock();
    virtual void addPoint(const DL_PointData& data);
    virtual void addLine(const DL_LineData& data);
    virtual void addArc(const DL_ArcData& data);
    virtual void addCircle(const DL_CircleData& data);
    virtual void addPolyline(const DL_PolylineData& data);
    virtual void addVertex(const DL_VertexData& data);
    virtual void addMText(const DL_MTextData& data);
    virtual void addEllipse(const DL_EllipseData& data);
    virtual void addText(const DL_TextData& data);

    virtual void addSpline(const DL_SplineData& data);
    virtual void addControlPoint(const DL_ControlPointData& data);

//    virtual void addInsert(const DL_InsertData& data);
//    virtual void addComment(const std::string& data);
//    virtual void addXLine(const DL_XLineData& data);
//    virtual void addRay(const DL_RayData& data);

    virtual void add3dFace(const DL_3dFaceData& data);
    void printAttributes();
    void clear();

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

    double m_width;
    double m_height;
    double m_centerX;
    double m_centerY;
    double m_scaleX;
    double m_scaleY;

    bool isBlock;
};

DrawDxfPrivate::DrawDxfPrivate()
{
    m_centerX = 0;
    m_centerY = 0;
    m_scaleX = 1;
    m_scaleY = 1;
    isBlock = false;
}

void DrawDxfPrivate::addBlock(const DL_BlockData &data)
{
    Q_UNUSED(data);
    isBlock = true;
}

void DrawDxfPrivate::endBlock()
{
    isBlock = false;
}

//void DrawDxfPrivate::addLayer(const DL_LayerData& data) {
//    printf("LAYER: %s flags: %d\n", data.name.c_str(), data.flags);
//    printAttributes();
//}

void DrawDxfPrivate::addPoint(const DL_PointData& data)
{
    if(!isBlock) {
        printAttributes();
        m_pointList.append(data);
        qDebug()<<"\n *****AddPoint(1)*****\n --- x,y,z = "<<data.x<<data.y<<data.z;
    }
}

void DrawDxfPrivate::addLine(const DL_LineData& data)
{
    if(!isBlock) {
        printAttributes();
        m_lineList.append(data);
        qDebug()<<"\n *****AddLine(2)*****\n --- x1,y1 = "<<data.x1<<data.y1<<"\n x2,y2 ="<<data.x2<<data.y2;
    }
}

void DrawDxfPrivate::addArc(const DL_ArcData& data)
{
    if(!isBlock) {
        printAttributes();
            m_arcList.append(data);
            qDebug()<<"\n *****AddArc(3)*****\n --- cx,y,z = ("<<data.cx<<data.cy<<data.cz<<") \n radius,Angle1,Angle2 ="<<data.radius<<data.angle1<<data.angle2;
    }
}

void DrawDxfPrivate::addCircle(const DL_CircleData& data)
{
    if(!isBlock) {
        printAttributes();
        m_circleList.append(data);
        qDebug()<<"\n *******AddCircle(4)********\n --- cx,y,z = ("<<data.cx<<data.cy<<data.cz<<") \n radius ="<<data.radius;
    }
}

void DrawDxfPrivate::addPolyline(const DL_PolylineData& data)
{
    if(!isBlock) {
        printAttributes();
        m_polyLineList.append(data);
        qDebug()<<"\n *******AddPolyline(5)********\n --- num,m,n ="<<data.number<<data.m<<data.n<<"\n flag ="<<data.flags;
    }
}

void DrawDxfPrivate::addVertex(const DL_VertexData& data)
{
    if(!isBlock) {
        printAttributes();
        m_vertexList.append(data);
        qDebug()<<"\n *******AddVertex(6)********\n ---x, y, z, bulge="<<data.x<<data.y<<data.z<<data.bulge;
    }
}

void DrawDxfPrivate::addMText(const DL_MTextData &data)
{
    if(!isBlock) {
        printAttributes();
        m_textList.append(data);
        qDebug()<<"\n *******AddMText(7)********\n ---ipx, y ="<<data.ipx<<data.ipy<<"\n angle ="<<data.angle<<"\n attachmentPoint, drawingDirection"<<data.attachmentPoint<<data.drawingDirection;
        qDebug()<<"width, height ="<<data.width<<data.height<<" \n TEXT ="<<data.text.c_str()<<"\n dirx,y ="<<data.dirx<<data.diry;
    }
}

void DrawDxfPrivate::addEllipse(const DL_EllipseData &data)
{
    if(!isBlock) {
        m_ellipseList.append(data);
        qDebug()<<"\n *******AddEllipse(8)********\n ---cx,y ="<<data.cx<<data.cy<<"\n mx,y ="<<data.mx<<data.my;
        qDebug()<<"ratio ="<<data.ratio<<"angle1,2 ="<<data.angle1<<data.angle2;
    }
}

void DrawDxfPrivate::addText(const DL_TextData &data)
{
    if(!isBlock) {
        m_textDataList.append(data);
        qDebug()<<"\n *****AddText(9)****\n ---text ="<<data.text.c_str()<<"factor = "<<data.xScaleFactor;
        qDebug()<<"ipx,y = "<<data.ipx<<data.ipy<<"apx,y ="<<data.apx<<data.apy;
        qDebug()<<"angle, height, hJustification,v="<<data.angle<<data.height<<data.hJustification<<data.vJustification;
    }
}

void DrawDxfPrivate::addSpline(const DL_SplineData &data)
{
    if(!isBlock) {
        m_splineList.append(data);
        qDebug()<<"\n *****addSpline(10)****\n ---degree,nfits,nknots ="<<data.degree<<data.nFit<<data.nKnots;
        qDebug()<<"tangentStartX,Y ="<<data.tangentStartX<<data.tangentStartY<<"\n tangentEndX,Y ="<<data.tangentEndX<<data.tangentEndY;
    }
}

void DrawDxfPrivate::addControlPoint(const DL_ControlPointData &data)
{
    if(!isBlock) {
        m_controlPointList.append(data);
        qDebug()<<"\n *****AddControlPoint(11)****\n ---x,y,z,w ="<<data.x<<data.y<<data.z<<data.w;

    }
}

//void DrawDxfPrivate::addInsert(const DL_InsertData &data)
//{
//    qDebug()<<"\n *****TEST-1***\n ---name ="<<data.name.c_str();
//}

//void DrawDxfPrivate::addComment(const std::string &data)
//{
//    qDebug()<<"\n *****TEST-2****\n ---text ="<<data.c_str();
//}

//void DrawDxfPrivate::addXLine(const DL_XLineData &data)
//{
//    qDebug()<<"\n *****TEST-3****\n ---bx ="<<data.bx;
//}

//void DrawDxfPrivate::addRay(const DL_RayData &data)
//{
//    qDebug()<<"\n *****TEST-4****\n ---bx ="<<data.bx;
//}

void DrawDxfPrivate::add3dFace(const DL_3dFaceData& data) {
    printf("3DFACE\n");
    for (int i=0; i<4; i++) {
        printf("   corner %d: %6.3f %6.3f %6.3f\n",
            i, data.x[i], data.y[i], data.z[i]);
    }
    printAttributes();
}

void DrawDxfPrivate::printAttributes() {
    printf("  Attributes: Layer: %s, ", attributes.getLayer().c_str());
    printf(" Color: ");
    if (attributes.getColor()==256)	{
        printf("BYLAYER");
    } else if (attributes.getColor()==0) {
        printf("BYBLOCK");
    } else {
        printf("%d", attributes.getColor());
    }
    printf(" Width: ");
    if (attributes.getWidth()==-1) {
        printf("BYLAYER");
    } else if (attributes.getWidth()==-2) {
        printf("BYBLOCK");
    } else if (attributes.getWidth()==-3) {
        printf("DEFAULT");
    } else {
        printf("%d", attributes.getWidth());
    }
    printf(" Type: %s\n", attributes.getLinetype().c_str());
}

void DrawDxfPrivate::clear()
{
    m_pointList.clear();
    m_lineList.clear();
    m_arcList.clear();
    m_textDataList.clear();
    m_textList.clear();
    m_ellipseList.clear();
    m_circleList.clear();
    m_vertexList.clear();
    m_polyLineList.clear();
    m_splineList.clear();
    m_controlPointList.clear();
}

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
};

DrawDxfHeaderPrivate::DrawDxfHeaderPrivate()
{
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
    qDebug()<<"\n *****INSUNITS(3)*****\n --- flag = "<<data.flags;
}

void DrawDxfHeaderPrivate::add_PUCS_name(const DXF_HEADER_PUCSNAME& data)
{
    m_dataPUCSName.append(data);
    qDebug()<<"\n *******PUCSNAME(4)********\n --- name = "<<data.name.c_str();
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

DrawDxf * g_pDrawDxf = NULL;
DrawDxf *DrawDxf::Instance()
{
    if(!g_pDrawDxf){
        g_pDrawDxf = new DrawDxf();
    }
    return g_pDrawDxf;
}

DrawDxf::DrawDxf(QWidget *parent) :
    QWidget(parent),
    d(new DrawDxfPrivate()),
    h(new DrawDxfHeaderPrivate())
{
    m_pPart = NULL;
    m_fThickness = 20;
}

DrawDxf::~DrawDxf()
{
    delete d;
    delete h;
}

int DrawDxf::get_dxf_data()
{
    if(m_pPart == NULL)
        return -1;

    DL_Dxf dxf;

    QString dxfFile = QString(m_pPart->strPartFile);
    if(!dxf.in(dxfFile.toLocal8Bit().data(), d)) {
        qDebug()<<"could not be opened";
        return -1;
    }

    return 0;
}

int DrawDxf::get_dxf_header()
{
    if(m_pPart == NULL)
        return -1;

    DxfHeader header;

    QString dxfFile = QString(m_pPart->strPartFile);
    if (!header.in(dxfFile.toLocal8Bit().data(), h)) {
        qDebug()<<"could not be opened";
        return -1;
    }

    return 0;
}

void DrawDxf::draw_dxf_part(QPainter &painter)
{
    paint_line(painter);

    paint_text(painter);

    paint_arc(painter);

    paint_circle(painter);

    paint_point(painter);

    paint_ellipse(painter);
}

void DrawDxf::paint_point(QPainter &painter)
{
    if(d->m_vertexList.size() > 0){
        for(int i = 0; i < d->m_vertexList.count(); i++){
            QPointF _point = coordinate_trans(d->m_vertexList.at(i).x, d->m_vertexList.at(i).y, false);
            painter.drawPoint(_point);
        }
    }

//    if(d->m_controlPointList.size() > 0){
//        for(int i = 0; i < d->m_controlPointList.count(); i++){
//            QPointF _point = coordinate_trans(d->m_controlPointList.at(i).x, d->m_controlPointList.at(i).y, false);
//            painter.drawPoint(_point);
//        }
//    }

    if(d->m_pointList.size() > 0){
        for(int i = 0; i < d->m_pointList.count(); i++){
            QPointF _point = coordinate_trans(d->m_pointList.at(i).x, d->m_pointList.at(i).y, false);
            painter.drawPoint(_point);
        }
    }
}

void DrawDxf::paint_line(QPainter &painter)
{
    if (d->m_lineList.size() > 0){
        for(int i = 0; i < d->m_lineList.count(); i++){
            QPointF _point1 = coordinate_trans(d->m_lineList.at(i).x1, d->m_lineList.at(i).y1, false);
            QPointF _point2 = coordinate_trans(d->m_lineList.at(i).x2, d->m_lineList.at(i).y2, false);
            painter.drawLine(_point1, _point2);
        }
    }

    paint_polyLine(painter);
}

void DrawDxf::paint_polyLine(QPainter &painter)
{
    if(d->m_vertexList.isEmpty()){
        return;
    }

    int count = 1;
    for(int i = 0; i < d->m_polyLineList.count(); i++) {
        int number = d->m_polyLineList.at(i).number;
        if(d->m_polyLineList.at(i).flags & 0x1) {
            QPointF _point1 = coordinate_trans(d->m_vertexList.at(count + number - 2).x, d->m_vertexList.at(count + number - 2).y, false);
            QPointF _point2 = coordinate_trans(d->m_vertexList.at(count - 1).x, d->m_vertexList.at(count - 1).y, false);
            painter.drawLine(_point1, _point2);
        }
        int _count = count;
        for(int j = count; j < _count + number - 1; j++){
            QPointF _point1 = coordinate_trans(d->m_vertexList.at(j - 1).x, d->m_vertexList.at(j - 1).y, false);
            QPointF _point2 = coordinate_trans(d->m_vertexList.at(j).x, d->m_vertexList.at(j).y, false);
            painter.drawLine(_point1, _point2);
            count++;
        }
        count += 1;
    }
}

void DrawDxf::paint_text(QPainter &painter)
{
    if(d->m_textList.size() > 0){
        for(int i = 0; i < d->m_textList.count(); i++){
            QString str = format_text(QString::fromStdString(d->m_textList.at(i).text));
            double height = d->m_textList.at(i).height;
            double width = d->m_textList.at(i).width;
            Qt::AlignmentFlag flagV = get_v_flag(d->m_textList.at(i).attachmentPoint);
            Qt::AlignmentFlag flagH = get_h_flag(d->m_textList.at(i).attachmentPoint);

            QPointF _point = coordinate_trans(d->m_textList.at(i).ipx, d->m_textList.at(i).ipy, false);
            double rotateAngle = d->m_textList.at(i).angle;

            if(rotateAngle < 0) {
                rotateAngle = 2 * M_PI + rotateAngle;
            }

            rotate(painter, _point, - rotateAngle);//以矩形的中心点为中心旋转

            if(width > 0) {
                painter.drawText(_point, str);
            } else {
                QPointF _point1 = coordinate_trans(d->m_textList.at(i).ipx - fontMetrics().width(str) / 2, d->m_textList.at(i).ipy/* - height*/, false);
                QRectF rect = QRectF(_point1.x(), _point1.y(), fontMetrics().width(str) * d->m_scaleX, height * d->m_scaleY);
                painter.drawText(rect, flagV | flagH, str);
            }

            rotate(painter, _point, rotateAngle);//以矩形的中心点为中心旋转
        }
    }

    if(d->m_textDataList.size() > 0){
        for(int i = 0; i < d->m_textDataList.count(); i++){
            QPointF _point = coordinate_trans(d->m_textDataList.at(i).ipx, d->m_textDataList.at(i).ipy, false);
            painter.drawText(_point, d->m_textDataList.at(i).text.c_str());
        }
    }
}

void DrawDxf::paint_arc(QPainter &painter)
{
    if(d->m_arcList.isEmpty()){
        return;
    }

    for(int i = 0; i < d->m_arcList.count(); i++){
        double r = d->m_arcList.at(i).radius;
        double startAngle = d->m_arcList.at(i).angle1;
        double endAngle = d->m_arcList.at(i).angle2;
        double spanAngle = get_span_angle(startAngle, endAngle, false);

        QPointF _point1 = coordinate_trans(d->m_arcList.at(i).cx * d->m_arcList.at(i).ez, d->m_arcList.at(i).cy, false);
        QPointF _point2 = coordinate_trans(r, r, true);
        QRectF rect = QRectF(_point1.x() -  _point2.x(), _point1.y() - _point2.y(),
                             2 * _point2.x(), 2 * _point2.y());

        switch (m_axis) {
        case Axis_Normal:
            painter.drawArc(rect, 16 * startAngle, 16 * spanAngle);
            break;
        case Axis_Vertical_Flip:
            painter.drawArc(rect, - 16 * endAngle, 16 * spanAngle);
            break;
        case Axis_Horizontal_Flip:
            painter.drawArc(rect, 16 * (360 - endAngle), 16 * spanAngle);
            break;
        case Axis_Rotate_180:
            painter.drawArc(rect, 16 * (startAngle - 180), 16 * spanAngle);
            break;
        default:
            break;
        }
    }
}

void DrawDxf::paint_circle(QPainter &painter)
{
    if(d->m_circleList.isEmpty()){
        return;
    }

    for(int i = 0; i < d->m_circleList.count(); i++){
        double r = d->m_circleList.at(i).radius;
        QPointF _point1 = coordinate_trans(d->m_circleList.at(i).cx * d->m_circleList.at(i).ez, d->m_circleList.at(i).cy, false);
        QPointF _point2 = coordinate_trans(r, r, true);
        painter.drawEllipse(_point1.x() - _point2.x(), _point1.y() - _point2.y(),
                            2 * _point2.x(), 2 *  _point2.y());
    }
}

double DrawDxf::calc_rotate_angle(double mx, double my)
{
    double rotateAngle = 0;
    double m = get_magnitude2D(mx, my);
    if(m > 1e-6) {
        double ret = mx / m;
        if(ret >= 1.0) {
            rotateAngle = 0.0;
        }  else if(ret < -1.0){
            rotateAngle = M_PI;
        } else {
            rotateAngle = acos(ret);
        }
        if(my < 0.0) {
            rotateAngle = 2 * M_PI - rotateAngle;
        }
    }
    return rotateAngle;
}

double DrawDxf::get_magnitude2D(double x, double y)
{
    return sqrt(x * x + y * y);
}

void DrawDxf::paint_ellipse(QPainter &painter)
{
    if(d->m_ellipseList.isEmpty()){
        return;
    }

    for(int i = 0; i < d->m_ellipseList.count(); i++){
        double k  = d->m_ellipseList.at(i).ratio;
        double r1 = get_magnitude2D(d->m_ellipseList.at(i).mx, d->m_ellipseList.at(i).my);
        double rotateAngle = calc_rotate_angle(d->m_ellipseList.at(i).mx, d->m_ellipseList.at(i).my);
        double startAngle = d->m_ellipseList.at(i).angle1 * 180 / M_PI;
        double endAngle = d->m_ellipseList.at(i).angle2 * 180 / M_PI;

        if (d->m_ellipseList.at(i).ez <= -0.999999) {
            double tmp = startAngle;
            startAngle = 360 - endAngle;
            endAngle = 360 - tmp;
        }

        double spanAngle = get_span_angle(startAngle, endAngle, false);

        QPointF _point1 = coordinate_trans(d->m_ellipseList.at(i).cx, d->m_ellipseList.at(i).cy, false);
        QPointF _point2 = coordinate_trans(r1, k * r1, true);
        QRectF rect = QRectF(_point1.x() - _point2.x(), _point1.y() - _point2.y(),
                             2 * r1 * d->m_scaleX, 2 * k * r1 * d->m_scaleY);

        switch (m_axis) {
        case Axis_Normal:
            rotate(painter, _point1, - rotateAngle);//以椭圆的中心点为中心旋转
            painter.drawArc(rect, 16 * startAngle, 16 * spanAngle);
            rotate(painter, _point1, rotateAngle);
            break;
        case Axis_Vertical_Flip:
            rotate(painter, _point1, rotateAngle);//以椭圆的中心点为中心旋转
            painter.drawArc(rect, - 16 * endAngle, 16 * spanAngle);
            rotate(painter, _point1, - rotateAngle);
            break;
        case Axis_Horizontal_Flip:
            rotate(painter, _point1, - (M_PI - rotateAngle));//以椭圆的中心点为中心旋转
            painter.drawArc(rect, 16 * (360 - endAngle), 16 * spanAngle);
            rotate(painter, _point1, M_PI - rotateAngle);
            break;
        case Axis_Rotate_180:
            rotate(painter, _point1, - rotateAngle);//以椭圆的中心点为中心旋转
            painter.drawArc(rect, 16 * (startAngle - 180), 16 * spanAngle);
            rotate(painter, _point1, rotateAngle);
            break;
        default:
            break;
        }
    }
}

void DrawDxf::draw_dxf_header(QPainter &painter)
{

    paint_wcs_axis(painter);

    paint_ucs_axis(painter);
}

void DrawDxf::paint_wcs_axis(QPainter &painter)
{
    if(!h->m_dataPUCSOrg.isEmpty()) {
        for(int i = 0; i < h->m_dataPUCSOrg.count(); i ++) {
            double x0 = h->m_dataPUCSOrg.at(i).x;
            double y0 = h->m_dataPUCSOrg.at(i).y;
            double x1 = x0 + 100 * h->m_dataPUCSXDir.at(i).x;
            double y1 = y0 + 100 * h->m_dataPUCSXDir.at(i).y;
            double x2 = x0 + 100 * h->m_dataPUCSYDir.at(i).x;
            double y2 = y0 + 100 * h->m_dataPUCSYDir.at(i).y;

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
    } else {
        double x0 = 100;
        double y0 = 100;
        QPointF _point1 = coordinate_trans(x0, 0, false);
        QPointF _point2 = coordinate_trans(0, y0, false);

        painter.drawLine(_point1, coordinate_trans(0, 0, false)); // X Axis
        painter.drawLine(_point2, coordinate_trans(0, 0, false)); // Y Axis

        painter.drawLine(coordinate_trans(x0 - 5, 5, false), _point1);
        painter.drawLine(coordinate_trans(x0 - 5, - 5, false), _point1);

        painter.drawLine(coordinate_trans(- 5, y0 - 5, false), _point2);
        painter.drawLine(coordinate_trans(5, y0 - 5, false), _point2);
    }
}

void DrawDxf::paint_ucs_axis(QPainter &painter)
{
    if(!h->m_dataUCSOrg.isEmpty()) {
        for(int i = 0; i < h->m_dataUCSOrg.count(); i ++) {
            double x0 = h->m_dataUCSOrg.at(i).x;
            double y0 = h->m_dataUCSOrg.at(i).y;
            double x1 = x0 + 100 * h->m_dataUCSXDir.at(i).x;
            double y1 = y0 + 100 * h->m_dataUCSXDir.at(i).y;
            double x2 = x0 + 100 * h->m_dataUCSYDir.at(i).x;
            double y2 = y0 + 100 * h->m_dataUCSYDir.at(i).y;

            QPointF _point1 = coordinate_trans(x0, y0, false);
            QPointF _point2 = coordinate_trans(x1, y1, false);
            QPointF _point3 = coordinate_trans(x2, y2, false);

            painter.drawLine(_point1, _point2); // X Axis
            painter.drawLine(_point1, _point3); // Y Axis

            /* X Axis Arrow */
            if(h->m_dataPUCSXDir.at(i).x * h->m_dataUCSXDir.at(i).x < 0) {
                painter.drawLine(coordinate_trans(x1 + 5, y1 + 5, false), _point2);
                painter.drawLine(coordinate_trans(x1 + 5, y1 - 5, false), _point2);
            } else {
                painter.drawLine(coordinate_trans(x1 - 5, y1 + 5, false), _point2);
                painter.drawLine(coordinate_trans(x1 - 5, y1 - 5, false), _point2);
            }

            /* Y Axis Arrow */
            if(h->m_dataPUCSYDir.at(i).y * h->m_dataUCSYDir.at(i).y < 0) {
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

void DrawDxf::draw_dxf_header(QPainterPath &path)
{
    Q_UNUSED(path);
//    draw_wcs_axis(path);

//    draw_ucs_axis(path);
}

//void DrawDxf::draw_wcs_axis(QPainterPath &path)
//{
//    if(!h->m_dataPUCSOrg.isEmpty()) {
//        for(int i = 0; i < h->m_dataPUCSOrg.count(); i ++) {
//            double x0 = h->m_dataPUCSOrg.at(i).x;
//            double y0 = h->m_dataPUCSOrg.at(i).y;
//            double x1 = x0 + 100 * h->m_dataPUCSXDir.at(i).x;
//            double y1 = y0 + 100 * h->m_dataPUCSXDir.at(i).y;
//            double x2 = x0 + 100 * h->m_dataPUCSYDir.at(i).x;
//            double y2 = y0 + 100 * h->m_dataPUCSYDir.at(i).y;

//            QPointF _point1 = coordinate_trans(x0, y0, false);
//            QPointF _point2 = coordinate_trans(x1, y1, false);
//            QPointF _point3 = coordinate_trans(x2, y2, false);

//            path.moveTo(_point1);
//            path.lineTo(_point2); // X Axis
//            path.moveTo(_point1);
//            path.lineTo(_point3); // Y Axis

//            path.moveTo(coordinate_trans(x1 - 5, y1 + 5, false));
//            path.lineTo(_point2);
//            path.lineTo(coordinate_trans(x1 - 5, y1 - 5, false));

//            path.moveTo(coordinate_trans(x2 - 5, y2 - 5, false));
//            path.lineTo(_point3);
//            path.lineTo(coordinate_trans(x2 + 5, y2 - 5, false));

//        }
//    }
//}

//void DrawDxf::draw_ucs_axis(QPainterPath &path)
//{
//    if(!h->m_dataUCSOrg.isEmpty()) {
//        for(int i = 0; i < h->m_dataUCSOrg.count(); i ++) {
//            double x0 = h->m_dataUCSOrg.at(i).x;
//            double y0 = h->m_dataUCSOrg.at(i).y;
//            double x1 = x0 + 100 * h->m_dataUCSXDir.at(i).x;
//            double y1 = y0 + 100 * h->m_dataUCSXDir.at(i).y;
//            double x2 = x0 + 100 * h->m_dataUCSYDir.at(i).x;
//            double y2 = y0 + 100 * h->m_dataUCSYDir.at(i).y;

//            QPointF _point1 = coordinate_trans(x0, y0, false);
//            QPointF _point2 = coordinate_trans(x1, y1, false);
//            QPointF _point3 = coordinate_trans(x2, y2, false);

//            path.moveTo(_point1);
//            path.lineTo(_point2);// X Axis
//            path.moveTo(_point1);
//            path.lineTo( _point3);// Y Axis

//            path.moveTo(coordinate_trans(x1 - 5, y1 + 5, false));
//            path.lineTo(_point2);
//            path.lineTo(coordinate_trans(x1 - 5, y1 - 5, false));

//            if(h->m_dataPUCSYDir.at(i).y * h->m_dataUCSYDir.at(i).y < 0) {
//                path.moveTo(coordinate_trans(x2 - 5, y2 + 5, false));
//                path.lineTo(_point3);
//                path.lineTo(coordinate_trans(x2 + 5, y2 + 5, false));
//            } else {
//                path.moveTo(coordinate_trans(x2 - 5, y2 - 5, false));
//                path.lineTo(_point3);
//                path.lineTo(coordinate_trans(x2 + 5, y2 - 5, false));
//            }
//        }
//    }
//}

int DrawDxf::set_part(PART_CONFIG *pInfo_)
{
    d->clear();
    h->clear();

    m_pPart = pInfo_;
    m_fThickness = m_pPart->afSize[0];

    int ret = get_dxf_data();
    int ret_ = get_dxf_header();

    return ret & ret_;
}

void DrawDxf::draw_dxf_part(QPainterPath &path)
{
    if(!d->m_lineList.isEmpty()) {
        draw_line(path);
    }

    if(!d->m_vertexList.isEmpty()) {
        draw_polyLine(path);
    }

    if(!d->m_arcList.isEmpty()) {
        draw_arc(path);
    }

    if(!d->m_circleList.isEmpty()) {
        draw_circle(path);
    }

    if(!d->m_ellipseList.isEmpty()) {
        draw_ellipse(path);
    }
}

void DrawDxf::draw_line(QPainterPath &path)
{
    if(d->m_lineList.size() > 0){
        for(int i = 0; i < d->m_lineList.count(); i++){
            QPointF _point1 = coordinate_trans(d->m_lineList.at(i).x1, d->m_lineList.at(i).y1, false);
            QPointF _point2 = coordinate_trans(d->m_lineList.at(i).x2, d->m_lineList.at(i).y2, false);
            path.moveTo(_point1);
            path.lineTo(_point2);
        }
    }
}

void DrawDxf::draw_polyLine(QPainterPath& path)
{
    int count = 1;
    for(int i = 0; i < d->m_polyLineList.count(); i++) {
        int number = d->m_polyLineList.at(i).number;
        if(d->m_polyLineList.at(i).flags & 0x1) {
            QPointF _point1 = coordinate_trans(d->m_vertexList.at(count + number - 2).x, d->m_vertexList.at(count + number - 2).y, false);
            QPointF _point2 = coordinate_trans(d->m_vertexList.at(count - 1).x, d->m_vertexList.at(count - 1).y, false);
            path.moveTo(_point1);
            path.lineTo(_point2);
        }
        int _count = count;
        for(int j = count; j < _count + number - 1; j++){
            QPointF _point1 = coordinate_trans(d->m_vertexList.at(j - 1).x, d->m_vertexList.at(j - 1).y, false);
            QPointF _point2 = coordinate_trans(d->m_vertexList.at(j).x, d->m_vertexList.at(j).y, false);
            path.moveTo(_point1);
            path.lineTo(_point2);
            count++;
        }
        count += 1;
    }
}

void DrawDxf::draw_arc(QPainterPath &path)
{
    for(int i = 0; i < d->m_arcList.count(); i++){
        double r = d->m_arcList.at(i).radius;
        double startAngle = d->m_arcList.at(i).angle1;
        double endAngle = d->m_arcList.at(i).angle2;
        double spanAngle = get_span_angle(startAngle, endAngle, false);

        QPointF _point1 = coordinate_trans(d->m_arcList.at(i).cx * d->m_arcList.at(i).ez, d->m_arcList.at(i).cy, false);
        QPointF _point2 = coordinate_trans(r, r, true);
        QRectF rect = QRectF(_point1.x() - _point2.x(), _point1.y() - _point2.y(),
                             2 * r * d->m_scaleX, 2 * r * d->m_scaleY);

        switch (m_axis) {
        case Axis_Normal:
            path.arcMoveTo(rect, startAngle);
            path.arcTo(rect, startAngle, spanAngle);
            break;
        case Axis_Vertical_Flip:
            path.arcMoveTo(rect, -endAngle);
            path.arcTo(rect, -endAngle, spanAngle);
            break;
        case Axis_Horizontal_Flip:
            path.arcMoveTo(rect, 360 - endAngle);
            path.arcTo(rect, 360 - endAngle, spanAngle);
            break;
        case Axis_Rotate_180:
            path.arcMoveTo(rect, startAngle - 180);
            path.arcTo(rect, startAngle - 180, spanAngle);
        default:
            break;
        }
    }
}

void DrawDxf::draw_circle(QPainterPath &path)
{
    for(int i = 0; i < d->m_circleList.count(); i++){
        double r = d->m_circleList.at(i).radius;
        QPointF _point1 = coordinate_trans(d->m_circleList.at(i).cx * d->m_circleList.at(i).ez, /*- */d->m_circleList.at(i).cy, false);
        QPointF _point2 = coordinate_trans(r, r, true);
        path.addEllipse(_point1.x() - _point2.x(), _point1.y() - _point2.y(),
                        2 * r * d->m_scaleX, 2 * r * d->m_scaleY);
    }
}

void DrawDxf::draw_ellipse(QPainterPath &path)
{
    for(int i = 0; i < d->m_ellipseList.count(); i++){
        double k  = d->m_ellipseList.at(i).ratio;
        double r1 = get_magnitude2D(d->m_ellipseList.at(i).mx, d->m_ellipseList.at(i).my);
        double rotateAngle = calc_rotate_angle(d->m_ellipseList.at(i).mx, d->m_ellipseList.at(i).my);
        double startAngle = d->m_ellipseList.at(i).angle1 * 180 / M_PI;
        double endAngle = d->m_ellipseList.at(i).angle2 * 180 / M_PI;

        if (d->m_ellipseList.at(i).ez <= -0.999999) {
            double tmp = startAngle;
            startAngle = 360 - endAngle;
            endAngle = 360 - tmp;
        }

        double spanAngle = get_span_angle(startAngle, endAngle, false);

        QPointF _point1 = coordinate_trans(d->m_ellipseList.at(i).cx, d->m_ellipseList.at(i).cy, false);

        if(rotateAngle <= 1e-9) {
            QPointF _point2 = coordinate_trans(r1, k * r1, true);
            QRectF rect = QRectF(_point1.x() - _point2.x(), _point1.y() - _point2.y(),
                                 2 * r1 * d->m_scaleX, 2 * k * r1 * d->m_scaleY);
            if(m_axis == Axis_Normal) {
                path.arcMoveTo(rect, startAngle);
                path.arcTo(rect, startAngle, spanAngle);
            } else if(m_axis == Axis_Vertical_Flip) {
                path.arcMoveTo(rect, - endAngle);
                path.arcTo(rect, - endAngle, spanAngle);
            }
        } else {
            QPolygonF pa;
            switch (m_axis) {
            case Axis_Normal:
                create_ellipse(pa, RVector(_point1.x(), _point1.y()),
                               r1 * d->m_scaleX, k * r1 * d->m_scaleY,
                               rotateAngle, startAngle * M_PI / 180, endAngle * M_PI / 180, -1);
                break;
            case Axis_Vertical_Flip:
                create_ellipse(pa, RVector(_point1.x(), _point1.y()),
                               r1 * d->m_scaleX, k * r1 * d->m_scaleY,
                               rotateAngle, startAngle * M_PI / 180, endAngle * M_PI / 180, 1);
                break;
            case Axis_Horizontal_Flip:
                create_ellipse(pa, RVector(_point1.x(), _point1.y()),
                               r1 * d->m_scaleX, k * r1 * d->m_scaleY,
                               M_PI - rotateAngle, (360 - endAngle) * M_PI / 180, (spanAngle + endAngle - 360) * M_PI / 180, -1);
                break;
            case Axis_Rotate_180:
                create_ellipse(pa, RVector(_point1.x(), _point1.y()),
                               r1 * d->m_scaleX, k * r1 * d->m_scaleY,
                               rotateAngle, (startAngle - 180) * M_PI / 180, (endAngle - 180) * M_PI / 180, -1);
                break;
            default:
                break;
            }


            path.addPolygon(pa);
        }
    }
}

void DrawDxf::create_ellipse(QPolygonF& pa, const RVector& cp, double radius1, double radius2,
                             double angle, double angle1, double angle2,  int factor)
{
    const RVector vr(radius1, radius2);
    const RVector rvp(radius2, radius1);
    const double ab = radius1 * radius2;
    double ea1 = angle1;
    double dA = get_span_angle(angle1, angle2, true);

    if(dA <= RS_TOLERANCE_ANGLE) {
        dA = 2 * M_PI;
    }
    double ea2 = ea1 + dA;

    const RVector angleVector(factor * angle);
    /*
      draw a new line after tangent changes by 0.01 rad
      ds^2 = (a^2 sin^2 + b^2 cos^2) da^2
      */
    RVector vp(factor * ea1);
    vp.scale(vr);
    vp.rotate(angleVector);
    vp.move(cp);
    pa.clear();
    const double minDea = fabs(ea2 - ea1) / 2048;
    // Arc Counterclockwise:
    do {
        RVector va(factor * ea1);
        vp = va;
        double r2 = va.scale(rvp).squared();
        if( r2 < 1.5e-15) r2 = RS_TOLERANCE15;
        double aStep = ab /(r2 * sqrt(r2));
        if(aStep < minDea) aStep = minDea;
        if(aStep > M_PI / 18) aStep = M_PI / 18;
        ea1 += aStep;

        vp.scale(vr);
        vp.rotate(angleVector);
        vp.move(cp);
        /*
         * 长轴为a，短轴为b，中心点坐标分别为cx、cy,
         * 椭圆旋转角度为fi，t是当前角度；
         * 长轴不与x轴或y轴平行的椭圆的参数方程：
         * x=cx+a*cos(t)*cos(fi)-b*sin(t)*sin(fi)
         * y=cy+a*cos(t)*sin(fi)+b*sin(t)*cos(fi)
        */
        pa << QPointF((qreal)vp.x, (qreal)vp.y);
    } while(fabs(angle1 - ea1) < dA);

    vp.set(cos(ea2) * radius1, factor * sin(ea2) * radius2);
    vp.rotate(angleVector);
    vp.move(cp);
    pa << QPointF((qreal)vp.x, (qreal)vp.y);//增加椭圆在angle2的坐标
}

double DrawDxf::get_span_angle(double angle1, double angle2, bool isRad)
{
    double spanAngle = 0.0;
    double ret = 0.0;
    if(isRad) {
        ret = 2 * M_PI;
    } else {
        ret = 360;
    }
    if(fabs(angle2 - angle1) < 1e-9 || ret - fabs(angle2 - angle1) < 1e-9) {
        spanAngle = ret;
    } else {
        if(angle1 < angle2) {
            spanAngle = angle2 - angle1;
        } else {
            spanAngle = ret - angle1 + angle2;
        }
    }
    return spanAngle;
}

QPointF DrawDxf::coordinate_trans(float x_, float y_, bool isRadius)
{
    float _fX;
    float _fY;

    float _fScaleX = d->m_scaleX;
    float _fScaleY = d->m_scaleY;
    float _fX0 = d->m_centerX;
    float _fY0 = d->m_centerY;

    if(isRadius) {
        _fX = x_ * _fScaleX;
        _fY = y_ * _fScaleY;
    } else {
        double x0 = 0.0;
        double y0 = 0.0;
        if(!h->m_dataUCSOrg.isEmpty()) {
            x0 = h->m_dataUCSOrg.at(0).x;
            y0 = h->m_dataUCSOrg.at(0).y;
        }
        switch (m_axis) {
        case Axis_Normal:
            _fX = (x_ - x0) * _fScaleX + _fX0;
            _fY = (- y_ + y0) * _fScaleY + _fY0;//x不变，y轴上下翻转
            break;
        case Axis_Vertical_Flip:
            _fX = (x_ - x0) * _fScaleX + _fX0;
            _fY = (y_ - y0) * _fScaleY + _fY0;//x不变，y不变
            break;
        case Axis_Horizontal_Flip:
            _fX = (- x_ + x0) * _fScaleX + _fX0;
            _fY = (- y_ + y0) * _fScaleY + _fY0;//x轴左右翻转，y轴上下翻转
            break;
        case Axis_Rotate_180:
            _fX = (- x_ + x0) * _fScaleX + _fX0;
            _fY = (y_ - y0) * _fScaleY + _fY0;//x轴左右翻转，y不变
        default:
            break;
        }
    }

    QPointF _point;
    _point.setX(_fX);
    _point.setY(_fY);

    return _point;
}

void DrawDxf::set(double width, double height, double centerX, double centerY, double scaleX, double scaleY)
{
    d->m_width = width;
    d->m_height = height;
    d->m_centerX = centerX;
    d->m_centerY = centerY;
    d->m_scaleX = scaleX;
    d->m_scaleY = scaleY;
}

QString DrawDxf::format_text(QString str)
{
    if(str.contains("%%D")) {
        str = str.left(str.indexOf("%%D")) + "°";
    }
    if(str.contains("\\A1;")) {
        str = str.right(str.length() - str.indexOf("\\A1;") - 3);
    }
    return str;
}

Qt::AlignmentFlag DrawDxf::get_v_flag(int flag)
{
    Qt::AlignmentFlag _flag;
    if(flag <= 3) {
        _flag = Qt::AlignTop;
    } else if(flag <= 6) {
        _flag = Qt::AlignVCenter;
    } else {
        _flag = Qt::AlignBottom;
    }
    return _flag;
}

Qt::AlignmentFlag DrawDxf::get_h_flag(int flag)
{
    Qt::AlignmentFlag _flag;
    if(flag % 3 == 1) {
        _flag = Qt::AlignLeft;
    } else if(flag % 3 == 2) {
        _flag = Qt::AlignHCenter;
    } else {
        _flag = Qt::AlignRight;
    }
    return _flag;
}

void DrawDxf::set_axis_orientation(DrawDxf::AxisOrientation value)
{
    m_axis = value;
}

void DrawDxf::set_axis_orientation_s_scan(DrawDxf::AxisOrientation value)
{
    if(h->m_dataUCSOrg.isEmpty()) {
        m_axis = value;
    } else {
        double x = h->m_dataUCSXDir.at(0).x;
        double y = h->m_dataUCSYDir.at(0).y;

        // S扫中坐标轴本身是Axis_Vertical_Flip
        if(x > 0 && y > 0) {
            m_axis = Axis_Vertical_Flip; //Axis_Normal & Axis_Vertical_Flip
        } else if(x > 0 && y < 0) {
            m_axis = Axis_Normal;//Axis_Vertical_Flip & Axis_Vertical_Flip
        } else if(x < 0 && y > 0) {
            m_axis = Axis_Rotate_180;//Axis_Horizontal_Flip & Axis_Vertical_Flip
        } else {
            m_axis = Axis_Horizontal_Flip;//Axis_Rotate_180 & Axis_Vertical_Flip
        }
    }
}

void DrawDxf::rotate(QPainter &painter, QPointF point, double angle)
{
    if(fabs(angle) > 1e-9) {
        painter.translate(point.x(), point.y());
        painter.rotate(angle * 180 / M_PI);
        painter.translate(- point.x(), - point.y());
    }
}


}
