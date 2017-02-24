#include "DrawDxf.h"
#include "dl_dxf.h"
#include "dl_creationadapter.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

#define QPAINTER 1
#define QPAINTERPATH 1

DrawDxf::DrawDxf(QWidget *parent) :
	QWidget(parent)
{
    m_zoom = 1.0;
}

void DrawDxf::getDxfData(QString dxf_file)
{
    Dxf_Data* dxfData = new Dxf_Data();
    DL_Dxf* dxf = new DL_Dxf();

    if (!dxf->in(dxf_file.toLatin1().data(), dxfData)) {
        qDebug()<<"could not be opened";
        return;
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

    QPainterPath newPath;
    m_path = newPath;
}

void DrawDxf::paint_line()
{
    if(m_lineList.isEmpty()) return;
    for(int i = 0; i < m_lineList.count(); i++){
        m_path.moveTo(m_lineList.at(i).x1, -m_lineList.at(i).y1);
        m_path.lineTo(m_lineList.at(i).x2, -m_lineList.at(i).y2);
    }
}

void DrawDxf::paint_vertexToLine()
{
    if(m_vertexList.isEmpty()) return;

    for(int i = 1; i < m_vertexList.count(); i++){
        m_path.moveTo(m_vertexList.at(i-1).x, -m_vertexList.at(i-1).y);
        m_path.lineTo(m_vertexList.at(i).x, -m_vertexList.at(i).y);
    }
}

void DrawDxf::paint_circle()
{
    if(m_circleList.isEmpty()) return;

    for(int i = 0; i < m_circleList.count(); i++){
        m_path.addEllipse(m_circleList.at(i).cx - m_circleList.at(i).radius,
                         -m_circleList.at(i).cy - m_circleList.at(i).radius,
                          2*m_circleList.at(i).radius, 2*m_circleList.at(i).radius);
    }
}

void DrawDxf::paint_arc()
{
    if(m_arcList.isEmpty()) return;

    float r = 0;
    float startAngle = 0;
    float endAngle = 0;

    for(int i = 0; i < m_arcList.count(); i++){
        r = m_arcList.at(i).radius;
        startAngle = m_arcList.at(i).angle1;
        endAngle = m_arcList.at(i).angle2;

        m_path.arcTo(m_arcList.at(i).cx -r, -m_zoom*m_arcList.at(i).cy - r,
                     2*r, 2*r, startAngle, fabs(endAngle - startAngle));
    }
}

void DrawDxf::paint_ellipse()
{

}

void DrawDxf::paint_text()
{
    if(m_textList.isEmpty()) return;

    QFont font;
    for(int i = 0; i < m_textList.count(); i++){
        m_path.addText(m_textList.at(i).ipx, -m_textList.at(i).ipy,
                       font, m_textList.at(i).text.c_str());
        qDebug()<<"text ="<<m_textList.at(i).text.c_str();
    }
}

void DrawDxf::paint_textData()
{
    if(m_textDataList.isEmpty())  return;

    QFont font;
    for(int i = 0; i < m_textDataList.count(); i++){
        m_path.addText(m_textDataList.at(i).ipx, -m_textDataList.at(i).ipy,
                       font, m_textDataList.at(i).text.c_str());
        qDebug()<<"textData ="<<m_textDataList.at(i).text.c_str();
    }
}

void DrawDxf::paintEvent (QPaintEvent*)
{
    QPainter painter(this);
    QPen pen = painter.pen();
    QPen NewPen(pen);

    NewPen.setWidth(1/m_zoom);
    NewPen.setColor(QColor(0, 255, 0));
    painter.setPen(NewPen);
    painter.setRenderHint(QPainter::Antialiasing, true);
#if QPAINTER
    paint_line(painter);
    paint_text(painter);
    paint_arc(painter);
    paint_circle(painter);
    paint_point(painter);
    paint_ellipse(painter);
#endif
#if QPAINTERPATH
    m_path.translate(endPoint.x()-lastPoint.x(), endPoint.y()-lastPoint.y());
    painter.scale(m_zoom, m_zoom);
    painter.drawPath(m_path);
    lastPoint = endPoint;
#endif
    painter.setPen(pen);

    QPainter painter1(this);
    QPen pen1 = painter.pen();
    QPen NewPen1(pen1);

    QVector<qreal> dashes;
    dashes << 3 << 5;
    NewPen1.setWidth(1);
    NewPen1.setDashPattern(dashes);
    NewPen1.setColor(QColor(0, 0, 255));
    painter1.setPen(NewPen1);
    painter1.drawLine(0, height()/2, width(), height()/2);
    painter1.drawLine(width()/2, 0, width()/2, height());

    painter1.setPen(pen1);
}

void DrawDxf::paint_point(QPainter &painter)
{
    if(m_vertexList.size() > 0){
        for(int i = 0; i < m_vertexList.count(); i++){
            painter.drawPoint(m_zoom*m_vertexList.at(i).x + width()/2, -m_zoom*m_vertexList.at(i).y + height()/2);
        }
    }

    if(m_controlPointList.size() > 0){
        for(int i = 0; i < m_controlPointList.count(); i++){
            painter.drawPoint(m_zoom*m_controlPointList.at(i).x + width()/2, -m_zoom*m_controlPointList.at(i).y + height()/2);
        }
    }

    if(m_pointList.size() > 0){
        for(int i = 0; i < m_pointList.count(); i++){
            painter.drawPoint(m_zoom*m_pointList.at(i).x + width()/2, -m_zoom*m_pointList.at(i).y + height()/2);
        }
    }
}

void DrawDxf::paint_line(QPainter &painter)
{
    if (m_lineList.size() > 0){
        for(int i = 0; i < m_lineList.count(); i++){
            painter.drawLine(m_zoom*m_lineList.at(i).x1 + width()/2, -m_zoom*m_lineList.at(i).y1 + height()/2,
                             m_zoom*m_lineList.at(i).x2 + width()/2, -m_zoom*m_lineList.at(i).y2 + height()/2);
        }
    }

//    if(m_polyLineList.size() > 0){
//        for(int i = 0; i < m_polyLineList.count(); i++){
//            if(m_polyLineList.at(i).flags){
//                paint_polyLine_1(painter);
//            }else{
//                paint_polyLine_0(painter);
//            }
//        }
//    }
    paint_polyLine_0(painter);
}

void DrawDxf::paint_polyLine_0(QPainter &painter)
{
    if(m_vertexList.isEmpty()){
        return;
    }

    for(int i = 1; i < m_vertexList.count(); i++){
        painter.drawLine(m_zoom*m_vertexList.at(i-1).x + width()/2, -m_zoom*m_vertexList.at(i-1).y + height()/2,
                         m_zoom*m_vertexList.at(i).x + width()/2, -m_zoom*m_vertexList.at(i).y + height()/2);
    }
}

void DrawDxf::paint_polyLine_1(QPainter &painter)
{
    if(m_vertexList.isEmpty()){
        return;
    }

    for(int i = 1; i < m_vertexList.count(); i++){
        painter.drawLine(m_zoom*m_vertexList.at(i-1).x + width()/2, -m_zoom*m_vertexList.at(i-1).y + height()/2,
                         m_zoom*m_vertexList.at(i).x + width()/2, -m_zoom*m_vertexList.at(i).y + height()/2);
        painter.drawLine(m_zoom*m_vertexList.at(0).x + width()/2, -m_zoom*m_vertexList.at(0).y + height()/2,
                         m_zoom*m_vertexList.at(m_vertexList.count()-1).x + width()/2,
                         -m_zoom*m_vertexList.at(m_vertexList.count()-1).y + height()/2);
    }
}

void DrawDxf::paint_text(QPainter &painter)
{
    if(m_textList.size() > 0){
        for(int i = 0; i < m_textList.count(); i++){
            painter.drawText(m_zoom*(m_textList.at(i).ipx-2*m_textList.at(i).height) + width()/2,
                             -m_zoom*m_textList.at(i).ipy + height()/2,
                             m_zoom*4*m_textList.at(i).height, m_zoom*m_textList.at(i).height,
                             Qt::AlignLeft, m_textList.at(i).text.c_str());
        }
    }

    if(m_textDataList.size() > 0){
        for(int i = 0; i < m_textDataList.count(); i++){
            painter.drawText(m_zoom*m_textDataList.at(i).ipx + width()/2,
                            -m_zoom*m_textDataList.at(i).ipy - m_textDataList.at(i).height + height()/2,
                             m_zoom*9*m_textDataList.at(i).height, m_zoom*m_textDataList.at(i).height,
                             Qt::AlignLeft, m_textDataList.at(i).text.c_str());
        }
    }
}

void DrawDxf::paint_arc(QPainter &painter)
{
    if(m_arcList.isEmpty()){
        return;
    }

    double r = 0;
    double startAngle = 0;
    double endAngle = 0;

    for(int i = 0; i < m_arcList.count(); i++){
        r = m_arcList.at(i).radius;
        startAngle = m_arcList.at(i).angle1*16;
        endAngle = m_arcList.at(i).angle2*16;

        painter.drawArc(m_zoom*m_arcList.at(i).cx -m_zoom*r + width()/2, -m_zoom*m_arcList.at(i).cy - m_zoom*r + height()/2,
                        m_zoom*2*r, m_zoom*2*r, startAngle, fabs(endAngle - startAngle));
    }
}

void DrawDxf::paint_circle(QPainter &painter)
{
    if(m_circleList.isEmpty()){
        return;
    }

    for(int i = 0; i < m_circleList.count(); i++){
        painter.drawEllipse(m_zoom*m_circleList.at(i).cx - m_zoom*m_circleList.at(i).radius + width()/2,
                            -m_zoom*m_circleList.at(i).cy - m_zoom*m_circleList.at(i).radius + height()/2,
                            2*m_zoom*m_circleList.at(i).radius, 2*m_zoom*m_circleList.at(i).radius);
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

void DrawDxf::paint_ellipse(QPainter &painter)
{
    if(m_ellipseList.isEmpty()){
        return;
    }

    double k  = 0;
    double r1 = 0;
    double rotateAngle = 0;
    double startAngle  = 0;
    double endAngle    = 0;
    double Angle = 0;

    for(int i = 0; i < m_ellipseList.count(); i++){
        k  = m_ellipseList.at(i).ratio;
        r1 = sqrt(pow((m_ellipseList.at(i).mx - m_ellipseList.at(i).cx), 2.0) +
                         pow((m_ellipseList.at(i).my - m_ellipseList.at(i).cy), 2.0));
        rotateAngle = calc_rotateAngle(m_ellipseList.at(i).cx, m_ellipseList.at(i).cy,
                                              m_ellipseList.at(i).mx, m_ellipseList.at(i).my);
        startAngle  = 16*m_ellipseList.at(i).angle1*180/M_PI;
        endAngle    = 16*m_ellipseList.at(i).angle2*180/M_PI;

        painter.translate(width()/2, height()/2);
        painter.rotate(360 - rotateAngle*180/M_PI);

        painter.scale(1, k);

        Angle = 16*360 - fabs(endAngle - startAngle);
        if(Angle < 1e-10){
            painter.drawArc(m_zoom*m_ellipseList.at(i).cx  - m_zoom*r1,
                            -m_zoom*m_ellipseList.at(i).cy  - m_zoom*r1,
                            m_zoom*2*r1, m_zoom*2*r1, startAngle, 16*360);
        }else{
            painter.drawArc(m_zoom*m_ellipseList.at(i).cx  - m_zoom*r1,
                            -m_zoom*m_ellipseList.at(i).cy  - m_zoom*r1,
                            m_zoom*2*r1, m_zoom*2*r1, startAngle, Angle);
        }

qDebug()<<"\n rotateAngle = "<<rotateAngle*180/M_PI<<"StartAngle = "<<startAngle/16<<"endAngle ="<<endAngle/16<<"r1="<<r1;
qDebug()<<"\n Angle = "<<fabs(endAngle - startAngle)/16<<Angle/16;
    }
}

void DrawDxf::wheelEvent(QWheelEvent *event)
{
    if(event->delta() >0){
        m_zoom += 1;

    }else{
        if(m_zoom > 1){
            m_zoom -= 1;

        }else if(0 < m_zoom && m_zoom <= 1){
            m_zoom = 0.5*m_zoom;
        }
    }

    update();
    emit zoom(m_zoom);
}

void DrawDxf::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        lastPoint = event->pos();
    }
}

void DrawDxf::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        endPoint = event->pos();
        update();//拖动时有痕迹
    }
}

void DrawDxf::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        endPoint = event->pos();
        update();
    }
}
