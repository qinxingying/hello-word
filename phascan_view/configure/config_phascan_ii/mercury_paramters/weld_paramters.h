#ifndef WELD_H
#define WELD_H

#include <QObject>
#include "weld_i_paramters.h"
#include "weld_v_paramters.h"
#include "weld_u_paramters.h"

namespace Paramters {

class Weld : public QObject
{
    Q_OBJECT

    enum WeldType {
        NONE_TYPE,
        I,
        V,
        U,
        VY,
        VV,
        UU,
        UV
    };

    enum WeldOrientation {
        AXIAL,
        CIRC
    };

public:
    explicit Weld(QObject *parent = 0);

private:
    bool m_enable;
    WeldType m_type;
    bool m_isSymmetry;
    WeldOrientation m_orientation;
    WeldI m_I;
    WeldV m_V;
    WeldU m_U;
    WeldI m_MidI;
    WeldI m_BtmI;
    WeldU m_BtmU;
    WeldU m_TopU;
    WeldV m_BtmV;
    WeldV m_MidV;
    WeldV m_TopV;

    friend class Config;
};

}

#endif // WELD_H
