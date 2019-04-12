#ifndef TCG_H
#define TCG_H

#include <QObject>
#include "../configure/Instrument.h"

namespace Paramters {

class TCG : public QObject
{
    Q_OBJECT
public:
    explicit TCG(QObject *parent = 0);

private:
    int m_currentPointIndex;
    int m_currentBeamIndex;
    int m_pointCount;
    double m_position[setup_MAX_LAW_QTY];
    double m_gain[setup_MAX_LAW_QTY];

    friend class Config;
};

}

#endif // TCG_H
