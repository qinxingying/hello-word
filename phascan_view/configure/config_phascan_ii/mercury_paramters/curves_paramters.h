﻿#ifndef CURVES_H
#define CURVES_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QPair>
#include "dac_paramters.h"
#include "linear_dac_paramters.h"
#include "tcg_paramters.h"
#include "../configure/Instrument.h"

namespace Paramters {

class Curves : public QObject
{
    Q_OBJECT
public:
    enum SizingType {
        SizingNONE,
        DAC,
        LINEAR_DAC,
        TCG
    };

    enum Standard {
        CUSTOM,
        NBT_47013_15,
        SYT_4019_2020,
        JIC,
        ASME
    };

    explicit Curves(QObject *parent = 0);

private:
	/* Linear DAC */
    double m_delay;
    double m_attenuation;
	
    Standard m_standard;
    int m_curveQty;
    double m_gain;
    QVector<double> m_offsets;
    uint m_pointQty;
    double m_refAmp;
    /* 保存所有beams对应的点数，
     * TCG: pair：first：Gain; secondvalue：position
     * DAC: pair：first：Offsets; secondvalue：position
     * secondvalue：position */
    QList< QList< QPair<double, double> > > m_beams;

    friend class Config;
};

}

#endif // CURVES_H
