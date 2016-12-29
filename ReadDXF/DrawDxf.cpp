#include "DrawDxf.h"
#include "dl_dxf.h"
#include "dl_creationadapter.h"
//#include "test_creationclass.h"

#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QDebug>

DrawDxf::DrawDxf(QWidget *parent) :
	QWidget(parent)
{
    creationClass = new Test_CreationClass();

}

QList<DRAW_LINE> DrawDxf::getLineList() const
{
    return m_lineList;
}

void DrawDxf::setLineList(const QList<DRAW_LINE> &lineList)
{
    m_lineList = lineList;
}

void DrawDxf::paintEvent (QPaintEvent*)
{
    if (m_lineList.size() <= 0) return ;

    QPainter painter(this);
    QPen pen = painter.pen();
    QPen NewPen(pen);

    NewPen.setWidth(2);
    NewPen.setColor(QColor(255, 0, 0));
    painter.setPen(NewPen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int i = 0; i < m_lineList.count(); i ++)
    {
        qDebug() << "m_line x2:" << m_lineList.at(i).x2 << "y2:" << m_lineList.at(i).y2;
        painter.drawLine(3*m_lineList.at(i).x1 +250, -3*m_lineList.at(i).y1 +400, 3*m_lineList.at(i).x2 +250, -3*m_lineList.at(i).y2 +400);
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
