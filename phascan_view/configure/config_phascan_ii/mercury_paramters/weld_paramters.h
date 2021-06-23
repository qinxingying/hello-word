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
        NONE_TYPE, //0
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
        AXIAL,//轴向
        CIRC//环向
    };

    enum Symmetry {
        SYMMETRIC, //对称
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
    WeldASY m_ASY;
    WeldI m_Main_I;
    WeldI m_Slave_I;
    WeldV m_Main_V;
    WeldV m_Slave_V;



    friend class Config;
};

}

#endif // WELD_H
