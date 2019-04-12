#ifndef GLOBALTRANSCEIVER_H
#define GLOBALTRANSCEIVER_H

#include <QObject>

namespace Paramters {

class GlobalTransceiver : public QObject
{
    Q_OBJECT
public:

    enum Voltage {
        V50  = 50,
        V100 = 100,
        V200 = 200,
        V400 = 400
    };

    enum Damping {
        R50  = 0b00,
        R100 = 0b01,
        R200 = 0b10,
        R500 = 0b11
    };

    explicit GlobalTransceiver(QObject *parent = 0);

private:
    Voltage m_paVoltage;
    Voltage m_utVoltage;
    Damping m_ut1TxDamping;
    Damping m_ut2TxDamping;

    friend class Config;
};

}

#endif // GLOBALTRANSCEIVER_H
