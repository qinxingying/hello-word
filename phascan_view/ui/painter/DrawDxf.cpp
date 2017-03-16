#include "DrawDxf.h"
#include "dl_dxf.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

DrawDxf * g_pDrawDxf = NULL;

DrawDxf *DrawDxf::Instance()
{
    if(!g_pDrawDxf){
        g_pDrawDxf = new DrawDxf();
    }
    return g_pDrawDxf;
}

DrawDxf::DrawDxf(QWidget *parent) :
	QWidget(parent)
{
    m_pPart = NULL;
    m_fThickness = 20;
}

int DrawDxf::getDxfData()
{
    if(m_pPart == NULL)
        return -1;

    Dxf_Data* dxfData = new Dxf_Data();
    DL_Dxf* dxf = new DL_Dxf();

    QString dxfFile = m_pPart->strPartFile;
    if (!dxf->in(dxfFile.toLatin1().data(), dxfData)) {
        qDebug()<<"could not be opened";
        return -1;
    }

    m_pointList = dxfData->getPointList();
    m_lineList = dxfData->getLineList();
    m_textList = dxfData->getTextList();
    m_arcList = dxfData->getArcList();
    m_circleList = dxfData->getCircleList();
    m_textDataList = dxfData->getTextDataList();
    m_vertexList = dxfData->getVertexList();
    m_controlPointList = dxfData->getControlPointList();
    m_polyLineList = dxfData->getPolyLineList();
    m_ellipseList = dxfData->getEllipseList();

    delete dxf;
    delete dxfData;
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
    if(m_vertexList.size() > 0){
        for(int i = 0; i < m_vertexList.count(); i++){
            painter.drawPoint(zoom*m_vertexList.at(i).x + centerX, -zoom*m_vertexList.at(i).y + centerY);
        }
    }

    if(m_controlPointList.size() > 0){
        for(int i = 0; i < m_controlPointList.count(); i++){
            painter.drawPoint(zoom*m_controlPointList.at(i).x + centerX, -zoom*m_controlPointList.at(i).y + centerY);
        }
    }

    if(m_pointList.size() > 0){
        for(int i = 0; i < m_pointList.count(); i++){
            painter.drawPoint(zoom*m_pointList.at(i).x + centerX, -zoom*m_pointList.at(i).y + centerY);
        }
    }
}

void DrawDxf::paint_line(QPainter &painter, double zoom, double centerX, double centerY)
{
    if (m_lineList.size() > 0){
        for(int i = 0; i < m_lineList.count(); i++){
            painter.drawLine(zoom*m_lineList.at(i).x1 + centerX, -zoom*m_lineList.at(i).y1 + centerY,
                             zoom*m_lineList.at(i).x2 + centerX, -zoom*m_lineList.at(i).y2 + centerY);
        }
    }

//    if(m_polyLineList.size() > 0){
//        for(int i = 0; i < m_polyLineList.count(); i++){
//            if(m_polyLineList.at(i).flags){
//                paint_polyLine_1(painter, zoom);
//            }else{
//                paint_polyLine_0(painter, zoom);
//            }
//        }
//    }
    paint_polyLine_0(painter, zoom, centerX, centerY);
}

void DrawDxf::paint_polyLine_0(QPainter &painter, double zoom, double centerX, double centerY)
{
    if(m_vertexList.isEmpty()){
        return;
    }

    for(int i = 1; i < m_vertexList.count(); i++){
        painter.drawLine(zoom*m_vertexList.at(i-1).x + centerX, -zoom*m_vertexList.at(i-1).y + centerY,
                         zoom*m_vertexList.at(i).x + centerX, -zoom*m_vertexList.at(i).y + centerY);
    }
}

void DrawDxf::paint_polyLine_1(QPainter &painter, double zoom, double centerX, double centerY)
{
    if(m_vertexList.isEmpty()){
        return;
    }

    for(int i = 1; i < m_vertexList.count(); i++){
        painter.drawLine(zoom*m_vertexList.at(i-1).x + centerX, -zoom*m_vertexList.at(i-1).y + centerY,
                         zoom*m_vertexList.at(i).x + centerX, -zoom*m_vertexList.at(i).y + centerY);
        painter.drawLine(zoom*m_vertexList.at(0).x + centerX, -zoom*m_vertexList.at(0).y + centerY,
                         zoom*m_vertexList.at(m_vertexList.count()-1).x + centerX,
                         -zoom*m_vertexList.at(m_vertexList.count()-1).y + centerY);
    }
}

