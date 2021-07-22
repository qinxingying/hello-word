#ifndef WELD_H
#define WELD_H

#include <QObject>
#include "weld_i_paramters.h"
#include "weld_v_paramters.h"
#include "weld_u_paramters.h"
#include "weld_t_paramters.h"
#include "weld_asy_paramters.h"
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
        UV,
        TKY,
        ASYMMETRIC
    };

    enum WeldOrientation {
        AXIAL,
        CIRC
    };

    enum Symmetry {
        SYMMETRIC,
        STRAIGHT_RIGHT,
        STRAIGHT_LEFT
    };

public:
    explicit Weld(QObject *parent = 0);

private:
    bool m_enable;
    WeldType m_type;
    Symmetry m_isSymmetry;
    WeldOrientation m_orientation;
    double HAZ;    //焊缝热影响区
    float m_bottomCapHeight {0};
    float m_bottomCapOverlap {0};
    float m_topCapHeight {0};
    float m_topCapOverlap {0};
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
    WeldTKY m_TKY;

    WeldASY m_asy;
    WeldI m_main_I;
    WeldI m_slave_I;
    WeldV m_main_V;
    WeldV m_slave_V;
    friend class Config;
};

}

#endif // WELD_H
