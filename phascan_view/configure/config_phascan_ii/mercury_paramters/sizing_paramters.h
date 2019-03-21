#ifndef SIZING_H
#define SIZING_H

#include <QObject>
#include "curves_paramters.h"

namespace Paramters {

class Sizing : public QObject
{
    Q_OBJECT
public:
    enum SizingType {
        SizingNONE,
        DAC,
        LINEAR_DAC,
        TCG
    };

    explicit Sizing(QObject *parent = 0);
    ~Sizing();

private:
    Curves m_curves;
    SizingType m_type;

    friend class Config;
};

}

#endif // SIZING_H