void DrawDxf::paint_text(QPainter &painter, double zoom, double centerX, double centerY)
{
    if(m_textList.size() > 0){
        for(int i = 0; i < m_textList.count(); i++){
            painter.drawText(zoom*(m_textList.at(i).ipx-2*m_textList.at(i).height) + centerX,
                             -zoom*m_textList.at(i).ipy + centerY,
                             zoom*4*m_textList.at(i).height, zoom*m_textList.at(i).height,
                             Qt::AlignLeft, m_textList.at(i).text.c_str());
        }
    }

    if(m_textDataList.size() > 0){
        for(int i = 0; i < m_textDataList.count(); i++){
            painter.drawText(zoom*m_textDataList.at(i).ipx + centerX,
                            -zoom*m_textDataList.at(i).ipy - m_textDataList.at(i).height + centerY,
                             zoom*9*m_textDataList.at(i).height, zoom*m_textDataList.at(i).height,
                             Qt::AlignLeft, m_textDataList.at(i).text.c_str());
        }
    }
}

void DrawDxf::paint_arc(QPainter &painter, double zoom, double centerX, double centerY)
{
    if(m_arcList.isEmpty()){
        return;
    }

    for(int i = 0; i < m_arcList.count(); i++){
        double r = m_arcList.at(i).radius;
        double startAngle = m_arcList.at(i).angle1;
        double endAngle = m_arcList.at(i).angle2;
        double spanAngle = 0.0;

        if(startAngle < endAngle) {
            spanAngle = endAngle - startAngle;
        } else {
            spanAngle = 360 - startAngle + endAngle;
        }

        painter.drawArc(zoom*m_arcList.at(i).cx -zoom*r + centerX, -zoom*m_arcList.at(i).cy - zoom*r + centerY,
                        zoom*2*r, zoom*2*r, startAngle * 16, spanAngle *16);
    }
}

void DrawDxf::paint_circle(QPainter &painter, double zoom, double centerX, double centerY)
{
    if(m_circleList.isEmpty()){
        return;
    }

    for(int i = 0; i < m_circleList.count(); i++){
        painter.drawEllipse(zoom*m_circleList.at(i).cx - zoom*m_circleList.at(i).radius + centerX,
                            -zoom*m_circleList.at(i).cy - zoom*m_circleList.at(i).radius + centerY,
                            2*zoom*m_circleList.at(i).radius, 2*zoom*m_circleList.at(i).radius);
    }

}

double DrawDxf::calc_rotateAngle(double mx, double my)
{
    double rotateAngle = 0;
    double m = getMagnitude2D(mx, my);

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
    if(m_ellipseList.isEmpty()){
        return;
    }
    painter.translate(centerX, centerY);
    for(int i = 0; i < m_ellipseList.count(); i++){
        double k  = m_ellipseList.at(i).ratio;
        double r1 = getMagnitude2D(m_ellipseList.at(i).mx, m_ellipseList.at(i).my);
        double rotateAngle = calc_rotateAngle(m_ellipseList.at(i).mx, m_ellipseList.at(i).my);
        double startAngle = m_ellipseList.at(i).angle1 * 180 / M_PI;
        double endAngle = m_ellipseList.at(i).angle2 * 180 / M_PI;
        double spanAngle = 0.0;

        if(rotateAngle > 1e-9) {
            painter.rotate(- rotateAngle * 180 / M_PI);
        }

        if(fabs(endAngle - startAngle) < 1e-9 || 360 - fabs(endAngle - startAngle) < 1e-9) {
            painter.drawEllipse(zoom * m_ellipseList.at(i).cx - zoom * r1, - zoom * m_ellipseList.at(i).cy - zoom * k * r1,
                                zoom * 2 * r1, zoom * 2 * k * r1);
        } else {
            if(startAngle < endAngle) {
                spanAngle = endAngle - startAngle;
            } else {
                spanAngle = 360 - startAngle + endAngle;
            }
            qDebug() << "spanAngle" << spanAngle;
            painter.drawArc(zoom * m_ellipseList.at(i).cx - zoom * r1, - zoom * m_ellipseList.at(i).cy - zoom * k * r1,
                            zoom * 2 * r1, zoom * 2 * k * r1, startAngle * 16, spanAngle * 16);
        }

        if(rotateAngle > 1e-9) {
            painter.rotate(rotateAngle * 180 / M_PI);
        }

        qDebug()<<"\ncx = "<<m_ellipseList.at(i).cx<<"cy = "<<m_ellipseList.at(i).cy<<"mx = "<<m_ellipseList.at(i).mx<<"my = "<<m_ellipseList.at(i).my;
        qDebug()<<"rotateAngle = "<<rotateAngle*180/M_PI<<"StartAngle = "<<startAngle<<"endAngle ="<<endAngle<<"r1="<<r1;
    }
}

