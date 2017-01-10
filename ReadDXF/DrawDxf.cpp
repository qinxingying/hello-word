#include "DrawDxf.h"
#include "dl_dxf.h"
#include "dl_creationadapter.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

DrawDxf::DrawDxf(QWidget *parent) :
	QWidget(parent)
{
    creationClass = new Test_CreationClass();

    m_zoom = 1.0;
}

QList<DL_LineData> DrawDxf::getLineList() const
{
    return m_lineList;
}

void DrawDxf::setLineList(const QList<DL_LineData> &lineList)
{
    m_lineList = lineList;
}

QList<DL_ArcData> DrawDxf::getArcList() const
{
    return m_arcList;
}

void DrawDxf::setArcList(const QList<DL_ArcData> &arcList)
{
    m_arcList = arcList;
}

QList<DL_MTextData> DrawDxf::getTextList() const
{
    return m_textList;
}

void DrawDxf::setTextList(const QList<DL_MTextData> &textList)
{
    m_textList = textList;
}

QList<DL_EllipseData> DrawDxf::getEllipseList() const
{
    return m_ellipseList;
}

void DrawDxf::setEllipseList(const QList<DL_EllipseData> &ellipseList)
{
    m_ellipseList = ellipseList;
}

QList<DL_CircleData> DrawDxf::getCircleList() const
{
    return m_circleList;
}

void DrawDxf::setCircleList(const QList<DL_CircleData> &circleList)
{
    m_circleList = circleList;
}

QList<DL_TextData> DrawDxf::getTextDataList() const
{
    return m_textDataList;
}

void DrawDxf::setTextDataList(const QList<DL_TextData> &textDataList)
{
    m_textDataList = textDataList;
}

QList<DL_VertexData> DrawDxf::getVertexList() const
{
    return m_vertexList;
}

void DrawDxf::setVertexList(const QList<DL_VertexData> &vertexList)
{
    m_vertexList = vertexList;
}

QList<DL_SplineData> DrawDxf::getSplineList() const
{
    return m_splineList;
}

void DrawDxf::setSplineList(const QList<DL_SplineData> &splineList)
{
    m_splineList = splineList;
}

QList<DL_ControlPointData> DrawDxf::getControlPointList() const
{
    return m_controlPointList;
}

void DrawDxf::setControlPointList(const QList<DL_ControlPointData> &controlPointList)
{
    m_controlPointList = controlPointList;
}

QList<DL_PointData> DrawDxf::getPointList() const
{
    return m_pointList;
}

void DrawDxf::setPointList(const QList<DL_PointData> &pointList)
{
    m_pointList = pointList;
}

QList<DL_PolylineData> DrawDxf::getPolyLineList() const
{
    return m_polyLineList;
}

void DrawDxf::setPolyLineList(const QList<DL_PolylineData> &polyLineList)
{
    m_polyLineList = polyLineList;
}

void DrawDxf::paintEvent (QPaintEvent*)
{
    QPainter painter(this);
    QPen pen = painter.pen();
    QPen NewPen(pen);

    NewPen.setWidth(1);
    NewPen.setColor(QColor(0, 255, 0));
    painter.setPen(NewPen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    paint_line(painter);

    paint_text(painter);

    paint_arc(painter);

    paint_circle(painter);

    paint_point(painter);

    paint_ellipse(painter);
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

    for(int i = 0; i < m_arcList.count(); i++){
        double r = m_arcList.at(i).radius;
        double startAngle = m_arcList.at(i).angle1*16;
        double endAngle = m_arcList.at(i).angle2*16;

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

    for(int i = 0; i < m_ellipseList.count(); i++){
        double k  = m_ellipseList.at(i).ratio;
        double r1 = sqrt(pow((m_ellipseList.at(i).mx - m_ellipseList.at(i).cx), 2.0) +
                         pow((m_ellipseList.at(i).my - m_ellipseList.at(i).cy), 2.0));
        double rotateAngle = calc_rotateAngle(m_ellipseList.at(i).cx, m_ellipseList.at(i).cy,
                                              m_ellipseList.at(i).mx, m_ellipseList.at(i).my);
        double startAngle  = 16*m_ellipseList.at(i).angle1*180/M_PI;
        double endAngle    = 16*m_ellipseList.at(i).angle2*180/M_PI;

        painter.translate(m_zoom*m_ellipseList.at(i).cx  - m_zoom*r1 + width()/2,
                          -m_zoom*m_ellipseList.at(i).cy  - m_zoom*k*r1 + height()/2);

        painter.rotate(360 - rotateAngle*180/M_PI);

        painter.scale(1, k);

        double Angle = 16*360 - fabs(endAngle - startAngle);
        if(Angle < 1e-10){
            painter.drawArc(0, 0, m_zoom*2*r1, m_zoom*2*r1, startAngle, 16*360);
        }else{
            painter.drawArc(0, 0, m_zoom*2*r1, m_zoom*2*r1, startAngle, Angle);
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
