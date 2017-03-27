#include "DrawDxf.h"
#include "dl_dxf.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

namespace DplDxf {
class DrawDxfPrivate : public DL_CreationAdapter
{
public:
    DrawDxfPrivate();

//    virtual void addLayer(const DL_LayerData& data);
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

private:

};

DrawDxfPrivate::DrawDxfPrivate()
{

}

//void DrawDxfPrivate::addLayer(const DL_LayerData& data) {
//    printf("LAYER: %s flags: %d\n", data.name.c_str(), data.flags);
//    printAttributes();
//}

void DrawDxfPrivate::addPoint(const DL_PointData& data)
{
    printAttributes();
    m_pointList.append(data);
    qDebug()<<"\n *****AddPoint(1)*****\n --- x,y,z = "<<data.x<<data.y<<data.z;
}

void DrawDxfPrivate::addLine(const DL_LineData& data)
{
    printAttributes();
    m_lineList.append(data);
    qDebug()<<"\n *****AddLine(2)*****\n --- x1,y1 = "<<data.x1<<data.y1<<"\n x2,y2 ="<<data.x2<<data.y2;
}

void DrawDxfPrivate::addArc(const DL_ArcData& data)
{
    printAttributes();
    m_arcList.append(data);
    qDebug()<<"\n *****AddArc(3)*****\n --- cx,y,z = ("<<data.cx<<data.cy<<data.cz<<") \n radius,Angle1,Angle2 ="<<data.radius<<data.angle1<<data.angle2;
}

void DrawDxfPrivate::addCircle(const DL_CircleData& data)
{
    printAttributes();
    m_circleList.append(data);
    qDebug()<<"\n *******AddCircle(4)********\n --- cx,y,z = ("<<data.cx<<data.cy<<data.cz<<") \n radius ="<<data.radius;
}

void DrawDxfPrivate::addPolyline(const DL_PolylineData& data)
{
    printAttributes();
    m_polyLineList.append(data);
    qDebug()<<"\n *******AddPolyline(5)********\n --- num,m,n ="<<data.number<<data.m<<data.n<<"\n flag ="<<data.flags;
}

void DrawDxfPrivate::addVertex(const DL_VertexData& data)
{
    printAttributes();
    m_vertexList.append(data);
    qDebug()<<"\n *******AddVertex(6)********\n ---x, y, z, bulge="<<data.x<<data.y<<data.z<<data.bulge;
}

void DrawDxfPrivate::addMText(const DL_MTextData &data)
{
    printAttributes();
    m_textList.append(data);
    qDebug()<<"\n *******AddMText(7)********\n ---ipx, y ="<<data.ipx<<data.ipy;
    qDebug()<<"width, height ="<<data.width<<data.height<<" \n TEXT ="<<data.text.c_str();
}

void DrawDxfPrivate::addEllipse(const DL_EllipseData &data)
{
    m_ellipseList.append(data);
    qDebug()<<"\n *******AddEllipse(8)********\n ---cx,y ="<<data.cx<<data.cy<<"\n mx,y ="<<data.mx<<data.my;
    qDebug()<<"ratio ="<<data.ratio<<"angle1,2 ="<<data.angle1<<data.angle2;
}

void DrawDxfPrivate::addText(const DL_TextData &data)
{
    m_textDataList.append(data);
    qDebug()<<"\n *****AddText(9)****\n ---text ="<<data.text.c_str()<<"factor = "<<data.xScaleFactor;
    qDebug()<<"ipx,y = "<<data.ipx<<data.ipy<<"apx,y ="<<data.apx<<data.apy;
    qDebug()<<"angle, height, hJustification,v="<<data.angle<<data.height<<data.hJustification<<data.vJustification;
}

void DrawDxfPrivate::addSpline(const DL_SplineData &data)
{
    m_splineList.append(data);
    qDebug()<<"\n *****addSpline(10)****\n ---degree,nfits,nknots ="<<data.degree<<data.nFit<<data.nKnots;
    qDebug()<<"tangentStartX,Y ="<<data.tangentStartX<<data.tangentStartY<<"\n tangentEndX,Y ="<<data.tangentEndX<<data.tangentEndY;
}

void DrawDxfPrivate::addControlPoint(const DL_ControlPointData &data)
{
    m_controlPointList.append(data);
    qDebug()<<"\n *****AddControlPoint(11)****\n ---x,y,z,w ="<<data.x<<data.y<<data.z<<data.w;
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
    d(new DrawDxfPrivate())
{
    m_pPart = NULL;
    m_fThickness = 20;

    m_pPart      = NULL;
    m_fThickness = 20;

    m_Info.fScaleX = 1;
    m_Info.fScaleY = 1;
    m_Info.fX = 0;
    m_Info.fY = 0;
}

DrawDxf::~DrawDxf()
{
    delete d;
}

int DrawDxf::getDxfData()
{
    if(m_pPart == NULL)
        return -1;

    DL_Dxf dxf;

    QString dxfFile = m_pPart->strPartFile;
    if (!dxf.in(dxfFile.toLatin1().data(), d)) {
        qDebug()<<"could not be opened";
        return -1;
    }

    return 0;
}

void DrawDxf::draw_dxfPart(QPainter &painter, double zoom, double centerX, double centerY)
{
    paint_line(painter, zoom, centerX, centerY);

    paint_text(painter, zoom, centerX, centerY);

    paint_arc(painter, zoom, centerX, centerY);

    paint_circle(painter, zoom, centerX, centerY);

    paint_point(painter, zoom, centerX, centerY);

    paint_ellipse(painter, zoom, centerX, centerY);
}

void DrawDxf::paint_point(QPainter &painter, double zoom, double centerX, double centerY)
{
    if(d->m_vertexList.size() > 0){
        for(int i = 0; i < d->m_vertexList.count(); i++){
            QPointF _point = coordinate_trans(d->m_vertexList.at(i).x, - d->m_vertexList.at(i).y);
            painter.drawPoint(_point);
//            painter.drawPoint(zoom*d->m_vertexList.at(i).x + centerX, -zoom*d->m_vertexList.at(i).y + centerY);
        }
    }

    if(d->m_controlPointList.size() > 0){
        for(int i = 0; i < d->m_controlPointList.count(); i++){
            QPointF _point = coordinate_trans(d->m_controlPointList.at(i).x, - d->m_controlPointList.at(i).y);
            painter.drawPoint(_point);
//            painter.drawPoint(zoom*d->m_controlPointList.at(i).x + centerX, -zoom*d->m_controlPointList.at(i).y + centerY);
        }
    }

    if(d->m_pointList.size() > 0){
        for(int i = 0; i < d->m_pointList.count(); i++){
            QPointF _point = coordinate_trans(d->m_pointList.at(i).x, - d->m_pointList.at(i).y);
            painter.drawPoint(_point);
//            painter.drawPoint(zoom*d->m_pointList.at(i).x + centerX, -zoom*d->m_pointList.at(i).y + centerY);
        }
    }
}

void DrawDxf::paint_line(QPainter &painter, double zoom, double centerX, double centerY)
{
    if (d->m_lineList.size() > 0){
        for(int i = 0; i < d->m_lineList.count(); i++){
            QPointF _point1 = coordinate_trans(d->m_lineList.at(i).x1, - d->m_lineList.at(i).y1);
            QPointF _point2 = coordinate_trans(d->m_lineList.at(i).x2, - d->m_lineList.at(i).y2);
            painter.drawLine(_point1, _point2);
//            painter.drawLine(zoom * d->m_lineList.at(i).x1 + centerX,
//                             - zoom * d->m_lineList.at(i).y1 + centerY,
//                             zoom * d->m_lineList.at(i).x2 + centerX,
//                             - zoom * d->m_lineList.at(i).y2 + centerY);
        }
    }

//    if(m_polyLineList.size() > 0){
//        for(int i = 0; i < m_polyLineList.count(); i++){
//            if(m_polyLineList.at(i).flags){
//                paint_polyLine_1(painter, zoom, centerX, centerY);
//            }else{
//                paint_polyLine_0(painter, zoom, centerX, centerY);
//            }
//        }
//    }
    paint_polyLine_0(painter, zoom, centerX, centerY);
}

void DrawDxf::paint_polyLine_0(QPainter &painter, double zoom, double centerX, double centerY)
{
    if(d->m_vertexList.isEmpty()){
        return;
    }

    int count = 1;
    for(int i = 0; i < d->m_polyLineList.count(); i++) {
        int number = d->m_polyLineList.at(i).number;
        for(int j = count; j < number; j++){
            QPointF _point1 = coordinate_trans(d->m_vertexList.at(j - 1).x, - d->m_vertexList.at(j - 1).y);
            QPointF _point2 = coordinate_trans(d->m_vertexList.at(j).x, - d->m_vertexList.at(j).y);
            painter.drawLine(_point1, _point2);

//            painter.drawLine(zoom * d->m_vertexList.at(j - 1).x + centerX, - zoom * d->m_vertexList.at(j - 1).y + centerY,
//                             zoom * d->m_vertexList.at(j).x + centerX, - zoom * d->m_vertexList.at(j).y + centerY);
            count++;
        }
    }

}

void DrawDxf::paint_polyLine_1(QPainter &painter, double zoom, double centerX, double centerY)
{
//    if(d->m_vertexList.isEmpty()){
//        return;
//    }

//    for(int i = 1; i < d->m_vertexList.count(); i++){
//        painter.drawLine(zoom*d->m_vertexList.at(i-1).x + centerX, -zoom*d->m_vertexList.at(i-1).y + centerY,
//                         zoom*d->m_vertexList.at(i).x + centerX, -zoom*d->m_vertexList.at(i).y + centerY);
//        painter.drawLine(zoom*d->m_vertexList.at(0).x + centerX, -zoom*d->m_vertexList.at(0).y + centerY,
//                         zoom*d->m_vertexList.at(d->m_vertexList.count()-1).x + centerX,
//                         -zoom*d->m_vertexList.at(d->m_vertexList.count()-1).y + centerY);
//    }
}

void DrawDxf::paint_text(QPainter &painter, double zoom, double centerX, double centerY)
{
    if(d->m_textList.size() > 0){
        for(int i = 0; i < d->m_textList.count(); i++){
            painter.drawText(zoom*(d->m_textList.at(i).ipx-2*d->m_textList.at(i).height) + centerX,
                             -zoom*d->m_textList.at(i).ipy + centerY,
                             zoom*4*d->m_textList.at(i).height, zoom*d->m_textList.at(i).height,
                             Qt::AlignLeft, d->m_textList.at(i).text.c_str());
        }
    }

    if(d->m_textDataList.size() > 0){
        for(int i = 0; i < d->m_textDataList.count(); i++){
            painter.drawText(zoom * d->m_textDataList.at(i).ipx + centerX,
                             - zoom * d->m_textDataList.at(i).ipy - d->m_textDataList.at(i).height + centerY,
                             zoom * 9 * d->m_textDataList.at(i).height, zoom * d->m_textDataList.at(i).height,
                             Qt::AlignLeft, d->m_textDataList.at(i).text.c_str());
        }
    }
}

void DrawDxf::paint_arc(QPainter &painter, double zoom, double centerX, double centerY)
{
    if(d->m_arcList.isEmpty()){
        return;
    }

    for(int i = 0; i < d->m_arcList.count(); i++){
        double r = d->m_arcList.at(i).radius;
        double startAngle = d->m_arcList.at(i).angle1;
        double endAngle = d->m_arcList.at(i).angle2;
        double spanAngle = get_span_angle(startAngle, endAngle, false);

        QPointF _point = coordinate_trans(d->m_arcList.at(i).cx - r, - d->m_arcList.at(i).cy - r);
        QRectF rect = QRectF(_point.x(), _point.y(), 2 * r * m_Info.fScaleX, 2 * r * m_Info.fScaleY);
        painter.drawArc(rect, 16 * startAngle, 16 * spanAngle);
//        painter.drawArc(zoom * d->m_arcList.at(i).cx -zoom*r + centerX,
//                        - zoom * d->m_arcList.at(i).cy - zoom*r + centerY,
//                        zoom*2*r, zoom*2*r, startAngle * 16, spanAngle *16);
    }
}

void DrawDxf::paint_circle(QPainter &painter, double zoom, double centerX, double centerY)
{
    if(d->m_circleList.isEmpty()){
        return;
    }

    for(int i = 0; i < d->m_circleList.count(); i++){
        double r = d->m_circleList.at(i).radius;
        QPointF _point = coordinate_trans(d->m_circleList.at(i).cx - r, - d->m_circleList.at(i).cy - r);
        painter.drawEllipse(_point.x(), _point.y(), 2 * r * m_Info.fScaleX, 2 * r * m_Info.fScaleY);
//        painter.drawEllipse(zoom*d->m_circleList.at(i).cx - zoom*d->m_circleList.at(i).radius + centerX,
//                            -zoom*d->m_circleList.at(i).cy - zoom*d->m_circleList.at(i).radius + centerY,
//                            2*zoom*d->m_circleList.at(i).radius, 2*zoom*d->m_circleList.at(i).radius);
    }
}

double DrawDxf::calc_rotateAngle(double mx, double my)
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

void DrawDxf::paint_ellipse(QPainter &painter, double zoom, double centerX, double centerY)
{
    if(d->m_ellipseList.isEmpty()){
        return;
    }

//    painter.translate(centerX, centerY);
    for(int i = 0; i < d->m_ellipseList.count(); i++){
        double k  = d->m_ellipseList.at(i).ratio;
        double r1 = get_magnitude2D(d->m_ellipseList.at(i).mx, d->m_ellipseList.at(i).my);
        double rotateAngle = calc_rotateAngle(d->m_ellipseList.at(i).mx, d->m_ellipseList.at(i).my);
        double startAngle = d->m_ellipseList.at(i).angle1 * 180 / M_PI;
        double endAngle = d->m_ellipseList.at(i).angle2 * 180 / M_PI;
        double spanAngle = get_span_angle(startAngle, endAngle, false);

        QPointF _point1 = coordinate_trans(d->m_ellipseList.at(i).cx, - d->m_ellipseList.at(i).cy);
        QPointF _point2 = coordinate_trans(d->m_ellipseList.at(i).cx - r1, - d->m_ellipseList.at(i).cy - k * r1);
        QRectF rect = QRectF(_point2.x(), _point2.y(), 2 * r1 * m_Info.fScaleX, 2 * k * r1 * m_Info.fScaleY);

        if(rotateAngle > 1e-9) {
            painter.translate(_point1.x(), _point1.y());//以椭圆的中心点为中心旋转
            painter.rotate(- rotateAngle * 180 / M_PI);
            painter.translate(- _point1.x(), - _point1.y());
//            painter.translate(zoom * d->m_ellipseList.at(i).cx,
//                              - zoom * d->m_ellipseList.at(i).cy);//以椭圆的中心点为中心旋转
//            painter.rotate(- rotateAngle * 180 / M_PI);
//            painter.translate(- zoom * d->m_ellipseList.at(i).cx,
//                              zoom * d->m_ellipseList.at(i).cy);
        }

        qDebug() << "spanAngle" << spanAngle;               
        painter.drawArc(rect, 16 * startAngle, 16 * spanAngle);
//        painter.drawArc(zoom * d->m_ellipseList.at(i).cx - zoom * r1,
//                        - zoom * d->m_ellipseList.at(i).cy - zoom * k * r1,
//                        zoom * 2 * r1, zoom * 2 * k * r1,
//                        startAngle * 16, spanAngle * 16);

        if(rotateAngle > 1e-9) {
            painter.translate(_point1.x(), _point1.y());
            painter.rotate(rotateAngle * 180 / M_PI);
            painter.translate(- _point1.x(), - _point1.y());
//            painter.translate(zoom * d->m_ellipseList.at(i).cx,
//                              - zoom * d->m_ellipseList.at(i).cy);
//            painter.rotate(rotateAngle * 180 / M_PI);
//            painter.translate(- zoom * d->m_ellipseList.at(i).cx,
//                              zoom * d->m_ellipseList.at(i).cy);
        }

        qDebug()<<"\ncx = "<<d->m_ellipseList.at(i).cx<<"cy = "<<d->m_ellipseList.at(i).cy<<"mx = "<<d->m_ellipseList.at(i).mx<<"my = "<<d->m_ellipseList.at(i).my;
        qDebug()<<"rotateAngle = "<<rotateAngle*180/M_PI<<"StartAngle = "<<startAngle<<"endAngle ="<<endAngle<<"r1="<<r1;
    }
//    painter.translate(-centerX, -centerY);
}

int DrawDxf::setPart(PART_CONFIG *pInfo_)
{
    d->clear();

    m_pPart = pInfo_;
    m_fThickness = m_pPart->afSize[0];

    int ret = getDxfData();
    return ret;
}

void DrawDxf::DrawDxfPart(QPainterPath &path, double originX, double kx, double ky)
{
    draw_line(path, originX, kx, ky);
    draw_arc(path, originX, kx, ky);
    draw_circle(path, originX, kx, ky);
    draw_ellipse(path, originX, kx, ky);
}

void DrawDxf::draw_line(QPainterPath &path, double originX, double kx, double ky)
{
    if(d->m_lineList.size() > 0){
        for(int i = 0; i < d->m_lineList.count(); i++){
            path.moveTo(kx*d->m_lineList.at(i).x1 + originX, ky*d->m_lineList.at(i).y1);
            path.lineTo(kx*d->m_lineList.at(i).x2 + originX, ky*d->m_lineList.at(i).y2);
        }
    }

    if(d->m_vertexList.isEmpty()){
        return;
    }

    for(int i = 1; i < d->m_vertexList.count(); i++){
        path.moveTo(kx*d->m_vertexList.at(i-1).x + originX, ky*d->m_vertexList.at(i-1).y);
        path.lineTo(kx*d->m_vertexList.at(i).x + originX, ky*d->m_vertexList.at(i).y);
    }
}

void DrawDxf::draw_arc(QPainterPath &path, double originX, double kx, double ky)
{
    if(d->m_arcList.isEmpty()){
        return;
    }

    for(int i = 0; i < d->m_arcList.count(); i++){
        double r = d->m_arcList.at(i).radius;
        double startAngle = d->m_arcList.at(i).angle1;
        double endAngle = d->m_arcList.at(i).angle2;
        double spanAngle = get_span_angle(startAngle, endAngle, false);

        path.arcMoveTo(kx * d->m_arcList.at(i).cx - r + originX,
                       ky * d->m_arcList.at(i).cy - r,
                       2 * r, 2 * r, startAngle);
        path.arcTo(kx * d->m_arcList.at(i).cx -r + originX,
                   ky * d->m_arcList.at(i).cy - r,
                   2 * r, 2 * r, 16 * startAngle, 16 * spanAngle);
    }
}

void DrawDxf::draw_circle(QPainterPath &path, double originX, double kx, double ky)
{
    if(d->m_circleList.isEmpty()){
        return;
    }

    for(int i = 0; i < d->m_circleList.count(); i++){
        path.addEllipse(kx * d->m_circleList.at(i).cx - d->m_circleList.at(i).radius + originX,
                        ky * d->m_circleList.at(i).cy - d->m_circleList.at(i).radius,
                        2*d->m_circleList.at(i).radius, 2*d->m_circleList.at(i).radius);
    }
}

void DrawDxf::draw_ellipse(QPainterPath &path, double originX, double kx, double ky)
{
    if(d->m_ellipseList.isEmpty()){
        return;
    }

    for(int i = 0; i < d->m_ellipseList.count(); i++){
        double k  = d->m_ellipseList.at(i).ratio;
        double r1 = get_magnitude2D(d->m_ellipseList.at(i).mx, d->m_ellipseList.at(i).my);
        double rotateAngle = calc_rotateAngle(d->m_ellipseList.at(i).mx, d->m_ellipseList.at(i).my);
        double startAngle = d->m_ellipseList.at(i).angle1 * 180 / M_PI;
        double endAngle = d->m_ellipseList.at(i).angle2 * 180 / M_PI;
        double spanAngle = get_span_angle(startAngle, endAngle, false);

        if(rotateAngle <= 1e-9) {
            qDebug() << "spanAngle" << spanAngle;
            path.arcMoveTo(kx *(d->m_ellipseList.at(i).cx - r1) + originX,
                           - ky * (d->m_ellipseList.at(i).cy - k * r1),
                           2 * kx * r1, 2 * ky * k * r1, 16 * startAngle);
            path.arcTo(kx *(d->m_ellipseList.at(i).cx - r1) + originX,
                       - ky * (d->m_ellipseList.at(i).cy - k * r1),
                       2 * kx * r1, 2 * ky * k * r1,
                       16 * startAngle, 16 * spanAngle);
        } else {
            QPolygonF pa;
            createEllipse(pa, RVector(kx * d->m_ellipseList.at(i).cx, - ky * d->m_ellipseList.at(i).cy), r1, k * r1,
                          rotateAngle, d->m_ellipseList.at(i).angle1, d->m_ellipseList.at(i).angle2, false);
            path.addPolygon(pa);
        }
    }
}

//void DrawDxf::draw_ellipse(QPainterPath &path, double originX, double kx, double ky)
//{
//    if(m_ellipseList.isEmpty()){
//        return;
//    }

//    for(int i = 0; i < m_ellipseList.count(); i++){
//        double k  = m_ellipseList.at(i).ratio;
//        double r1 = sqrt(pow((m_ellipseList.at(i).mx - m_ellipseList.at(i).cx), 2.0) +
//                         pow((m_ellipseList.at(i).my - m_ellipseList.at(i).cy), 2.0));
//   //     double rotateAngle = calc_rotateAngle(m_ellipseList.at(i).cx, m_ellipseList.at(i).cy,
//  //                                            m_ellipseList.at(i).mx, m_ellipseList.at(i).my);
//        double startAngle  = 16*m_ellipseList.at(i).angle1*180/M_PI;
//        double endAngle    = 16*m_ellipseList.at(i).angle2*180/M_PI;

//      //  path.translate(originX, 0);
//      //  path.angleAtPercent(rotateAngle/2*M_PI);
//      //  painter.rotate(360 - rotateAngle*180/M_PI);

//        double Angle = 16*360 - fabs(endAngle - startAngle);
//        path.arcMoveTo(kx*m_ellipseList.at(i).cx - r1 + originX, ky*m_ellipseList.at(i).cy - k*r1,
//                   2*r1, 2*k*r1, startAngle);
//        if(Angle < 1e-10){
//           path.arcTo(kx*m_ellipseList.at(i).cx - r1 + originX, ky*m_ellipseList.at(i).cy - k*r1,
//                      2*r1, 2*k*r1, startAngle, 16*360);
//        }else{
//           path.arcTo(kx*m_ellipseList.at(i).cx - r1 + originX, ky*m_ellipseList.at(i).cy - k*r1,
//                       2*r1, 2*k*r1, startAngle, Angle);
//        }
//    }
//}

void DrawDxf::createEllipse(QPolygonF& pa, const RVector& cp, double radius1, double radius2,
                            double angle, double angle1, double angle2,  bool reversed)
{
    const RVector vr(radius1, radius2);
    const RVector rvp(radius2, radius1);
    const double ab = radius1 * radius2;
    double ea1 = angle1;
    double ea2;
    double dA = get_span_angle(angle1, angle2, true);

    if(dA <= RS_TOLERANCE_ANGLE) {
        dA = 2 * M_PI;
        ea2 = ea1 + dA;
    }else
        ea2 = ea1 +(reversed ? - dA : dA);

    const RVector angleVector(- angle);
    /*
      draw a new line after tangent changes by 0.01 rad
      ds^2 = (a^2 sin^2 + b^2 cos^2) da^2
      */
    RVector vp(- ea1);
    vp.scale(vr);
    vp.rotate(angleVector);
    vp.move(cp);
    pa.clear();
    const double minDea = fabs(ea2 - ea1) / 2048;
    // Arc Counterclockwise:
    do {
        RVector va(- ea1);
        vp = va;
        double r2 = va.scale(rvp).squared();
        if( r2 < 1.5e-15) r2 = RS_TOLERANCE15;
        double aStep = ab /(r2 * sqrt(r2));
        if(aStep < minDea) aStep = minDea;
        if(aStep > M_PI / 18) aStep = M_PI / 18;
        ea1 += reversed ? - aStep : aStep;

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

    vp.set(cos(ea2)*radius1, -sin(ea2)*radius2);
    vp.rotate(angleVector);
    vp.move(cp);
    pa << QPointF((qreal)vp.x, (qreal)vp.y);//增加椭圆在angle2的坐标
}

double DrawDxf::get_magnitude2D(double x, double y)
{
    return sqrt(x * x + y * y);
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

QPointF DrawDxf::coordinate_trans(float x_, float y_)
{
    float _fScaleX = m_Info.fScaleX;
    float _fScaleY = m_Info.fScaleY;
    float     _fX0 = m_Info.fX;
    float     _fY0 = m_Info.fY;

    qDebug() << _fScaleX << _fScaleY << _fX0 << _fY0;
    float _fX = x_ * _fScaleX + _fX0;
    float _fY = y_ * _fScaleY + _fY0;

    QPointF _point;
    _point.setX(_fX);
    _point.setY(_fY);

    return _point;
}

}
