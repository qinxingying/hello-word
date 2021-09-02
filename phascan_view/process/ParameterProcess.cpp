#include "ParameterProcess.h"
#include "configure/const.h"
#include "Limitation.h"
#include <QString>
#include <gHeader.h>
#include "../configure/config_phascan_ii/config.h"
#include "DopplerDrawSScanTrueDepth.h"

extern int currentgroup;
extern int lastgroup;
double FreScale = 400/511.0;
double NFreScale = 200/511.0;
extern int Phascan_Version;
ParameterProcess* g_pParameterProcess = NULL ;

int ParameterProcess::cursorOffset=1;
float CalPeakAmp2( float, int);

float CalculatePeakAmp(float nPeak_, int nRectify_)
{
    if( Phascan_Version == 1 || Phascan_Version == 3 || Phascan_Version == 4 || Phascan_Version == 6 || Phascan_Version == 8)
    {
        return CalPeakAmp( nPeak_, nRectify_);
    }
    else
    {
        return CalPeakAmp2( nPeak_, nRectify_);
    }
}


ParameterProcess* ParameterProcess::Instance()
{
	if(!g_pParameterProcess)
	{
		g_pParameterProcess = new ParameterProcess() ;
	}
	return g_pParameterProcess ;
}


ParameterProcess::ParameterProcess(QObject *parent) :
	QObject(parent)
{
    m_pConfig = DopplerConfigure::Instance();
}

/****************************************************************************
  Description:   向参数中添加一个组参数
  Input:  nGroupId_: 使用该组参数初始化添加组， 如果为“-1”则用默认参数初始化
  Output: 如果成功返回空，否则返回错误说明
*****************************************************************************/
QString ParameterProcess::AddOneGroup(int nGroupId_)
{
	//*****************************
	int _nGroupQty = m_pConfig->common.nGroupQty  ;
	if(_nGroupQty >= setup_MAX_GROUP_QTY)  return QString(tr(" Message : Max Group Quantity is %1!").arg(setup_MAX_GROUP_QTY));
	//**********************
	if(nGroupId_ > _nGroupQty)   return QString(tr(" Message : Template Group Configure does not exist!"));

	if(nGroupId_ < 0)
	{
		m_pConfig->InitGroupConfig( _nGroupQty );
	}
	else
	{
		GROUP_CONFIG* _pConfigDis = &m_pConfig->group[_nGroupQty] ;
		GROUP_CONFIG* _pConfigSrc = &m_pConfig->group[nGroupId_] ;
		memcpy(_pConfigDis , _pConfigSrc , sizeof(GROUP_CONFIG)) ;
	}
	m_pConfig->common.nGroupQty++ ;
	Limitation limit;
	QString _str = limit.IsGroupConfigureAvailible() ;
	if(!_str.isEmpty ())
	{
		m_pConfig->common.nGroupQty-- ;
		GROUP_CONFIG* _pConfigDis = &m_pConfig->group[_nGroupQty] ;
		memset((void*) _pConfigDis , 0 , sizeof(GROUP_CONFIG)) ;
	}
	return _str ;
}
/****************************************************************************
  Description:   删除一个组参数
  Input:  nGroupId_: 删除的组参数ID
  Output: 如果成功返回空，否则返回错误说明
*****************************************************************************/
QString ParameterProcess::DeleteOneGroup(int nGroupId_)
{
	//*****************************
	int _nGroupQty = m_pConfig->common.nGroupQty ;
	if(nGroupId_ > _nGroupQty - 1)   return QString(tr("Group Configure does not exist!"));
	m_pConfig->common.nGroupQty-- ;
	for(int i = nGroupId_ ; i < _nGroupQty - 1 ; i++)
	{
		GROUP_CONFIG* _pConfigDis = &m_pConfig->group[i] ;
		GROUP_CONFIG* _pConfigSrc = &m_pConfig->group[i+1] ;
		memcpy(_pConfigDis , _pConfigSrc , sizeof(GROUP_CONFIG)) ;
	}
	return QString() ;
}


int  ParameterProcess::SetupGain(int nGroupId_ , double fValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.fGain  = fValue_ ;
	return 0 ;
}

int  ParameterProcess::SetupRefGain(int nGroupId_ , double fValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
    group.fRefGain  = fValue_;
	return 0 ;
}

//应该禁止改SampleStart，这个参数是扫查的时候就确定了的
//int  ParameterProcess::SetupSampleStart(int nGroupId_ , double fValue_)
//{
//	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
//	group.fSampleStart  = fValue_ ; //GetSoundPath(nGroupId_ , fValue_) ;
//	qDebug("%d %f %f" , nGroupId_ , fValue_ , group.fSampleStart);
//	return 0 ;
//}

//应该禁止改SampleRange，这个参数是扫查的时候就确定了的
//int  ParameterProcess::SetupSampleRange(int nGroupId_ , double fValue_)
//{
//	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
//	group.fSampleRange  = fValue_ ; //GetSoundPath(nGroupId_ , fValue_) ;
//	qDebug("%d %f %f" , nGroupId_ , fValue_ ,  group.fSampleRange);
//	return 0 ;
//}

