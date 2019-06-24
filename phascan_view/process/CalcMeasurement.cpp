#include "CalcMeasurement.h"
#include <process/ParameterProcess.h>
#include <configure/DopplerConfigure.h>
#include <gHeader.h>

PEAK_CONFIG g_PeakInfo[setup_GATE_MAX];
extern double RL_EL_SL[5];

CalcMeasurement::CalcMeasurement(QObject *parent) :
	QObject(parent)
{
}

void CalGatePeakInfo(int nGroupId_ , int nLaw_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	int _nScanPos = _process->GetScanIndexPos();
	_process->GetGatePeakInfos(nGroupId_, _nScanPos, nLaw_, g_PeakInfo);
}

int CalGateAmp2Ref(int , int  , setup_GATE_NAME  , float* )
{
	int ret = -1 ;
	return ret ;
}

float CalIEdgeInWater(int nGroupId_ , float fEdge_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;

	float _fC = _pGroup->fVelocity;
	if(_fC < 0.5) {
		_fC = 0.5;
	}
	return fEdge_ * 2000 / _fC;
}

float CalcML(int nGroupId_ , float _fTApos)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	float _fDepth  = _fTApos;
	float _fThickness = _process->GetPartThickness(nGroupId_) ;
	if(_fThickness < 0.5)
		_fThickness = 0.5;
	return 100 * ( _fThickness - _fDepth ) / _fThickness;
}


int CalARCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_A_REF] ;
	return 0;
}

int CalAMCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_A_MES] ;
	return 0;
}
int CalAMRCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_A_MES] - _pGroup->afCursor[setup_CURSOR_A_REF];

	return 0;
}
int CalURCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_U_REF] ;
	return 0;
}

int CalUMCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_U_MES] ;
	return 0;
}
int CalUMRCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_U_MES] - _pGroup->afCursor[setup_CURSOR_U_REF];
	return 0;
}
int CalPRCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_I_REF] - _pGroup->fIndexOffset ;
	return 0;
}
int CalPMCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_I_MES] - _pGroup->fIndexOffset ;
	return 0;
}
int CalPMRCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_I_MES] - _pGroup->afCursor[setup_CURSOR_I_REF] ;
	return 0;
}
int CalSRCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_S_REF] ;
	return 0;
}
int CalSMCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_S_MES] ;
	return 0;
}
int CalSMRCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_S_MES] -  _pGroup->afCursor[setup_CURSOR_S_REF] ;
	return 0;
}
int CalIRCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_I_REF] ;
	return 0;
}
int CalIMCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_I_MES] ;
	return 0;
}
int CalIMRCursor(int nGroupId_ , float* pResult_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	GROUP_CONFIG* _pGroup = _process->GetGroupConfig(nGroupId_) ;
	*pResult_ = _pGroup->afCursor[setup_CURSOR_I_MES] -  _pGroup->afCursor[setup_CURSOR_I_REF] ;
	return 0;
}

int CalPDist(int nGroupId_ , int nLaw_ , setup_GATE_NAME eGate_ ,  float* pResult_ )
{
    //Q_UNUSED(eGate_)
	int ret = 0;

	ParameterProcess* _process = ParameterProcess::Instance() ;
    float _nHeight = g_PeakInfo[eGate_].fGh ;
    float _fAmp    = g_PeakInfo[eGate_].fAmp;

	_fAmp = fabs(_fAmp);
	if(_nHeight < 1) _nHeight = 1  ;

	if(_nHeight > _fAmp)
		ret  =  -1 ;

    if(_process->GetGateInfo(nGroupId_ , eGate_)->eMeasure){
        *pResult_ = g_PeakInfo[eGate_].fLEdge + _process->GetBeamInsertPos(nGroupId_  , nLaw_);
    }else{
        *pResult_ = g_PeakInfo[eGate_].fL + _process->GetBeamInsertPos(nGroupId_  , nLaw_);
    }
	return ret ;
}

