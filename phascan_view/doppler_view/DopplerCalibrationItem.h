#ifndef DOPPLERCALIBRATIONITEM_H
#define DOPPLERCALIBRATIONITEM_H

#include "DopplerLineItem.h"


class DopplerCalibrationItem : public DopplerLineItem
{
public:
    DopplerCalibrationItem(const QColor& cColor_);

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

    void DrawLabel(QPainter *painter, QString str);
};

#endif // DOPPLERCALIBRATIONITEM_H
