#include "ParameterProcess.h"
#include "configure/const.h"
#include "Limitation.h"
#include <QString>
#include <gHeader.h>

ParameterProcess* g_pParameterProcess = NULL ;

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
	m_pConfig = DopplerConfigure::Instance() ;
}

/****************************************************************************
  Name:  AddOneGroup
  Copyright: Sheng Shen
  Author: Sheng Shen
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
  Name:  DeleteOneGroup
  Copyright: Sheng Shen
  Author: Sheng Shen
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
	group.fRefGain  = fValue_ ;
	return 0 ;
}

int  ParameterProcess::SetupSampleStart(int nGroupId_ , double fValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.fSampleStart  = fValue_ ; //GetSoundPath(nGroupId_ , fValue_) ;
	qDebug("%d %f %f" , nGroupId_ , fValue_ , group.fSampleStart);
	return 0 ;
}

int  ParameterProcess::SetupSampleRange(int nGroupId_ , double fValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.fSampleRange  = fValue_ ; //GetSoundPath(nGroupId_ , fValue_) ;
	qDebug("%d %f %f" , nGroupId_ , fValue_ ,  group.fSampleRange);
	return 0 ;
}

int  ParameterProcess::SetupTravelMode(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.eTravelMode  = (setup_TRAVEL_MODE)nValue_ ;
	qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

int  ParameterProcess::SetupVelocity(int nGroupId_ , double fValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.fVelocity	 = fValue_ ;
	qDebug("%d %f" , nGroupId_ , fValue_);
	return 0 ;
}

int  ParameterProcess::SetupWedgeDelay(int nGroupId_ , double fValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.nWedgeDelay   = (int)(fValue_ * 1000);
	qDebug("%d %f" , nGroupId_ , fValue_);
	return 0 ;
}

int  ParameterProcess::SetupTxElementStart(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.nTrigeStart   = nValue_ ;
	qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

int  ParameterProcess::SetupRxElementStart(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.nReceiveStart   = nValue_ ;
	qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}


int  ParameterProcess::SetupFilter(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	group.eFileter   = (setup_FILTER_MODE) nValue_ ;
	qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

int  ParameterProcess::SetupRectifier(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	group.eRectifier   = (setup_RECTIFIER_MODE) nValue_ ;
	qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

int  ParameterProcess::SetupVedioOnOff(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	group.bVedioFilter   =  nValue_ ;
	qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

int  ParameterProcess::SetupPointQty(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	group.nPointQty  =  nValue_ ;
	qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

int  ParameterProcess::SetupPointQtyAutoMode(int nGroupId_ , int bValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	group.bPointQtyAuto = bValue_ ;
	qDebug("%d %d" , nGroupId_ , bValue_);
	return 0;
}


int  ParameterProcess::SetupSumGain(int nGroupId_ , double fValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	group.fSumGain  =  fValue_ ;
	qDebug("%d %f" , nGroupId_ , fValue_);
	return 0 ;
}

int  ParameterProcess::SetupSumGainAutoMode(int nGroupId_ , int bValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	group.bSumGainAuto = bValue_ ;
	qDebug("%d %d" , nGroupId_ , bValue_);
	return 0;
}

int  ParameterProcess::SetupAverage(int nGroupId_ , int nValue_)
{
	GROUP_CONFIG& group = m_pConfig->group[nGroupId_]   ;
	group.eAveraging  =  (setup_AVERAGE_MODE) nValue_ ;
	qDebug("%d %d" , nGroupId_ , nValue_);
	return 0 ;
}

int ParameterProcess::SetupGroupMode(int nGroupId_ , int nValue_)
{
	m_pConfig->GroupModeChanged(nGroupId_ , (setup_GROUP_MODE)nValue_) ;
	qDebug("%d %d" , nGroupId_ , nValue_);
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
	qDebug("%d %d SetupWedgeLoad" , nGroupId_ , TxRx_);
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

int  ParameterProcess::GetShowMeasureNumber(int nGroupId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;

	int _nNumber = 0;
	for(int i = 0; i  < 5; i++){
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
	qDebug("%d %d SetupWedgeLoad" , nGroupId_ , nValue_);
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

	if(_fPos < _scaner.fScanStart)
		_fPos = _scaner.fScanStart;

	if(_fPos > _scaner.fScanStop)
		_fPos = _scaner.fScanStop;

	_scaner.fScanPos = _fPos;
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
	_scan.eEncoderType = eType_ ;
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
	_scan.fScanStop  = afValue_[2]  ;
	_scan.fIndexStop  = afValue_[3]  ;
	_scan.fScanStep   = afValue_[4]  ;
	_scan.fIndexStep  = afValue_[5]  ;
	return 0;
}

int  ParameterProcess::SetupEncoderConfigure(setup_ENCODER_TYPE eEncoder_, ENCODER_CONFIG* pEncoder_)
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
	int _nBeamQty  = GetGroupLawQty(nGroupId_) ;
	int _nRet = (setup_DATA_PENDIX_LENGTH + _nPointQty) * _nBeamQty  ;
	return _nRet;
}

#include <configure/const.h>
int ParameterProcess::GetTotalDataSize() const
{
	int _nGroupQty = m_pConfig->common.nGroupQty  ;
	int _nRet = setup_DATA_OFFSET ;
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
		else
		{
			_ret = (_law.nLastElemFir - _law.nFirstElemFir - _law.nElemQtyFir + 1) / _law.nElemStepFir + 1 ;
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

WDATA ParameterProcess::GetRefGainScaleData(WDATA wData_, float fScale_, bool bRectify_)
{
	int _iData = wData_;

	if(bRectify_)
	{
	_iData  = _iData - WAVE_HALF ;
	_iData = _iData * fScale_ + WAVE_HALF;
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

int ParameterProcess::SAxisDistToIndex(float fDist_) const
{
	SCANNER& _scaner = m_pConfig->common.scanner ;
	int _index;
	if(_scaner.eEncoderType) {
		_index = (fDist_ - _scaner.fScanStart) / _scaner.fScanStep + 0.5;
	} else {
		_index =  (fDist_ * _scaner.fPrf  - _scaner.fScanStart) / _scaner.fScanStep + 0.5;
	}
	return _index;
}

float ParameterProcess::SAxisIndexToDist(int index_) const
{
	SCANNER& _scaner = m_pConfig->common.scanner ;
	float _fPos;
	if(_scaner.eEncoderType) {
		_fPos = index_ * _scaner.fScanStep + _scaner.fScanStart;
	} else {
		_fPos = (index_ * _scaner.fScanStep + _scaner.fScanStart) / _scaner.fPrf;
	}
	return _fPos;
}

int  ParameterProcess::GetGroupLawDataOffset(int nGroupId_ , int nLawId_) const
{
	int _nLawOffset  = nLawId_ * (m_pConfig->group[nGroupId_].nPointQty + setup_DATA_PENDIX_LENGTH)  ;
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

	if(!_pMarker[_nScanPos]) {
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
	bool _bRectify = GetRectifierMode(nGroupId_);
	F32	 _fData    = GetRefGainScaleData(_pData[_index], _fScale, _bRectify);

	return CalPeakAmp(_fData, _bRectify);
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
	if(iEnd_ >= nPointQty_) {
		iEnd_ = nPointQty_ - 1;
	}
	if(iStart_ > iEnd_) {
		iStart_ = iEnd_;
	}
	int _iS = iStart_;
	int _iE = iEnd_;
	int _iH = iHeight_;

	int _iFro = 0;//pData_[iStart_];
	int _iTmp = 0;
	int _iPos = iEnd_;

	if(!bRectify_) {// 射频
		int mode = 0;
		if(iHeight_ > WAVE_HALF)
			mode = 1;

		if(!mode) {
			for(int i = _iS; i < _iE; i++) {
				_iTmp = pData_[i];
				if(_iTmp <= _iH) {
					_iFro = _iTmp;
					_iPos = i;
					break;
				}
			}
		} else {
			for(int i = _iS; i < _iE; i++) {
				_iTmp = pData_[i];
				if(_iTmp >= _iH) {
					_iFro = _iTmp;
					_iPos = i;
					break;
				}
			}
		}
	} else {
		for(int i = _iS; i < _iE; i++) {
			_iTmp = pData_[i];
			if(_iTmp >= _iH) {
				_iFro = _iTmp;
				_iPos = i;
				break;
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
	if(iEnd_ >= nPointQty_) {
		iEnd_ = nPointQty_ - 1;
	}
	if(iStart_ > iEnd_) {
		iStart_ = iEnd_;
	}
	int _iS = iStart_;
	int _iE = iEnd_;

	int _iAmp = 0;
	int _iTmp = 0;
	int _iPos = 0;

	if(!bRectify_) {// 射频
		int _iMax = 0;
		int _iData = 0;
		for(int i = _iS; i < _iE; i++) {
			_iTmp = pData_[i];
			_iData = abs(_iTmp - WAVE_HALF);

			if(_iData > _iMax) {
				_iMax = _iData;
				_iAmp = _iTmp;
				_iPos = i;
			}
		}
	} else {
		for(int i = _iS; i < _iE; i++) {
			_iTmp = pData_[i];

			if(_iTmp > _iAmp) {
				_iAmp = _iTmp;
				_iPos = i;
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
	int     _nLawSize = _nPointQty + 32;
	int        _index = GetRealScanIndex(nGroupId_, nScanPos_);

	if(_pData) {
		_pData += (_nFrameOffset * _index + _nGroupOffset + nLawId_ * _nLawSize);
	}

	GetGatePeakInfos(nGroupId_, _pData, nLawId_, pInfo_);
	return true;
}

bool ParameterProcess::GetGatePeakInfos(int nGroupId_, WDATA* pData_, int nLawId_, PEAK_CONFIG* pInfo_)
{
//	if(!pData_) return false;
	memset(pInfo_, 0x00, 3*sizeof(PEAK_CONFIG));

	int      _nPointQty = GetGroupPointQty(nGroupId_);
	float _fSampleStart = GetSampleStart(nGroupId_ , nLawId_);
	float _fSampleRange = GetSampleRange(nGroupId_ , nLawId_);
	float	   _fScale  = _nPointQty / _fSampleRange;
	int       _nRectify = GetRectifierMode(nGroupId_);

	float _fDist, _fEdge;
	float _fAngle  = DEGREE_TO_ARCH(GetLawAngle(nGroupId_ , nLawId_)) ;
	float _fThick  = GetPartThickness(nGroupId_);
	float _fSin    = sin(_fAngle);
	float _fCos    = cos(_fAngle);
	//-----------------------------------
	// I
	GATE_CONFIG* _pGate = GetGateInfo(nGroupId_ , setup_GATE_I);

	float _fStart = _fScale * (_pGate->fStart - _fSampleStart) ;
	float _fWidth = _fScale * _pGate->fWidth;
	float _fHeigh = _pGate->nThreshold * WAVE_MAX / 100;
	if(_fStart+_fWidth >= _nPointQty) _fWidth = _nPointQty - _fStart - 1;

	pInfo_[setup_GATE_I].iYEdge = SearchPeakFront(pData_, &pInfo_[setup_GATE_I].iXEdge, _fStart, _fStart+_fWidth, _fHeigh, _nRectify, _nPointQty);
	pInfo_[setup_GATE_I].iY    = SearchPeakAmp(pData_, &pInfo_[setup_GATE_I].iX, _fStart, _fStart+_fWidth, _nRectify, _nPointQty);

	pInfo_[setup_GATE_I].fGs   = _pGate->fStart;
	pInfo_[setup_GATE_I].fGw   = _pGate->fWidth;
	pInfo_[setup_GATE_I].fGh   = GateHeight(_pGate->nThreshold, _nRectify);

	_fEdge = DistDotPosToMm(nGroupId_ , pInfo_[setup_GATE_I].iXEdge);
	pInfo_[setup_GATE_I].fSEdge = _fEdge;
	pInfo_[setup_GATE_I].fHEdge = _fEdge * _fCos;
	pInfo_[setup_GATE_I].fLEdge = _fEdge * _fSin;
	pInfo_[setup_GATE_I].fDEdge = GetDepth(pInfo_[setup_GATE_I].fHEdge, _fThick);

	_fDist = DistDotPosToMm(nGroupId_ , pInfo_[setup_GATE_I].iX);
	pInfo_[setup_GATE_I].fS     = _fDist;
	pInfo_[setup_GATE_I].fH     = _fDist * _fCos;
	pInfo_[setup_GATE_I].fL     = _fDist * _fSin;
	pInfo_[setup_GATE_I].fD     = GetDepth(pInfo_[setup_GATE_I].fH, _fThick);

	pInfo_[setup_GATE_I].fAmp   = CalPeakAmp(pInfo_[setup_GATE_I].iY, _nRectify);
	pInfo_[setup_GATE_I].fXdXA  = A_DB_B(pInfo_[setup_GATE_I].fAmp, pInfo_[setup_GATE_I].fGh);
	//-----------------------------------
	// A
	_pGate = GetGateInfo(nGroupId_ , setup_GATE_A);

	_fStart = _fScale * (_pGate->fStart - _fSampleStart);
	_fWidth = _fScale * _pGate->fWidth;
	_fHeigh = _pGate->nThreshold * WAVE_MAX / 100;
	switch(_pGate->eSynChro)
	{
	case setup_GATE_AYNC_I:
		_fStart += pInfo_[setup_GATE_I].iXEdge;
		break;
	default:	break;
	}
	if(_fStart+_fWidth >= _nPointQty) _fWidth = _nPointQty - _fStart - 1;

	pInfo_[setup_GATE_A].iYEdge = SearchPeakFront(pData_, &pInfo_[setup_GATE_A].iXEdge, _fStart, _fStart+_fWidth, _fHeigh, _nRectify, _nPointQty);
	pInfo_[setup_GATE_A].iY    = SearchPeakAmp(pData_, &pInfo_[setup_GATE_A].iX, _fStart, _fStart+_fWidth, _nRectify, _nPointQty);

	pInfo_[setup_GATE_A].fGs   = _fStart / _fScale + _fSampleStart;//_pGate->fStart;
	pInfo_[setup_GATE_A].fGw   = _fWidth / _fScale;//_pGate->fWidth;
	pInfo_[setup_GATE_A].fGh   = GateHeight(_pGate->nThreshold, _nRectify);

	_fEdge = DistDotPosToMm(nGroupId_ , pInfo_[setup_GATE_I].iXEdge);
	pInfo_[setup_GATE_A].fSEdge = _fEdge;
	pInfo_[setup_GATE_A].fHEdge = _fEdge * _fCos;
	pInfo_[setup_GATE_A].fLEdge = _fEdge * _fSin;
	pInfo_[setup_GATE_A].fDEdge = GetDepth(pInfo_[setup_GATE_A].fHEdge, _fThick);

	_fDist = DistDotPosToMm(nGroupId_ , pInfo_[setup_GATE_A].iX);
	pInfo_[setup_GATE_A].fS     = _fDist;
	pInfo_[setup_GATE_A].fH     = _fDist * _fCos;
	pInfo_[setup_GATE_A].fL     = _fDist * _fSin;
	pInfo_[setup_GATE_A].fD     = GetDepth(pInfo_[setup_GATE_A].fH, _fThick);

	pInfo_[setup_GATE_A].fAmp   = CalPeakAmp(pInfo_[setup_GATE_A].iY, _nRectify);
	pInfo_[setup_GATE_A].fXdXA  = A_DB_B(pInfo_[setup_GATE_A].fAmp, pInfo_[setup_GATE_A].fGh);
	//-----------------------------------
	// B
	_pGate = GetGateInfo(nGroupId_ , setup_GATE_B);

	_fStart = _fScale * (_pGate->fStart - _fSampleStart);
	_fWidth = _fScale * _pGate->fWidth;
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
	if(_fStart+_fWidth >= _nPointQty) _fWidth = _nPointQty - _fStart - 1;

	pInfo_[setup_GATE_B].iYEdge = SearchPeakFront(pData_, &pInfo_[setup_GATE_B].iXEdge, _fStart, _fStart+_fWidth, _fHeigh, _nRectify, _nPointQty);
	pInfo_[setup_GATE_B].iY    = SearchPeakAmp(pData_, &pInfo_[setup_GATE_B].iX, _fStart, _fStart+_fWidth, _nRectify, _nPointQty);

	pInfo_[setup_GATE_B].fGs   = _fStart / _fScale + _fSampleStart;//_pGate->fStart;
	pInfo_[setup_GATE_B].fGw   = _fWidth / _fScale;//_pGate->fWidth;
	pInfo_[setup_GATE_B].fGh   = GateHeight(_pGate->nThreshold, _nRectify);

	_fEdge = DistDotPosToMm(nGroupId_ , pInfo_[setup_GATE_I].iXEdge);
	pInfo_[setup_GATE_A].fSEdge = _fEdge;
	pInfo_[setup_GATE_A].fHEdge = _fEdge * _fCos;
	pInfo_[setup_GATE_A].fLEdge = _fEdge * _fSin;
	pInfo_[setup_GATE_A].fDEdge = GetDepth(pInfo_[setup_GATE_A].fHEdge, _fThick);

	_fDist = DistDotPosToMm(nGroupId_ , pInfo_[setup_GATE_B].iX);
	pInfo_[setup_GATE_B].fS     = _fDist;
	pInfo_[setup_GATE_B].fH     = _fDist * _fCos;
	pInfo_[setup_GATE_B].fL     = _fDist * _fSin;
	pInfo_[setup_GATE_B].fD     = GetDepth(pInfo_[setup_GATE_B].fH, _fThick);

	pInfo_[setup_GATE_B].fAmp   = CalPeakAmp(pInfo_[setup_GATE_B].iY, _nRectify);
	pInfo_[setup_GATE_B].fXdXA  = A_DB_B(pInfo_[setup_GATE_B].fAmp, pInfo_[setup_GATE_B].fGh);
	return true;
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
	return (_pData + _nFrameOffset + _nGroupOffset)  ;
}

WDATA* ParameterProcess::GetLawDataPointer(int nGroupId_ , int nLawId_)
{
	WDATA* _pData = GetGroupDataPointer(nGroupId_) ;
	if(!_pData)  return 0 ;
	int _nLawOffset  = GetGroupLawDataOffset(nGroupId_ , nLawId_)  ;
	//*** total offset
	return (_pData + _nLawOffset)  ;
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

void ParameterProcess::FittedCurveGetPoints(int nGroupId_, float fPrecX_, float fPrecY_, float fTX0_, int iDots_, QPointF* pPoints_)
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

	int _x = (_Tx - _TX0) / _precX;
	int _y = i;

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

void  ParameterProcess::GetScanScanAxisRange(int nGroupId_ ,  int nDist_ , double* fStart_ , double* fStop_, double* fSliderStart_ , double* fSliderStop_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_];
	//float      _fScanOff = _group.fScanOffset;

	SCANNER& _scan = m_pConfig->common.scanner  ;
	float _fScanPos = _scan.fScanPos;//  + _fScanOff;
	float _fRange ;
	float _fStart ;
	if(_scan.eEncoderType == setup_ENCODER_TYPE_TIMER)
	{
		_fRange = (nDist_ - 1 ) / _scan.fPrf  ;
		_fStart = 0;// + _fScanOff;
	}
	else
	{
		_fRange = (nDist_ - 1) * _scan.fScanStep  ;
		_fStart = _scan.fScanStart;// + _fScanOff;
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

	*fStart_  = 0.5			;
	*fStop_   = _nLawQty + 0.5 ;

	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	if(setup_GROUP_MODE_PA == _group.eGroupMode)
	{
		if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
		{
			LAW_CONFIG* _law = GetLawConfig(nGroupId_);
			float _fStartAngle  =  _law->nAngleStartRefract / 10.0 ;
			float _fStepAngle   =  _law->nAngleStepRefract / 10.0  ;

			*fStart_  = _fStartAngle - 0.5		   ;
			*fStop_   = _fStartAngle + _nLawQty * _fStepAngle + 0.5 ;
		}
	}
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

void  ParameterProcess::GetSImageVerticalRange(int nGroupId_ , float* fStart_ , float* fStop_)
{
	*fStart_ = 0 ;
	*fStop_  = 0 ;
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	if(_group.eGroupMode != setup_GROUP_MODE_PA)  return  ;
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
		if(_fAngleStart * _fAngleStop < 0)
			*fStop_ = _fSampleStop ;
		else
			*fStop_   = _pos3 > _pos4 ? _pos3 : _pos4 ;
	}
	else
	{
		*fStart_ = _fSampleStart * cos(DEGREE_TO_ARCH(_fAngleStart))  ;
		*fStop_  = _fSampleStop  * cos(DEGREE_TO_ARCH(_fAngleStart))  ;
	}

	if(FLOAT_EQ(*fStart_ , *fStop_)) *fStop_ = *fStart_ + 1 ;
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

void  ParameterProcess::GetSScanVerticalRange(int nGroupId_ , float* fStart_ , float* fStop_)
{
	GetSImageVerticalRange(nGroupId_ , fStart_ , fStop_);
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
QString ParameterProcess::GetSonicAxisUnit()
{
	return QString("mm");
}

QString ParameterProcess::GetScanAxisUnit()
{
	SCANNER _scan = m_pConfig->common.scanner  ;
	if(_scan.eEncoderType == setup_ENCODER_TYPE_TIMER)
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
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	if(setup_GROUP_MODE_PA == _group.eGroupMode)
	{
		if(_group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
			return QString("deg");
		else
			return QString("vpa");
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
	if(_group.eTravelMode == setup_TRAVEL_MODE_HALF_PATH)
	{
		_fRet = _group.fSampleStart ;
	}
	else
	{
		float _fAngle = GetLawAngle(nGroupId_ , nLawId_);
		_fRet = _group.fSampleStart * cos(DEGREE_TO_ARCH(_fAngle)) ;
	}

	return _fRet;
}

float ParameterProcess::GetSampleRange(int nGroupId_ , int nLawId_)
{
	GROUP_CONFIG& _group = m_pConfig->group[nGroupId_] ;
	float _fRet  ;
	if(_group.eTravelMode == setup_TRAVEL_MODE_HALF_PATH)
	{
		_fRet = _group.fSampleRange ;
	}
	else
	{
		float _fAngle = GetLawAngle(nGroupId_ ,nLawId_);
		_fRet = _group.fSampleRange * cos(DEGREE_TO_ARCH(_fAngle)) ;
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
  Name:  CalGateValueAmp
  Copyright: Sheng Shen
  Author: Sheng Shen
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
  Name:  CalGateValuePos
  Copyright: Sheng Shen
  Author: Sheng Shen
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
