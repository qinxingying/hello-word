#ifndef AXIS_H
#define AXIS_H

#include <QObject>

namespace Paramters {

class Axis : public QObject
{
    Q_OBJECT
public:

    enum Driving {
        TIMER,
        ENCODER_X,
        ENCODER_Y,
        NONE
    };

    explicit Axis(QObject *parent = 0);

private:
    Driving m_driving;
    double m_start;
    double m_end;
    double m_resolution;

    friend class Config;
};

}

#endif // AXIS_H