int  ParameterProcess::SetupTravelMode(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.eTravelMode  = (setup_TRAVEL_MODE)nValue_ ;
    //qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

setup_TRAVEL_MODE ParameterProcess::getTravelMode(int nGroupId_)
{
    GROUP_CONFIG& group = m_pConfig->group[nGroupId_];
    return group.eTravelMode;
}

int  ParameterProcess::SetupVelocity(int nGroupId_ , double fValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.fVelocity	 = fValue_ ;
    //qDebug("%d %f" , nGroupId_ , fValue_);
	return 0 ;
}

int  ParameterProcess::SetupWedgeDelay(int nGroupId_ , double fValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.nWedgeDelay   = (int)(fValue_ * 1000);
    //qDebug("%d %f" , nGroupId_ , fValue_);
	return 0 ;
}

int  ParameterProcess::SetupTxElementStart(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.nTrigeStart   = nValue_ ;
    //qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

int  ParameterProcess::SetupRxElementStart(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.nReceiveStart   = nValue_ ;
    //qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}


int  ParameterProcess::SetupFilter(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.eFileter   = (setup_FILTER_MODE) nValue_ ;
    //qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

int  ParameterProcess::SetupRectifier(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	group.eRectifier   = (setup_RECTIFIER_MODE) nValue_ ;
    //qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

int  ParameterProcess::SetupVedioOnOff(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	group.bVedioFilter   =  nValue_ ;
    //qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

int  ParameterProcess::SetupPointQty(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	group.nPointQty  =  nValue_ ;
    //qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

int  ParameterProcess::SetupPointQtyAutoMode(int nGroupId_ , int bValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	group.bPointQtyAuto = bValue_ ;
    //qDebug("%d %d" , nGroupId_ , bValue_);
	return 0;
}


int  ParameterProcess::SetupSumGain(int nGroupId_ , double fValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	group.fSumGain  =  fValue_ ;
    //qDebug("%d %f" , nGroupId_ , fValue_);
	return 0 ;
}

int  ParameterProcess::SetupSumGainAutoMode(int nGroupId_ , int bValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	group.bSumGainAuto = bValue_ ;
    //qDebug("%d %d" , nGroupId_ , bValue_);
	return 0;
}

int  ParameterProcess::SetupAverage(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	group.eAveraging  =  (setup_AVERAGE_MODE) nValue_ ;
    //qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

int ParameterProcess::SetupGroupMode(int nGroupId_ , int nValue_)
{
	m_pConfig->GroupModeChanged(nGroupId_ , (setup_GROUP_MODE)nValue_) ;
    //qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

int  ParameterProcess::SetupProbeLoad(int nGroupId_ , PROBE_CONFIG* probe_ , int TxRx_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	PROBE_CONFIG* _probe = &group.probe[TxRx_?1 :0]  ;
	memcpy(_probe , probe_ , sizeof(PROBE_CONFIG)) ;
	return 0 ;
}

int  ParameterProcess::SetupWedgeLoad(int nGroupId_ , WEDGE_CONFIG* wedge_ , int TxRx_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	WEDGE_CONFIG* _wedge = &group.wedge[TxRx_?1 :0]  ;
	memcpy(_wedge , wedge_ , sizeof(WEDGE_CONFIG)) ;
    //qDebug("%d %d SetupWedgeLoad" , nGroupId_ , TxRx_);
	return 0 ;
}

int  ParameterProcess::SetupFocalLaw(int nGroupId_ , LAW_CONFIG* pLaw_)
{
	LAW_CONFIG* _pLaw = &m_pConfig->group[nGroupId_].law ;
	memcpy((void*)_pLaw , (void*) pLaw_ , sizeof(LAW_CONFIG)) ;
	// 计算聚焦法则
	return 0 ;
}

int  ParameterProcess::SetupGateInfo(int nGroupId_ , setup_GATE_NAME gate_ ,GATE_CONFIG* pData_ )
{
	GATE_CONFIG* _pGate= &m_pConfig->group[nGroupId_].gate[gate_]  ;
	memcpy((void*)_pGate , (void*)pData_ , sizeof(GATE_CONFIG))  ;
	return 0 ;
}

int  ParameterProcess::SetupSizingCurve(int /*nGroupId_*/ , CURVES /*curve_*/)
{
	return 0 ;
}


int  ParameterProcess::SetupPart(int nGroupId_ , PART_CONFIG* part_)
{
	PART_CONFIG& _part = m_pConfig->group[nGroupId_].part ;
	memcpy((void*)&_part, (void*)part_, sizeof(PART_CONFIG))  ;
	return 0 ;
}

int  ParameterProcess::SetupPartGeometry(int nGroupId_ , PART_CONFIG* part_)
{
	PART_CONFIG& _part = m_pConfig->group[nGroupId_].part ;
	memcpy((void*)_part.afSize , (void*)part_->afSize , sizeof(float) * 4)  ;
	_part.eGeometry  = part_->eGeometry  ;

	return 0 ;
}

int  ParameterProcess::SetupPartMaterial(int nGroupId_ , int nIndex_)
{
	MATERIAL* _pMaterial =  m_pConfig->m_listMaterial->at(nIndex_) ;
	memcpy((void*)&m_pConfig->group[nGroupId_].part.material , (void*)_pMaterial , sizeof(MATERIAL)) ;
	SetupVelocity(nGroupId_ , _pMaterial->fVelocityLon) ;
	return 0 ;
}
/*
int  ParameterProcess::SetupPartWeld(int nGroupId_, PART_CONFIG* part_)
{
	return 0 ;
}
*/
int  ParameterProcess::SetupWedgePosition(int nGroupId_ , float fScanOffset_ , float fIndexOffset_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	_group.fScanOffset  = fScanOffset_  ;
	_group.fIndexOffset = fIndexOffset_ ;

	return 0 ;
}

int ParameterProcess::SetupWedgeSkewAngle(int nGroupId_ , setup_PROBE_ANGLE eAngle_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	_group.eSkew  = eAngle_  ;
	return 0 ;
}


//设置S扫反射类型
int ParameterProcess::SetupReflectType(int nGroupId_,setup_REFLECT_TYPE index)
{
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
    _group.m_Retype  = index  ;
    return 0 ;
}

//设置S扫1:1显示
int ParameterProcess::SetupReflectShows(int nGroupId_,setup_REFLECT_SHOWS index)
{
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
    _group.m_Shows  = index  ;

    return 0 ;
}

int ParameterProcess::GetShowWeldPart(int nGroupId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	return _group.bShowWeldPart;
}

int ParameterProcess::SetupShowWeldPart(int nGroupId_ , int bShow_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	_group.bShowWeldPart = bShow_ ;
	return 0 ;
}

int  ParameterProcess::SetupMeasureData(int nGroupId_ , int nField_ , int index_ )
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	_group.aeMeasureType[nField_] = index_ ;
	return 0 ;
}

int  ParameterProcess::SetupShowMeasure(int nGroupId_ , int bShow_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	_group.bShowMeasure = bShow_ ;
	return 0 ;
}

void ParameterProcess::GetDefaultMeasure(int nGroupId_, int *defaultValue)
{
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_];
    if(_group.eTxRxMode == setup_TX_RX_MODE_TOFD){//tofd
        defaultValue[0]  = FEILD_TofdDepth1;
        defaultValue[1]  = FEILD_TofdDepth2;
        defaultValue[2]  = FEILD_TofdHeight;
        defaultValue[3]  = FEILD_Sr;
        defaultValue[4]  = FEILD_Sm;
        defaultValue[5]  = FEILD_Smr;
        defaultValue[6]  = FEILD_NONE;
        defaultValue[7]  = FEILD_NONE;
        defaultValue[8]  = FEILD_NONE;
        defaultValue[9]  = FEILD_NONE;
        defaultValue[10] = FEILD_NONE;
        defaultValue[11] = FEILD_NONE;
        defaultValue[12] = FEILD_NONE;
        defaultValue[13] = FEILD_NONE;
    }else{
        if(_group.law.eLawType){//线扫，全聚焦
            defaultValue[0]  = FEILD_A100;
            if(_group.gate[setup_GATE_A].eSynChro == setup_GATE_AYNC_I){
                defaultValue[1]  = FEILD_APos_DEC_IPos;
            }else{
                defaultValue[1]  = FEILD_DA;
            }
            defaultValue[2]  = FEILD_Imr;
            defaultValue[3]  = FEILD_Umr;
            defaultValue[4]  = FEILD_Sr;
            defaultValue[5]  = FEILD_Sm;
            defaultValue[6]  = FEILD_Smr;
            defaultValue[7]  = FEILD_F;
            defaultValue[8]  = FEILD_NONE;
            defaultValue[9]  = FEILD_NONE;
            defaultValue[10] = FEILD_NONE;
            defaultValue[11] = FEILD_NONE;
            defaultValue[12] = FEILD_NONE;
            defaultValue[13] = FEILD_NONE;
        }else{//扇扫
            defaultValue[0]  = FEILD_A100;
            defaultValue[1]  = FEILD_DA;
            defaultValue[2]  = FEILD_ViA;
            defaultValue[3]  = FEILD_Umr;
            defaultValue[4]  = FEILD_Sr;
            defaultValue[5]  = FEILD_Sm;
            defaultValue[6]  = FEILD_Smr;
            defaultValue[7]  = FEILD_sMax;
            defaultValue[8]  = FEILD_SL;
            defaultValue[9]  = FEILD_ZA;
            defaultValue[10] = FEILD_NONE;
            defaultValue[11] = FEILD_NONE;
            defaultValue[12] = FEILD_NONE;
            defaultValue[13] = FEILD_NONE;
        }
    }
}

int  ParameterProcess::GetShowMeasureNumber(int nGroupId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;

	int _nNumber = 0;
    for(int i = 0; i  < 8; i++){
		if(_group.aeMeasureType[i]) {
			_nNumber++;
		}
	}
	return _nNumber;
}

int  ParameterProcess::SetupCursor(int nGroupId_ , setup_CURSOR_TYPE eType_ , float fValue_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	_group.afCursor[eType_] = fValue_ ;
	return 0 ;
}

int  ParameterProcess::SetupShowCursor(int nGroupId_ , int bShow_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	_group.bShowCursor = bShow_ ;
	return 0 ;
}

int  ParameterProcess::SetupCurrentLawCursor(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_]  ;
	_group.afCursor[setup_CURSOR_LAW]  = nValue_ ;
    LAW_CONFIG _law = _group.law ;
    float _fAngleStart = _law.nAngleStartRefract / 10.0 ;
    float _fAngleStep = _law.nAngleStepRefract/10.0;
    int tmpCScanLinePos =  _fAngleStart + nValue_*_fAngleStep;
    _group.afCursor[setup_CURSOR_C_ANGLE]  = tmpCScanLinePos ;
    //qDebug("%d %d SetupWedgeLoad" , nGroupId_ , nValue_);
	return 0 ;
}

int  ParameterProcess::SetupPalette(int nGroupId_, PALETTE_NAME eName_ , void* pColor_)
{
	if(eName_>= PALETTE_NAME_MAX) return -1 ;
	GROUP_COLOR& _color = m_pConfig->group[nGroupId_].color  ;
	void* _pColor ;
	switch(eName_)
	{
	case	PALETTE_AMP :
		_pColor = (void*)_color.Amp  ;
		break;
	case	PALETTE_THICKNESS:
		 _pColor = (void*)_color.Thickness  ;
		break;
	case	PALETTE_RECTIFY:
		 _pColor = (void*)_color.Rf  ;
		break;
	default:
		return -1 ;
		break;
	}
	memcpy(_pColor , pColor_ , 256 * 3)  ;
	return 0;
}

int  ParameterProcess::SetupAScanColor(int nGroupId_ , int nLineId_ , int eColor_)
{
	GROUP_COLOR& _color = m_pConfig->group[nGroupId_].color  ;
	_color.anColor[nLineId_]  = eColor_  ;
	return 0;
}
//######################################################################
//######################################################################
//######################################################################
//######################################################################
int  ParameterProcess::SetupScanPos(float fScanPos_)
{

	SCANNER& _scaner = m_pConfig->common.scanner ;
	float _fPos = fScanPos_;

    if(_fPos < _scaner.fScanStart2)
        _fPos = _scaner.fScanStart2;

//    if(_fPos > _scaner.fScanStop)
//        _fPos = _scaner.fScanStop;
    if(_fPos > _scaner.fScanend)
        _fPos = _scaner.fScanend;

	_scaner.fScanPos = _fPos;
//    if((_scaner.fScanPos < _scaner.fScanStart2)&&(_scaner.fScanPos >= _scaner.fScanStart))
//        _scaner.fScanStart2 = _scaner.fScanPos;
//    if((_scaner.fScanPos > _scaner.fScanend) && (_scaner.fScanPos <= _scaner.fScanStop))
//        _scaner.fScanend = _scaner.fScanPos;
    g_pMainWnd->UpdateSlider();
	return 0;
	//return -1;
}

int  ParameterProcess::SetupScanType(setup_SCAN_TYPE eType_)
{
	SCANNER& _scan = m_pConfig->common.scanner  ;
	_scan.eScanType = eType_ ;
	return 0;
}

int  ParameterProcess::SetupScanMode(setup_SCAN_MODE eMode_)
{
	SCANNER& _scan = m_pConfig->common.scanner  ;
	_scan.eScanMode = eMode_;
	return 0;
}

int  ParameterProcess::SetupEncoderType(setup_ENCODER_TYPE eType_)
{
	SCANNER& _scan = m_pConfig->common.scanner  ;
    _scan.eScanEncoderType = eType_ ;
	return 0;
}

int  ParameterProcess::SetupPrf(float fValue_)
{
	SCANNER& _scan = m_pConfig->common.scanner  ;
	_scan.fPrf = fValue_ ;
	return 0;
}

int  ParameterProcess::SetupScanArea(float afValue_[6])
{
	SCANNER& _scan = m_pConfig->common.scanner  ;
	_scan.fScanStart  = afValue_[0]  ;
	_scan.fIndexStart = afValue_[1]  ;
    _scan.fScanStop   = afValue_[2]  ;
	_scan.fIndexStop  = afValue_[3]  ;
	_scan.fScanStep   = afValue_[4]  ;
	_scan.fIndexStep  = afValue_[5]  ;
	return 0;
}

int  ParameterProcess::SetupEncoderConfigure(int eEncoder_, ENCODER_CONFIG* pEncoder_)
{
	SCANNER& _scan = m_pConfig->common.scanner  ;
	memcpy((void*)&_scan.encoder[eEncoder_] , (void*)pEncoder_ , sizeof(ENCODER_CONFIG))  ;
	return 0;
}

int  ParameterProcess::SetupPAVoltage(setup_VOLTAGE_MODE eVoltage_)
{
	INSTRUMENT_CONFIG& _instrument = m_pConfig->common.instrument ;
	_instrument.eVoltagePA  = eVoltage_ ;
	return 0;
}

int  ParameterProcess::SetupUTVoltage(setup_VOLTAGE_MODE eVoltage_)
{
	INSTRUMENT_CONFIG& _instrument = m_pConfig->common.instrument ;
	_instrument.eVoltageUT  = eVoltage_ ;
	return 0;
}

//int  ParameterProcess::SetupPATxRxMode(setup_TX_RX_MODE eMode_)
//{
//	INSTRUMENT_CONFIG& _instrument = m_pConfig->common.instrument ;
//	_instrument.eTxRxModePA  = eMode_ ;
//	return 0;
//}

//int  ParameterProcess::SetupUTTxRxMode(setup_TX_RX_MODE eMode_)
//{
//	INSTRUMENT_CONFIG& _instrument = m_pConfig->common.instrument ;
//	_instrument.eTxRxModeUT  = eMode_ ;
//	return 0;
//}


//######################################################################
//######################################################################
//######################################################################
//######################################################################

int ParameterProcess::GetGroupDataSize(int nGroupId_) const
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	int _nPointQty = _group.nPointQty ;
    int _nBeamQty  = GetGroupLawQtyForPosition(nGroupId_) ;
    int _nRet;
//    if(_group.law.eLawType == setup_LAW_TYPE_TFM){
//        _nRet = _nPointQty * _nBeamQty + setup_DATA_PENDIX_LENGTH;
//    }else{
        _nRet = (setup_DATA_PENDIX_LENGTH + _nPointQty) * _nBeamQty;
//    }

	return _nRet;
}

#include <configure/const.h>
int ParameterProcess::GetTotalDataSize() const
{
	int _nGroupQty = m_pConfig->common.nGroupQty  ;
	int _nRet = setup_DATA_OFFSET ;
    if(Config::instance()->is_phascan_ii()) {
        /* not align 1024 for mercury data file!! */
        _nRet = 0;
        for(int i = 0 ; i < _nGroupQty ; i++)
        {
            _nRet += GetGroupDataSize(i) ;
        }
        /* 4 byte align */
        _nRet  = (_nRet + 4 - 1) / 4  ;
        _nRet  = 4 * _nRet ;
        return _nRet;
    }
	for(int i = 0 ; i < _nGroupQty ; i++)
	{
		_nRet += GetGroupDataSize(i) ;
	}
	_nRet  = (_nRet + setup_DATA_ALIAN - 1) / setup_DATA_ALIAN  ;
	_nRet  = setup_DATA_ALIAN * _nRet ;
	return _nRet ;
}

int ParameterProcess::GetGroupLawQty(int nGroupId_) const
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	int _ret = 1 ;
	if(_group.eGroupMode == setup_GROUP_MODE_PA)
	{
		LAW_CONFIG& _law = _group.law ;
		if(_law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
		{
			_ret = (_law.nAngleStopRefract - _law.nAngleStartRefract) / _law.nAngleStepRefract + 1;
		}
        else if(_law.eLawType == setup_LAW_TYPE_LINEAR)
		{
			_ret = (_law.nLastElemFir - _law.nFirstElemFir - _law.nElemQtyFir + 1) / _law.nElemStepFir + 1 ;
        }else{
            _ret = (_law.nLastElemFir - _law.nFirstElemFir) / _law.nElemStepFir + 1;
        }
	}
	return _ret;
}

int  ParameterProcess::GetGroupLawQtyForPosition(int nGroupId_) const
{
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
    int _ret = 1 ;
    if(_group.eGroupMode == setup_GROUP_MODE_PA)
    {
        LAW_CONFIG& _law = _group.law ;
        if(_law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
        {
            _ret = (_law.nAngleStopRefract - _law.nAngleStartRefract) / _law.nAngleStepRefract + 1;
        }
        else if(_law.eLawType == setup_LAW_TYPE_LINEAR)
        {
            _ret = (_law.nLastElemFir - _law.nFirstElemFir - _law.nElemQtyFir + 1) / _law.nElemStepFir + 1 ;
        }else{
            _ret = (_law.nLastElemFir - _law.nFirstElemFir) / _law.nElemStepFir + 1;
        }

        //耦合监控有一条beam用于耦合监控
        if(_group.coupleMonitoringState)
        {
            _ret++;
        }
    }else{
        if(_group.coupleMonitoringState){
            _ret++;
        }
    }
    return _ret;
}

int ParameterProcess::GetTotalLawQty() const
{
	int _nGroupQty = m_pConfig->common.nGroupQty  ;
	int _nRet = 0 ;
	for(int i = 0 ; i < _nGroupQty ; i++)
	{
		_nRet += GetGroupLawQty(i) ;
	}
	return _nRet ;
}

int ParameterProcess::GetScanIndexNum()
{
    SCANNER& _scaner = m_pConfig->common.scanner;
    int _index;
    if(_scaner.eScanEncoderType) {
        _index = (_scaner.fScanend - _scaner.fScanStart2) / _scaner.fScanStep ;
    } else {
        _index =  (_scaner.fScanend * _scaner.fPrf - _scaner.fScanStart2 *_scaner.fPrf ) / _scaner.fScanStep;
    }
    return _index;
}

int ParameterProcess::GetGroupQty() const
{
	return m_pConfig->common.nGroupQty ;
}

float  ParameterProcess::GetRefGainScale(int nGroupId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	float ret = pow(10 , _group.fRefGain / 20) ;
	return ret ;
}

int ParameterProcess::getWaveHalfValue()
{
    if( Phascan_Version == 1 || Phascan_Version == 3 || Phascan_Version == 4 || Phascan_Version == 6 || Phascan_Version == 8)
    {
        return 128;
    }
    else
    {
        return 256;
    }
}

int ParameterProcess::correctionPdata( WDATA value)
{
    if( Phascan_Version == 1 || Phascan_Version == 3 || Phascan_Version == 4 || Phascan_Version == 6 || Phascan_Version == 8)
    {
        return value;
    }
    else
    {
        return (int)value * 2 | 1;
    }
}

bool ParameterProcess::is200Data()
{
    if( Phascan_Version == 1 || Phascan_Version == 3 || Phascan_Version == 4 || Phascan_Version == 6 || Phascan_Version == 8){
        return false;
    }else{
        return true;
    }
}

WDATA ParameterProcess::GetRefGainScaleData(WDATA wData_, float fScale_, bool bRectify_)
{
    int _iData = wData_;
    int WAVE_HALF;

    WAVE_HALF = getWaveHalfValue();
    _iData = correctionPdata(wData_);

	if(bRectify_)
	{
	_iData  = _iData - WAVE_HALF ;
    _iData = _iData * fScale_ + 128;
	if(_iData > WAVE_MAX )	_iData = WAVE_MAX ;
	if(_iData < 0 )		_iData = 0   ;
	}
	else
	{
	_iData = _iData * fScale_ ;
	if(_iData > WAVE_MAX)	_iData = WAVE_MAX ;
	}
	return _iData;
}
unsigned int* ParameterProcess::GetGroupBeamDelay(int nGroupId_) const
{
	return m_pConfig->group[nGroupId_].anBeamDelay  ;
}

unsigned int  ParameterProcess::GetGroupWedgeDelay(int nGroupId_) const
{
	return m_pConfig->group[nGroupId_].nWedgeDelay ;
}

unsigned int  ParameterProcess::GetGroupPulserWidth(int nGroupId_) const
{
	return m_pConfig->group[nGroupId_].nPulserWidth ;
}

void ParameterProcess::GetCScanThicknessRangeTime(int nGroupId_ , int* nStart_ , int* nStop_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	float _fVelocity = _group.fVelocity / 1000.0;
	float _nThickMin = _group.fMinThickness ;
	float _nThickMax = _group.fMaxThickness ;

	*nStart_ = 200 * _nThickMin / _fVelocity  ;
	*nStop_  = 200 * _nThickMax / _fVelocity  ;
}

float ParameterProcess::GetCScanThicknessStart(int nGroupId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	float _fThickMin = _group.fMinThickness ;
	return _fThickMin;
}

float ParameterProcess::GetCScanThicknessStop(int nGroupId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	float _fThickMax = _group.fMaxThickness ;
	return _fThickMax ;
}

int  ParameterProcess::GetGroupDataOffset(int nGroupId_) const
{
	int _nGroupOffset = setup_DATA_OFFSET  ;
    if(Config::instance()->is_phascan_ii()) {
        _nGroupOffset = 0;
    }
	for(int i = 0 ; i < nGroupId_; i++)
		_nGroupOffset += GetGroupDataSize(i)  ;

	return _nGroupOffset ;
}

int  ParameterProcess::GetScanIndexPos() const
{
	SCANNER& _scaner = m_pConfig->common.scanner ;
	int _nScanPos = SAxisDistToIndex(_scaner.fScanPos);
	return _nScanPos ;
}

/*!
  \brief 二维扫查将当前位置转换成scaner数据的索引位置

  \return 索引位置
*/
int  ParameterProcess::transforRasterPosToMarker() const
{
    SCANNER& _scaner = m_pConfig->common.scanner;
    int _nScanIndex  = SAxisDistToIndex(_scaner.fScanPos);
    int _nIndexIndex = TransforIndexPosToIndex(_scaner.fIndexPos);
    int scanQty = ( _scaner.fScanStop - _scaner.fScanStart) / _scaner.fScanStep + 0.5;
    int markerPos = _nIndexIndex*scanQty + _nScanIndex;
    return markerPos;
}

int  ParameterProcess::GetScanIndexStart2() const
{
    SCANNER& _scaner = m_pConfig->common.scanner ;
    int _nScanStart2 = SAxisDistToIndex(_scaner.fScanStart2);
    return _nScanStart2 ;
}

/*!
  \brief 将超声轴坐标值转换为数据索引index

  \param fDist_ 编码器时单位为mm,时间编码时为s

  \return 数据索引index
*/
int ParameterProcess::SAxisDistToIndex(float fDist_) const
{
	SCANNER& _scaner = m_pConfig->common.scanner ;
	int _index;
    if(_scaner.eScanEncoderType) {
        if(fDist_ < _scaner.fScanStart)
        {
            fDist_ = _scaner.fScanStart;
        }
        if(fDist_ > _scaner.fScanStop)
        {
            fDist_ = _scaner.fScanStop;
        }
        _index = ceil((fDist_ - _scaner.fScanStart) / _scaner.fScanStep) ;
	} else {
        if( fDist_ < _scaner.fScanStart2)
        {
            fDist_ = _scaner.fScanStart2;
        }
        if( fDist_ > _scaner.fScanend){
            fDist_ = _scaner.fScanend;
        }
        _index =  ceil((fDist_ * _scaner.fPrf  - _scaner.fScanStart) / _scaner.fScanStep);
	}
	return _index;
}

//fStop 编码器时单位为mm,时间编码时为s
int ParameterProcess::SAxisstoptoIndex(float fStop) const
{
    SCANNER& _scaner = m_pConfig->common.scanner ;
    int _index;
    if(_scaner.eScanEncoderType) {
        _index = (fStop - _scaner.fScanStart2) / _scaner.fScanStep ;
    } else {
        _index =  (fStop * _scaner.fPrf - _scaner.fScanStart2 *_scaner.fPrf ) / _scaner.fScanStep;
    }
    return _index;
}

float ParameterProcess::GetIndexStartPos() const
{
    SCANNER& _scaner = m_pConfig->common.scanner;
    return _scaner.fIndexStart;
}

float ParameterProcess::GetIndexEndPos() const
{
    SCANNER& _scaner = m_pConfig->common.scanner;
    return _scaner.fIndexStop;
}

/*!
  \brief 将二维扫查的距离单位mm转换成步进方向的索引值

  \param fPos 在C扫中步进轴方向的位置单位mm

  \return 步进索引值
*/
int ParameterProcess::TransforIndexPosToIndex(float fPos) const
{
    SCANNER& _scaner = m_pConfig->common.scanner;
    int _index;
    if( fPos < _scaner.fIndexStart){
        fPos = _scaner.fIndexStart;
    }
    if( fPos > _scaner.fIndexStop){
        fPos = _scaner.fIndexStop;
    }
    _index = ( fPos - _scaner.fIndexStart) / _scaner.fIndexStep;
    return _index;
}

/*!
  \brief 将二维扫查的步进索引值转换为距离值mm

  \param fIndex 步进方向的索引值

  \return C扫步进轴对应位置，单位mm
*/
float ParameterProcess::TransforIndexIndexToPos(int fIndex) const
{
    SCANNER& _scaner = m_pConfig->common.scanner;
    float _Pos;
    if(fIndex <0){
        fIndex = 0;
    }
    _Pos = _scaner.fIndexStart + fIndex*_scaner.fIndexStep;
    if(_Pos > _scaner.fIndexStop){
        _Pos = _scaner.fIndexStop;
    }
    return _Pos;
}

/*!
  \brief 将数据索引index转换为超声轴坐标值

  \param index_ 数据索引index

  \return 编码器时单位为mm,时间编码时为s
*/
float ParameterProcess::SAxisIndexToDist(int index_) const
{
	SCANNER& _scaner = m_pConfig->common.scanner ;
	float _fPos;
    if(_scaner.eScanEncoderType) {
		_fPos = index_ * _scaner.fScanStep + _scaner.fScanStart;
	} else {
        _fPos = (index_ * _scaner.fScanStep + _scaner.fScanStart) / _scaner.fPrf;
	}
    if(_fPos > _scaner.fScanend){
        _fPos = _scaner.fScanend;
    }

	return _fPos;
}

int  ParameterProcess::GetGroupLawDataOffset(int nGroupId_ , int nLawId_) const
{
    int _nLawOffset;
//    if(m_pConfig->group[nGroupId_].law.eLawType == setup_LAW_TYPE_TFM){
//        _nLawOffset  = nLawId_ * m_pConfig->group[nGroupId_].nPointQty;
//    }else{
        _nLawOffset  = nLawId_ * (m_pConfig->group[nGroupId_].nPointQty + setup_DATA_PENDIX_LENGTH);
    //}
	return _nLawOffset ;
}

WDATA* ParameterProcess::GetDataPointer()
{
	return m_pConfig->GetFileDataPoint() ;
}

int ParameterProcess::GetRealScanIndex(int nGroupId_, int nScanPos_)
{
	U8*	 _pMarker = GetScanMarker(nGroupId_);
	int _nScanPos = nScanPos_;
	int _nScanOff = GetScanOff(nGroupId_) ;

    if(!_pMarker[_nScanPos]){
		if(_nScanPos < _nScanOff) {
			_nScanPos = _nScanOff;
			int _nScanMax = GetScanMax();
			while(_nScanPos < _nScanMax) {
				if(_pMarker[_nScanPos]) {
					break;
				}
				_nScanPos++;
			}
		} else {
			while(_nScanPos > _nScanOff) {
				if(_pMarker[_nScanPos]) {
					break;
				}
				_nScanPos--;
			}
		}
	}

	int _nRealMax = GetRealScanMax();
	int    _index = _nScanPos - _nScanOff;

	if(_index < 0)			_index = 0;
	if(_index >= _nRealMax)	_index = _nRealMax - 1;

	return _index;
}

WDATA* ParameterProcess::GetShadowDataPointer()
{
	return m_pConfig->GetShadowDataPoint();
}

WDATA* ParameterProcess::GetDataAbsolutePosPointer(int nGroupId_, int nScanPos_, int nLawId_, WDATA* pSource_)
{
	if(!pSource_)
		return NULL;
	if(nScanPos_ < 0)
		return NULL;
	if(nScanPos_ >= GetScanMax())
		return NULL;

	int _nFrameOffset = GetTotalDataSize() ;
	int _nGroupOffset = GetGroupDataOffset(nGroupId_);
	int   _nLawOffset = GetGroupLawDataOffset(nGroupId_ , nLawId_) ;
	int	     _nOffset = _nGroupOffset + _nLawOffset  ;
	int        _index = GetRealScanIndex(nGroupId_, nScanPos_);

	WDATA* _pData = pSource_ + _nOffset + _nFrameOffset * _index;
	return _pData;
}

//用于测试，打印出指定位置A扫数据
void ParameterProcess::testOutputSrcData(int nGroupId_, int nScanPos_, int nLawId_)
{
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_];
    int _nPointQty = _group.nPointQty;
    WDATA* _pData  = GetShadowDataPointer();
    int _nFrameOffset = GetTotalDataSize();
    int _nGroupOffset = GetGroupDataOffset(nGroupId_);
    int   _nLawOffset = GetGroupLawDataOffset(nGroupId_ , nLawId_);
    int	     _nOffset = _nGroupOffset + _nLawOffset;
    int        _index = GetRealScanIndex(nGroupId_, nScanPos_);
    _pData = _pData + _nOffset + _nFrameOffset * _index;
    QVector<unsigned char> buff;
    for(int i = 0; i < _nPointQty; i++){
        buff.append(_pData[i]);
    }
    qDebug()<<"output"<<buff;
}

float ParameterProcess::GetSizingCurveRefAmp(int nGroupId_, int nBeamNo_,  int nPoint_)
{
	float _fRefAmp = -1;
	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_]  ;
	CURVES& _curve = _pGroup->curve;

	if(_pGroup->curve.eType == setup_CURVE_TYPE_NULL  || nPoint_ > _curve.nPointQty)
		return _fRefAmp;

	switch(_pGroup->curve.eType)
	{
	case setup_CURVE_TYPE_DAC:{
			int   _nBeamNo = nBeamNo_;
			float _fRefAmpOff = pow(10, _curve.fAmpOffsetAmp / 2.0f);
			if(nPoint_ > 0)	{
				float  _fAmp = _fRefAmpOff * _curve.faAmp[_nBeamNo][nPoint_-1];
				_fRefAmp = _fAmp;
			} else {
				float _fAmp0 = _fRefAmpOff * _curve.faAmpRef[_nBeamNo] * 100.0;
				_fRefAmp = _fAmp0;
			}
		}
		break;
	case setup_CURVE_TYPE_LINEAR_DAC:{
			if(nPoint_ == 0) {
				_fRefAmp = _curve.fMatAtten;
			} else if(nPoint_ == 1) {
				_fRefAmp = DistNsToMm(nGroupId_, _curve.nLinearDelay);
			} else {
				_fRefAmp = 0;
			}
		}
		break;
	case setup_CURVE_TYPE_TCG:{
			if(nPoint_ > 0)
			{
				int   _nBeamNo = nBeamNo_;
				float _fRefAmpOff = pow(10, _curve.fAmpOffsetAmp / 2.0f);
				float _H0 = _fRefAmpOff * _curve.faAmpRef[_nBeamNo] * (float)WAVE_MAX;
				float _H1 = _fRefAmpOff * _curve.faAmp[_nBeamNo][nPoint_-1] * (float)WAVE_MAX / 100.0f;
				_fRefAmp = fabs(20 * (log10(_H0) - log10(_H1)));
			}
			else
			{
				_fRefAmp = 0;
			}
		}
		break;
	default:
		break;
	}

	return _fRefAmp;
}

void ParameterProcess::PutRecDataToShadow(int nGroupId_)
{
	WDATA* _pSource = GetDataPointer();
	WDATA*   _pDest = GetShadowDataPointer();
	int   _nScanOff = GetScanOff(nGroupId_);
	GroupDataMove(nGroupId_, _pSource, _pDest, _nScanOff, _nScanOff);
}

void ParameterProcess::GroupDataMove(int nGroupId_, WDATA* pSource_, WDATA* pDest_, int nSourceOff, int nDestOff_)
{
	int _nGroupSize = GetGroupDataSize(nGroupId_) ;
	//int _nLaw = GetGroupLawQty(nGroupId_);
	int _nRealScanMax = GetRealScanMax();

	WDATA* _pS, *_pD;
	for(int i = 0; i < _nRealScanMax; i++)
	{
		_pS = GetDataAbsolutePosPointer(nGroupId_, i + nSourceOff, 0, pSource_);
		_pD = GetDataAbsolutePosPointer(nGroupId_, i + nDestOff_, 0, pDest_);
		//if(_pS && _pD)
			memcpy(_pD, _pS, _nGroupSize);
	}
}

float CalPeakAmp2(float nPeak_, int nRectify_)
{
    float amp;
    if(!nRectify_)
    {
       return amp = nPeak_ * FreScale - 200;
    }
    else
    {
        return amp = nPeak_ * NFreScale;
    }
}

float ParameterProcess::GetPeakTraceHeight(int nGroupId_, int nScanPos_, int nLawId_, float fUDist_)
{
	WDATA* _pShadow = GetShadowDataPointer();
	WDATA*   _pData = GetDataAbsolutePosPointer(nGroupId_, nScanPos_, nLawId_, _pShadow);
	float	_fDist = fUDist_;

	if(_pData == NULL)
	return 0;

//	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_]  ;
//	if(_pGroup->eGroupMode == setup_GROUP_MODE_PA)
//	{
//		float _Angle  = DEGREE_TO_ARCH(GetLawAngle(nGroupId_ , nLawId_)) ;
//		_fDist /= cos(_Angle);
//	}

	int	  _index = DistMmToDotPos(nGroupId_ , nLawId_, _fDist);
	int    _iQty = GetGroupPointQty(nGroupId_);
	if(_index < 0 || _index >= _iQty) {
		return 0;
	}
	F32	_fScale    = GetRefGainScale(nGroupId_) ;
    bool _bRectify = (GetRectifierMode(nGroupId_) == setup_RECTIFIER_RF );
    //F32	 _fData    = GetRefGainScaleData(_pData[_index], _fScale, _bRectify);

    if(Phascan_Version == 1 || Phascan_Version == 3 || Phascan_Version == 4 || Phascan_Version == 6 || Phascan_Version == 8)
    {
        F32	 _fData    = GetRefGainScaleData(_pData[_index], _fScale, _bRectify);
        int bRectify_  = GetRectifierMode(nGroupId_);

        return CalPeakAmp(_fData, bRectify_);
    }
    else
    {
        F32 _iData = _pData[_index] * 2 + 1;
        if(_bRectify)
        {
        _iData  = _iData - 256 ;
        _iData = _iData * _fScale + 256;
        if(_iData < 0 )		_iData = 0   ;
        }
        else
        {
        _iData = _iData * _fScale ;
        }
        int bRectify_  = GetRectifierMode(nGroupId_);

        return CalPeakAmp2(_iData, bRectify_);
    }
}

int SearchPeakFront(WDATA* pData_, int* _pPos, int iStart_, int iEnd_, int iHeight_, bool bRectify_, int nPointQty_)
{
	if(!pData_) return 0;

	if(iStart_ < 0) {
		iStart_ = 0;
	}
	if(iEnd_ < 0) {
		iEnd_ = 0;
	}
//	if(iEnd_ >= nPointQty_) {
//		iEnd_ = nPointQty_ - 1;
//	}
	if(iStart_ > iEnd_) {
		iStart_ = iEnd_;
	}
	int _iS = iStart_;
    int _iE;
    if(iEnd_ >= nPointQty_) {
        _iE = nPointQty_ - 1;
    } else {
        _iE = iEnd_;
    }
	int _iH = iHeight_;

	int _iFro = 0;//pData_[iStart_];
	int _iTmp = 0;
    int _iPos = iEnd_;

    WDATA* tempData_=pData_;
    ParameterProcess* _process = ParameterProcess::Instance();
    int _nFrameOffset = _process->GetTotalDataSize() ;//一帧数据偏移量

	if(!bRectify_) {// 射频
		int mode = 0;
        if(iHeight_ > 127.5)
			mode = 1;

		if(!mode) {
			for(int i = _iS; i < _iE; i++) {

                _iTmp = ParameterProcess::correctionPdata( pData_[i]);
				if(_iTmp <= _iH) {
					_iFro = _iTmp;
					_iPos = i;
					break;
				}
			}
		} else {
			for(int i = _iS; i < _iE; i++) {

                _iTmp = ParameterProcess::correctionPdata(pData_[i]);
				if(_iTmp >= _iH) {
					_iFro = _iTmp;
					_iPos = i;
					break;
				}
			}
		}
	} else {

        for(int j=0;j<ParameterProcess::cursorOffset;j++)
        {

         pData_=tempData_+j*_nFrameOffset;
		for(int i = _iS; i < _iE; i++) {

            _iTmp = ParameterProcess::correctionPdata(pData_[i]);
			if(_iTmp >= _iH) {
				_iFro = _iTmp;
				_iPos = i;
				break;
			}
         }
       }
	}

    *_pPos = _iPos;
	return _iFro;
}

int SearchPeakAmp(WDATA* pData_, int* _pPos, int iStart_, int iEnd_, bool bRectify_, int nPointQty_)
{
	if(!pData_) return 0;

	if(iStart_ < 0) {
        iStart_ = 0;
	}
	if(iEnd_ < 0) {
		iEnd_ = 0;
	}
//	if(iEnd_ >= nPointQty_) {
//		iEnd_ = nPointQty_ - 1;
//	}
	if(iStart_ > iEnd_) {
		iStart_ = iEnd_;
	}
	int _iS = iStart_;
    int _iE;
    if(iEnd_ >= nPointQty_) {
        _iE = nPointQty_ - 1;
    } else {
        _iE = iEnd_;
    }

	int _iAmp = 0;
	int _iTmp = 0;
	int _iPos = 0;
    int WAVE_HALF;
    WDATA* tempData_=pData_;

    WAVE_HALF = ParameterProcess::getWaveHalfValue();
    ParameterProcess* _process = ParameterProcess::Instance();
    int _nFrameOffset = _process->GetTotalDataSize() ;//一帧数据偏移量
	if(!bRectify_) {// 射频
        int _iMax = 0;
        int _iData = 0;
        for(int i = _iS; i < _iE; i++) {
            _iTmp = ParameterProcess::correctionPdata( pData_[i]);
            _iData = abs(_iTmp - WAVE_HALF);

            if(_iData > _iMax) {
                _iMax = _iData;
                _iAmp = _iTmp;
                _iPos = i;
            }
        }
	} else {
        for(int j=0;j<ParameterProcess::cursorOffset;j++)
        {
        pData_=tempData_+j*_nFrameOffset;

        for(int i = _iS; i < _iE; i++) {
            _iTmp = ParameterProcess::correctionPdata( pData_[i]);

            if(_iTmp > _iAmp) {
                _iAmp = _iTmp;
                _iPos = i;
            }
          }
       }

	}
	*_pPos = _iPos;
	return _iAmp;
}

bool ParameterProcess::GetGatePeakInfos(int nGroupId_, int nScanPos_, int nLawId_, PEAK_CONFIG* pInfo_)
{
	WDATA* _pData  = GetShadowDataPointer();
//	if(!_pData) return false;

	int    _nPointQty = GetGroupPointQty(nGroupId_);

	int _nFrameOffset = GetTotalDataSize() ;
	int _nGroupOffset = GetGroupDataOffset(nGroupId_);
    int _nLawSize;
//    if(m_pConfig->group[nGroupId_].law.eLawType == setup_LAW_TYPE_TFM){
//        _nLawSize = _nPointQty;
//    }else{
        _nLawSize = _nPointQty + setup_DATA_PENDIX_LENGTH;
    //}

        float _mScanPos;
        ParameterProcess* _process = ParameterProcess::Instance();
        DopplerConfigure* _pConfig = DopplerConfigure::Instance();
        GROUP_CONFIG& _group = _pConfig->group[nGroupId_];

        if( _group.m_mode==D_MODE){

            if(_group.afCursor[ setup_CURSOR_S_MES ]> _group.afCursor[setup_CURSOR_S_REF]&&_group.afCursor[ setup_CURSOR_S_MES ]<m_pConfig->comTmp.nRecMax)
             _mScanPos= _group.afCursor[ setup_CURSOR_S_REF ];
            else if(_group.afCursor[ setup_CURSOR_S_MES ]< _group.afCursor[setup_CURSOR_S_REF]&&_group.afCursor[ setup_CURSOR_S_REF ]<m_pConfig->comTmp.nRecMax)
              _mScanPos= _group.afCursor[ setup_CURSOR_S_MES ];

            nScanPos_ = _process->SAxisDistToIndex(_mScanPos);
         }

    int _index = GetRealScanIndex(nGroupId_, nScanPos_);

	if(_pData) {
		_pData += (_nFrameOffset * _index + _nGroupOffset + nLawId_ * _nLawSize);
	}
	GetGatePeakInfos(nGroupId_, _pData, nLawId_, pInfo_);
	return true;
}

//计算闸门内各个参数的值，用于显示测量值
bool ParameterProcess::GetGatePeakInfos(int nGroupId_, WDATA* pData_, int nLawId_, PEAK_CONFIG* pInfo_)
{
//	if(!pData_) return false;
	memset(pInfo_, 0x00, 3*sizeof(PEAK_CONFIG));
    DopplerConfigure* m_pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG* config = &(m_pConfig->group[nGroupId_]);

    int      _nPointQty = GetGroupPointQty(nGroupId_);
    int       _nRectify = GetRectifierMode(nGroupId_);
    float _fSampleStart, _fSampleRange, _fScale;
    float _fDist, _fEdge;
    float _fAngle  = DEGREE_TO_ARCH(GetLawAngle(nGroupId_ , nLawId_)) ;
    float _fThick  = GetPartThickness(nGroupId_);
    float _fSin    = sin(_fAngle);
    float _fCos    = cos(_fAngle);
    float _fIRadius, _fORadius, _fSstep, _fLstep;

    if(config->m_mode==D_MODE&&config->afCursor[ setup_CURSOR_S_MES ]<m_pConfig->comTmp.nRecMax&& config->afCursor[setup_CURSOR_S_REF]<m_pConfig->comTmp.nRecMax)
       {
        cursorOffset=config->afCursor[ setup_CURSOR_S_MES ]- config->afCursor[setup_CURSOR_S_REF];
       if(cursorOffset<0)cursorOffset=-cursorOffset;
       if(cursorOffset==0)cursorOffset=1;

       }else{
        cursorOffset=1;
    }

    if( config->part.eGeometry == setup_PART_GEOMETRY_OD){
        if (config->part.weldFormat == PHASCAN_II_FORMAT && config->part.weld_ii.eWeldDir == CIRC) {
            _fSampleStart = GetSampleStart(nGroupId_ , nLawId_);
            _fSampleRange = GetSampleRange(nGroupId_ , nLawId_);
            _fScale  = _nPointQty / _fSampleRange;
        } else {
            _fSampleStart = GetSampleStart(nGroupId_ , nLawId_);
            _fSampleRange = GetSampleRange(nGroupId_ , nLawId_);
            _fScale  = _nPointQty / _fSampleRange;
            _fIRadius = config->part.afSize[3] / 2 - _fThick;
            _fORadius = config->part.afSize[3] / 2;
            _fSstep = _fORadius * _fCos - sqrt( _fIRadius * _fIRadius - _fORadius * _fORadius * _fSin * _fSin);
            _fLstep = ( asin( _fORadius * _fSin / _fIRadius) - _fAngle) * _fORadius;
        }

    }else if( config->part.eGeometry == setup_PART_GEOMETRY_ID){
        if (config->part.weldFormat == PHASCAN_II_FORMAT && config->part.weld_ii.eWeldDir == CIRC) {
            _fSampleStart = GetSampleStart(nGroupId_ , nLawId_);
            _fSampleRange = GetSampleRange(nGroupId_ , nLawId_);
            _fScale  = _nPointQty / _fSampleRange;
        } else {
            _fSampleStart = GetSampleStart(nGroupId_ , nLawId_);
            _fSampleRange = GetSampleRange(nGroupId_ , nLawId_);
            _fScale  = _nPointQty / _fSampleRange;
            _fIRadius = config->part.afSize[3] / 2;
            _fORadius = config->part.afSize[3] / 2 + _fThick;
            _fSstep = sqrt( _fORadius * _fORadius - _fIRadius * _fIRadius * _fSin * _fSin) - _fIRadius * _fCos;
            _fLstep = ( _fAngle - asin( _fIRadius * _fSin / _fORadius)) * _fORadius;
        }
    }else{
        _fSampleStart = GetSampleStart(nGroupId_ , nLawId_);
        _fSampleRange = GetSampleRange(nGroupId_ , nLawId_);
        _fScale  = _nPointQty / _fSampleRange;
    }

	//-----------------------------------
	// I
	GATE_CONFIG* _pGate = GetGateInfo(nGroupId_ , setup_GATE_I);
    float _fStart, _fWidth, _fHeigh;
    if(config->eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH){
        if(_pGate->gTravelMode == setup_GATE_DEPTH){
            _fStart = _fScale * (_pGate->fStart - _fSampleStart);
            _fWidth = _fScale * _pGate->fWidth;
        }else{
            _fStart = _fScale * (_pGate->fStart * _fCos - _fSampleStart);
            _fWidth = _fScale * _pGate->fWidth * _fCos;
        }
    }else if(config->eTravelMode == setup_TRAVEL_MODE_HALF_PATH){
        if(_pGate->gTravelMode == setup_GATE_DEPTH){
            _fStart = _fScale * (_pGate->fStart / _fCos - _fSampleStart);
            _fWidth = _fScale * _pGate->fWidth / _fCos;
        }else{
            _fStart = _fScale * (_pGate->fStart - _fSampleStart);
            _fWidth = _fScale * _pGate->fWidth;
        }
    } else{
        if(_pGate->gTravelMode == setup_GATE_DEPTH){
            _fStart = _fScale * ( DistMmToUs( nGroupId_, _pGate->fStart / _fCos) - _fSampleStart);
            _fWidth = _fScale * DistMmToUs( nGroupId_, _pGate->fWidth / _fCos);
        }else{
            _fStart = _fScale * ( DistMmToUs( nGroupId_, _pGate->fStart) - _fSampleStart);
            _fWidth = _fScale * DistMmToUs( nGroupId_, _pGate->fWidth);
        }
    }
    _fHeigh = _pGate->nThreshold * WAVE_MAX / 100;
//	if(_fStart+_fWidth >= _nPointQty) _fWidth = _nPointQty - _fStart - 1;

	pInfo_[setup_GATE_I].iYEdge = SearchPeakFront(pData_, &pInfo_[setup_GATE_I].iXEdge, _fStart, _fStart+_fWidth, _fHeigh, _nRectify, _nPointQty);
	pInfo_[setup_GATE_I].iY    = SearchPeakAmp(pData_, &pInfo_[setup_GATE_I].iX, _fStart, _fStart+_fWidth, _nRectify, _nPointQty);

//    if( config->part.eGeometry == setup_PART_GEOMETRY_OD || config->part.eGeometry == setup_PART_GEOMETRY_ID){
//        pInfo_[setup_GATE_I].fGs   = _pGate->fStart * _fCos;
//        pInfo_[setup_GATE_I].fGw   = _pGate->fWidth * _fCos;
//    }else{
        pInfo_[setup_GATE_I].fGs   = _fStart / _fScale + _fSampleStart;
        pInfo_[setup_GATE_I].fGw   = _fWidth / _fScale;
    //}
	pInfo_[setup_GATE_I].fGh   = GateHeight(_pGate->nThreshold, _nRectify);

	_fEdge = DistDotPosToMm(nGroupId_ , pInfo_[setup_GATE_I].iXEdge);
	pInfo_[setup_GATE_I].fSEdge = _fEdge;
    if( config->part.eGeometry == setup_PART_GEOMETRY_OD){
        if (config->part.weldFormat == PHASCAN_II_FORMAT && config->part.weld_ii.eWeldDir == CIRC) {
            pInfo_[setup_GATE_I].fHEdge = _fEdge * _fCos;
            pInfo_[setup_GATE_I].fLEdge = _fEdge * _fSin;
            pInfo_[setup_GATE_I].fDEdge = GetDepth(pInfo_[setup_GATE_I].fHEdge, _fThick);
        } else {
            int cycle = _fEdge / _fSstep;
            float calSEdge;
            if( cycle & 0x1){
                calSEdge = ( cycle + 1) * _fSstep - _fEdge;
            }else{
                calSEdge = _fEdge - cycle * _fSstep;
            }
    //        pInfo_[setup_GATE_I].fDEdge = _fORadius - sqrt( calSEdge * calSEdge + _fORadius * _fORadius - 2 * _fORadius * _fCos);
    //        float calLEdge = atan( _fSin * calSEdge / ( _fORadius - _fCos * calSEdge)) * _fORadius;
            pInfo_[setup_GATE_I].fDEdge = calSEdge / _fSstep * _fThick;
            float calLEdge = calSEdge / _fSstep * _fLstep;
            if(cycle & 0x1){
                pInfo_[setup_GATE_I].fLEdge = ( cycle + 1) * _fLstep - calLEdge;
            }else{
                pInfo_[setup_GATE_I].fLEdge = cycle * _fLstep + calLEdge;
            }
            pInfo_[setup_GATE_I].fHEdge = _fEdge;
        }

    }else if( config->part.eGeometry == setup_PART_GEOMETRY_ID){
        if (config->part.weldFormat == PHASCAN_II_FORMAT && config->part.weld_ii.eWeldDir == CIRC) {
            pInfo_[setup_GATE_I].fHEdge = _fEdge * _fCos;
            pInfo_[setup_GATE_I].fLEdge = _fEdge * _fSin;
            pInfo_[setup_GATE_I].fDEdge = GetDepth(pInfo_[setup_GATE_I].fHEdge, _fThick);
        } else {
            int cycle = _fEdge / _fSstep;
            float calSEdge;
            if( cycle & 0x1){
                calSEdge = ( cycle + 1) * _fSstep - _fEdge;
            }else{
                calSEdge = _fEdge - cycle * _fSstep;
            }
    //        pInfo_[setup_GATE_I].fDEdge = sqrt( calSEdge * calSEdge + _fIRadius * _fIRadius + 2 * _fIRadius * _fCos) - _fIRadius;
    //        float calLEdge = asin( _fSin * calSEdge / ( _fIRadius + _fCos * calSEdge)) * _fORadius;
            pInfo_[setup_GATE_I].fDEdge = calSEdge / _fSstep * _fThick;
            float calLEdge = calSEdge / _fSstep * _fLstep;
            if(cycle & 0x1){
                pInfo_[setup_GATE_I].fLEdge = ( cycle + 1) * _fLstep - calLEdge;
            }else{
                pInfo_[setup_GATE_I].fLEdge = cycle * _fLstep + calLEdge;
            }
            pInfo_[setup_GATE_I].fHEdge = _fEdge;
        }

    }else{
        pInfo_[setup_GATE_I].fHEdge = _fEdge * _fCos;
        pInfo_[setup_GATE_I].fLEdge = _fEdge * _fSin;
        pInfo_[setup_GATE_I].fDEdge = GetDepth(pInfo_[setup_GATE_I].fHEdge, _fThick);
    }

	_fDist = DistDotPosToMm(nGroupId_ , pInfo_[setup_GATE_I].iX);
	pInfo_[setup_GATE_I].fS     = _fDist;
    if( config->part.eGeometry == setup_PART_GEOMETRY_OD){
        if (config->part.weldFormat == PHASCAN_II_FORMAT && config->part.weld_ii.eWeldDir == CIRC) {
            pInfo_[setup_GATE_I].fH     = _fDist * _fCos;
            pInfo_[setup_GATE_I].fL     = _fDist * _fSin;
            pInfo_[setup_GATE_I].fD     = GetDepth(pInfo_[setup_GATE_I].fH, _fThick);
        } else {
            int cycle = _fDist / _fSstep;
            float calSEdge;
            if( cycle & 0x1){
                calSEdge = ( cycle + 1) * _fSstep - _fDist;
            }else{
                calSEdge = _fDist - cycle * _fSstep;
            }
    //        pInfo_[setup_GATE_I].fD = _fORadius - sqrt( calSEdge * calSEdge + _fORadius * _fORadius - 2 * _fORadius * _fCos);
    //        float calLEdge = atan( _fSin * calSEdge / ( _fORadius - _fCos * calSEdge)) * _fORadius;
            pInfo_[setup_GATE_I].fD = calSEdge / _fSstep * _fThick;
            float calLEdge = calSEdge / _fSstep * _fLstep;
            if(cycle & 0x1){
                pInfo_[setup_GATE_I].fL = ( cycle + 1) * _fLstep - calLEdge;
            }else{
                pInfo_[setup_GATE_I].fL = cycle * _fLstep + calLEdge;
            }
            pInfo_[setup_GATE_I].fH = _fDist;
        }

    }else if( config->part.eGeometry == setup_PART_GEOMETRY_ID){
        if (config->part.weldFormat == PHASCAN_II_FORMAT && config->part.weld_ii.eWeldDir == CIRC) {
            pInfo_[setup_GATE_I].fH     = _fDist * _fCos;
            pInfo_[setup_GATE_I].fL     = _fDist * _fSin;
            pInfo_[setup_GATE_I].fD     = GetDepth(pInfo_[setup_GATE_I].fH, _fThick);
        } else {
            int cycle = _fDist / _fSstep;
            float calSEdge;
            if( cycle & 0x1){
                calSEdge = ( cycle + 1) * _fSstep - _fDist;
            }else{
                calSEdge = _fDist - cycle * _fSstep;
            }
    //        pInfo_[setup_GATE_I].fD = sqrt( calSEdge * calSEdge + _fIRadius * _fIRadius + 2 * _fIRadius * _fCos) - _fIRadius;
    //        float calLEdge = asin( _fSin * calSEdge / ( _fIRadius + _fCos * calSEdge)) * _fORadius;
            pInfo_[setup_GATE_I].fD = calSEdge / _fSstep * _fThick;
            float calLEdge = calSEdge / _fSstep * _fLstep;
            if(cycle & 0x1){
                pInfo_[setup_GATE_I].fL = ( cycle + 1) * _fLstep - calLEdge;
            }else{
                pInfo_[setup_GATE_I].fL = cycle * _fLstep + calLEdge;
            }
            pInfo_[setup_GATE_I].fH = _fDist;
        }

    }else{
        pInfo_[setup_GATE_I].fH     = _fDist * _fCos;
        pInfo_[setup_GATE_I].fL     = _fDist * _fSin;
        pInfo_[setup_GATE_I].fD     = GetDepth(pInfo_[setup_GATE_I].fH, _fThick);
    }

    pInfo_[setup_GATE_I].fAmp = CalculatePeakAmp(pInfo_[setup_GATE_I].iY, _nRectify);
    pInfo_[setup_GATE_I].fXdXA  = A_DB_B(pow(10.0, config->fRefGain/20.0) * pInfo_[setup_GATE_I].fAmp, pInfo_[setup_GATE_I].fGh);
	//-----------------------------------

	// A
	_pGate = GetGateInfo(nGroupId_ , setup_GATE_A);
    if(config->eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH){
        if(_pGate->gTravelMode == setup_GATE_DEPTH){
            _fStart = _fScale * (_pGate->fStart - _fSampleStart);
            _fWidth = _fScale * _pGate->fWidth;
        }else{
            _fStart = _fScale * (_pGate->fStart * _fCos - _fSampleStart);
            _fWidth = _fScale * _pGate->fWidth * _fCos;
        }
    }else if(config->eTravelMode == setup_TRAVEL_MODE_HALF_PATH){
        if(_pGate->gTravelMode == setup_GATE_DEPTH){
            _fStart = _fScale * (_pGate->fStart / _fCos - _fSampleStart);
            _fWidth = _fScale * _pGate->fWidth / _fCos;
        }else{
            _fStart = _fScale * (_pGate->fStart - _fSampleStart);
            _fWidth = _fScale * _pGate->fWidth;
        }
    }else{
        if(_pGate->gTravelMode == setup_GATE_DEPTH){
            _fStart = _fScale * ( DistMmToUs( nGroupId_, _pGate->fStart / _fCos) - _fSampleStart);
            _fWidth = _fScale * DistMmToUs( nGroupId_, _pGate->fWidth / _fCos);
        }else{
            _fStart = _fScale * ( DistMmToUs( nGroupId_, _pGate->fStart) - _fSampleStart);
            _fWidth = _fScale * DistMmToUs( nGroupId_, _pGate->fWidth);
        }
    }
	_fHeigh = _pGate->nThreshold * WAVE_MAX / 100;
	switch(_pGate->eSynChro)
	{
	case setup_GATE_AYNC_I:
		_fStart += pInfo_[setup_GATE_I].iXEdge;
		break;
	default:	break;
	}
//	if(_fStart+_fWidth >= _nPointQty) _fWidth = _nPointQty - _fStart - 1;

	pInfo_[setup_GATE_A].iYEdge = SearchPeakFront(pData_, &pInfo_[setup_GATE_A].iXEdge, _fStart, _fStart+_fWidth, _fHeigh, _nRectify, _nPointQty);
    pInfo_[setup_GATE_A].iY    = SearchPeakAmp(pData_, &pInfo_[setup_GATE_A].iX, _fStart, _fStart+_fWidth, _nRectify, _nPointQty);

//    if( config->part.eGeometry == setup_PART_GEOMETRY_OD || config->part.eGeometry == setup_PART_GEOMETRY_ID){
//        pInfo_[setup_GATE_A].fGs   = ( _fStart / _fScale + _fSampleStart) * _fCos;
//        pInfo_[setup_GATE_A].fGw   = _pGate->fWidth * _fCos;
//    }else{
        pInfo_[setup_GATE_A].fGs   = _fStart / _fScale + _fSampleStart;//_pGate->fStart;
        pInfo_[setup_GATE_A].fGw   = /*_fWidth / _fScale;//*/_fWidth / _fScale;
    //}
    pInfo_[setup_GATE_A].fGh   = GateHeight(_pGate->nThreshold, _nRectify);

    _fEdge = DistDotPosToMm(nGroupId_ , pInfo_[setup_GATE_A].iXEdge);
	pInfo_[setup_GATE_A].fSEdge = _fEdge;
    if( config->part.eGeometry == setup_PART_GEOMETRY_OD){
        if (config->part.weldFormat == PHASCAN_II_FORMAT && config->part.weld_ii.eWeldDir == CIRC) {
            pInfo_[setup_GATE_A].fHEdge = _fEdge * _fCos;
            pInfo_[setup_GATE_A].fLEdge = _fEdge * _fSin;
            pInfo_[setup_GATE_A].fDEdge = GetDepth(pInfo_[setup_GATE_A].fHEdge, _fThick);
        } else {
            int cycle = _fEdge / _fSstep;
            float calSEdge;
            if( cycle & 0x1){
                calSEdge = ( cycle + 1) * _fSstep - _fEdge;
            }else{
                calSEdge = _fEdge - cycle * _fSstep;
            }
            //pInfo_[setup_GATE_A].fDEdge = _fORadius - sqrt( calSEdge * calSEdge + _fORadius * _fORadius - 2 * _fORadius * _fCos);
            //float calLEdge = atan( _fSin * calSEdge / ( _fORadius - _fCos * calSEdge)) * _fORadius;
            pInfo_[setup_GATE_A].fDEdge = calSEdge / _fSstep * _fThick;
            float calLEdge = calSEdge / _fSstep * _fLstep;
            if(cycle & 0x1){
                pInfo_[setup_GATE_A].fLEdge = ( cycle + 1) * _fLstep - calLEdge;
            }else{
                pInfo_[setup_GATE_A].fLEdge = cycle * _fLstep + calLEdge;
            }
            pInfo_[setup_GATE_A].fHEdge = _fEdge;
        }

    }else if( config->part.eGeometry == setup_PART_GEOMETRY_ID){
        if (config->part.weldFormat == PHASCAN_II_FORMAT && config->part.weld_ii.eWeldDir == CIRC) {
            pInfo_[setup_GATE_A].fHEdge = _fEdge * _fCos;
            pInfo_[setup_GATE_A].fLEdge = _fEdge * _fSin;
            pInfo_[setup_GATE_A].fDEdge = GetDepth(pInfo_[setup_GATE_A].fHEdge, _fThick);
        } else {
            int cycle = _fEdge / _fSstep;
            float calSEdge;
            if( cycle & 0x1){
                calSEdge = ( cycle + 1) * _fSstep - _fEdge;
            }else{
                calSEdge = _fEdge - cycle * _fSstep;
            }
            //pInfo_[setup_GATE_A].fDEdge = sqrt( calSEdge * calSEdge + _fIRadius * _fIRadius + 2 * _fIRadius * _fCos) - _fIRadius;
            //float calLEdge = asin( _fSin * calSEdge / ( _fIRadius + _fCos * calSEdge)) * _fORadius;
            pInfo_[setup_GATE_A].fDEdge = calSEdge / _fSstep * _fThick;
            float calLEdge = calSEdge / _fSstep * _fLstep;
            if(cycle & 0x1){
                pInfo_[setup_GATE_A].fLEdge = ( cycle + 1) * _fLstep - calLEdge;
            }else{
                pInfo_[setup_GATE_A].fLEdge = cycle * _fLstep + calLEdge;
            }
            pInfo_[setup_GATE_A].fHEdge = _fEdge;
        }

    }else{
        pInfo_[setup_GATE_A].fHEdge = _fEdge * _fCos;
        pInfo_[setup_GATE_A].fLEdge = _fEdge * _fSin;
        pInfo_[setup_GATE_A].fDEdge = GetDepth(pInfo_[setup_GATE_A].fHEdge, _fThick);
    }
    _fDist = DistDotPosToMm(nGroupId_ , pInfo_[setup_GATE_A].iX);
	pInfo_[setup_GATE_A].fS     = _fDist;
    if( config->part.eGeometry == setup_PART_GEOMETRY_OD){
        if (config->part.weldFormat == PHASCAN_II_FORMAT && config->part.weld_ii.eWeldDir == CIRC) {
            pInfo_[setup_GATE_A].fH     = _fDist * _fCos;
            pInfo_[setup_GATE_A].fL     = _fDist * _fSin;
            pInfo_[setup_GATE_A].fD     = GetDepth(pInfo_[setup_GATE_A].fH, _fThick);
        } else {
            int cycle = _fDist / _fSstep;
            float calSEdge;
            if( cycle & 0x1){
                calSEdge = ( cycle + 1) * _fSstep - _fDist;
            }else{
                calSEdge = _fDist - cycle * _fSstep;
            }
    //        pInfo_[setup_GATE_A].fD = _fORadius - sqrt( calSEdge * calSEdge + _fORadius * _fORadius - 2 * _fORadius * _fCos);
    //        float calLEdge = atan( _fSin * calSEdge / ( _fORadius - _fCos * calSEdge)) * _fORadius;
            pInfo_[setup_GATE_A].fD = calSEdge / _fSstep * _fThick;
            float calLEdge = calSEdge / _fSstep * _fLstep;
            if(cycle & 0x1){
                pInfo_[setup_GATE_A].fL = ( cycle + 1) * _fLstep - calLEdge;
            }else{
                pInfo_[setup_GATE_A].fL = cycle * _fLstep + calLEdge;
            }
            pInfo_[setup_GATE_A].fH = _fDist;
        }

    }else if( config->part.eGeometry == setup_PART_GEOMETRY_ID){
        if (config->part.weldFormat == PHASCAN_II_FORMAT && config->part.weld_ii.eWeldDir == CIRC) {
            pInfo_[setup_GATE_A].fH     = _fDist * _fCos;
            pInfo_[setup_GATE_A].fL     = _fDist * _fSin;
            pInfo_[setup_GATE_A].fD     = GetDepth(pInfo_[setup_GATE_A].fH, _fThick);
        } else {
            int cycle = _fDist / _fSstep;
            float calSEdge;
            if( cycle & 0x1){
                calSEdge = ( cycle + 1) * _fSstep - _fDist;
            }else{
                calSEdge = _fDist - cycle * _fSstep;
            }
    //        pInfo_[setup_GATE_A].fD = sqrt( calSEdge * calSEdge + _fIRadius * _fIRadius + 2 * _fIRadius * _fCos) - _fIRadius;
    //        float calLEdge = asin( _fSin * calSEdge / ( _fIRadius + _fCos * calSEdge)) * _fORadius;
            pInfo_[setup_GATE_A].fD = calSEdge / _fSstep * _fThick;
            float calLEdge = calSEdge / _fSstep * _fLstep;
            if(cycle & 0x1){
                pInfo_[setup_GATE_A].fL = ( cycle + 1) * _fLstep - calLEdge;
            }else{
                pInfo_[setup_GATE_A].fL = cycle * _fLstep + calLEdge;
            }
            pInfo_[setup_GATE_A].fH = _fDist;
        }

    }else{
        pInfo_[setup_GATE_A].fH     = _fDist * _fCos;
        pInfo_[setup_GATE_A].fL     = _fDist * _fSin;
        pInfo_[setup_GATE_A].fD     = GetDepth(pInfo_[setup_GATE_A].fH, _fThick);
    }

    pInfo_[setup_GATE_A].fAmp = CalculatePeakAmp(pInfo_[setup_GATE_A].iY, _nRectify);
    pInfo_[setup_GATE_A].fXdXA  = A_DB_B(pow(10.0, config->fRefGain/20.0) * pInfo_[setup_GATE_A].fAmp, pInfo_[setup_GATE_A].fGh);
	//-----------------------------------
	// B
	_pGate = GetGateInfo(nGroupId_ , setup_GATE_B);

    if(config->eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH){
        if(_pGate->gTravelMode == setup_GATE_DEPTH){
            _fStart = _fScale * (_pGate->fStart - _fSampleStart);
            _fWidth = _fScale * _pGate->fWidth;
        }else{
            _fStart = _fScale * (_pGate->fStart * _fCos - _fSampleStart);
            _fWidth = _fScale * _pGate->fWidth * _fCos;
        }
    }else if(config->eTravelMode == setup_TRAVEL_MODE_HALF_PATH){
        if(_pGate->gTravelMode == setup_GATE_DEPTH){
            _fStart = _fScale * (_pGate->fStart / _fCos - _fSampleStart);
            _fWidth = _fScale * _pGate->fWidth / _fCos;
        }else{
            _fStart = _fScale * (_pGate->fStart - _fSampleStart);
            _fWidth = _fScale * _pGate->fWidth;
        }
    }else{
        if(_pGate->gTravelMode == setup_GATE_DEPTH){
            _fStart = _fScale * ( DistMmToUs( nGroupId_, _pGate->fStart / _fCos) - _fSampleStart);
            _fWidth = _fScale * DistMmToUs( nGroupId_, _pGate->fWidth / _fCos);
        }else{
            _fStart = _fScale * ( DistMmToUs( nGroupId_, _pGate->fStart) - _fSampleStart);
            _fWidth = _fScale * DistMmToUs( nGroupId_, _pGate->fWidth);
        }
    }
	_fHeigh = _pGate->nThreshold * WAVE_MAX / 100;
	switch(_pGate->eSynChro)
	{
	case setup_GATE_AYNC_I:
		_fStart += pInfo_[setup_GATE_I].iXEdge;
		break;
	case setup_GATE_AYNC_A:
		_fStart += pInfo_[setup_GATE_A].iXEdge;
		break;
	default:	break;
	}
//    if(_fStart+_fWidth >= _nPointQty) _fWidth = _nPointQty - _fStart - 1;

	pInfo_[setup_GATE_B].iYEdge = SearchPeakFront(pData_, &pInfo_[setup_GATE_B].iXEdge, _fStart, _fStart+_fWidth, _fHeigh, _nRectify, _nPointQty);
	pInfo_[setup_GATE_B].iY    = SearchPeakAmp(pData_, &pInfo_[setup_GATE_B].iX, _fStart, _fStart+_fWidth, _nRectify, _nPointQty);

//    if( config->part.eGeometry == setup_PART_GEOMETRY_OD || config->part.eGeometry == setup_PART_GEOMETRY_ID){
//        pInfo_[setup_GATE_B].fGs   = ( _fStart / _fScale + _fSampleStart) * _fCos;
//        pInfo_[setup_GATE_B].fGw   = _pGate->fWidth * _fCos;
//    }else{
        pInfo_[setup_GATE_B].fGs   = _fStart / _fScale + _fSampleStart;//_pGate->fStart;
        pInfo_[setup_GATE_B].fGw   = /*_fWidth / _fScale;//*/_fWidth / _fScale;
    //}

	pInfo_[setup_GATE_B].fGh   = GateHeight(_pGate->nThreshold, _nRectify);

    _fEdge = DistDotPosToMm(nGroupId_ , pInfo_[setup_GATE_B].iXEdge);
    pInfo_[setup_GATE_B].fSEdge = _fEdge;
    if( config->part.eGeometry == setup_PART_GEOMETRY_OD){
        if (config->part.weldFormat == PHASCAN_II_FORMAT && config->part.weld_ii.eWeldDir == CIRC) {
            pInfo_[setup_GATE_B].fHEdge = _fEdge * _fCos;
            pInfo_[setup_GATE_B].fLEdge = _fEdge * _fSin;
            pInfo_[setup_GATE_B].fDEdge = GetDepth(pInfo_[setup_GATE_B].fHEdge, _fThick);
        } else {
            int cycle = _fEdge / _fSstep;
            float calSEdge;
            if( cycle & 0x1){
                calSEdge = ( cycle + 1) * _fSstep - _fEdge;
            }else{
                calSEdge = _fEdge - cycle * _fSstep;
            }
    //        pInfo_[setup_GATE_B].fDEdge = _fORadius - sqrt( calSEdge * calSEdge + _fORadius * _fORadius - 2 * _fORadius * _fCos);
    //        float calLEdge = atan( _fSin * calSEdge / ( _fORadius - _fCos * calSEdge)) * _fORadius;
            pInfo_[setup_GATE_B].fDEdge = calSEdge / _fSstep * _fThick;
            float calLEdge = calSEdge / _fSstep * _fLstep;
            if(cycle & 0x1){
                pInfo_[setup_GATE_B].fLEdge = ( cycle + 1) * _fLstep - calLEdge;
            }else{
                pInfo_[setup_GATE_B].fLEdge = cycle * _fLstep + calLEdge;
            }
            pInfo_[setup_GATE_B].fHEdge = _fEdge;
        }

    }else if( config->part.eGeometry == setup_PART_GEOMETRY_ID){
        if (config->part.weldFormat == PHASCAN_II_FORMAT && config->part.weld_ii.eWeldDir == CIRC) {
            pInfo_[setup_GATE_B].fHEdge = _fEdge * _fCos;
            pInfo_[setup_GATE_B].fLEdge = _fEdge * _fSin;
            pInfo_[setup_GATE_B].fDEdge = GetDepth(pInfo_[setup_GATE_B].fHEdge, _fThick);
        } else {
            int cycle = _fEdge / _fSstep;
            float calSEdge;
            if( cycle & 0x1){
                calSEdge = ( cycle + 1) * _fSstep - _fEdge;
            }else{
                calSEdge = _fEdge - cycle * _fSstep;
            }
    //        pInfo_[setup_GATE_B].fDEdge = sqrt( calSEdge * calSEdge + _fIRadius * _fIRadius + 2 * _fIRadius * _fCos) - _fIRadius;
    //        float calLEdge = asin( _fSin * calSEdge / ( _fIRadius + _fCos * calSEdge)) * _fORadius;
            pInfo_[setup_GATE_B].fDEdge = calSEdge / _fSstep * _fThick;
            float calLEdge = calSEdge / _fSstep * _fLstep;
            if(cycle & 0x1){
                pInfo_[setup_GATE_B].fLEdge = ( cycle + 1) * _fLstep - calLEdge;
            }else{
                pInfo_[setup_GATE_B].fLEdge = cycle * _fLstep + calLEdge;
            }
            pInfo_[setup_GATE_B].fHEdge = _fEdge;
        }

    }else{
        pInfo_[setup_GATE_B].fHEdge = _fEdge * _fCos;
        pInfo_[setup_GATE_B].fLEdge = _fEdge * _fSin;
        pInfo_[setup_GATE_B].fDEdge = GetDepth(pInfo_[setup_GATE_B].fHEdge, _fThick);
    }

	_fDist = DistDotPosToMm(nGroupId_ , pInfo_[setup_GATE_B].iX);
	pInfo_[setup_GATE_B].fS     = _fDist;
    if( config->part.eGeometry == setup_PART_GEOMETRY_OD){
        if (config->part.weldFormat == PHASCAN_II_FORMAT && config->part.weld_ii.eWeldDir == CIRC) {
            pInfo_[setup_GATE_B].fH     = _fDist * _fCos;
            pInfo_[setup_GATE_B].fL     = _fDist * _fSin;
            pInfo_[setup_GATE_B].fD     = GetDepth(pInfo_[setup_GATE_B].fH, _fThick);
        } else {
            int cycle = _fDist / _fSstep;
            float calSEdge;
            if( cycle & 0x1){
                calSEdge = ( cycle + 1) * _fSstep - _fDist;
            }else{
                calSEdge = _fDist - cycle * _fSstep;
            }
    //        pInfo_[setup_GATE_B].fD = _fORadius - sqrt( calSEdge * calSEdge + _fORadius * _fORadius - 2 * _fORadius * _fCos);
    //        float calLEdge = atan( _fSin * calSEdge / ( _fORadius - _fCos * calSEdge)) * _fORadius;
            pInfo_[setup_GATE_B].fD = calSEdge / _fSstep * _fThick;
            float calLEdge = calSEdge / _fSstep * _fLstep;
            if(cycle & 0x1){
                pInfo_[setup_GATE_B].fL = ( cycle + 1) * _fLstep - calLEdge;
            }else{
                pInfo_[setup_GATE_B].fL = cycle * _fLstep + calLEdge;
            }
            pInfo_[setup_GATE_B].fH = _fDist;
        }

    }else if( config->part.eGeometry == setup_PART_GEOMETRY_ID){
        if (config->part.weldFormat == PHASCAN_II_FORMAT && config->part.weld_ii.eWeldDir == CIRC) {
            pInfo_[setup_GATE_B].fH     = _fDist * _fCos;
            pInfo_[setup_GATE_B].fL     = _fDist * _fSin;
            pInfo_[setup_GATE_B].fD     = GetDepth(pInfo_[setup_GATE_B].fH, _fThick);
        } else {
            int cycle = _fDist / _fSstep;
            float calSEdge;
            if( cycle & 0x1){
                calSEdge = ( cycle + 1) * _fSstep - _fDist;
            }else{
                calSEdge = _fDist - cycle * _fSstep;
            }
    //        pInfo_[setup_GATE_B].fD = sqrt( calSEdge * calSEdge + _fIRadius * _fIRadius + 2 * _fIRadius * _fCos) - _fIRadius;
    //        float calLEdge = asin( _fSin * calSEdge / ( _fIRadius + _fCos * calSEdge)) * _fORadius;
            pInfo_[setup_GATE_B].fD = calSEdge / _fSstep * _fThick;
            float calLEdge = calSEdge / _fSstep * _fLstep;
            if(cycle & 0x1){
                pInfo_[setup_GATE_B].fL = ( cycle + 1) * _fLstep - calLEdge;
            }else{
                pInfo_[setup_GATE_B].fL = cycle * _fLstep + calLEdge;
            }
            pInfo_[setup_GATE_B].fH = _fDist;
        }

    }else{
        pInfo_[setup_GATE_B].fH     = _fDist * _fCos;
        pInfo_[setup_GATE_B].fL     = _fDist * _fSin;
        pInfo_[setup_GATE_B].fD     = GetDepth(pInfo_[setup_GATE_B].fH, _fThick);
    }

    pInfo_[setup_GATE_B].fAmp = CalculatePeakAmp(pInfo_[setup_GATE_B].iY, _nRectify);
    pInfo_[setup_GATE_B].fXdXA  = A_DB_B(pow(10.0, config->fRefGain/20.0) * pInfo_[setup_GATE_B].fAmp, pInfo_[setup_GATE_B].fGh);
	return true;
}

void ParameterProcess::GetGateRangeInfos(int nGroupId_, int nLawId_, PEAK_CONFIG* gInfo_)
{
    DopplerConfigure* m_pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG* config = &(m_pConfig->group[nGroupId_]);
    int       _nRectify = GetRectifierMode(nGroupId_);
    if(config->eGroupMode == setup_GROUP_MODE_PA){
        float _fAngle = DEGREE_TO_ARCH(GetLawAngle(nGroupId_, nLawId_));
        float _fCos    = cos(_fAngle);
        if(config->eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH){
            for(int i = 0; i < setup_GATE_MAX; i++){
                if(config->gate[i].gTravelMode == setup_GATE_DEPTH){
                    gInfo_[i].fGs = config->gate[i].fStart;
                    gInfo_[i].fGw = config->gate[i].fWidth;
                    gInfo_[i].fGh = GateHeight(config->gate[i].nThreshold, _nRectify);
                }else{
                    gInfo_[i].fGs = config->gate[i].fStart * _fCos;
                    gInfo_[i].fGw = config->gate[i].fWidth * _fCos;
                    gInfo_[i].fGh = GateHeight(config->gate[i].nThreshold, _nRectify);
                }
            }
        }else if(config->eTravelMode == setup_TRAVEL_MODE_HALF_PATH){
            for(int i = 0; i < setup_GATE_MAX; i++){
                if(config->gate[i].gTravelMode == setup_GATE_DEPTH){
                    gInfo_[i].fGs = config->gate[i].fStart / _fCos;
                    gInfo_[i].fGw = config->gate[i].fWidth / _fCos;
                    gInfo_[i].fGh = GateHeight(config->gate[i].nThreshold, _nRectify);
                }else{
                    gInfo_[i].fGs = config->gate[i].fStart;
                    gInfo_[i].fGw = config->gate[i].fWidth;
                    gInfo_[i].fGh = GateHeight(config->gate[i].nThreshold, _nRectify);
                }
            }
        }else{
            for(int i = 0; i < setup_GATE_MAX; i++){
                if(config->gate[i].gTravelMode == setup_GATE_DEPTH){
                    gInfo_[i].fGs = DistMmToUs( nGroupId_, config->gate[i].fStart / _fCos);
                    gInfo_[i].fGw = DistMmToUs( nGroupId_, config->gate[i].fWidth / _fCos);
                    gInfo_[i].fGh = GateHeight(config->gate[i].nThreshold, _nRectify);
                }else{
                    gInfo_[i].fGs = DistMmToUs( nGroupId_, config->gate[i].fStart);
                    gInfo_[i].fGw = DistMmToUs( nGroupId_, config->gate[i].fWidth);
                    gInfo_[i].fGh = GateHeight(config->gate[i].nThreshold, _nRectify);
                }
            }
        }
    }else{
        if(config->eTravelMode == setup_TRAVEL_MODE_HALF_PATH){
            for(int i = 0; i < setup_GATE_MAX; i++){
                gInfo_[i].fGs = config->gate[i].fStart;
                gInfo_[i].fGw = config->gate[i].fWidth;
                gInfo_[i].fGh = GateHeight(config->gate[i].nThreshold, _nRectify);
            }
        }else{
            for(int i = 0; i < setup_GATE_MAX; i++){
                gInfo_[i].fGs = DistMmToUs(nGroupId_, config->gate[i].fStart);
                gInfo_[i].fGw = DistMmToUs(nGroupId_, config->gate[i].fWidth);
                gInfo_[i].fGh = GateHeight(config->gate[i].nThreshold, _nRectify);
            }
        }
    }
}

int ParameterProcess::GetCoupleMonitoringData(int nGroupId_, float* pResult_)
{
    int ret = 0;
    DopplerConfigure* m_pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG* config = &(m_pConfig->group[nGroupId_]);
    if( !config->coupleMonitoringState){
        ret = -1;
        return ret;
    }
    int _nScanPos = GetScanIndexPos();
    int _nRectify = GetRectifierMode(nGroupId_);
    int _index = GetRealScanIndex(nGroupId_, _nScanPos);
    QVector<WDATA> buff = GetCoupleCScanData(nGroupId_);
    //WDATA data = buff[_index];
    int cbuff = correctionPdata(buff[_index]);
    float  _fScale =  pow(10.0,CUR_RES.Couple_Com_Gain[nGroupId_]/20.0);
    *pResult_  = CalculatePeakAmp( cbuff, _nRectify) * _fScale;
    return ret;
}

WDATA* ParameterProcess::GetScanPosPointer(int nGroupId_, int nScanPos_)
{
    WDATA* _pData = GetShadowDataPointer();
    if(!_pData)  return 0;
    int _nFrameOffset = GetTotalDataSize() ;
    int _nGroupOffset = GetGroupDataOffset(nGroupId_);
    int        _index = GetRealScanIndex(nGroupId_, nScanPos_);
    return (_pData + _nFrameOffset * _index + _nGroupOffset);
}

WDATA* ParameterProcess::GetGroupDataPointer(int nGroupId_)
{
    WDATA* _pData = GetShadowDataPointer();
    if(!_pData)  return 0 ;
    int   _nFrameSize = GetTotalDataSize() ;
    int     _nScanPos = GetScanIndexPos()  ;
    int        _index = GetRealScanIndex(nGroupId_, _nScanPos);
    int _nFrameOffset = _nFrameSize * _index  ;
    int _nGroupOffset = GetGroupDataOffset(nGroupId_) ;
    //qDebug()<<"_index"<<_index<<"offset"<<_nFrameOffset + _nGroupOffset;
    return (_pData + _nFrameOffset + _nGroupOffset)  ;
}

WDATA* ParameterProcess::GetGroupDataDscanPointer(int nGroupId_)
{
    float _mScanPos;
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG& _group = _pConfig->group[nGroupId_];

   if(_group.afCursor[ setup_CURSOR_S_MES ]> _group.afCursor[setup_CURSOR_S_REF])
    _mScanPos= _group.afCursor[ setup_CURSOR_S_REF ];
   else if(_group.afCursor[ setup_CURSOR_S_MES ]< _group.afCursor[setup_CURSOR_S_REF])
     _mScanPos= _group.afCursor[ setup_CURSOR_S_MES ];

    WDATA* _pData = GetShadowDataPointer();
    if(!_pData)  return 0 ;
    int   _nFrameSize = GetTotalDataSize() ;
    int _nScanPos = SAxisDistToIndex(_mScanPos);
    int        _index = GetRealScanIndex(nGroupId_, _nScanPos);
    int _nFrameOffset = _nFrameSize * _index ;
    int _nGroupOffset = GetGroupDataOffset(nGroupId_) ;
    return (_pData + _nFrameOffset + _nGroupOffset)  ;

}

WDATA* ParameterProcess::GetGroupDataPointerRaster(int nGroupId_)
{
    WDATA* _pData = GetShadowDataPointer();
    if(!_pData)  return 0;
    int   _nFrameSize = GetTotalDataSize();
    int     _nScanPos = transforRasterPosToMarker();
    int        _index = GetRealScanIndex(nGroupId_, _nScanPos);
    int _nFrameOffset = _nFrameSize * _index;
    int _nGroupOffset = GetGroupDataOffset(nGroupId_);
    return (_pData + _nFrameOffset + _nGroupOffset);
}

WDATA* ParameterProcess::GetLawDataPointer(int nGroupId_ , int nLawId_)
{
    WDATA* _pData;
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
    if( m_pConfig->common.scanner.eScanType == setup_SCAN_TYPE_ONE_LINE&&_group.m_mode){

        _pData=GetGroupDataDscanPointer(nGroupId_);
    }else if( m_pConfig->common.scanner.eScanType == setup_SCAN_TYPE_ONE_LINE) {

        _pData = GetGroupDataPointer(nGroupId_);

    }
    else{
        _pData = GetGroupDataPointerRaster(nGroupId_);
    }

	if(!_pData)  return 0 ;
	int _nLawOffset  = GetGroupLawDataOffset(nGroupId_ , nLawId_)  ;
	//*** total offset
	return (_pData + _nLawOffset)  ;
}

WDATA* ParameterProcess::GetCoupleDataPointer( int nGroupId_)
{
    WDATA* _pData = GetGroupDataPointer( nGroupId_);
    if( !_pData)  return 0;
    int nLawId_ = GetGroupLawQty(nGroupId_);
    int _nLawOffset;
//    if(m_pConfig->group[nGroupId_].law.eLawType == setup_LAW_TYPE_TFM){
//        _nLawOffset  = nLawId_ * m_pConfig->group[nGroupId_].nPointQty; //偏移到耦合监控beam
//    }else{
        _nLawOffset  = nLawId_ * (m_pConfig->group[nGroupId_].nPointQty + setup_DATA_PENDIX_LENGTH); //偏移到耦合监控beam
    //}

    return (_pData + _nLawOffset);
}

//RL RL SL 合法 返回值 0-100
double ParameterProcess::GetDetermineThreshold(int nGroupId_, DAC_MODE mode)
{
    double midx = 0;
    float refAmp = CUR_RES.Ref_Amp[nGroupId_];
    switch (mode) {
    case setup_RL:
        midx = pow(10.0, (CUR_RES.REF_Gain[nGroupId_] + CUR_RES.CurRL[nGroupId_] + CUR_RES.CurSS[nGroupId_])/20.0)*refAmp;
        break;
    case setup_EL:
        midx = pow(10.0, (CUR_RES.REF_Gain[nGroupId_] + CUR_RES.CurEL[nGroupId_] + CUR_RES.CurSS[nGroupId_])/20.0)*refAmp;
        break;
    case setup_SL:
        midx = pow(10.0, (CUR_RES.REF_Gain[nGroupId_] + CUR_RES.CurSL[nGroupId_] + CUR_RES.CurSS[nGroupId_])/20.0)*refAmp;
        break;
    default:
        break;
    }
    return midx;
}

unsigned int   ParameterProcess::GetLawGateDWORD(int nGroupId_ , int nLawId_ , setup_GATE_NAME eGate_)
{
	WDATA* _pData = GetLawDataPointer(nGroupId_ ,  nLawId_) ;
	if(!_pData)  return 0;

	U32 ret ;
	U8* _pTmp = (U8*)&ret;
	int _nPointQty = GetGroupPointQty(nGroupId_) ;
	int _nGate = (int)eGate_ + 1 ;
	_pData = _pData + _nPointQty + _nGate *  4  ;
	memcpy(_pTmp , _pData , 4);
	return ret ;
}

int  ParameterProcess::TofdDepthCalibration(int nGroupId_)
{
	UpdateTofdParam(nGroupId_);

	TOFD_PARA*	_pTofd = m_pConfig->GetTofdConfig(nGroupId_) ;
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;

	float   _H = _pTofd->fDepthCal;
	float   _L = _pTofd->fPCS / 2.0f;
	float   _S = sqrt(_H * _H + _L *_L);
	float  _T1 = DistMmToUs(nGroupId_ , _S);
//	float  _T2 = DistMmToUs(nGroupId_ , _group.afCursor[setup_CURSOR_U_MES]);
	float  _T2 = DistMmToUs(nGroupId_ , _group.afCursor[setup_CURSOR_U_REF]);

	_pTofd->fZeroOff = _T2 - _T1;
	TofdCursorCalibration(nGroupId_);
	return 0;
}

void ParameterProcess::TofdCursorCalibration(int nGroupId_)
{
	TOFD_PARA*	 _pTofd = m_pConfig->GetTofdConfig(nGroupId_) ;
	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_]  ;

	float _U1 = DistUsToMm(nGroupId_ , _pTofd->fZeroOff);
	float  _S = _pTofd->fLayerStart;
	float  _E = _pTofd->fLayerEnd;
	float  _A = _pTofd->fPCS / 2.0f;

	float   _Lw = sqrt(_S*_S + _A*_A) + _U1;
	float   _Bw = sqrt(_E*_E + _A*_A) + _U1;

	if(_Lw < _pGroup->fSampleStart)
		_Lw = _pGroup->fSampleStart;

	if(_Lw > _pGroup->fSampleStart + _pGroup->fSampleRange)
		_Lw = _pGroup->fSampleStart + _pGroup->fSampleRange;

	if(_Bw < _pGroup->fSampleStart)
		_Bw = _pGroup->fSampleStart;

	if(_Bw > _pGroup->fSampleStart + _pGroup->fSampleRange)
		_Bw = _pGroup->fSampleStart + _pGroup->fSampleRange;

	_pGroup->afCursor[setup_CURSOR_TFOD_LW] = _Lw;
	_pGroup->afCursor[setup_CURSOR_TFOD_BW] = _Bw;
}

void ParameterProcess::UpdateTofdParam(int nGroupId_)
{
	TOFD_PARA*	 _pTofd = m_pConfig->GetTofdConfig(nGroupId_) ;
	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_]  ;

	_pTofd->fZero = (float)((double)_pGroup->nWedgeDelay / 1000.0);
	_pTofd->fD	= _pTofd->fLayerEnd - _pTofd->fLayerStart;
	_pTofd->fC	= _pGroup->fVelocity / 1000.0f;
	_pTofd->fTa   = DistMmToUs(nGroupId_ , _pGroup->afCursor[setup_CURSOR_TFOD_LW]) + _pTofd->fZero;
	_pTofd->fTb   = DistMmToUs(nGroupId_ , _pGroup->afCursor[setup_CURSOR_TFOD_BW]) + _pTofd->fZero;
}

float ParameterProcess::CalculateTofdProbeDelay(int nGroupId_)
{
	UpdateTofdParam(nGroupId_);
	TOFD_PARA* _pTofd = m_pConfig->GetTofdConfig(nGroupId_) ;
	TofdProbeDelay(_pTofd);
	return _pTofd->fT0;
}

float ParameterProcess::CalculateTofdPcs(int nGroupId_)
{
	CalculateTofdProbeDelay(nGroupId_);

	TOFD_PARA* _pTofd = m_pConfig->GetTofdConfig(nGroupId_) ;
	TofdPcs(_pTofd);
	return _pTofd->fPcs;
}

double ParameterProcess::transTofdHalfSoundPathToDepth(double halfSoundPath, float pcs)
{
    float halfPcs = pcs / 2;
    if(halfSoundPath > halfPcs){
        return qSqrt(qPow(halfSoundPath, 2) - qPow(halfPcs, 2));
    }else if(halfSoundPath < halfPcs){
        return 0 - qSqrt(qPow(halfPcs, 2) - qPow(halfSoundPath, 2));
    }else{
        return 0;
    }
}

double ParameterProcess::transTofdDepthToHalfSoundPath(double depth, float pcs)
{
    if(depth > 0){
        return qSqrt(qPow( depth, 2) + qPow( pcs / 2, 2));
    }else if(depth < 0){
        return qSqrt(qPow(pcs / 2, 2) - qPow( -depth, 2));
    }else{
        return pcs;
    }
}

float  ParameterProcess::GetTofdDepth(int nGroupId_ , float fCursorPos_)
{
	CalculateTofdPcs(nGroupId_);

	TOFD_PARA* _pTofd = m_pConfig->GetTofdConfig(nGroupId_) ;

	float _fZero = _pTofd->fZero;
	float  _T = DistMmToUs(nGroupId_ , fCursorPos_) + _fZero;

	float _fDepth = TofdDepth(_pTofd, _T, fCursorPos_);

	return _fDepth;
}

int  ParameterProcess::GetTofdDepth(int nGroupId_ , int ID_ , float* fValue_)
{
	if(m_pConfig->group[nGroupId_].eTxRxMode != setup_TX_RX_MODE_TOFD )
	return -1 ;

	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;

	switch(ID_)
	{
	case 1:
		*fValue_ = GetTofdDepth(nGroupId_ , _group.afCursor[setup_CURSOR_U_REF]);
		break;
	case 2:
		*fValue_ = GetTofdDepth(nGroupId_ , _group.afCursor[setup_CURSOR_U_MES]);
		break;
	case 3:
	{
		double _fCursor1 = GetTofdDepth(nGroupId_ , _group.afCursor[setup_CURSOR_U_REF]);
		double _fCursor2 = GetTofdDepth(nGroupId_ , _group.afCursor[setup_CURSOR_U_MES]);
			*fValue_ = fabs( _fCursor2 -  _fCursor1);
		break;
	}
	default:
		break;
	}
	return 0;
}

void ParameterProcess::FittedCurveGetPoints(int nGroupId_, float fPrecX_, float fPrecY_, float fTX0_, int iDots_, float scaleH, float scaleV, QPointF* pPoints_)
{
	CalculateTofdPcs(nGroupId_);

	TOFD_PARA*	  _pTofd = m_pConfig->GetTofdConfig(nGroupId_) ;
	COMMON_CONFIG& _common = m_pConfig->common ;

	float   _D = _pTofd->fD;
	float   _C = _pTofd->fC;
	float  _Tb = _pTofd->fTb;
	float  _Ta = _pTofd->fTa;
	float  _T0 = (_Tb+_Ta)/2 + (2*_D*_D)/((_Tb-_Ta)*_C*_C);
	float _PCS = _pTofd->fPCS;

	float  _precX = fPrecX_;
	float  _precY = fPrecY_;
	float	_TX0 = fTX0_;
	int	_iDots = iDots_;

	float _dY = 0;
	float _Tx = 0;

	int _isign = 1;
	if(_Ta > _Tb)
	_isign = -1;

	for(int i = 0; i < _iDots+1; i++)
	{
        _dY = _precY*i;

        if(_common.scanner.eScanMode == setup_SCAN_NORMAL)
        {
            _Tx = FittedCurveDTX(_dY, _C, _TX0, _T0);
        }
        else if(_common.scanner.eScanMode == setup_SCAN_PARALLEL)
        {
            _Tx = FittedCurveDTXParallel(_dY, _C, _TX0, _T0, _PCS);
        }

        int _x = (_Tx - _TX0) / _precX*scaleV;
        int _y = i*scaleH;

        pPoints_[_iDots+i].setX(_x);
        pPoints_[_iDots+i].setY(_y);

        pPoints_[_iDots-i].setX(_x);
        pPoints_[_iDots-i].setY(-_y);
    }

    float _fDeltaX = pPoints_[_iDots].x();
    for(int i = 0; i < 2*_iDots+1; i++)
    {
        int _x = _isign*(pPoints_[i].x() - _fDeltaX);
        pPoints_[i].setX(_x);
    }
}


U8* ParameterProcess::GetScanMarker(int nGroupId_) const
{
	int _nOffMax  = m_pConfig->common.nScanOffMax;
	int _nOff     = m_pConfig->common.nScanOff[nGroupId_];
	int _nIdx     = _nOffMax - _nOff;
	int _nScanMax = GetScanMax();

	if(_nIdx < 0)
		_nIdx = 0;
	if(_nIdx >= setup_MAX_REC_LEN)
		_nIdx = setup_MAX_REC_LEN - 1;
	if(_nIdx >= _nScanMax)
		_nIdx = _nScanMax - 1;

	return &m_pConfig->common.nRecMark[_nIdx];
}

float ParameterProcess::GetScanStart() const
{
    return m_pConfig->common.scanner.fScanStart;
}

float ParameterProcess::GetScanStop() const
{
    return m_pConfig->common.scanner.fScanStop;
}

float ParameterProcess::GetScanStart2() const
{
    return m_pConfig->common.scanner.fScanStart2;
}

float ParameterProcess::GetScanend() const
{
    return m_pConfig->common.scanner.fScanend;
}

int ParameterProcess::GetLawStart() const
{
    return m_pConfig->common.scanner.fLawStart;
}

int ParameterProcess::GetLawStop() const
{
    return m_pConfig->common.scanner.fLawStop;
}

void ParameterProcess::ChangeLawStart(int lawstart) const
{
    SCANNER& _scan = m_pConfig->common.scanner  ;
    _scan.fLawStart = lawstart;
}

void ParameterProcess::ChangeLawStop(int lawstop) const
{
    SCANNER& _scan = m_pConfig->common.scanner  ;
    _scan.fLawStop = lawstop;
}

float ParameterProcess::GetScanPos() const
{
    return m_pConfig->common.scanner.fScanPos;
}

int ParameterProcess::GetScanOff(int nGroupId_) const
{
	return m_pConfig->common.nScanOff[nGroupId_];
}

int ParameterProcess::GetScanMax() const
{
	return m_pConfig->common.nRecMax;
}

int ParameterProcess::GetRealScanMax() const
{
	return m_pConfig->comTmp.nRecMax;
}

float ParameterProcess::GetVelocity(int nGroupId_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	return group.fVelocity ;
}

float ParameterProcess::GetPrf()
{
	SCANNER _scan = m_pConfig->common.scanner  ;
	return _scan.fPrf ;
}

float ParameterProcess::GetScanSpeed()
{
	SCANNER _scan = m_pConfig->common.scanner  ;
	float _ret = _scan.fPrf * _scan.fScanStep  ;
	return _ret ;
}

double ParameterProcess::GetRealScanRange()
{
    SCANNER _scan = m_pConfig->comTmp.scanner;
    double scanRange;
    if(_scan.eScanEncoderType){
        scanRange = _scan.fScanStop - _scan.fScanStart;
    }
    else{
        scanRange = ( _scan.fScanStop - _scan.fScanStart)/_scan.fPrf;
    }
    return scanRange;
}

void  ParameterProcess::GetScanScanAxisRange(int nGroupId_ ,  int nDist_ , double* fStart_ , double* fStop_, double* fSliderStart_ , double* fSliderStop_)
{
    Q_UNUSED(nGroupId_);
//	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_];
	//float      _fScanOff = _group.fScanOffset;
    ParameterProcess* _process = ParameterProcess::Instance();
	SCANNER& _scan = m_pConfig->common.scanner  ;
	float _fScanPos = _scan.fScanPos;//  + _fScanOff;
	float _fRange ;
	float _fStart ;
    int scanend = _process->SAxisstoptoIndex(_process->GetScanend());
    if(_scan.eScanEncoderType == setup_ENCODER_TYPE_TIMER)
	{
        _fRange = (nDist_ ) / _scan.fPrf  ;
        float scanRange = ( _scan.fScanend - _scan.fScanStart2);
        if( _fRange > scanRange){
            _fRange = scanRange;
        }
        _fStart = 0;// + _fScanOff;
	}
	else
	{
        _fRange = (nDist_) * _scan.fScanStep  ;
        float scanRange = ( _scan.fScanend - _scan.fScanStart)/_scan.fScanStep;
        if( _fRange > scanRange){
            _fRange = scanRange;
        }
        _fStart = _scan.fScanStart2;// + _fScanOff;
	}
    *fSliderStart_ = _scan.fScanStart;
	*fSliderStop_  = _scan.fScanStop;

	if(FLOAT_EQ(*fStart_ , *fStop_))
	{
		*fStart_ = _fStart  ;
		*fStop_  = _fStart + _fRange  ;
	}

    if(_fScanPos < *fStart_)
        {
            *fStart_ = _fScanPos  ;
            *fStop_  = _fScanPos + _fRange  ;
        }
        else if(_fScanPos > *fStop_)
        {
            *fStart_ = _fScanPos - _fRange  ;
            *fStop_  = _fScanPos ;
        }
        else
        {
            *fStop_ = *fStart_ +  _fRange ;
        }
    if(_scan.fScanStart2 == _scan.fScanStart && _scan.fScanPos == _scan.fScanStart2)
    {
        if((_scan.eScanEncoderType && _scan.fScanStop == _scan.fScanend)||(!_scan.eScanEncoderType && _scan.fScanend == _scan.fScanStop/_scan.fPrf + _scan.fScanStart))
        {
            if(_scan.fScanPos == 0)
            {
                *fStart_ = _scan.fScanPos;
                *fStop_  = _scan.fScanPos + _fRange;
            }
            else if(_scan.fScanPos > 0)
            {
                *fStop_  = _scan.fScanPos;
                *fStart_ = _scan.fScanPos - _fRange;
                if(*fStart_ < 0)
                {
                    *fStart_ = 0;
                    *fStop_  = _fRange;
                }
            }

       }
    }
    if(scanend == nDist_)
    {
        *fStart_ = _scan.fScanStart2;
        *fStop_  = _scan.fScanend;
    }
    //qDebug()<<"fStart_"<<*fStart_<<"fStop_"<<*fStop_;
}

void  ParameterProcess::GetBScanScanAxisRange(int nGroupId_ ,  int nDist_ , double* fStart_ , double* fStop_, double* fSliderStart_ , double* fSliderStop_)
{
	GetScanScanAxisRange(nGroupId_ ,  nDist_ , fStart_ , fStop_, fSliderStart_ , fSliderStop_);
/*
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_];
	float      _fScanOff = _group.fScanOffset;
	if(_fScanOff != m_fBScanOff[nGroupId_]) {
		float _fDelta = _fScanOff - m_fBScanOff[nGroupId_];
		*fStart_ += _fDelta;
		*fStop_  += _fDelta;
		m_fBScanOff[nGroupId_] = _fScanOff;
	}*/
}

void  ParameterProcess::GetBScanIndexAxisRange(int /*nGroupId_*/ ,  int /*nDist_*/ , double* , double*)
{
}

void ParameterProcess::GetCScanScanAxisRange(int nGroupId_ , int nDist_ , double* fStart_ , double* fStop_, double* fSliderStart_ , double* fSliderStop_)
{
	GetScanScanAxisRange(nGroupId_ ,  nDist_ , fStart_ , fStop_, fSliderStart_ , fSliderStop_);

	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_];
	float      _fScanOff = _group.fScanOffset;
	if(_fScanOff != m_fCScanOff[nGroupId_]) {
		float _fDelta = _fScanOff - m_fCScanOff[nGroupId_];
		*fStart_ += _fDelta;
		*fStop_  += _fDelta;
		m_fCScanOff[nGroupId_] = _fScanOff;
	}
}

void ParameterProcess::GetCScanIndexAxisRange(int nGroupId_ , double* fStart_ , double* fStop_)
{
	int _nLawQty = GetGroupLawQty(nGroupId_) ;
    SCANNER& _scanner = m_pConfig->common.scanner;
    if(lastgroup != currentgroup)
    {
        _scanner.fLawStart = 0;
        _scanner.fLawStop = _nLawQty;


    }

    if((_scanner.fLawStart == _scanner.fLawStop)&& (_scanner.fLawStart == 0))
    {
        _scanner.fLawStart = 0;
        _scanner.fLawStop = _nLawQty;
    }

    *fStart_  =_scanner.fLawStart 		;
    *fStop_   = _scanner.fLawStop  ;


	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	if(setup_GROUP_MODE_PA == _group.eGroupMode)
	{
		if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
		{
			LAW_CONFIG* _law = GetLawConfig(nGroupId_);
			float _fStartAngle  =  _law->nAngleStartRefract / 10.0 ;
			float _fStepAngle   =  _law->nAngleStepRefract / 10.0  ;

            *fStart_  = _fStartAngle + _scanner.fLawStart * _fStepAngle;
            *fStop_   = _fStartAngle + _scanner.fLawStop * _fStepAngle ;

		}
	}
}

void ParameterProcess::ChangeCscanIndexRange( double* fStart_ , double* fStop_,double* fStart2_,double* fStop2_,double* fstep)
{
    SCANNER& _scanner = m_pConfig->common.scanner;
    int _nLawQty ;
    if(currentgroup != -1)
        _nLawQty= GetGroupLawQty(currentgroup) ;
    else
        _nLawQty = GetGroupLawQty(0) ;
    if(lastgroup != currentgroup)
    {
        _scanner.fLawStart = 0 ;
        _scanner.fLawStop   =   _nLawQty;
    }
    *fStart_  = _scanner.fLawStart 			;
    *fStop_   = _scanner.fLawStop  ;
    *fStart2_   =   0;
    *fStop2_    =   _nLawQty ;
    *fstep      =   1;
    GROUP_CONFIG& _group = m_pConfig->group[currentgroup>0?currentgroup:0] ;
    if(setup_GROUP_MODE_PA == _group.eGroupMode)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
        {
            LAW_CONFIG* _law = GetLawConfig(currentgroup>0?currentgroup:0);
            float _fStartAngle  =  _law->nAngleStartRefract / 10.0 ;
            float _fStepAngle   =  _law->nAngleStepRefract / 10.0  ;

            *fStart_  = _fStartAngle + _scanner.fLawStart * _fStepAngle;
            *fStop_   = _fStartAngle + _scanner.fLawStop * _fStepAngle;
            *fStart2_ = _fStartAngle;
            *fStop2_  = _fStartAngle + _nLawQty * _fStepAngle;
            *fstep    = _fStepAngle;
        }
    }
}

