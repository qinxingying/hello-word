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
        double startAngle = m_arcList.at(i).angle1*16;
        double endAngle = m_arcList.at(i).angle2*16;

        painter.drawArc(zoom*m_arcList.at(i).cx -zoom*r + centerX, -zoom*m_arcList.at(i).cy - zoom*r + centerY,
                        zoom*2*r, zoom*2*r, startAngle, fabs(endAngle - startAngle));
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

double DrawDxf::calc_rotateAngle(double cx, double cy, double mx, double my)
{
    double rotateAngle = 0;

    if ( fabs(mx-cx) < 1e-15 ) {
        if ( my-cy < -(1e-15) ) {
            rotateAngle = 3*M_PI/2;
        } else if ( my-cy > 1e-15 ) {
            rotateAngle = M_PI/2;
        }
    }

    rotateAngle = atan(fabs((my-cy)/(mx-cx)));

    if ( mx-cx > 1e-15 ) {
        if (my-cy > 1e-15) {
            /*第一象区*/
            rotateAngle = rotateAngle;
        } else if ( my-cy < -1e-15 ) {
            /*第四象区*/
            rotateAngle = 2*M_PI - rotateAngle;
        }
    } else if (mx-cx < -1e-15) {
        if (my-cy > 1e-15) {
            /*第二象区*/
            rotateAngle = M_PI - rotateAngle;
        } else if (my-cy < -1e-15) {
            /*第三象区*/
            rotateAngle = M_PI + rotateAngle;
        }
    }

    return rotateAngle;
}

void DrawDxf::paint_ellipse(QPainter &painter, double zoom, double centerX, double centerY)
{
    if(m_ellipseList.isEmpty()){
        return;
    }

    for(int i = 0; i < m_ellipseList.count(); i++){
        double k  = m_ellipseList.at(i).ratio;
        double r1 = sqrt(pow((m_ellipseList.at(i).mx - m_ellipseList.at(i).cx), 2.0) +
                         pow((m_ellipseList.at(i).my - m_ellipseList.at(i).cy), 2.0));
        double rotateAngle = calc_rotateAngle(m_ellipseList.at(i).cx, m_ellipseList.at(i).cy,
                                              m_ellipseList.at(i).mx, m_ellipseList.at(i).my);
        double startAngle  = 16*m_ellipseList.at(i).angle1*180/M_PI;
        double endAngle    = 16*m_ellipseList.at(i).angle2*180/M_PI;

        painter.translate(centerX, centerY);
        painter.rotate(360 - rotateAngle*180/M_PI);

        painter.scale(1, k);

        double Angle = 16*360 - fabs(endAngle - startAngle);
        if(Angle < 1e-10){
            painter.drawArc(zoom*m_ellipseList.at(i).cx  - zoom*r1,
                            -zoom*m_ellipseList.at(i).cy  - zoom*r1,
                            zoom*2*r1, zoom*2*r1, startAngle, 16*360);
        }else{
            painter.drawArc(zoom*m_ellipseList.at(i).cx  - zoom*r1,
                            -zoom*m_ellipseList.at(i).cy  - zoom*r1,
                            zoom*2*r1, zoom*2*r1, startAngle, Angle);
        }

qDebug()<<"\n rotateAngle = "<<rotateAngle*180/M_PI<<"StartAngle = "<<startAngle/16<<"endAngle ="<<endAngle/16<<"r1="<<r1;
qDebug()<<"\n Angle = "<<fabs(endAngle - startAngle)/16<<Angle/16;
    }
}

int DrawDxf::setPart(PART_CONFIG *pInfo_)
{
    m_pPart = pInfo_;
    m_fThickness = m_pPart->afSize[0];

    int ret = getDxfData();
    return ret;
}

void DrawDxf::DrawDxfPart(QPainterPath &path, double originX)
{
    draw_point(path);
    draw_line(path, originX);
    draw_polyLine(path);
    draw_arc(path);
    draw_circle(path);
    draw_ellipse(path);
}

void DrawDxf::draw_point(QPainterPath &path)
{

}

void DrawDxf::draw_line(QPainterPath &path, double originX)
{
    if(m_lineList.size() > 0){
        for(int i = 0; i < m_lineList.count(); i++){
            path.moveTo(m_lineList.at(i).x1 + originX, m_lineList.at(i).y1);
            path.lineTo(m_lineList.at(i).x2 + originX, m_lineList.at(i).y2);
            qDebug()<<"line.P(X, Y) = "<<m_lineList.at(i).x1<<m_lineList.at(i).y1;
        }
    }

}

void DrawDxf::draw_polyLine(QPainterPath &path)
{

}

void DrawDxf::draw_arc(QPainterPath &path)
{

}

void DrawDxf::draw_circle(QPainterPath &path)
{

}

void DrawDxf::draw_ellipse(QPainterPath &path)
{

}
