#ifndef SCAN_H
#define SCAN_H

#include <QObject>

namespace Paramters {

class Scan : public QObject
{
    Q_OBJECT
public:
    explicit Scan(QObject *parent = 0);

private:
    double m_refractAngle;
    double m_screwAngle;

    double m_refractStartAngle;
    double m_refractStopAngle;
    double m_refractStepAngle;

    double m_screwStartAngle;
    double m_screwStopAngle;
    double m_screwStepAngle;

    double m_colOffset;
    double m_colRes;
    double m_rowOffset;
    double m_rowRes;

    int m_colQty;
    int m_rowQty;

    uint m_secApe;
    uint m_secStartElem;
    uint m_secElemStep;
    uint m_secStopElem;

    uint m_priApe;
    uint m_priStartElem;
    uint m_priElemStep;
    uint m_priStopElem;

    friend class Config;
};

}

#endif // SCAN_H
