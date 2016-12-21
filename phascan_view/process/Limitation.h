/***************************
  Description:   计算各参数之间的互相约束关系
************************************/

#ifndef LIMITATION_H
#define LIMITATION_H

#include <QObject>

class DopplerConfigure ;

class Limitation : public QObject
{
    Q_OBJECT
public:
    explicit Limitation(QObject *parent = 0);
    QString IsGroupConfigureAvailible() ;

    float GetGroupGainMax(int nGroupId_);
    float GetGroupGainMin(int nGroupId_);
    float GetGroupSampleRangeMax(int nGroupId_);
    unsigned int GetGroupMaxBeamDelay(int nGroupId_ ) ;

protected:
    DopplerConfigure* m_pConfig ;
signals:

public slots:

};

#endif // LIMITATION_H
