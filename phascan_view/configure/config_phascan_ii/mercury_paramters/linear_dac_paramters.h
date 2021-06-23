#ifndef LINEARDAC_H
#define LINEARDAC_H

#include <QObject>

namespace Paramters {

class LinearDAC : public QObject
{
    Q_OBJECT
public:
    explicit LinearDAC(QObject *parent = 0);

private:
    double m_matAttenuation;
    double m_delay;

    friend class Config;
};

}

#endif // LINEARDAC_H
