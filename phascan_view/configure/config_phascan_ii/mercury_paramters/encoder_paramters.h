#ifndef ENCODER_H
#define ENCODER_H

#include <QObject>

namespace Paramters {

class Encoder : public QObject
{
    Q_OBJECT
public:

    enum EncoderStatus {
        OFF,
        ON
    };

    enum Polarity {
        NORMAL,
        INVERSE
    };

    enum EncoderMode {
        DOWN,
        UP,
        QUAD
    };

    explicit Encoder(QObject *parent = 0);

private:
    EncoderStatus m_status;
    Polarity m_polarity;
    EncoderMode m_mode;
    double m_resolution;
    double m_origin;

    friend class Config;
};

}

#endif // ENCODER_H
