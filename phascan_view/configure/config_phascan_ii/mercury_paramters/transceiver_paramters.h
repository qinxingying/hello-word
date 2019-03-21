#ifndef TRANSCEIVER_H
#define TRANSCEIVER_H

#include <QObject>

namespace Paramters {

class Transceiver : public QObject
{
    Q_OBJECT

    enum Averaging {
        AVERAGING_1,
        AVERAGING_2,
        AVERAGING_4,
        AVERAGING_8,
        AVERAGING_16
    };

    enum TxRxMode {
        PE,
        PC,
        TT,
        TOFD
    };

    enum Rectifier {
        RF,
        POSITIVE_HW,
        NEGATIVE_HW,
        FULL_WAVE,
    };

public:
    explicit Transceiver(QObject *parent = 0);

private:
    bool m_autoCalPW;
    Averaging m_average;
    uint m_filter;
    TxRxMode m_txRxMode;
    float m_pw;
    uint m_pulser;
    uint m_receiver;
    Rectifier m_rectifier;
    bool m_videoFilter;

    friend class Config;
};

}

#endif // TRANSCEIVER_H
