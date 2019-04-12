#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include "axis_paramters.h"
#include "encoder_paramters.h"

namespace Paramters {

class Scanner : public QObject
{
    Q_OBJECT
public:

    enum ScanType {
        OneLine,
        RasterScan,
        HelicoidalScan
    };

    explicit Scanner(QObject *parent = 0);

private:
    ScanType m_scanType;
    uint m_rate;
    Axis m_scanAxis;
    Axis m_indexAxis;
    Encoder m_encoderX;
    Encoder m_encoderY;

    friend class Config;
};

}

#endif // SCANNER_H
