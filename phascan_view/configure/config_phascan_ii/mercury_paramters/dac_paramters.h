#ifndef DAC_H
#define DAC_H

#include <QObject>
#include "../configure/Instrument.h"

namespace Paramters {

class DAC : public QObject
{
    Q_OBJECT
public:

    enum CurveType {
        STRAIGHT,
        LOGARITHMIC,
        POLYNOMIAL
    };

    explicit DAC(QObject *parent = 0);

private:
    CurveType m_curveType;
    bool m_applyAllBeams; /* 二代默认应用到所有beam？？  */
    int m_pointCount;
    double m_position[setup_MAX_LAW_QTY];
    double m_amplitude[setup_MAX_LAW_QTY];
    int m_currentPoint;
    int m_currentBeamIndex;

    friend class Config;
};

}

#endif // DAC_H
