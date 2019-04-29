#ifndef WELDSHOWDATAIIWIDGET_H
#define WELDSHOWDATAIIWIDGET_H

#include <QWidget>
#include "Instrument.h"

class WeldShowDataIIWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WeldShowDataIIWidget(QWidget *parent = 0);
    void SerPart(PART_CONFIG *pInfo_);

protected:
    void paintEvent( QPaintEvent *event);

private:
    PART_CONFIG* m_pPart;
    float m_fThickness;
};

#endif // WELDSHOWDATAIIWIDGET_H
