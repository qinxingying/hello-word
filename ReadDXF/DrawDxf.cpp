#include "DrawDxf.h"
#include "dl_dxf.h"
#include "dl_creationadapter.h"
#include "test_creationclass.h"

#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QDebug>

DrawDxf::DrawDxf(QWidget *parent) :
	QWidget(parent)
{

}

void DrawDxf::paintEvent (QPaintEvent*)
{
//    Test_CreationClass* creationClass = new Test_CreationClass();
//    DL_Dxf* dxf = new DL_Dxf();

    QPainter painter(this);
    QPen pen = painter.pen();
    QPen NewPen(pen);
    NewPen.setWidth(2);
    NewPen.setColor(QColor(255, 0, 0));
    painter.setPen(NewPen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawLine (width()/2, 20, 150,50);
    painter.drawLine (130, 60, 80, height()/2);

    QVector<qreal> dashes;
    dashes << 3 << 5;
    NewPen.setWidth(1);
    NewPen.setDashPattern(dashes);
    NewPen.setColor(QColor(0, 0, 255));
    painter.setPen(NewPen);
    painter.drawLine(0, height()/2, width(), height()/2);
    painter.drawLine(width()/2, 0, width()/2, height());

//        DL_LineData& data;
//        painter.drawLine (data.x1, data.y1, data.x2,data.y2);

    painter.setPen(pen);
}
