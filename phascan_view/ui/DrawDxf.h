#ifndef DrawDxf_H
#define DrawDxf_H

#include "dl_creationadapter.h"
#include "test_creationclass.h"

#include <QWidget>
#include <QPaintEvent>

namespace DplDxf {
    class DrawDxf;
}

class DrawDxf : public QWidget
{
	Q_OBJECT

public:
    explicit DrawDxf(QWidget *parent = 0);

    QList<DRAW_LINE> getLineList() const;
    void setLineList(const QList<DRAW_LINE> &lineList);
    double m_zoom;

private:
    Test_CreationClass* creationClass;
    DRAW_LINE m_line;
    QList<DRAW_LINE> m_lineList;

protected:
    void paintEvent (QPaintEvent * event);

    void wheelEvent(QWheelEvent *event);

signals:
    void zoom(double v);
};

#endif // DrawDxf_H
