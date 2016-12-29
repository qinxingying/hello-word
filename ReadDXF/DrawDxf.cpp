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

DRAW_LINE DrawDxf::getLine() const
{
    return m_line;
}

void DrawDxf::setLine(const DRAW_LINE &line)
{
    m_line = line;
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

    qDebug() << "m_line x1:" << m_line.x1 << "x2:" << m_line.x2;
    painter.drawLine(m_line.x1, m_line.y1, m_line.x2, m_line.y2);

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