void ParameterProcess::ChangeCscanIndexstart( double* fStart_ )
{
    SCANNER& _scanner = m_pConfig->common.scanner;
    _scanner.fLawStart = *fStart_;
    GROUP_CONFIG& _group = m_pConfig->group[currentgroup>0?currentgroup:0] ;
    if(setup_GROUP_MODE_PA == _group.eGroupMode)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
        {
            LAW_CONFIG* _law = GetLawConfig(currentgroup>0?currentgroup:0);
            float _fStartAngle  =  _law->nAngleStartRefract / 10.0 ;
            float _fStepAngle   =  _law->nAngleStepRefract / 10.0  ;
            _scanner.fLawStart  =   (*fStart_ - _fStartAngle ) / _fStepAngle;
        }
    }
}

void ParameterProcess::ChangeCscanIndexstop( double* fStop_ )
{
    SCANNER& _scanner = m_pConfig->common.scanner;
    _scanner.fLawStop = *fStop_;

    GROUP_CONFIG& _group = m_pConfig->group[currentgroup>0?currentgroup:0] ;
    if(setup_GROUP_MODE_PA == _group.eGroupMode)
    {
        if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
        {
            LAW_CONFIG* _law = GetLawConfig(currentgroup>0?currentgroup:0);
            float _fStartAngle  =  _law->nAngleStartRefract / 10.0 ;
            float _fStepAngle   =  _law->nAngleStepRefract / 10.0  ;
            _scanner.fLawStop  =   (*fStop_ - _fStartAngle ) / _fStepAngle;
        }
    }
}

