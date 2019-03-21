#ifndef WELDU_H
#define WELDU_H

#include <QObject>

namespace Paramters {

class WeldU : public QObject
{
    Q_OBJECT
public:
    explicit WeldU(QObject *parent = 0);

private:
    uint m_orientation;
    bool m_symmetry;
    double m_width;
    double m_height;
    double m_radius;

    friend class Config;
};

}

#endif // WELDU_H