int CalViDist(int nGroupId_ , int nLaw_ , setup_GATE_NAME eGate_ ,  float* pResult_ )
{
	int ret = 0;
	ret = CalPDist(nGroupId_ ,nLaw_ ,  eGate_ , pResult_ ) ;
	if(ret)  return ret;

	ParameterProcess* _process = ParameterProcess::Instance() ;
	setup_PROBE_ANGLE _eSkew = _process->GetGroupSkewType(nGroupId_)  ;
	float  _fIndexOffset ;
	_process->GetWedgePosition( nGroupId_ , NULL , &_fIndexOffset );


	if(setup_PROBE_PART_SKEW_90 == _eSkew)
	{
		*pResult_ +=_fIndexOffset ;
	}
	else if(setup_PROBE_PART_SKEW_270  == _eSkew )
	{
		*pResult_ =_fIndexOffset - *pResult_ ;
	}
	else
		ret = -1 ;

	return ret ;

}


int CalVsDist(int nGroupId_ , int nLaw_ , setup_GATE_NAME eGate_ ,  float* pResult_ )
{
	int ret = 0;
	ret = CalPDist(nGroupId_ ,nLaw_ ,  eGate_ , pResult_ ) ;
	if(ret)  return ret;

	ParameterProcess* _process = ParameterProcess::Instance() ;
	setup_PROBE_ANGLE _eSkew = _process->GetGroupSkewType(nGroupId_)  ;
	float  _fSOffset ;
	_process->GetWedgePosition( nGroupId_ , &_fSOffset , NULL );
	if(setup_PROBE_PART_SKEW_0 == _eSkew)
	{
		*pResult_ +=_fSOffset ;
	}
	else if(setup_PROBE_PART_SKEW_180  == _eSkew )
	{
		*pResult_ =_fSOffset - *pResult_ ;
	}
	else
		ret = -1 ;
	return ret ;

}

int CalLTimes(int nGroupId_ , int nLaw_ , setup_GATE_NAME eGate_ ,  float* pResult_ )
{
    Q_UNUSED(nLaw_);
	int ret = 0;

	ParameterProcess* _process = ParameterProcess::Instance() ;
    float _nHeight = g_PeakInfo[eGate_].fGh ;
    float _fAmp    = g_PeakInfo[eGate_].fAmp;

	_fAmp = fabs(_fAmp);

	float _nDepth = 0 ;
	if(_nHeight < 1) _nHeight = 1  ;

	if(_nHeight > _fAmp)
		ret  =  -1 ;
    if(_process->GetGateInfo( nGroupId_ , eGate_)->eMeasure){
        _nDepth = g_PeakInfo[eGate_].fDEdge;
    }else{
        _nDepth = g_PeakInfo[eGate_].fD;
    }

	float _fThickness = _process->GetPartThickness(nGroupId_) ;
	*pResult_  = (int)(_nDepth / _fThickness)  ;
/*	int ret = 0 ;

	ParameterProcess* _process = ParameterProcess::Instance() ;
	float _nHeight = (float)(_process->GetGateInfo(nGroupId_ , eGate_)->nThreshold) ;
	float _fValue = _process->GetGateValueAmp(nGroupId_ , nLaw_ , eGate_);
	_fValue = fabs(_fValue)  ;

	float _nDepth = 0 ;
	if(_nHeight < 1) _nHeight = 1  ;
	if(_nHeight > _fValue)
		ret  =  -1 ;
	else
		_nDepth = _process->GetGateValuePos(nGroupId_ , nLaw_ , eGate_ , MM_TRUE_DEPTH ) ;//+ _process->GetBeamInsertPos(nGroupId_  , nLaw_);

	float _fThickness = _process->GetPartThickness(nGroupId_) ;
	*pResult_  = (int)(_nDepth / _fThickness)  ;
*/
	return ret ;
}


int TOFD_GetDepth(int nGroupId_ ,  float* pResult_ , int nIndex_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	int ret = 0 ;
	ret = _process->GetTofdDepth(nGroupId_ , nIndex_ , pResult_) ;
	return  ret ;
}

