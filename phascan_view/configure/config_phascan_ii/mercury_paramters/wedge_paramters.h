#ifndef WEDGE_H
#define WEDGE_H

#include <QObject>

namespace Paramters {

class Wedge : public QObject
{
    Q_OBJECT

    enum Orientation {
        Reversal,
        Normal
    };

    enum WaveType {
        Longitudinal,
        Shear
    };

public:
    explicit Wedge(QObject *parent = 0);

private:
    QString m_serial;
    QString m_model;
    double m_angle;
    double m_fstElemHeight;
    double m_length;
    double m_width;
    double m_height;
    double m_velocity;
    double m_priOffset;
    double m_secOffset;
    Orientation m_orientation;
    double m_rootAngle;
    uint m_delay;
    double m_clampOffset;

    WaveType m_waveType;
    uint m_refPoint;

    friend class Config;
};

}

#endif // WEDGE_H
