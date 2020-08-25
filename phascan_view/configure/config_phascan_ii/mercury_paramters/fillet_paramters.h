#ifndef FILLET_PARAMTERS_H
#define FILLET_PARAMTERS_H

#include <QObject>
#include "plane_paramters.h"
namespace Paramters {
class Fillet : public QObject
{
    Q_OBJECT
public:
    explicit Fillet(QObject *parent = 0);
    enum ProbePosition {
        WED_1,
        WED_2,
        WING_1,
        WING_2,
        WING_3,
        WING_4
    };
private:
    double m_angle;
    Fillet::ProbePosition m_probePos;
    Plane m_bottomPlane;
    Plane m_topPlane;

    friend class Config;
};
}
#endif // FILLET_PARAMTERS_H