int CalcMeasurement::Calc(int nGroupId_ ,int nLaw_ , FEILD_VALUE_INDEX eIndex_ , float* pResult_)
{
	DopplerConfigure* m_pConfig = DopplerConfigure::Instance();
	GROUP_CONFIG* config = &(m_pConfig->group[nGroupId_]);

    ParameterProcess* _process = ParameterProcess::Instance() ;
    CalGatePeakInfo(nGroupId_ , nLaw_);
    GATE_CONFIG* A_pGate = _process->GetGateInfo(nGroupId_ , setup_GATE_A ) ;
    GATE_CONFIG* B_pGate = _process->GetGateInfo(nGroupId_ , setup_GATE_B ) ;
    GATE_CONFIG* I_pGate = _process->GetGateInfo(nGroupId_ , setup_GATE_I ) ;

	int ret = 0 ;
	switch(eIndex_)
	{
	case FEILD_A100:
	//	*pResult_ = g_PeakInfo[setup_GATE_A].fAmp;
		*pResult_ = pow(10.0, config->fRefGain/20.0)*g_PeakInfo[setup_GATE_A].fAmp;
		break;
	case FEILD_AdBA:
		*pResult_ = g_PeakInfo[setup_GATE_A].fXdXA;
		break;
	case FEILD_AdBr:
		ret = CalGateAmp2Ref(nGroupId_ , nLaw_ , setup_GATE_A , pResult_ );
		break;
	case FEILD_B100:
        //*pResult_ = g_PeakInfo[setup_GATE_B].fAmp;
        *pResult_ = pow(10.0, config->fRefGain/20.0)*g_PeakInfo[setup_GATE_B].fAmp;
		break;
	case FEILD_BdBB:
		*pResult_ = g_PeakInfo[setup_GATE_B].fXdXA;
		break;
	case FEILD_BdBr:
		ret = CalGateAmp2Ref(nGroupId_ , nLaw_ , setup_GATE_B , pResult_ );
		break;
	case FEILD_APos://A^		
        if(A_pGate->eMeasure){
            //*pResult_ = g_PeakInfo[setup_GATE_A].fDEdge;
            *pResult_ = g_PeakInfo[setup_GATE_A].fHEdge;
        }else{
            *pResult_ = g_PeakInfo[setup_GATE_A].fH;
        }
        if(g_PeakInfo[setup_GATE_A].fAmp < g_PeakInfo[setup_GATE_A].fGh) {
            ret = -1;
        }
		break;
	case FEILD_BPos://B^		
        if(B_pGate->eMeasure){
            *pResult_ = g_PeakInfo[setup_GATE_B].fHEdge;            
        }else{
            *pResult_ = g_PeakInfo[setup_GATE_B].fH;
        }
        if(g_PeakInfo[setup_GATE_B].fAmp < g_PeakInfo[setup_GATE_B].fGh) {
            ret = -1;
        }
		break;
	case FEILD_IEdge://I/

        if(I_pGate->eMeasure){
            *pResult_ = g_PeakInfo[setup_GATE_I].fHEdge;            
        }else{
            *pResult_ = g_PeakInfo[setup_GATE_I].fH;
        }
        if(g_PeakInfo[setup_GATE_I].fAmp < g_PeakInfo[setup_GATE_I].fGh) {
            ret = -1;
        }
		break;
	case FEILD_IEdgeInWater://I(W)/
		*pResult_ = CalIEdgeInWater(nGroupId_ , g_PeakInfo[setup_GATE_I].fDEdge);
		if(g_PeakInfo[setup_GATE_I].fAmp < g_PeakInfo[setup_GATE_I].fGh) {
			ret = -1;
		}
		break;
	case FEILD_ThicknessAPos://T(A^)
		*pResult_ = g_PeakInfo[setup_GATE_A].fH;
		if(g_PeakInfo[setup_GATE_A].fAmp < g_PeakInfo[setup_GATE_A].fGh) {
			ret = -1;
		}
		break;
	case FEILD_ML:
		*pResult_ = CalcML(nGroupId_ , g_PeakInfo[setup_GATE_A].fH);
		if(g_PeakInfo[setup_GATE_A].fAmp < g_PeakInfo[setup_GATE_A].fGh) {
			ret = -1;
		}
		break;
	case FEILD_r100://(%r)
		ret = CalARCursor(nGroupId_ , pResult_);
		break;
	case FEILD_m100://(%m)
		ret = CalAMCursor(nGroupId_ , pResult_);
		break;
	case FEILD_mr100://(%m-r)
		ret = CalAMRCursor(nGroupId_ , pResult_);
		break;
	case FEILD_Ur:
		ret = CalURCursor(nGroupId_ , pResult_);
		break;
	case FEILD_Um:
		ret = CalUMCursor(nGroupId_ , pResult_);
		break;
	case FEILD_Umr:
		ret = CalUMRCursor(nGroupId_ , pResult_);
		break;
	case FEILD_Pr:
		ret = CalPRCursor(nGroupId_ , pResult_);
		break;
	case FEILD_Pm:
		ret = CalPMCursor(nGroupId_ , pResult_);
		break;
	case FEILD_Pmr:
		ret = CalPMRCursor(nGroupId_ , pResult_);
		break;
	case FEILD_Sr:
		ret = CalSRCursor(nGroupId_ , pResult_);
		break;
	case FEILD_Sm:
		ret = CalSMCursor(nGroupId_ , pResult_);
		break;
	case FEILD_Smr:
		ret = CalSMRCursor(nGroupId_ , pResult_);
		break;
	case FEILD_Ir:
		ret = CalIRCursor(nGroupId_ , pResult_);
		break;
	case FEILD_Im:
		ret = CalIMCursor(nGroupId_ , pResult_);
		break;
	case FEILD_Imr:
		ret = CalIMRCursor(nGroupId_ , pResult_);
		break;
	case FEILD_RA:		
        if(A_pGate->eMeasure){
            *pResult_ = g_PeakInfo[setup_GATE_A].fLEdge;
        }else{
            *pResult_ = g_PeakInfo[setup_GATE_A].fL;
        }
        if(g_PeakInfo[setup_GATE_A].fAmp < g_PeakInfo[setup_GATE_A].fGh) {
            ret = -1;
        }
		break;
	case FEILD_RB:		
        if(B_pGate->eMeasure){
            *pResult_ = g_PeakInfo[setup_GATE_B].fLEdge;
        }else{
            *pResult_ = g_PeakInfo[setup_GATE_B].fL;
        }
        if(g_PeakInfo[setup_GATE_B].fAmp < g_PeakInfo[setup_GATE_B].fGh) {
            ret = -1;
        }
		break;
	case FEILD_PA:
		ret = CalPDist(nGroupId_ , nLaw_ , setup_GATE_A , pResult_ );
		break;
	case FEILD_PB:
		ret = CalPDist(nGroupId_ , nLaw_ , setup_GATE_B , pResult_ );
		break;
	case FEILD_DA:		
        if(A_pGate->eMeasure){
            *pResult_ = g_PeakInfo[setup_GATE_A].fDEdge;
        }else{
            *pResult_ = g_PeakInfo[setup_GATE_A].fD;
        }
        if(g_PeakInfo[setup_GATE_A].fAmp < g_PeakInfo[setup_GATE_A].fGh) {
            ret = -1;
        }
		break;
	case FEILD_DB:		
        if(B_pGate->eMeasure){
            *pResult_ = g_PeakInfo[setup_GATE_B].fDEdge;
        }else{
            *pResult_ = g_PeakInfo[setup_GATE_B].fD;
        }
        if(g_PeakInfo[setup_GATE_B].fAmp < g_PeakInfo[setup_GATE_B].fGh) {
            ret = -1;
        }
		break;
	case FEILD_SA:
        if(A_pGate->eMeasure){
            *pResult_ = g_PeakInfo[setup_GATE_A].fSEdge;
        }else{
            *pResult_ = g_PeakInfo[setup_GATE_A].fS;
        }
        if(g_PeakInfo[setup_GATE_A].fAmp < g_PeakInfo[setup_GATE_A].fGh) {
            ret = -1;
        }
		break;
	case FEILD_SB:
        if(B_pGate->eMeasure){
            *pResult_ = g_PeakInfo[setup_GATE_B].fSEdge;
        }else{
            *pResult_ = g_PeakInfo[setup_GATE_B].fS;
        }
        if(g_PeakInfo[setup_GATE_B].fAmp < g_PeakInfo[setup_GATE_B].fGh) {
            ret = -1;
        }
		break;
	case FEILD_ViA:
		ret = CalViDist(nGroupId_ , nLaw_ , setup_GATE_A , pResult_) ;
		break;
	case FEILD_ViB:
		ret = CalViDist(nGroupId_ , nLaw_ , setup_GATE_B , pResult_) ;
		break;
	case FEILD_VsA :
		ret = CalVsDist(nGroupId_ , nLaw_ , setup_GATE_A , pResult_) ;
		break;
	case FEILD_VsB :
		ret = CalVsDist(nGroupId_ , nLaw_ , setup_GATE_B , pResult_) ;
		break;
	case FEILD_LA :
		ret = CalLTimes(nGroupId_ , nLaw_ , setup_GATE_A , pResult_) ;
		break;
	case FEILD_LB :
        ret = CalLTimes(nGroupId_ , nLaw_ , setup_GATE_B , pResult_) ;
		break;
    case FEILD_RL :
        *pResult_ = 20 * log10(pow(10.0, config->fRefGain/20.0)*g_PeakInfo[setup_GATE_A].fAmp/(RL_EL_SL[setup_RL]*100));
        if(RL_EL_SL[setup_RL] < 0.0000001)
            ret = 1;
        break;
    case FEILD_EL :
        *pResult_ = 20 * log10(pow(10.0, config->fRefGain/20.0)*g_PeakInfo[setup_GATE_A].fAmp/(RL_EL_SL[setup_EL]*100));
        if(RL_EL_SL[setup_EL] < 0.0000001)
            ret = 1;
        break;
    case FEILD_SL :
        *pResult_ = 20 * log10(pow(10.0, config->fRefGain/20.0)*g_PeakInfo[setup_GATE_A].fAmp/(RL_EL_SL[setup_SL]*100));
        if(RL_EL_SL[setup_SL] < 0.0000001)
            ret = 1;
        break;
#if 0
	case FEILD_AWSDA:
		break;
	case FEILD_AWSDB:
		break;
	case FEILD_AWSDC:
		break;
	case FEILD_AWSDD:
		break;
	case FEILD_AWSD45:
		break;
	case FEILD_AWSD60:
		break;
	case FEILD_AWSD70:
		break;
	case FEILD_AWSDCL:
		break;
	case FEILD_E100:
		break;
	case FEILD_EPeak:
		break;
	case FEILD_E3dB:
		break;
	case FEILD_E6dB:
		break;
	case FEILD_E12dB:
		break;
	case FEILD_E20dB:
		break;
	case FEILD_APIDL:
		break;
	case FEILD_APIHW:
		break;
	case FEILD_Scale:
		break;
	case FEILD_Ur100:
		break;
	case FEILD_Um100:
		break;
#endif
	case FEILD_TofdDepth1 :
		ret = TOFD_GetDepth(nGroupId_  , pResult_ , 1) ;
		break;
	case FEILD_TofdDepth2 :
		ret = TOFD_GetDepth(nGroupId_  , pResult_ , 2) ;
		break;
	case FEILD_TofdLength :
		ret = CalSMRCursor(nGroupId_ , pResult_);
		break;
	case FEILD_TofdHeight :
		ret = TOFD_GetDepth(nGroupId_  , pResult_ , 3) ;
		break;
    case FEILD_APos_DEC_IPos:
        *pResult_ = g_PeakInfo[setup_GATE_A].fH - g_PeakInfo[setup_GATE_I].fH;
        break;
    case FEILD_BPos_DEC_IPos:
        *pResult_ = g_PeakInfo[setup_GATE_B].fH - g_PeakInfo[setup_GATE_I].fH;
        break;
	default:
		break;
	} ;
	return ret ;
}


