#include "DrawDxf.h"
#include "dl_dxf.h"
#include "dl_creationadapter.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

#define M_PI   3.14159265358979323846

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

void DrawDxf::paintEvent (QPaintEvent*)
{
    QPainter painter(this);
    QPen pen = painter.pen();
    QPen NewPen(pen);

    NewPen.setWidth(2);
    NewPen.setColor(QColor(255, 0, 0));
    painter.setPen(NewPen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if (m_lineList.size() > 0){
        for(int i = 0; i < m_lineList.count(); i++){
            painter.drawLine(m_zoom*m_lineList.at(i).x1 + width()/2, -m_zoom*m_lineList.at(i).y1 + height()/2,
                             m_zoom*m_lineList.at(i).x2 + width()/2, -m_zoom*m_lineList.at(i).y2 + height()/2);
        }
    }

//    if(m_arcList.size() > 0){
//        for(int i = 0; i < m_arcList.count(); i++){
//            double r = m_arcList.at(i).radius;
//            double x = m_arcList.at(i).cx - 1.141*r;
//            double y = m_arcList.at(i).cy - 1.141*r;
//            double startAngle = m_arcList.at(i).angle1* 2*M_PI / 360;
//            double endAngle = m_arcList.at(i).angle2* 2*M_PI / 360;
//            painter.drawArc(m_zoom*x + width()/2, m_zoom*y + height()/2, m_zoom*2*r, m_zoom*2*r,
//                            startAngle, fabs(endAngle - startAngle));
//            qDebug()<<__func__<<"arc = "<<m_arcList.at(i).radius;
//        }
//    }

    if(m_textList.size() > 0){
        for(int i = 0; i < m_textList.count(); i++){
            painter.drawText(m_zoom*(m_textList.at(i).ipx-2*m_textList.at(i).height) + width()/2, -m_zoom*m_textList.at(i).ipy + height()/2,
                             m_zoom*4*m_textList.at(i).height, m_zoom*m_textList.at(i).height, Qt::AlignLeft, m_textList.at(i).text.c_str());
            qDebug()<<__func__<<"text = "<<m_textList.at(i).text.c_str();
        }
    }

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