void ParameterProcess::ChangeCscanruler( int fscanstart, int fscanend)
{
    SCANNER& _scanner = m_pConfig->common.scanner;
    _scanner.fScanStart2 = fscanstart;
    _scanner.fScanend = fscanend;

}

//计算步进轴覆盖的长度，假如长度大于步进step表示有重复覆盖，小于表示有空白，适用于二维扫查
float ParameterProcess::GetRasterCoveredLength( int nGroupId_)
{
    float start, stop;
    GetSImageHorizentalRange( nGroupId_, &start, &stop);
    return abs( stop - start);
}

//计算步进轴的当前位置，要考虑Law的位置，适用于二维扫查
float ParameterProcess::GetRasterCurrentIndexPos( int nGroupId_)
{
    SCANNER& _scanner = m_pConfig->common.scanner;
    float indexPos = _scanner.fIndexPos;
    float coverlength = GetRasterCoveredLength(nGroupId_);
    int beamQty = GetGroupLawQty(nGroupId_);
    int curLaw = m_pConfig->group[nGroupId_].afCursor[setup_CURSOR_LAW];
    float curPos = curLaw * coverlength / beamQty;
    return indexPos + curPos;
}

//通过步进轴位置计算出步进和 law
void ParameterProcess::GetRasterIndexAndLaw(int nGroupId_, float pos, float *index, int *law)
{
    SCANNER& _scanner = m_pConfig->common.scanner;
    int indexIndex = pos / _scanner.fIndexStep;
    float indexPos = indexIndex * _scanner.fIndexStep;
    float _remainder = pos - indexPos;
    float coverlength = GetRasterCoveredLength(nGroupId_);
    int beamQty = GetGroupLawQty(nGroupId_);
    int lawPos = beamQty * _remainder / coverlength;
    if( lawPos >= beamQty){
        lawPos = beamQty - 1;
    }
    *index = indexPos;
    *law   = lawPos;
}