const char* CalcMeasurement::GetMeasureNameString(int nGroupId_ , FEILD_VALUE_INDEX eIndex_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	switch(eIndex_)
	{
	case FEILD_APos :
	case FEILD_ThicknessAPos :
	case FEILD_RA :
	case FEILD_PA :
	case FEILD_DA :
	case FEILD_SA :
	case FEILD_ViA :
	case FEILD_LA  :
		{
			GATE_CONFIG* _pGate = _process->GetGateInfo(nGroupId_ , setup_GATE_A ) ;
			if(_pGate->eMeasure)
                return g_strMeasureFildName[eIndex_][2];
			else
                return g_strMeasureFildName[eIndex_][0];
		}
		break;
	case FEILD_BPos :
	case FEILD_RB :
	case FEILD_PB :
	case FEILD_DB :
	case FEILD_SB :
	case FEILD_ViB :
	case FEILD_LB :
		{
			GATE_CONFIG* _pGate = _process->GetGateInfo(nGroupId_ , setup_GATE_B ) ;
			if(_pGate->eMeasure)
                return g_strMeasureFildName[eIndex_][2];
			else
                return g_strMeasureFildName[eIndex_][0];
		}
		break;
	default:
        return g_strMeasureFildName[eIndex_][0];
		break;
	} ;
}

