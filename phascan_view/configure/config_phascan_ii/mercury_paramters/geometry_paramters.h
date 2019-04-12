#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QObject>
#include "plane_paramters.h"
#include "cylinder_paramters.h"
#include "nozzle_paramters.h"

namespace Paramters {

class Geometry : public QObject
{
    Q_OBJECT
public:
    explicit Geometry(QObject *parent = 0);

private:
    Plane m_plane;
    Cylinder m_cylinder;
    Nozzle m_nozzle;

    friend class Config;
};

}

#endif // GEOMETRY_H