//计算步进轴一个分辨率内的beam数，一个beam对应一个像素，画栅格扫查
int ParameterProcess::GetRasterIndexStepBeam( int nGroupId_)
{
    float range = GetRasterCoveredLength(nGroupId_);
    SCANNER& _scanner = m_pConfig->common.scanner;
    float step = _scanner.fIndexStep;
    int beamQty = GetGroupLawQty(nGroupId_);
    float buff = (step * beamQty / range) + 0.5;
    int stepBeam = (int)buff;
    if(stepBeam == 0){
        stepBeam++;
    }
    return stepBeam;
}

void ParameterProcess::GetSImageHorizentalRange(int nGroupId_ , float* fStart_ , float* fStop_)
{
	float _fStart = 0 ;
	float _fStop  = 0 ;
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;

	if(_group.eGroupMode != setup_GROUP_MODE_PA)  return  ;
	LAW_CONFIG _law = _group.law ;
	float _fAngleStart = _law.nAngleStartRefract / 10.0 ;
	float _fAngleStop  = _law.nAngleStopRefract / 10.0  ;
	float _fSampleStart= _group.fSampleStart  ;
	float _fSampleStop = _fSampleStart + _group.fSampleRange  ;
	float*   _pBeamPos = _group.afBeamPos	   ;
	int       _nLawQty = GetGroupLawQty(nGroupId_) ;
	bool    _bWedgeRev = (_pBeamPos[_nLawQty - 1] - _pBeamPos[0]) > 0 ? false : true ;

	if(_law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
	{
		float _pos1 = _fSampleStart * sin(DEGREE_TO_ARCH(_fAngleStart))  ;
		float _pos2 = _fSampleStart * sin(DEGREE_TO_ARCH(_fAngleStop))  ;
		float _pos3 = _fSampleStop * sin(DEGREE_TO_ARCH(_fAngleStart))  ;
		float _pos4 = _fSampleStop * sin(DEGREE_TO_ARCH(_fAngleStop))  ;

		_fStart  = _pos1 > _pos3 ? _pos3 : _pos1 ;
		_fStop   = _pos2 > _pos4 ? _pos2 : _pos4 ;

		ParameterProcess _process ;
		int _nLawQty = _process.GetGroupLawQty(nGroupId_) ;
		if(_bWedgeRev) {
			_fStart +=  _pBeamPos[_nLawQty - 1]  ;
			_fStop  +=  _pBeamPos[0]  ;
		} else {
			_fStart +=  _pBeamPos[0]  ;
			_fStop  +=  _pBeamPos[_nLawQty - 1]  ;
		}
	}
	else
	{
		float _pos1  = _fSampleStart * sin(DEGREE_TO_ARCH(_fAngleStart))  ;
		float _pos2  = _fSampleStop * sin(DEGREE_TO_ARCH(_fAngleStart))   ;

		ParameterProcess _process ;
		int _nLawQty = _process.GetGroupLawQty(nGroupId_);

		if(_bWedgeRev) {
			if(_fAngleStart < 0) {
				_fStop   = _pos1 +  _pBeamPos[0]  ;
				_fStart  = _pos2 +  _pBeamPos[_nLawQty - 1]  ;
			} else {
				_fStop   = _pos2 +  _pBeamPos[0]  ;
				_fStart  = _pos1 +  _pBeamPos[_nLawQty - 1]  ;
			}
		} else {
			if(_fAngleStart < 0) {
				_fStart = _pos2 +  _pBeamPos[0]  ;
				_fStop  = _pos1 +  _pBeamPos[_nLawQty - 1]  ;
			} else {
				_fStart = _pos1 +  _pBeamPos[0]  ;
				_fStop  = _pos2 +  _pBeamPos[_nLawQty - 1]  ;
			}
		}
	}

	*fStart_ =  _fStart ;
	*fStop_  =  _fStop ;
	if(FLOAT_EQ(*fStart_ , *fStop_)) *fStop_ = *fStart_ + 1 ;
}

/*!
  \brief 用于画S扫垂直的标尺范围

  \param nGroupId_  组Id
  \param fStart_    计算得出的开始位置的深度
  \param fStop_     计算得出的结束位置的深度

  \return 不是PA组返回1，PA组返回0

*/
int  ParameterProcess::GetSImageVerticalRange(int nGroupId_ , float* fStart_ , float* fStop_)
{
	*fStart_ = 0 ;
	*fStop_  = 0 ;
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
    if(_group.eGroupMode != setup_GROUP_MODE_PA)  return 1 ;
	LAW_CONFIG _law = _group.law ;
	float _fAngleStart = _law.nAngleStartRefract / 10.0 ;
	float _fAngleStop  = _law.nAngleStopRefract / 10.0 ;
	float _fSampleStart= _group.fSampleStart  ;
	float _fSampleStop = _fSampleStart + _group.fSampleRange  ;
	if(_law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
	{
		float _pos1 = _fSampleStart * cos(DEGREE_TO_ARCH(_fAngleStart))  ;
		float _pos2 = _fSampleStart * cos(DEGREE_TO_ARCH(_fAngleStop))  ;
		float _pos3 = _fSampleStop * cos(DEGREE_TO_ARCH(_fAngleStart))  ;
		float _pos4 = _fSampleStop * cos(DEGREE_TO_ARCH(_fAngleStop))  ;

		*fStart_  = _pos1 > _pos2 ? _pos2 : _pos1 ;
        if(!_group.m_Retype)
        {
          *fStart_=*fStart_;
        }else
            {
           *fStart_=*fStart_-OFFSET_Y;

            }

		if(_fAngleStart * _fAngleStop < 0)
			*fStop_ = _fSampleStop ;
		else
			*fStop_   = _pos3 > _pos4 ? _pos3 : _pos4 ;

        if(!_group.m_Retype)
        {
          *fStop_=*fStop_;
        }else
        {
            *fStop_=*fStop_-OFFSET_Y;
        }


	}


	else
	{
		*fStart_ = _fSampleStart * cos(DEGREE_TO_ARCH(_fAngleStart))  ;
		*fStop_  = _fSampleStop  * cos(DEGREE_TO_ARCH(_fAngleStart))  ;
	}

	if(FLOAT_EQ(*fStart_ , *fStop_)) *fStop_ = *fStart_ + 1 ;
    return 0;
}

void ParameterProcess::GetSScanHorizentalRange(int nGroupId_ , float* fStart_ , float* fStop_)
{
	GetSImageHorizentalRange(nGroupId_ , fStart_ , fStop_);

	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	setup_PROBE_ANGLE _eAngle = GetProbeAngle(nGroupId_) ;
	float _fAxisOffset ;

	float _fStart = *fStart_;
	float _fStop  = *fStop_;

	if(_eAngle == setup_PROBE_PART_SKEW_0 )
	{
		_fAxisOffset = _group.fScanOffset ;
		*fStart_ =  _fStart + _fAxisOffset  ;
		*fStop_  =  _fStop  + _fAxisOffset  ;
	}
	else if (_eAngle == setup_PROBE_PART_SKEW_90 )
	{
		_fAxisOffset = _group.fIndexOffset  ;
		*fStart_ =  _fStart + _fAxisOffset  ;
		*fStop_  =  _fStop  + _fAxisOffset  ;
	}
	else if ( _eAngle == setup_PROBE_PART_SKEW_180 )
	{
		_fAxisOffset = _group.fScanOffset  ;
		*fStart_ = _fAxisOffset  - _fStop  ;
		*fStop_  = _fAxisOffset  - _fStart ;
	}
	else if ( _eAngle == setup_PROBE_PART_SKEW_270 )
	{
		_fAxisOffset = _group.fIndexOffset  ;
		*fStart_ = _fAxisOffset  - _fStop  ;
		*fStop_  = _fAxisOffset  - _fStart ;
	}
}

int  ParameterProcess::GetSScanVerticalRange(int nGroupId_ , float* fStart_ , float* fStop_)
{
    return GetSImageVerticalRange(nGroupId_ , fStart_ , fStop_);
}


int ParameterProcess::DistMmToDotPos(int nGroupId_ , int nLawId_, float fDist_)
{
	float _fSampleStart = GetSampleStart(nGroupId_ , nLawId_);
	float _fSampleRange = GetSampleRange(nGroupId_ , nLawId_);

	int _iQty = GetGroupPointQty(nGroupId_);
	int _iDot = _iQty * (fDist_ - _fSampleStart) / _fSampleRange;

	return _iDot;
}

float ParameterProcess::DistDotPosToMm(int nGroupId_ , int nPos_)
{
	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_]  ;
	int _iQty = GetGroupPointQty(nGroupId_);
	float _fDist = nPos_ * _pGroup->fSampleRange / _iQty + _pGroup->fSampleStart;
	return _fDist;
}

float ParameterProcess::DistUsToMm(int nGroupId_ , float fTime_)
{
	float _fVelocity = m_pConfig->group[nGroupId_].fVelocity / 1000.0 ;
	float _fDist = fTime_;
	_fDist /= 2;
	_fDist = _fDist * _fVelocity ;
	return _fDist ;
}

float ParameterProcess::DistMmToUs(int nGroupId_ , float fDist_)
{
	//GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_]  ;
	float _fVelocity = m_pConfig->group[nGroupId_].fVelocity / 1000.0;
	float _fTime = fDist_;
	//if(_pGroup->eTravelMode == setup_TRAVEL_MODE_HALF_PATH) {
	_fTime *= 2;
	//}
	_fTime = _fTime / _fVelocity ;
	return _fTime ;
}

float ParameterProcess::DistNsToMm(int nGroupId_ , int nTime_)
{
	float _fVelocity = m_pConfig->group[nGroupId_].fVelocity / 1000.0 ;
	float _fDist = nTime_ / 1000.0 ;
	_fDist /= 2;
	_fDist = _fDist * _fVelocity ;
	return _fDist ;
}

int   ParameterProcess::DistMmToNs(int nGroupId_ , float fDist_)
{
	//GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_]  ;
	float _fVelocity = m_pConfig->group[nGroupId_].fVelocity / 1000.0;
	float _fTime = fDist_ * 1000.0 ;
	//if(_pGroup->eTravelMode == setup_TRAVEL_MODE_HALF_PATH) {
	_fTime *= 2;
	//}
	_fTime = _fTime / _fVelocity ;
    return _fTime ;
}

int ParameterProcess::SCanAngleToCScanLineAngle(int nGroupId_, float _fCursor)
{
    int tmpCScanLinePos;
    int _nLawQty = GetGroupLawQty(nGroupId_) ;
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
    LAW_CONFIG _law = _group.law ;
    float _fAngleStart = _law.nAngleStartRefract / 10.0 ;
    float _fAngleStep = _law.nAngleStepRefract/10.0;
    float _fAngleStop  = _law.nAngleStopRefract / 10.0 ;
    qDebug("****** %s[%d]: lawType:%d, focalType:%d, angleType:%d, _fcursor:%.2f, depthStart:%.2f, depthStop:%.2f, angleStart:%d"
           "angleStep:%d, angleStop:%d, offsetStart:%.2f, offsetStop:%.2f, posStart:%.2f, posStop:%.2f, posStep:%.2f", __FUNCTION__, __LINE__,
           _law.eLawType, _law.eFocalType, _law.eAngleType, _fCursor, _law.fDepthStart, _law.fDepthStop,
           _law.nAngleStartRefract, _law.nAngleStepRefract, _law.nAngleStopRefract, _law.fOffsetStart, _law.fOffsetStop,
           _law.fPositionStart, _law.fPositionStop, _law.fPositionStep);
    if((_law.eLawType == setup_LAW_TYPE_LINEAR || _law.eLawType == setup_LAW_TYPE_TFM) && _law.eFocalType == 1){
        return (int)(_fCursor);
    }

    if(_fCursor  > _fAngleStart){
        tmpCScanLinePos = (int)((_fCursor - _fAngleStart)/_fAngleStep);
        if(tmpCScanLinePos > _fAngleStop){
            tmpCScanLinePos = (_fAngleStop - _fAngleStart)/_fAngleStep;
        }
    }else{
        tmpCScanLinePos = 0;
    }
    qDebug("_fAngleStop:%.2f, _nLawQty:%d", _fAngleStop, _nLawQty);
    return tmpCScanLinePos;
}

//通过S扫的点坐标查询到此点的lawId和在此beam上的位置index,返回值 false表示点在s扫范围外
bool ParameterProcess::SscanPointMaptoLawAndindex(int nGroupId_, QPointF point, int &lawId, int &pointIndex)
{
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_];
    TOPC_INFO& _TOPCInfo = _group.TopCInfo;
    int _nPointQty = _group.nPointQty;
    float pointx = point.x();
    float pointy = point.y();
    float indexOffset = _group.fIndexOffset;

    switch (_group.eSkew) {
    case setup_PROBE_PART_SKEW_0:
        break;
    case setup_PROBE_PART_SKEW_90:
        pointx -= indexOffset;
        break;
    case setup_PROBE_PART_SKEW_180:
        pointx = -pointx;
        break;
    case setup_PROBE_PART_SKEW_270:
        pointx = -pointx;
        pointx += indexOffset;
        break;
    default:
        break;
    }

    if( _TOPCInfo.startX > pointx || _TOPCInfo.stopX < pointx || _TOPCInfo.startY > pointy || _TOPCInfo.stopY < pointy){
        return false;
    }
    int index_x = ( pointx - _TOPCInfo.startX) / ( _TOPCInfo.stopX - _TOPCInfo.startX) * (_TOPCInfo.pixelWidth - 1);
    int index_y = ( pointy - _TOPCInfo.startY) / ( _TOPCInfo.stopY - _TOPCInfo.startY) * (_TOPCInfo.pixelHeigh - 1);
    int index_offset = _TOPCInfo.pixelWidth * index_y + index_x;
    int buff = _TOPCInfo.pDataIndex[index_offset];
    if(buff == 0){
        return false;
    }
    lawId = buff / _nPointQty;
    pointIndex = buff % _nPointQty;
    return true;
}