const char* CalcMeasurement::GetMeasureContentString(int nGroupId_ , FEILD_VALUE_INDEX eIndex_)
{
	ParameterProcess* _process = ParameterProcess::Instance() ;

	switch(eIndex_)
	{
	case FEILD_APos :
	case FEILD_ThicknessAPos :
	case FEILD_RA :
	case FEILD_PA :
	case FEILD_DA :
	case FEILD_SA :
	case FEILD_ViA :
	case FEILD_VsA :
	case FEILD_LA  :
		{
			GATE_CONFIG* _pGate = _process->GetGateInfo(nGroupId_ , setup_GATE_A ) ;
			if(_pGate->eMeasure)
				return g_strMeasureFildName[eIndex_][3] ;
			else
				return g_strMeasureFildName[eIndex_][1] ;
		}
		break;
	case FEILD_BPos :
	case FEILD_RB :
	case FEILD_PB :
	case FEILD_DB :
	case FEILD_SB :
	case FEILD_ViB :
	case FEILD_VsB :
	case FEILD_LB :
		{
			GATE_CONFIG* _pGate = _process->GetGateInfo(nGroupId_ , setup_GATE_B) ;
			if(_pGate->eMeasure)
				return g_strMeasureFildName[eIndex_][3] ;
			else
				return g_strMeasureFildName[eIndex_][1] ;
		}
		break;
	default:
		return g_strMeasureFildName[eIndex_][1] ;
		break;
	} ;
}

