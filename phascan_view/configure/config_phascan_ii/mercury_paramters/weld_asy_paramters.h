#ifndef WELDASY_H
#define WELDASY_H
//#include "weld_paramters.h"
#include <QObject>
namespace Paramters {
class WeldASY : public QObject
{
    Q_OBJECT
public:
    explicit WeldASY(QObject *parent = nullptr);

signals:
private:

   // WeldI m_I;
    //WeldV m_V;

    uint m_orientation;
    bool m_symmetry;
    double W1;
    double H1;
    double W2;
    double H2;
    double W3;
friend class Config;

};
}
#endif // WELDASY_H