//获取闸门内峰值在S扫对应的坐标
void ParameterProcess::SscanGetPeakPoint(int nGroupId_, int lawId, setup_GATE_NAME eGate_, QPointF &point)
{
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_];
    float indexOffset = _group.fIndexOffset;
    PEAK_CONFIG _info[setup_GATE_MAX];
    int scanIndex = GetScanIndexPos();
    GetGatePeakInfos(nGroupId_, scanIndex, lawId, _info);
    float Posy = _info[eGate_].fH;
    float posx = _info[eGate_].fL + GetBeamInsertPos( nGroupId_, lawId);
    switch (_group.eSkew) {
    case setup_PROBE_PART_SKEW_0:
        posx = posx;
        break;
    case setup_PROBE_PART_SKEW_90:
        posx += indexOffset;
        break;
    case setup_PROBE_PART_SKEW_180:
        posx = -posx;
        break;
    case setup_PROBE_PART_SKEW_270:
        posx = -posx + indexOffset;
        break;
    default:
        posx = posx;
        break;
    }
    point.setX(posx);
    point.setY(Posy);
}

float ParameterProcess::CScanLineAngleToScanLineAngle(int nGroupId_, int _nPos)
{
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
    LAW_CONFIG _law = _group.law ;
    float _fAngleStart = _law.nAngleStartRefract / 10.0 ;
    float _fAngleStep = _law.nAngleStepRefract/10.0;

    if(_nPos<2 || _nPos>65535){
        return _fAngleStart;
    }

    int tmpCScanLinePos =  _fAngleStart + _nPos*_fAngleStep;
    return tmpCScanLinePos;
}
/*
float ParameterProcess::DistNsToMm(int nGroupId_ , int nTime_)
{
	float _fVelocity = m_pConfig->group[nGroupId_].fVelocity / 1000.0 ;
	float _fDist = nTime_ / 2000.0 ;
	_fDist = _fDist * _fVelocity ;
	return _fDist ;
}

int   ParameterProcess::DistMmToNs(int nGroupId_ , float fDist_)
{
	float _fVelocity = m_pConfig->group[nGroupId_].fVelocity / 1000.0;
	float _fTime = fDist_ * 2000.0 ;
	_fTime = _fTime / _fVelocity ;
	return _fTime ;
}
*/
QString ParameterProcess::GetSonicAxisUnit(int nGroupId_)
{
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_];
    if(_group.eTravelMode == setup_TRAVEL_MODE_TIME){
        return QString("us");
    }else{
       return QString("mm");
    }
}