QString CalcMeasurement::GetMeasureValueString (int nGroupId_ , int nLaw_ , FEILD_VALUE_INDEX eIndex_ )
{
	QString _str ; float _fValue ;
	if( Calc(nGroupId_ , nLaw_ , eIndex_ , &_fValue))
		_str.sprintf("%s: NA" , GetMeasureNameString(nGroupId_, eIndex_ ));
	else
		_str.sprintf("%s: %3.1f %s" , GetMeasureNameString(nGroupId_, eIndex_ ) , _fValue ,  g_strMeasureFildUnit[eIndex_][1]);

	return _str ;
}

QString CalcMeasurement::GetMeasureValueSimpleString (int nGroupId_ , int nLaw_ , FEILD_VALUE_INDEX eIndex_ )
{
	QString _str ;
	float _fValue ;
	if( Calc(nGroupId_ , nLaw_ , eIndex_ , &_fValue))
		_str.sprintf("NA");
	else
		_str.sprintf("%3.1f" , _fValue);
	return _str ;
}

QString CalcMeasurement::GetMeasureString(int nGroupId_ , FEILD_VALUE_INDEX eIndex_)
{
	QString _str ;
	_str.sprintf("%s" , GetMeasureNameString(nGroupId_, eIndex_ ))  ;
	return _str ;
}

QString CalcMeasurement::GetMeasureUnit(FEILD_VALUE_INDEX eIndex_ )
{
	QString _str ;
	_str.sprintf("%s" , g_strMeasureFildUnit[eIndex_][1])  ;
	return _str ;
}

QString CalcMeasurement::GetMeasureValue(int nGroupId_ , int nLaw_ , FEILD_VALUE_INDEX eIndex_ )
{
	QString _str ; float _fValue ;
	if( Calc(nGroupId_ , nLaw_ , eIndex_ , &_fValue))
		_str.sprintf("NA");
	else
		_str.sprintf("%3.1f" , _fValue);

	return _str ;
}

