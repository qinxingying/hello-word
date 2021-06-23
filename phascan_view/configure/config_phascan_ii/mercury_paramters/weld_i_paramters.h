#ifndef WELDI_H
#define WELDI_H
//#include "weld_paramters.h"
#include <QObject>

namespace Paramters {

class WeldI : public QObject
{
    Q_OBJECT
public:
    explicit WeldI(QObject *parent = 0);

private:
    uint m_orientation;
    bool m_symmetry;
    double m_width;

    friend class Config;
};

}



#endif // WELDI_H