int DrawDxf::setPart(PART_CONFIG *pInfo_)
{
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
    if(m_lineList.size() > 0){
        for(int i = 0; i < m_lineList.count(); i++){
            path.moveTo(kx*m_lineList.at(i).x1 + originX, ky*m_lineList.at(i).y1);
            path.lineTo(kx*m_lineList.at(i).x2 + originX, ky*m_lineList.at(i).y2);
        }
    }

    if(m_vertexList.isEmpty()){
        return;
    }

    for(int i = 1; i < m_vertexList.count(); i++){
        path.moveTo(kx*m_vertexList.at(i-1).x + originX, ky*m_vertexList.at(i-1).y);
        path.lineTo(kx*m_vertexList.at(i).x + originX, ky*m_vertexList.at(i).y);
    }
}

void DrawDxf::draw_arc(QPainterPath &path, double originX, double kx, double ky)
{
    if(m_arcList.isEmpty()){
        return;
    }

    for(int i = 0; i < m_arcList.count(); i++){
        double r = m_arcList.at(i).radius;
        double startAngle = m_arcList.at(i).angle1*16;
        double endAngle = m_arcList.at(i).angle2*16;

        path.arcMoveTo(kx*m_arcList.at(i).cx -r + originX, ky*m_arcList.at(i).cy - r,
                   2*r, 2*r, startAngle);
        path.arcTo(kx*m_arcList.at(i).cx -r + originX, ky*m_arcList.at(i).cy - r,
                   2*r, 2*r, startAngle, fabs(endAngle - startAngle));
    }
}

void DrawDxf::draw_circle(QPainterPath &path, double originX, double kx, double ky)
{
    if(m_circleList.isEmpty()){
        return;
    }

    for(int i = 0; i < m_circleList.count(); i++){
        path.addEllipse(kx*m_circleList.at(i).cx - m_circleList.at(i).radius + originX,
                        ky*m_circleList.at(i).cy - m_circleList.at(i).radius,
                        2*m_circleList.at(i).radius, 2*m_circleList.at(i).radius);
    }
}

void DrawDxf::draw_ellipse(QPainterPath &path, double originX, double kx, double ky)
{
    if(m_ellipseList.isEmpty()){
        return;
    }

    for(int i = 0; i < m_ellipseList.count(); i++){
        double k  = m_ellipseList.at(i).ratio;
        double r1 = sqrt(pow((m_ellipseList.at(i).mx - m_ellipseList.at(i).cx), 2.0) +
                         pow((m_ellipseList.at(i).my - m_ellipseList.at(i).cy), 2.0));
   //     double rotateAngle = calc_rotateAngle(m_ellipseList.at(i).cx, m_ellipseList.at(i).cy,
  //                                            m_ellipseList.at(i).mx, m_ellipseList.at(i).my);
        double startAngle  = 16*m_ellipseList.at(i).angle1*180/M_PI;
        double endAngle    = 16*m_ellipseList.at(i).angle2*180/M_PI;

      //  path.translate(originX, 0);
      //  path.angleAtPercent(rotateAngle/2*M_PI);
      //  painter.rotate(360 - rotateAngle*180/M_PI);

        double Angle = 16*360 - fabs(endAngle - startAngle);
        path.arcMoveTo(kx*m_ellipseList.at(i).cx - r1 + originX, ky*m_ellipseList.at(i).cy - k*r1,
                   2*r1, 2*k*r1, startAngle);
        if(Angle < 1e-10){
           path.arcTo(kx*m_ellipseList.at(i).cx - r1 + originX, ky*m_ellipseList.at(i).cy - k*r1,
                      2*r1, 2*k*r1, startAngle, 16*360);
        }else{
           path.arcTo(kx*m_ellipseList.at(i).cx - r1 + originX, ky*m_ellipseList.at(i).cy - k*r1,
                       2*r1, 2*k*r1, startAngle, Angle);
        }
    }
}

double DrawDxf::getMagnitude2D(double x, double y)
{
    return sqrt(x * x + y * y);
}
