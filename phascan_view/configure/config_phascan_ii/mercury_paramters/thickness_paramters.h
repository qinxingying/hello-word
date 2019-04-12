#ifndef THICKNESS_H
#define THICKNESS_H

#include <QObject>

namespace Paramters {

class Thickness : public QObject
{
    Q_OBJECT
public:
    explicit Thickness(QObject *parent = 0);

private:
    double m_min;
    double m_max;

    friend class Config;
};

}

#endif // THICKNESS_H
