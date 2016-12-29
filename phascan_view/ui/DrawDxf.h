#ifndef DrawDxf_H
#define DrawDxf_H

#include "dl_creationadapter.h"

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

private:
//    const DL_LineData& data;

protected:
    void  paintEvent (QPaintEvent * event);

};

#endif // DrawDxf_H
