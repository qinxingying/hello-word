#ifndef CYLINDER_H
#define CYLINDER_H

#include <QObject>

namespace Paramters {

class Cylinder : public QObject
{
    Q_OBJECT
public:
    enum ProbePosition {
        CID,
        COD
    };
    explicit Cylinder(QObject *parent = 0);

private:
    double m_length;
    double m_angle;
    double m_inside;
    double m_outside;
    Cylinder::ProbePosition m_probePos;

    friend class Config;
};

}

#endif // CYLINDER_H
