#ifndef WELDV_H
#define WELDV_H
//#include "weld_paramters.h"
#include <QObject>

namespace Paramters {

class WeldV : public QObject
{
    Q_OBJECT
public:
    explicit WeldV(QObject *parent = 0);

private:
    uint m_orientation;
    bool m_symmetry;
    double m_width;
    double m_height;

    friend class Config;
};

}

#endif // WELDV_H
