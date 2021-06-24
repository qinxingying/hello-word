#ifndef ASYMMETRIC_PLANE_H
#define ASYMMETRIC_PLANE_H

#include <QObject>
#include "plane_paramters.h"
namespace Paramters{

class Asymmetric_Plane : public QObject
{
    Q_OBJECT
public:
    explicit Asymmetric_Plane(QObject *parent = nullptr);

    enum Align {
        Top,
        Center,
        Bottom
    };


signals:


 private:
    Plane m_mainplane;
    Plane m_slaveplane;
    bool m_edgeenabled; //消边
    Asymmetric_Plane::Align m_align;//对齐方式
 //   double t1;//
 //   double t2;//在板子参数中（高度）
      double m_l1;
      double m_h1;
      double m_l2;
      double m_h2;

      friend class Config;


};

}

#endif // ASYMMETRIC_PLANE_H