QString ParameterProcess::GetScanAxisUnit()
{
	SCANNER _scan = m_pConfig->common.scanner  ;
    if(_scan.eScanEncoderType == setup_ENCODER_TYPE_TIMER)
		return QString("s");
	else
		return QString("mm");
}

QString ParameterProcess::GetIndexAxisUnit()
{
	return QString("mm");
}

QString ParameterProcess::GetCscanIndexUnit(int nGroupId_)
{
    if(m_pConfig->common.scanner.eScanType == setup_SCAN_TYPE_RASTER){
        return QString("mm");
    }
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	if(setup_GROUP_MODE_PA == _group.eGroupMode)
	{
        if(_group.TopCInfo.TOPCStatus){
            return QString("mm");
        }else{
            if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
                return QString("deg");
            else
                return QString("vpa");
        }
	}
	return QString("");
}

setup_CSCAN_SOURCE_MODE ParameterProcess::GetCScanSource(int nGroupId_ , int eCScan_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	return _group.eCScanSource[eCScan_] ;
}


float ParameterProcess::GetLawAngle(int nGroupId_ , int nLawId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	LAW_CONFIG& _law = _group.law ;
	float ret ;
	if((_law.eLawType == setup_LAW_TYPE_AZIMUTHAL) && (_group.eGroupMode == setup_GROUP_MODE_PA))
		ret = (_law.nAngleStartRefract + _law.nAngleStepRefract * nLawId_) / 10.0 ;
	else
		ret = _law.nAngleStartRefract / 10.0 ;

	return ret;
}

float ParameterProcess::GetSampleStart(int nGroupId_ , int nLawId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	float _fRet  ;
	if(_group.eTravelMode == setup_TRAVEL_MODE_HALF_PATH){
		_fRet = _group.fSampleStart ;
	}else if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH){
        if(_group.eGroupMode == setup_GROUP_MODE_PA){
            float _fAngle = GetLawAngle(nGroupId_ , nLawId_);
            _fRet = _group.fSampleStart * cos(DEGREE_TO_ARCH(_fAngle));
        }else{
            _fRet = _group.fSampleStart;
        }

    }else{
        _fRet = _group.nTimeStart / 1000.0;
    }
	return _fRet;
}

float ParameterProcess::GetSampleRange(int nGroupId_ , int nLawId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	float _fRet  ;
	if(_group.eTravelMode == setup_TRAVEL_MODE_HALF_PATH){
		_fRet = _group.fSampleRange ;
    }else if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH){
        if(_group.eGroupMode == setup_GROUP_MODE_PA){
            float _fAngle = GetLawAngle(nGroupId_ ,nLawId_);
            _fRet = _group.fSampleRange * cos(DEGREE_TO_ARCH(_fAngle));
        }else{
            _fRet = _group.fSampleRange;
        }
    }else{
        _fRet = _group.nTimeRange / 1000.0;
    }
	return _fRet;
}

float ParameterProcess::GetSampleStartSoundpath(int nGroupId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	float _fRet = _group.fSampleStart ;
	return _fRet ;
}

float ParameterProcess::GetSampleRangeSoundpath(int nGroupId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	float _fRet = _group.fSampleRange ;
	return _fRet ;
}


float ParameterProcess::GetMaterialVelocity(int nGroupId_ , int bTran_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_]   ;
	MATERIAL& _material  = _group.part.material ;
	return (bTran_ ?  _material.fVelocityTran : _material.fVelocityLon)	;
}

float ParameterProcess::GetPartThickness(int nGroupId_) const
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_]   ;
	return _group.part.afSize[0] ;
}

float ParameterProcess::GetWeldBorder(int nGroupId_)
{
    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_];
    float weldBorder = 10;
    if(PHASCAN_I_FORMAT == _group.part.weldFormat){
        WELD& _weld = _group.part.weld;
        switch (_weld.eType) {
        case setup_WELD_I:
            weldBorder = _weld.weland_offset;
            break;
        case setup_WELD_V:
        case setup_WELD_DV:
            weldBorder = _weld.weland_offset + tan(DEGREE_TO_ARCH(_weld.fizone_angle)) * _weld.fizone_height;
            break;
        case setup_WELD_U:
            weldBorder = _weld.weland_offset + tan(DEGREE_TO_ARCH(_weld.fizone_angle))*
                    _weld.fizone_height + _weld.fizone_radius;
            break;
        case setup_WELD_DIFF_DV:
            weldBorder =  _weld.weland_offset + tan(DEGREE_TO_ARCH(_weld.fizone_angle))
                    * _weld.fizone_height;
            break;
        case setup_WELD_J:
            weldBorder = _weld.weland_offset + tan(DEGREE_TO_ARCH(_weld.fizone_angle))*
                    _weld.fizone_height + _weld.fizone_radius;
            break;
        case setup_WELD_VY:
            weldBorder = _weld.weland_offset + tan(DEGREE_TO_ARCH(_weld.fizone_angle))
                    * _weld.fizone_height;
            break;
        default:
            break;
        }
    }else{
        WELD_II& _weld = _group.part.weld_ii;
        switch (_weld.eType) {
        case I:
            weldBorder = _weld.I.w;
            break;
        case V:
            weldBorder = _weld.V.w1;
            break;
        case U:
            weldBorder = _weld.U.w1;
            break;
        case VY:
            weldBorder = _weld.VY.w1;
            break;
        case VV:
            weldBorder = (_weld.VV.w1 > _weld.VV.w3) ? _weld.VV.w1 : _weld.VV.w3;
            break;
        case UU:
            weldBorder = (_weld.UU.w1 > _weld.UU.w3) ? _weld.UU.w1 : _weld.UU.w3;
            break;
        case UV:
            weldBorder = (_weld.UV.w1 > _weld.UV.w3) ? _weld.UV.w1 : _weld.UV.w3;
            break;
        default:
            break;
        }
    }
    return weldBorder;
}

void  ParameterProcess::GetWedgePosition(int nGroupId_ , float* fScanOffset_ , float* fIndexOffset_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_]   ;
	if(fScanOffset_)
		*fScanOffset_ = _group.fScanOffset ;
	if(fIndexOffset_)
		*fIndexOffset_= _group.fIndexOffset ;
}

setup_PROBE_ANGLE ParameterProcess::GetProbeAngle(int nGroupId_) const
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_]   ;
	return _group.eSkew;
}

setup_RECTIFIER_MODE ParameterProcess::GetRectifierMode(int nGroupId_)  const
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_]   ;
	return _group.eRectifier;
}

setup_PROBE_ANGLE  ParameterProcess::GetGroupSkewType(int nGroupId_) const
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_]   ;
	return _group.eSkew;
}

setup_TX_RX_MODE  ParameterProcess::GetGroupTxRxMode(int nGroupId_) const
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_]   ;
	return _group.eTxRxMode;
}

float* ParameterProcess::GetBeamInsertPos(int nGroupId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_]   ;
	return _group.afBeamPos ;
}

float  ParameterProcess::GetBeamInsertPos(int nGroupId_ , int nLawId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_]   ;
	float _fValue = _group.afBeamPos[nLawId_] ;
	return _fValue ;
}

int  ParameterProcess::GetGroupPointQty(int nGroupId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_]   ;
	return _group.nPointQty ;
}

PART_CONFIG* ParameterProcess::GetPart(int nGroupId_)
{
	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_];
	return &_pGroup->part;
}

GATE_CONFIG* ParameterProcess::GetGateInfo(int nGroupId_ , setup_GATE_NAME eGate_)
{
	if(eGate_ >= setup_GATE_MAX)  return 0;
	GATE_CONFIG* _pGate = &m_pConfig->group[nGroupId_].gate[eGate_]  ;
	return _pGate ;
}


PROBE_CONFIG* ParameterProcess::GetProbeConfig(int nGroupId_ , int TxRx_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	PROBE_CONFIG* _pProbe  ;
	_pProbe = TxRx_ ? (&group.probe[1]) : (&group.probe[0]) ;
	return _pProbe  ;
}

WEDGE_CONFIG* ParameterProcess::GetWedgeConfig(int nGroupId_ , int TxRx_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	WEDGE_CONFIG* _pWedge  ;
	_pWedge = TxRx_ ? (&group.wedge[1]) : (&group.wedge[0]) ;
	return _pWedge  ;
}

LAW_CONFIG*   ParameterProcess::GetLawConfig(int nGroupId_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	LAW_CONFIG* _pLaw  = &group.law ;

	return _pLaw  ;

}

GROUP_CONFIG* ParameterProcess::GetGroupConfig(int nGroupId_)
{
	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_]   ;
	return _pGroup  ;
}

WELD* ParameterProcess::GetWeld(int nGroupId_)
{
	GROUP_CONFIG* _pGroup = &m_pConfig->group[nGroupId_]   ;
	return &_pGroup->part.weld  ;
}

void  ParameterProcess::SetWeld(int nGroupId_ , WELD* pWeld_ )
{
	GROUP_CONFIG* _pGroup = & m_pConfig->group[nGroupId_] ;
	void* _pWeld = &_pGroup->part.weld ;
	memcpy(_pWeld , (void*)pWeld_  , sizeof(WELD)) ;
}

void* ParameterProcess::GetPalete(int nGroupId_ , PALETTE_NAME eName_)
{
	if(eName_>= PALETTE_NAME_MAX) eName_ = PALETTE_AMP ;
	GROUP_COLOR& _color = m_pConfig->group[nGroupId_].color  ;
	switch(eName_)
	{
	case	PALETTE_AMP :
		return (void*)_color.Amp ;
		break;
	case	PALETTE_THICKNESS:
		return (void*)_color.Thickness ;
		break;
	case	PALETTE_RECTIFY:
		return (void*)_color.Rf ;
		break;
	default:
		break;
	}
	return 0 ;
}
/****************************************************************************
  Description:   计算闸门读数 幅度
  Input:  32bit 的闸门采样数据 前31-22位为幅度  0-21位为位置
*****************************************************************************/
float ParameterProcess::GetGateValueAmp(int nGroupId_ , int nLaw_ , setup_GATE_NAME eGate_)
{

    GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;

    PEAK_CONFIG _info[setup_GATE_MAX];
    GetGatePeakInfos(nGroupId_, GetScanIndexPos(), nLaw_, _info);
    float _fRet = _info[eGate_].iY;
    if(_group.eRectifier) {
        _fRet = _fRet / (float)WAVE_MAX;
    } else {
        float _half = (float)WAVE_MAX/2.0;

        _fRet = (_fRet - _half) / (float)_half;
        if(_fRet > 1)	_fRet = 1;
        if(_fRet < -1)	_fRet = -1;
    }

    return _fRet * 100.0f;
}
/******************************************************
  Description:   计算闸门读数 位置
  Input:  32bit 的闸门采样数据 前31-22位为幅度  0-21位为位置
******************************************************/
float ParameterProcess::GetGateValuePos(int nGroupId_ , int nLaw_ , setup_GATE_NAME eGate_ , GATE_POS_VALUE_TYPE eType_ )
{
	float _fRet = 0 ;
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	float _fVelocity = _group.fVelocity ;
	unsigned int _nGateValue   = GetLawGateDWORD(nGroupId_ , nLaw_ , eGate_) ;

	_fRet = (float)(_nGateValue & 0xfffff) ;
	switch(eType_)
	{
	case NS_WITH_DELAY	 :
		_fRet = _fRet * 10 - _group.nPulserWidth ;
		break;
	case MM_WITH_DELAY	 :
		_fRet = ( _fRet * 10 - _group.nPulserWidth ) * _fVelocity / 2000000.0;
		break;
	case NS_WITHOUT_DELAY  :
		_fRet = _fRet * 10 - _group.nWedgeDelay - _group.anBeamDelay[nLaw_] ;
		break;
	case MM_WITHOUT_DELAY  :
		_fRet = _fRet * 10 - _group.nWedgeDelay - _group.nPulserWidth - _group.anBeamDelay[nLaw_] ;
		_fRet = _fRet * _fVelocity / 2000000.0;
		break;
	case MM_TRUE_DEPTH:
		{
			_fRet = _fRet * 10 - _group.nWedgeDelay - _group.nPulserWidth - _group.anBeamDelay[nLaw_] ;
			_fRet = _fRet * _fVelocity / 2000000.0;
			float _fAngle = GetLawAngle(nGroupId_ , nLaw_) ;
			_fRet = _fRet * cos(DEGREE_TO_ARCH(_fAngle))   ;
		}
		break;
	case MM_HORIZENTAL_DIST:
		{
			_fRet = _fRet * 10 - _group.nWedgeDelay - _group.nPulserWidth - _group.anBeamDelay[nLaw_] ;
			_fRet = _fRet * _fVelocity / 2000000.0;
			float _fAngle = GetLawAngle(nGroupId_ , nLaw_) ;
			_fRet = _fRet * sin(DEGREE_TO_ARCH(_fAngle))   ;
		}
		break;
	default:
		break;
	};
	return _fRet ;
}

void ParameterProcess::InitScanOff(int nGroupId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_];
	m_fBScanOff[nGroupId_] = _group.fScanOffset;
	m_fCScanOff[nGroupId_] = _group.fScanOffset;
}

/*!
  \brief 获取耦合监控数据

  \param nGroupId_ 组ID

  \return 计算后的耦合监控数据

*/
QVector<WDATA> ParameterProcess::GetCoupleCScanData( int nGroupId_)
{
    coupleCScanGroupInfo &CScanInfo = m_pConfig->coupleCScanData[nGroupId_];
    float partThickness = GetPartThickness(nGroupId_);

    //初始化的时候和工件厚度改变时重新计算
    if( CScanInfo.calculateState && abs(partThickness - CScanInfo.oldPartThickness) < 0.1)
    {
        return CScanInfo.data;
    }

    if( !m_pConfig->group[nGroupId_].coupleMonitoringState)
    {
        CScanInfo.calculateState = true;
        return CScanInfo.data;
    }

    CScanInfo.calculateState = true;

    int recMax = m_pConfig->comTmp.nRecMax;
    CScanInfo.data.resize( recMax);

    CScanInfo.oldPartThickness = partThickness;

    float partStart = 0.75 * partThickness;
    float partRange = 0.5 * partThickness;

    int dataQty = m_pConfig->group[nGroupId_].nPointQty;
    float coupleStart = m_pConfig->group[nGroupId_].coupleMonitoringVelocity * m_pConfig->group[nGroupId_].nTimeStart/2000000.0;
    float coupleDepth = m_pConfig->group[nGroupId_].coupleMonitoringVelocity * m_pConfig->group[nGroupId_].nTimeRange/2000000.0;
    int fixSize = coupleStart / partThickness;
    if(fixSize < 0){
        fixSize = 0;
    }
    partStart = ( 0.75 + fixSize)* partThickness;

    float overlapStart;
    float overlapEnd;
    if( partStart > coupleStart)
    {
        overlapStart = partStart;
    }
    else
    {
        overlapStart = coupleStart;
    }

    if( partStart + partRange > coupleStart + coupleDepth)
    {
        overlapEnd = coupleStart + coupleDepth;
    }
    else
    {
        overlapEnd = partStart + partRange;
    }

    int startData;
    int endData;
    if( overlapEnd > overlapStart)
    {
        startData = (overlapStart - coupleStart) / coupleDepth * (dataQty - 1);
        endData = (overlapEnd - coupleStart) / coupleDepth * (dataQty - 1);
    }
    else
    {
        startData = 0;
        endData = 0;
    }

    if( startData == endData)
    {
        memset( CScanInfo.data.data(), 0x00, recMax);
        return CScanInfo.data;
    }

    WDATA* _pData = GetShadowDataPointer();
    //if(!_pData)  return 0 ;
    int _nFrameSize = GetTotalDataSize();
    int _nGroupOffset = GetGroupDataOffset(nGroupId_);
    int nLawId_ = GetGroupLawQty(nGroupId_);
    int _nLawOffset;
//    if(m_pConfig->group[nGroupId_].law.eLawType == setup_LAW_TYPE_TFM){
//        _nLawOffset  = nLawId_ * m_pConfig->group[nGroupId_].nPointQty;
//    }else{
        _nLawOffset  = nLawId_ * (m_pConfig->group[nGroupId_].nPointQty + setup_DATA_PENDIX_LENGTH);
    //}

    _pData = _pData + _nGroupOffset + _nLawOffset;

    for(int i = 0; i < recMax; i++)
    {
        if(m_pConfig->comTmp.nRecMark[i])
        {
            WDATA buff = 0;
            for( int j = startData; j <= endData; j++)
            {
                if( _pData[j] > buff)
                {
                    buff = _pData[j];
                }
            }
//            int cbuff = correctionPdata(buff);
//            if( cbuff > WAVE_MAX)
//            {
//                cbuff = WAVE_MAX;
//            }

//            CScanInfo.data[i] = (WDATA)cbuff;
            CScanInfo.data[i] = buff;
        }
        else
        {
            CScanInfo.data[i] = 0;
        }
        _pData += _nFrameSize;
    }
    return CScanInfo.data;
}

