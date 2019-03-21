#ifndef CURSOR_H
#define CURSOR_H

#include <QObject>

namespace Paramters {

class Cursor : public QObject
{
    Q_OBJECT
public:
    explicit Cursor(QObject *parent = 0);

private:
    double m_ampMeas;
    double m_ampRef;
    double m_depthMeas;
    double m_depthRef;
    double m_indexMeas;
    double m_indexRef;
    double m_scanMeas;
    double m_scanRef;
    double m_ultraMeas;
    double m_ultraRef;

    friend class Config;
};

}

#endif // CURSOR_H
