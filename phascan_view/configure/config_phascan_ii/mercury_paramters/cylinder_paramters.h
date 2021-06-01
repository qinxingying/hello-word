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
    enum WeldOrientation {
        AXIAL,
        CIRC
    };
    explicit Cylinder(QObject *parent = 0);

private:
    double m_length;
    double m_angle;
    double m_inside; // 半径 or 直径
    double m_outside;
    Cylinder::ProbePosition m_probePos;
    Cylinder::WeldOrientation m_weldDir;

    friend class Config;
};

}

#endif // CYLINDER_H
