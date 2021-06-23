#ifndef SPECIMEN_H
#define SPECIMEN_H

#include <QObject>
#include "geometry_paramters.h"
#include "weld_paramters.h"

namespace Paramters {

class Specimen : public QObject
{
    Q_OBJECT

    enum Shape {
        PLANE, //0
        CYLINDER,
        NOZZLE,
        FILLET,
        ASYMMETRIC_PLANE //不等厚焊缝
    };

    enum Material {
        ALUMINUM,
        STEEL_COMMON,
        STEEL_STAINLESS,
        BRASS,
        COPPER,
        IRON,
        LEAD,
        NYLON,
        SILVER,
        GOLD,
        ZINC,
        TITANIUM,
        TIN,
        EPOXY_RESIN,
        ICE,
        NICKEL,
        PLEXIGLASS,
        POLYSTYRENE,
        ORCELAIN,
        PVC,
        QUARTZ_GLASS,
        RUBBER_VULCANIZED,
        TEFLON,
        WATER
    };

    enum WeldType {
        NONE_TYPE,
        I,
        V,
        U,
        VY,
        VV,
        UU,
        UV,
        TKY,
        DXF,
        ASYMMETRIC
    };

public:
    explicit Specimen(QObject *parent = 0);

private:
    Shape m_shape;
    double m_LV;
    double m_SV;
    Material m_material;
    double m_density;
    WeldType m_weldType;
    Geometry m_geometry;
    Weld m_weld;

    friend class Config;
};

}

#endif // SPECIMEN_H
