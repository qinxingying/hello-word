#ifndef PLANE_H
#define PLANE_H

#include <QObject>

namespace Paramters {

class Plane : public QObject
{
    Q_OBJECT
public:
    explicit Plane(QObject *parent = 0);

private:
    double m_width;
    double m_height;//厚度
    double m_length;

    friend class Config;
};

}

#endif // PLANE_H
