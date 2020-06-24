#ifndef TOFD_PARAMTERS_H
#define TOFD_PARAMTERS_H

#include <QObject>

namespace Paramters {
class Tofd : public QObject
{
    Q_OBJECT
public:
    explicit Tofd(QObject *parent = 0);
private:
    float m_PCS;
    float m_RefPosition;
    friend class Config;
};
}
#endif // TOFD_PARAMTERS_H
