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

void DrawDxf::paintEvent (QPaintEvent*)
{
    QPainter painter(this);
    QPen pen = painter.pen();
    QPen NewPen(pen);

    NewPen.setWidth(2);
    NewPen.setColor(QColor(255, 0, 0));
    painter.setPen(NewPen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    paint_line(painter);

    paint_text(painter);

    paint_arc(painter);

    paint_circle(painter);

    paint_vertex(painter);

    QVector<qreal> dashes;
    dashes << 3 << 5;
    NewPen.setWidth(1);
    NewPen.setDashPattern(dashes);
    NewPen.setColor(QColor(0, 0, 255));
    painter.setPen(NewPen);
    painter.drawLine(0, height()/2, width(), height()/2);
    painter.drawLine(width()/2, 0, width()/2, height());

    painter.setPen(pen);
}

void DrawDxf::paint_line(QPainter &painter)
{
    if (m_lineList.size() > 0){
        for(int i = 0; i < m_lineList.count(); i++){
            painter.drawLine(m_zoom*m_lineList.at(i).x1 + width()/2, -m_zoom*m_lineList.at(i).y1 + height()/2,
                             m_zoom*m_lineList.at(i).x2 + width()/2, -m_zoom*m_lineList.at(i).y2 + height()/2);
        }
    }
    if(m_vertexList.size() > 0){
        for(int i = 1; i < m_vertexList.count(); i++){
            painter.drawLine(m_zoom*m_vertexList.at(i-1).x + width()/2, -m_zoom*m_vertexList.at(i-1).y + height()/2,
                             m_zoom*m_vertexList.at(i).x + width()/2, -m_zoom*m_vertexList.at(i).y + height()/2);
        }
    }
}

void DrawDxf::paint_text(QPainter &painter)
{
    if(m_textList.size() > 0){
        for(int i = 0; i < m_textList.count(); i++){
            painter.drawText(m_zoom*(m_textList.at(i).ipx-2*m_textList.at(i).height) + width()/2, -m_zoom*m_textList.at(i).ipy + height()/2,
                             m_zoom*4*m_textList.at(i).height, m_zoom*m_textList.at(i).height, Qt::AlignLeft, m_textList.at(i).text.c_str());
        }
    }

    if(m_textDataList.size() > 0){
        for(int i = 0; i < m_textDataList.count(); i++){
            painter.drawText(m_zoom*m_textDataList.at(i).ipx + width()/2, -m_zoom*m_textDataList.at(i).ipy + height()/2,
                             m_zoom*8*m_textDataList.at(i).height, m_zoom*m_textDataList.at(i).height,
                             Qt::AlignCenter, m_textDataList.at(i).text.c_str());
        }
    }
}

void DrawDxf::paint_arc(QPainter &painter)
{
    if(m_arcList.size() > 0){
        for(int i = 0; i < m_arcList.count(); i++){
            double r = m_arcList.at(i).radius;
            double x = m_arcList.at(i).cx - r;
            double y = m_arcList.at(i).cy - r;
            double startAngle = m_arcList.at(i).angle1*16;
            double endAngle = m_arcList.at(i).angle2*16;

            painter.drawArc(m_zoom*x + width()/2, m_zoom*y + height()/2, m_zoom*2*r, m_zoom*2*r,
                            startAngle, abs(endAngle - startAngle));
        }
    }
}

void DrawDxf::paint_ellipse(QPainter &painter)
{
    if(m_ellipseList.size() > 0){
        for(int i = 0; i < m_ellipseList.count(); i++){
            double r = m_ellipseList.at(i).ratio;
            double x = m_ellipseList.at(i).cx - sqrt(2)*r/2;
            double y = m_ellipseList.at(i).cy - sqrt(2)*r/2;
            double startAngle = m_ellipseList.at(i).angle1*16;
            double endAngle = m_ellipseList.at(i).angle2*16;
            painter.drawArc(m_zoom*x + width()/2, -m_zoom*y + height()/2, m_zoom*sqrt(2)*r, m_zoom*sqrt(2)*r,
                            startAngle, abs(endAngle - startAngle));
      //      painter.drawEllipse();

qDebug()<<__func__<<"r = "<<m_ellipseList.at(i).ratio;
        }
    }
}

void DrawDxf::paint_circle(QPainter &painter)
{
    if(!m_circleList.isEmpty()){
        for(int i = 0; i < m_circleList.count(); i++){
            painter.drawEllipse(m_zoom*m_circleList.at(i).cx + width()/2, -m_zoom*m_circleList.at(i).cy + height()/2,
                                m_zoom*m_circleList.at(i).radius, m_zoom*m_circleList.at(i).radius);
        }
    }
}

void DrawDxf::paint_vertex(QPainter &painter)
{
    if(m_vertexList.size() > 0){
        for(int i = 0; i < m_vertexList.count(); i++){
            painter.drawPoint(m_zoom*m_vertexList.at(i).x + width()/2, -m_zoom*m_vertexList.at(i).y + height()/2);
        }
    }
}

void DrawDxf::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0){
        m_zoom += 0.5;
    }else{
        if(m_zoom > 0){
            m_zoom -= 0.5;
        }
    }
    update();
    emit zoom(m_zoom);
}
