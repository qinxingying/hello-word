#ifndef WELD_T_PARAMTERS_H
#define WELD_T_PARAMTERS_H

#include <QObject>
namespace Paramters {

class WeldTKY : public QObject
{
    Q_OBJECT
public:
    explicit WeldTKY(QObject *parent = 0);

private:
    double m_a1;
    double m_a2;
    double m_h1;
    double m_h2;
    double m_l1;
    double m_l2;

    friend class Config;
};

}
#endif // WELD_T_PARAMTERS_H
