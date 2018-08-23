#ifndef DOPPLERCSCANLINEMARK_H
#define DOPPLERCSCANLINEMARK_H

#include "DopplerLineItem.h"

class DopplerCScanLineMark :public QObject, public DopplerLineItem
{

    Q_OBJECT

public:
    explicit DopplerCScanLineMark(const QColor& cColor_, QObject *parent = 0);
    ~DopplerCScanLineMark();

    void SendSignalIndex(int index);
signals:
    void SignalChangeSScanLawMarkIndex(int index);

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    void DrawLabel(QPainter *painter);

public slots:

};

#endif // DOPPLERCSCANLINEMARK_H
