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

    double m_zoom;

    QList<DRAW_LINE> getLineList() const;
    void setLineList(const QList<DRAW_LINE> &lineList);

    QList<DRAW_ARC> getArcList() const;
    void setArcList(const QList<DRAW_ARC> &arcList);

    QList<DRAW_MTEXT> getTextList() const;
    void setTextList(const QList<DRAW_MTEXT> &textList);

private:
    Test_CreationClass* creationClass;
    QList<DRAW_LINE> m_lineList;
    QList<DRAW_ARC> m_arcList;
    QList<DRAW_MTEXT> m_textList;

protected:
    void paintEvent (QPaintEvent * event);

    void wheelEvent(QWheelEvent *event);

signals:
    void zoom(double v);
};

#endif // DrawDxf_H
