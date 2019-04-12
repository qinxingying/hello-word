#ifndef NOZZLE_H
#define NOZZLE_H

#include <QObject>
#include "cylinder_paramters.h"

namespace Paramters {

class Nozzle : public QObject
{
    Q_OBJECT
public:
    explicit Nozzle(QObject *parent = 0);

private:
    double m_angle;
    double m_inside;
    double m_outside;
    Cylinder m_cylinder1;
    Cylinder m_cylinder2;

    friend class Config;
};

}

#endif // NOZZLE_H
