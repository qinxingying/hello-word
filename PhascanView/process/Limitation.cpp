#include "Limitation.h"
#include <string.h>
#include <configure/DopplerConfigure.h>
#include <configure/const.h>
#include "ParameterProcess.h"

Limitation::Limitation(QObject *parent) :
    QObject(parent)
{
    m_pConfig = DopplerConfigure::Instance() ;
}


QString Limitation::IsGroupConfigureAvailible()
{
    QString _str ;
    return _str;
}

static const float MAX_GAIN_VALUE = 80.0  ;
float Limitation::GetGroupGainMax(int nGroupId_)
{
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
    float _ret = MAX_GAIN_VALUE - _group.fRefGain ;
    return _ret;
}
float Limitation::GetGroupGainMin(int nGroupId_)
{
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
    float _ret =  -_group.fRefGain ;
    return _ret;
}
float Limitation::GetGroupSampleRangeMax(int nGroupId_)
{
    ParameterProcess* _process = ParameterProcess::Instance();
    int _nLawQty = _process->GetTotalLawQty() ;
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;

    double _fMaxLength = 1000000.0 / (4 * _nLawQty) ; // us
    float _fVelocity = _group.fVelocity  ;
    float _ret = GetGroupMaxBeamDelay(nGroupId_) / 1000.0 ;
    _ret = _fMaxLength - _ret - _group.nWedgeDelay / 1000.0 ;
    _ret = _ret * _fVelocity / 20000 ;

    if(_ret > 5000)  _ret = 5000 ;
    return _ret ; // mm
}

unsigned int Limitation::GetGroupMaxBeamDelay(int nGroupId_ )
{
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
    unsigned int _nBeamDelay = 0;
    ParameterProcess* _process = ParameterProcess::Instance();
    int _nGroupLawQty = _process->GetGroupLawQty(nGroupId_) ;
    for(int i = 0 ; i < _nGroupLawQty ; i++)
    {
        if(_nBeamDelay < _group.anBeamDelay[i])
            _nBeamDelay = _group.anBeamDelay[i]  ;
    }
    return _nBeamDelay ;
}