WDATA* ParameterProcess::GetTOPCData(int nGroupId_, int startX_, int stopX_, int startY_, int stopY_, int direction_)
{
    //qDebug()<<"startX_"<<nGroupId_<<startX_<<stopX_<<startY_<<stopY_;
    TOPC_DATA &TOPCData   = m_pConfig->group[nGroupId_].TopCData;
    TOPC_INFO &_TOPCInfo  = m_pConfig->group[nGroupId_].TopCInfo;
    if( TOPCData.startX == startX_ && TOPCData.stopX == stopX_ && TOPCData.startY == startY_
            && TOPCData.stopY == stopY_ && TOPCData.direction == direction_){
        return TOPCData.topcData;
    }
    TOPCData.startX = startX_;
    TOPCData.stopX  = stopX_;
    TOPCData.startY = startY_;
    TOPCData.stopY  = stopY_;
    TOPCData.direction = direction_;
    int rangeY = stopX_ - startX_;
    int recMax = m_pConfig->comTmp.nRecMax;
    int buff = rangeY * recMax;
    if(TOPCData.topcData){
        free(TOPCData.topcData);
    }
    TOPCData.topcData = (WDATA*)malloc( buff * sizeof(WDATA));
    //qDebug()<<"num"<<buff<<TOPCData.topcData;
    memset(TOPCData.topcData, 0x00, buff);
    WDATA* _disData = TOPCData.topcData;
    WDATA* _pData = GetShadowDataPointer();
    int _nFrameSize = GetTotalDataSize();
    int _nGroupOffset = GetGroupDataOffset(nGroupId_);
    _pData = _pData + _nGroupOffset;
    int j, n;
    for(int i = 0; i < recMax; i++){
        if(m_pConfig->comTmp.nRecMark[i]){
            if(direction_ == 0){
                for( j = startX_, n = 0; j < stopX_; j++, n++){
                    WDATA _buff = 0;
                    WDATA _nTmpValue = 0;
                    for( int k = startY_; k < stopY_; k++){
                        int index = k * _TOPCInfo.pixelWidth + j;
                        index = _TOPCInfo.pDataIndex[index];
                        if(index){
                            _buff = _pData[index];
                        }else{
                            _buff = 0;
                        }
                        if(_buff > _nTmpValue){
                            _nTmpValue = _buff;
                        }
                    }
                    _disData[recMax * n + i] = _nTmpValue;
                }
            }else{
                for(j = stopX_ - 1, n = 0; j >= startX_; j--, n++){
                    WDATA _buff = 0;
                    WDATA _nTmpValue = 0;
                    for( int k = startY_; k < stopY_; k++){
                        int index = k * _TOPCInfo.pixelWidth + j;
                        index = _TOPCInfo.pDataIndex[index];
                        if(index){
                            _buff = _pData[index];
                        }else{
                            _buff = 0;
                        }
                        if(_buff > _nTmpValue){
                            _nTmpValue = _buff;
                        }
                    }
                    _disData[recMax * n + i] = _nTmpValue;
                }
            }
        }
        _pData += _nFrameSize;
        //_disData += recMax;
    }
    return TOPCData.topcData;
}

WDATA* ParameterProcess::GetRasterData(int nGroupId_, setup_CSCAN_SOURCE_MODE source_mode)
{
    //峰值
    if(source_mode == setup_CSCAN_AMP_A || source_mode == setup_CSCAN_AMP_B){
        float sampleStart = m_pConfig->group[nGroupId_].fSampleStart;
        float sampleRange = m_pConfig->group[nGroupId_].fSampleRange;
        int _nPointQty = GetGroupPointQty(nGroupId_);
        int markLength = Config::instance()->data_mark_length();
        int beamQty = GetGroupLawQty(nGroupId_);
        int dataLength = markLength * beamQty;
        RASTER_DATA &RasterData = m_pConfig->group[nGroupId_].RasterData;
        if(RasterData.rasterData == NULL){
            RasterData.rasterData =  (WDATA*)malloc( dataLength * sizeof(WDATA));
        }

        U8* _pMarker = GetScanMarker(nGroupId_);

        int _nFrameOffset = GetTotalDataSize();
        int _nGroupOffset = GetGroupDataOffset(nGroupId_);
        int _nLawSize;

        _nLawSize = _nPointQty + setup_DATA_PENDIX_LENGTH;

        memset(RasterData.rasterData, 0x00, dataLength);
        for(int i = 0; i < markLength; i++){
            if(_pMarker[i]){
                int _index = GetRealScanIndex(nGroupId_, i);
                int offset = _nFrameOffset * _index + _nGroupOffset;
                int Roffset = _index * beamQty;
                for(int j = 0; j < beamQty; j++){
                    ///
                    PEAK_CONFIG _info[setup_GATE_MAX];
                    GetGatePeakInfos(nGroupId_, _index, j, _info);
                    float _fStart;	 // gate start position
                    float _fWidth;	 // gate width
                    if(source_mode == setup_CSCAN_AMP_A){
                        _fStart = _info[setup_GATE_A].fGs;
                        _fWidth = _info[setup_GATE_A].fGw;
                    }else{
                        _fStart = _info[setup_GATE_B].fGs;
                        _fWidth = _info[setup_GATE_B].fGw;
                    }

                    RasterData.fStart1 = _fStart;
                    RasterData.fWidth1 = _fWidth;
                    RasterData.rasterMode = raster_AMP;

                    int pointStart = 0;
                    int pointRange = 0;
                    if(_fStart < sampleStart){
                        if(_fStart + _fWidth <= sampleStart){
                            continue;
                        }else if(_fStart + _fWidth <= sampleStart + sampleRange){
                            pointStart = 0;
                            pointRange = _nPointQty * (_fStart + _fWidth - sampleStart) / sampleRange;

                        }else{
                            pointStart = 0;
                            pointRange = _nPointQty;
                        }
                    }else if(_fStart < sampleStart + sampleRange){
                        if(_fStart + _fWidth <= sampleStart + sampleRange){
                            pointStart = _nPointQty * (_fStart - sampleStart) / sampleRange;
                            pointRange = _nPointQty * _fWidth / sampleRange;
                        }else{
                            pointStart = _nPointQty * (_fStart - sampleStart) / sampleRange;
                            pointRange = _nPointQty * (sampleStart + sampleRange - _fStart) / sampleRange;
                        }
                    }////

                    WDATA* _pData = GetShadowDataPointer();
                    _pData += offset + pointStart + j * _nLawSize;
                    WDATA buff = 0;
                    for(int k = 0; k < pointRange; k++){
                        if(_pData[k] > buff){
                            buff = _pData[k];
                        }
                    }
                    RasterData.rasterData[Roffset + j] = buff;
                }
            }
        }
        return RasterData.rasterData;
    }else if(source_mode == setup_CSCAN_POS_I || source_mode == setup_CSCAN_POS_A || source_mode == setup_CSCAN_POS_B){
        RASTER_DATA &RasterData = m_pConfig->group[nGroupId_].RasterData;
        int markLength = Config::instance()->data_mark_length();
        int beamQty = GetGroupLawQty(nGroupId_);
        int dataLength = markLength * beamQty;
        if(RasterData.rasterData == NULL){
            RasterData.rasterData =  (WDATA*)malloc( dataLength * sizeof(WDATA));
        }
        memset(RasterData.rasterData, 0x00, dataLength);
        float sampleStart = m_pConfig->group[nGroupId_].fSampleStart;
        float sampleRange = m_pConfig->group[nGroupId_].fSampleRange;
        int _nPointQty = GetGroupPointQty(nGroupId_);
        float _fMinThickness = m_pConfig->group[nGroupId_].fMinThickness;
        float _fMaxThickness = m_pConfig->group[nGroupId_].fMaxThickness;

        U8* _pMarker = GetScanMarker(nGroupId_);
        int _nFrameOffset = GetTotalDataSize();
        int _nGroupOffset = GetGroupDataOffset(nGroupId_);
        int _nLawSize;
        _nLawSize = _nPointQty + setup_DATA_PENDIX_LENGTH;
        float _posRange = _fMaxThickness - _fMinThickness;

        float _fScale = GetRefGainScale(nGroupId_);
        int _nTmpValue;
        float _nDepth;
        for(int i = 0; i < markLength; i++){
            if(_pMarker[i]){
                int _index = GetRealScanIndex(nGroupId_, i);
                int offset = _nFrameOffset * _index + _nGroupOffset;
                int Roffset = _index * beamQty;
                for(int j = 0; j < beamQty; j++){
                    ///
                    //位置
                    PEAK_CONFIG _info[setup_GATE_MAX];
                    GetGatePeakInfos(nGroupId_, _index, j, _info);
                    float _fStart;	 // gate start position
                    float _fWidth;	 // gate width
                    unsigned int _threshold;
                    if(source_mode == setup_CSCAN_POS_I){
                        _fStart = _info[setup_GATE_I].fGs;
                        _fWidth = _info[setup_GATE_I].fGw;
                        _threshold = _info[setup_GATE_I].fGh;
                    }else if(source_mode == setup_CSCAN_POS_A){
                        _fStart = _info[setup_GATE_A].fGs;
                        _fWidth = _info[setup_GATE_A].fGw;
                        _threshold = _info[setup_GATE_A].fGh;
                    }else{
                        _fStart = _info[setup_GATE_B].fGs;
                        _fWidth = _info[setup_GATE_B].fGw;
                        _threshold = _info[setup_GATE_B].fGh;
                    }

                    RasterData.fStart1 = _fStart;
                    RasterData.fWidth1 = _fWidth;
                    RasterData.threshold1 = _threshold;
                    RasterData.fMinThickness = _fMinThickness;
                    RasterData.fMaxThickness = _fMaxThickness;
                    RasterData.rasterMode = raster_POS_ONE;

                    int pointStart = 0;
                    int pointRange = 0;
                    if(_fStart < sampleStart){
                        if(_fStart + _fWidth <= sampleStart){
                            continue;
                        }else if(_fStart + _fWidth <= sampleStart + sampleRange){
                            pointStart = 0;
                            pointRange = _nPointQty * (_fStart + _fWidth - sampleStart) / sampleRange;

                        }else{
                            pointStart = 0;
                            pointRange = _nPointQty;
                        }
                    }else if(_fStart < sampleStart + sampleRange){
                        if(_fStart + _fWidth <= sampleStart + sampleRange){
                            pointStart = _nPointQty * (_fStart - sampleStart) / sampleRange;
                            pointRange = _nPointQty * _fWidth / sampleRange;
                        }else{
                            pointStart = _nPointQty * (_fStart - sampleStart) / sampleRange;
                            pointRange = _nPointQty * (sampleStart + sampleRange - _fStart) / sampleRange;
                        }
                    }

                    int _threshold_ = _threshold * 255.0 / 100;
                    ///

                    WDATA* _pData = GetShadowDataPointer();
                    _pData += offset + pointStart + j * _nLawSize;
                    WDATA buff = 0;
                    int posBuff = pointStart;
                    for(int k = 0; k < pointRange; k++){
                        if(_pData[k] > buff){
                            buff = _pData[k];
                            posBuff = pointStart + k;
                        }
                    }
                    _nTmpValue = correctionPdata(buff) * _fScale;
                    if(_nTmpValue < _threshold_){
                        RasterData.rasterData[Roffset + j] = 0;
                    }else{
                         _nDepth = ( posBuff * sampleRange / _nPointQty) + sampleStart;
                         if(_nDepth < _fMinThickness){
                             RasterData.rasterData[Roffset + j] = 0;
                         }else if(_nDepth > _fMaxThickness){
                             RasterData.rasterData[Roffset + j] = WAVE_MAX;
                         }else{
                             _nTmpValue = WAVE_MAX * (_nDepth - _fMinThickness) / _posRange;
                             RasterData.rasterData[Roffset + j] = _nTmpValue;
                         }
                    }
                }
            }
        }
        return RasterData.rasterData;
    }else{
        float _fMinThickness = m_pConfig->group[nGroupId_].fMinThickness;
        float _fMaxThickness = m_pConfig->group[nGroupId_].fMaxThickness;
        RASTER_DATA &RasterData = m_pConfig->group[nGroupId_].RasterData;
        int markLength = Config::instance()->data_mark_length();
        int beamQty = GetGroupLawQty(nGroupId_);
        int dataLength = markLength * beamQty;
        if(RasterData.rasterData == NULL){
            RasterData.rasterData =  (WDATA*)malloc( dataLength * sizeof(WDATA));
        }
        memset(RasterData.rasterData, 0x00, dataLength);
        float sampleStart = m_pConfig->group[nGroupId_].fSampleStart;
        float sampleRange = m_pConfig->group[nGroupId_].fSampleRange;
        int _nPointQty = GetGroupPointQty(nGroupId_);

        U8* _pMarker = GetScanMarker(nGroupId_);
        int _nFrameOffset = GetTotalDataSize();
        int _nGroupOffset = GetGroupDataOffset(nGroupId_);
        int _nLawSize;
//        if(m_pConfig->group[nGroupId_].law.eLawType == setup_LAW_TYPE_TFM){
//            _nLawSize = _nPointQty;
//        }else{
            _nLawSize = _nPointQty + setup_DATA_PENDIX_LENGTH;
        //}
        float _posRange = _fMaxThickness - _fMinThickness;
        float _fScale = GetRefGainScale(nGroupId_);

        int _nTmpValue1, _nTmpValue2;
        float _nDepth1, _nDepth2;
        for(int i = 0; i < markLength; i++){
            if(_pMarker[i]){
                int _index = GetRealScanIndex(nGroupId_, i);
                int offset = _nFrameOffset * _index + _nGroupOffset;
                int Roffset = _index * beamQty;
                for(int j = 0; j < beamQty; j++){
                    ///
                    PEAK_CONFIG _info[setup_GATE_MAX];
                    GetGatePeakInfos(nGroupId_, _index, j, _info);

                    PEAK_CONFIG _pPeak1;
                    PEAK_CONFIG _pPeak2;
                    if(source_mode == setup_CSCAN_POS_AI){
                        _pPeak1 = _info[setup_GATE_A];
                        _pPeak2 = _info[setup_GATE_I];
                    }else if(source_mode == setup_CSCAN_POS_BI){
                        _pPeak1 = _info[setup_GATE_B];
                        _pPeak2 = _info[setup_GATE_I];
                    }else{
                        _pPeak1 = _info[setup_GATE_B];
                        _pPeak2 = _info[setup_GATE_A];
                    }
                    float _fStart1 = _pPeak1.fGs;
                    float _fWidth1 = _pPeak1.fGw;
                    unsigned int _threshold1 = _pPeak1.fGh;
                    float _fStart2 = _pPeak2.fGs;
                    float _fWidth2 = _pPeak2.fGw;;
                    unsigned int _threshold2 = _pPeak2.fGh;

                    RasterData.fStart1 = _fStart1;
                    RasterData.fWidth1 = _fWidth1;
                    RasterData.threshold1 = _threshold1;
                    RasterData.fStart2 = _fStart2;
                    RasterData.fWidth2 = _fWidth2;
                    RasterData.threshold2 = _threshold2;
                    RasterData.fMinThickness = _fMinThickness;
                    RasterData.fMaxThickness = _fMaxThickness;
                    RasterData.rasterMode = raster_POS_TWO;

                    int pointStart1 = 0;
                    int pointRange1 = 0;
                    int pointStart2 = 0;
                    int pointRange2 = 0;

                    if(_fStart1 < sampleStart){
                        if(_fStart1 + _fWidth1 <= sampleStart){
                            continue;
                        }else if(_fStart1 + _fWidth1 <= sampleStart + sampleRange){
                            pointStart1 = 0;
                            pointRange1 = _nPointQty * (_fStart1 + _fWidth1 - sampleStart) / sampleRange;

                        }else{
                            pointStart1 = 0;
                            pointRange1 = _nPointQty;
                        }
                    }else if(_fStart1 < sampleStart + sampleRange){
                        if(_fStart1 + _fWidth1 <= sampleStart + sampleRange){
                            pointStart1 = _nPointQty * (_fStart1 - sampleStart) / sampleRange;
                            pointRange1 = _nPointQty * _fWidth1 / sampleRange;
                        }else{
                            pointStart1 = _nPointQty * (_fStart1 - sampleStart) / sampleRange;
                            pointRange1 = _nPointQty * (sampleStart + sampleRange - _fStart1) / sampleRange;
                        }
                    }else{
                        continue;
                    }

                    if(_fStart2 < sampleStart){
                        if(_fStart2 + _fWidth2 <= sampleStart){
                            continue;
                        }else if(_fStart2 + _fWidth2 <= sampleStart + sampleRange){
                            pointStart2 = 0;
                            pointRange2 = _nPointQty * (_fStart2 + _fWidth2 - sampleStart) / sampleRange;

                        }else{
                            pointStart2 = 0;
                            pointRange2 = _nPointQty;
                        }
                    }else if(_fStart2 < sampleStart + sampleRange){
                        if(_fStart2 + _fWidth2 <= sampleStart + sampleRange){
                            pointStart2 = _nPointQty * (_fStart2 - sampleStart) / sampleRange;
                            pointRange2 = _nPointQty * _fWidth2 / sampleRange;
                        }else{
                            pointStart2 = _nPointQty * (_fStart2 - sampleStart) / sampleRange;
                            pointRange2 = _nPointQty * (sampleStart + sampleRange - _fStart2) / sampleRange;
                        }
                    }

                    int _threshold1_ = _threshold1 * 255.0 / 100;
                    int _threshold2_ = _threshold2 * 255.0 / 100;
                    ///
                    WDATA* _pData = GetShadowDataPointer();
                    _pData += offset + pointStart1 + j * _nLawSize;
                    WDATA buff1 = 0;
                    int posBuff1 = pointStart1;
                    for(int k = 0; k < pointRange1; k++){
                        if(_pData[k] > buff1){
                            buff1 = _pData[k];
                            posBuff1 = pointStart1 + k;
                        }
                    }
                    _pData = GetShadowDataPointer();
                    _pData += offset + pointStart2 + j * _nLawSize;
                    WDATA buff2 = 0;
                    int posBuff2 = pointStart2;
                    for(int k = 0; k < pointRange2; k++){
                        if(_pData[k] > buff2){
                            buff2 = _pData[k];
                            posBuff2 = pointStart2 + k;
                        }
                    }
                    _nTmpValue1 = correctionPdata(buff1) * _fScale;
                    _nTmpValue2 = correctionPdata(buff2) * _fScale;

                    if(_nTmpValue1 >= _threshold1_ && _nTmpValue2 >= _threshold2_){
                        _nDepth1 = ( posBuff1 * sampleRange / _nPointQty) + sampleStart;
                        _nDepth2 = ( posBuff2 * sampleRange / _nPointQty) + sampleStart;
                        _nDepth1 = abs(_nDepth2 - _nDepth1);

                        if(_nDepth1 < _fMinThickness){
                            RasterData.rasterData[Roffset + j] = 0;
                        }else if(_nDepth1 > _fMaxThickness){
                            RasterData.rasterData[Roffset + j] = WAVE_MAX;
                        }else{
                            _nTmpValue1 = WAVE_MAX * (_nDepth1 - _fMinThickness) / _posRange;
                            RasterData.rasterData[Roffset + j] = _nTmpValue1;
                        }
                    }else{
                        RasterData.rasterData[Roffset + j] = 0;
                    }
                }
            }
        }
        return RasterData.rasterData;
    }

}

WDATA CScanData[2048][2048];
void ParameterProcess::SetCScanData(WDATA data[2048][2048])
{
    memset(CScanData,0x00,sizeof(CScanData));
    memcpy(CScanData, data, sizeof(CScanData));
}

void ParameterProcess::SetCScanRange(int _start, int _end)
{
    m_cPosStart = _start;
    m_cPosStop = _end;
}

void ParameterProcess::GetCScanRange(int &_start, int &_end)
{
    _start = m_cPosStart;
    _end = m_cPosStop;
}

void ParameterProcess::SetCScanStep(float _step)
{
    m_cStep = _step;
}

void ParameterProcess::GetCScanStep(float &_step)
{
    _step = m_cStep;
}

WDATA *ParameterProcess::GetCScanData()
{
    return CScanData[0];
}

WDATA BScanData[2048][2048];
void ParameterProcess::SetBScanData(WDATA data[2048][2048])
{
    memset(BScanData,0x00,sizeof(BScanData));
    memcpy(BScanData, data, sizeof(BScanData));
}

WDATA *ParameterProcess::GetBScanData()
{
    return BScanData[0];
}

