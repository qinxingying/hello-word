#include "DopplerDrawSScanTrueDepth.h"
#include <process/ParameterProcess.h>
#include <QImage>
#include <math.h>
#include <gHeader.h>

DopplerDrawSScanTrueDepth::DopplerDrawSScanTrueDepth() :
	DopplerDrawScan()
{
	m_nWidth = m_nHeight  = 0 ;
	m_pDraw	   = NULL ;
	m_pAngleZoom  = NULL ;
	m_pDrawRate   = NULL ;
	m_pDataNo	 = NULL ;
	m_bClear	= false  ;
}

DopplerDrawSScanTrueDepth::~DopplerDrawSScanTrueDepth ()
{
	ReleaseMatrixBuff();
}

void DopplerDrawSScanTrueDepth::UpdateDrawInfo()
{
	m_hMutex.lock();
	ParameterProcess* _process = ParameterProcess::Instance();

	LAW_CONFIG* _law = _process->GetLawConfig(m_cInfo.nGroupId);
    m_SScaninfo.fStartAngle  =  DEGREE_TO_ARCH(_law->nAngleStartRefract / 10.0) ;

	m_SScaninfo.fStepAngle   =  DEGREE_TO_ARCH(_law->nAngleStepRefract / 10.0)  ;
    m_SScaninfo.fStopAngle   =  DEGREE_TO_ARCH(_law->nAngleStopRefract / 10.0)  ;

    m_SScaninfo.nStartElement=  _law->nFirstElemFir  ;
	m_SScaninfo.nStopElement =  _law->nLastElemFir   ;
	m_SScaninfo.nStepElement =  _law->nElemStepFir   ;
	m_SScaninfo.nElementQty  =  _law->nElemQtyFir	;

	m_SScaninfo.fSampleRange =  _process->GetSampleRangeSoundpath(m_cInfo.nGroupId) ;
	m_SScaninfo.fSampleStart =  _process->GetSampleStartSoundpath(m_cInfo.nGroupId) ;
    m_SScaninfo.nPointQty	 =  _process->GetGroupPointQty(m_cInfo.nGroupId) ;
	m_SScaninfo.pExitPoint   =  _process->GetBeamInsertPos(m_cInfo.nGroupId) ;
    m_SScaninfo.width		 =  m_nWidth ;
    m_SScaninfo.height	     =  m_nHeight ;
    setup_PROBE_ANGLE _eAngle=  _process->GetProbeAngle(m_cInfo.nGroupId) ;

	if(_eAngle >= setup_PROBE_PART_SKEW_180 )
		m_SScaninfo.direction   =  1 ;
	else
		m_SScaninfo.direction   =  0 ;

	m_SScaninfo.eType   = _law->eLawType  ;
	CalcMatrix();
	m_bClear = true ;
	m_hMutex.unlock();
}

void DopplerDrawSScanTrueDepth::Draw (QImage *pImage_)
{
	int _nHeight	  = pImage_->height();
	int _nWidth	   = pImage_->width();

	if((m_nWidth !=  _nWidth) || (m_nHeight != _nHeight))
	{
		m_nWidth  =  _nWidth ;
		m_nHeight =  _nHeight ;
		UpdateDrawInfo() ;
	}

	if(m_bClear)
	{
		m_bClear = false ;
		int _nWidthStep   = pImage_->bytesPerLine()  ;
        U8* _pImageBits = pImage_->bits() ;
		memset(_pImageBits , 0 , m_nHeight * _nWidthStep) ;
	}

	DrawPixbuff(pImage_) ;
}

void DopplerDrawSScanTrueDepth::CalcMatrix()
{
	CreateMatrixBuff();

	if(m_SScaninfo.eType)
		CalcMatrixLinear(&m_SScaninfo) ;
    else
        CalcMatrixAzimuthal(&m_SScaninfo) ;
}

void DopplerDrawSScanTrueDepth::CreateMatrixBuff()
{
	ReleaseMatrixBuff();

	int _nSize = m_nWidth * m_nHeight  ;

	m_pDraw       =  (U8*)malloc(_nSize);
	m_pAngleZoom  =  (U8*)malloc(_nSize);
	m_pDrawRate   =  (U8*)malloc(_nSize);
	m_pDataNo     =  (int*)malloc(_nSize * sizeof(int));
	memset((void*)(m_pDraw) , 0 , _nSize) ;
}

void DopplerDrawSScanTrueDepth::ReleaseMatrixBuff()
{
	if(m_pDraw)	  {free(m_pDraw); m_pDraw = NULL;}
	if(m_pAngleZoom) {free(m_pAngleZoom); m_pAngleZoom = NULL;}
	if(m_pDrawRate)  {free(m_pDrawRate); m_pDrawRate = NULL;}
	if(m_pDataNo)	{free(m_pDataNo); m_pDataNo = NULL;}
}

bool DopplerDrawSScanTrueDepth::MatrixBuffValid()
{
	bool _bValid = true;

	if(m_pDraw == NULL)	  _bValid = false;
	if(m_pAngleZoom == NULL) _bValid = false;
	if(m_pDrawRate == NULL)  _bValid = false;
	if(m_pDataNo == NULL)	_bValid = false;

	return _bValid;
}

void DopplerDrawSScanTrueDepth::CalcMatrixAzimuthal(FAN_SCAN_INFO* pInfo_)
{
	//-----------------------------------------------------------------------------
	// get real window size
	float  _nAngleStart = pInfo_->fStartAngle									;
	float   _nAngleStop = pInfo_->fStopAngle									;
	float   _nAngleStep = pInfo_->fStepAngle									;
	int	  _nPointQty = pInfo_->nPointQty										;
	int	   _nBeamQty = (int)((_nAngleStop - _nAngleStart) / _nAngleStep + 1.1)	;
	float _nSampleStart = pInfo_->fSampleStart									;
	float _nSampleRange = pInfo_->fSampleRange									;
	float  _nSampleStop = _nSampleStart + _nSampleRange							;
	float*  _pExitPoint = pInfo_->pExitPoint									;
	int	 _nDirection = pInfo_->direction										;

	float _nStartX , _nStopX , _nStartY , _nStopY , _nStepX , _nStepY ;

	ParameterProcess* _process = ParameterProcess::Instance();
	_process->GetSImageHorizentalRange(m_cInfo.nGroupId , &_nStartX , &_nStopX) ;
	_process->GetSImageVerticalRange(m_cInfo.nGroupId , &_nStartY , &_nStopY);

	// get real step of each pixel
	int  _width = pInfo_->width  ;	//  图像 宽	单位 像素
	int _height = pInfo_->height ;	//  图像 高	单位 像素
	_nStepX  = (_nStopX - _nStartX) / (_width - 1) ;
	_nStepY  = (_nStopY - _nStartY) / (_height - 1) ;
	//-----------------------------------------------------------------------------
	// get juction of each two beam
	float _nTopLocation[256]  ;
	for(int i = 0 ; i < _nBeamQty - 1; i++)
	{
		_nTopLocation[i] = (_pExitPoint[i] + _pExitPoint[i+1]) / 2 ;
	}
	// get all values of angle
	float _nAngles[256];
	for(int i = 0 ; i < _nBeamQty ; i++)
	{
		_nAngles[i] = _nAngleStart + i * _nAngleStep ;
	}

	float _nPosJunction[256]; // 每个Y轴坐标上声线的位置
	int i, j, k, t, _index;
	float _fX, _fY, _nTmp;

	for(j = 0 ; j < _height ; j++)
	{
		_fY = _nStartY + j * _nStepY ;	// current y position

		for(k = 0 ; k < _nBeamQty ; k++)
		{// beam junctions with current y coordinates
			_nPosJunction[k] = _pExitPoint[k] + tan(_nAngles[k]) * _fY  ;
		}
		// calculate matrix
		t = 0 ;
		for(i = 0 ; i < _width ; i++)
		{
			_fX = _nStartX + _nStepX * i ;	// get current pixel position in real coordinate
			for( ; t < _nBeamQty - 1; t++)
			{// if current position is less than minimun or bigger than maximum  get out
				if(_fX > _nPosJunction[_nBeamQty - 1] || _fX < _nPosJunction[0] )
				{
					break;
				}
				if(_fX >= _nPosJunction[t] && _fX <= _nPosJunction[t+1] )
				{
					if(_nDirection)
					{// if draw direction is inverse , transfer the x coordinate
						_index = _width - i + j * _width  ;
                    }else{
						_index = i + j * _width  ;
					}
					m_pAngleZoom[_index]  = t ;
					_nTmp = _fX - _nTopLocation[t]  ;
					_nTmp = sqrt(_fY * _fY + _nTmp * _nTmp) ;

					if(_nTmp > _nSampleStop || _nTmp < _nSampleStart)
					{// if current position is out of sample range , get out
						break;
					}
					// get current point data index in data block
					m_pDataNo[_index] = _nPointQty * (_nTmp - _nSampleStart) / _nSampleRange ;

                    if((_nPosJunction[t+1] - _fX) < FLOAT_ZERO_GATE)
					{
						m_pDrawRate[_index] = COLOR_STEP  ;
					}else{
						_nTmp = cos(_nAngles[t]) * (_fX - _nPosJunction[t])
							/ ( cos(_nAngles[t+1]) * (_nPosJunction[t+1] - _fX))  ;
						_nTmp = _nTmp / (1 + _nTmp) ;
						m_pDrawRate[_index] =  _nTmp * COLOR_STEP ;
					}
					m_pDraw[_index]  = 255 ;
					break ;
				}
			}
		}
	}
}

void DopplerDrawSScanTrueDepth::CalcMatrixLinear(FAN_SCAN_INFO* pInfo_)
{
	int _nStartElement = pInfo_->nStartElement ;
	int  _nStopElement = pInfo_->nStopElement  ;
	int  _nStepElement = pInfo_->nStepElement  ;
	int   _nElementQty = pInfo_->nElementQty   ;
	double     _fAngle = pInfo_->fStartAngle   ;
	int	    _nPointQty = pInfo_->nPointQty	 ;
	double	   _fRange = pInfo_->fSampleRange  ;
	int		    _width = pInfo_->width		 ;
	int	       _height = pInfo_->height		;
	int	   _bDirection = pInfo_->direction	 ;
	float* _pExitPoint = pInfo_->pExitPoint	;

	int  _nBeamMaxId = (_nStopElement  - _nStartElement - _nElementQty + 1 ) / _nStepElement ;
	float _fStartPos = _pExitPoint [0] ;
	float  _fStopPos = _pExitPoint [_nBeamMaxId] ;
	double	  _angle = fabs(_fAngle);

    double _real_height = _fRange * cos(_angle);
	double  _real_width = fabs(_fStopPos - _fStartPos) + _fRange * sin(_angle) ;	// 实际高度
	double	    _xScale = _width / _real_width ;									// X轴比例(像素/实际)
	double	     _xVacc = tan(_angle) * _real_height * _xScale ;					// 角度横向偏移量(像素)
	double	    _fScale = _xVacc / _height ;										// [角度横向偏移量(像素)]/[角度纵向偏移量(像素)]
	double  _beam_width = _width - _xVacc ;											// 波束宽度(像素)

	bool _bWedgeRev = (_fStopPos - _fStartPos) > 0 ? false : true ;

	double tmpX , xxx;		// 波束索引 中间变量
	double tmpDrawRate ;	// 波束索引
	double tmpDataNo   ;	// 数据位置索引

	int i ,  j  , index ;
	for( i = 0 ; i < _height ; i++)
	{
		tmpX = i * _fScale ;
		tmpDataNo = ((double)i) / _height ;
		for( j = 0 ; j < _width ; j++ )
		{
			if(_bDirection) // reverse
			{
				index  = _width - j + i * _width ;
            }else{
				index  = j + i * _width ;
			}
			if( _fAngle >=0 )
				xxx = j - tmpX ;
			else
				xxx = j - _xVacc + tmpX ;

			if( xxx >= 0 && xxx < _beam_width)
			{
				m_pDraw[index] = 255 ;
            }else{
				continue ;
			}

			tmpDrawRate = ( xxx / _beam_width ) *  _nBeamMaxId  ;
			if(_bWedgeRev)
			{
				m_pAngleZoom[index] = _nBeamMaxId - (U8)tmpDrawRate ;
				tmpDrawRate =  (int)(tmpDrawRate + 1) - tmpDrawRate  ;
            }else{
				m_pAngleZoom[index] = (U8)tmpDrawRate ;
				tmpDrawRate =  tmpDrawRate - (int)tmpDrawRate  ;
			}

			m_pDrawRate[index] = (U8)( tmpDrawRate * COLOR_STEP ) ;
			m_pDataNo[index]   = (int) _nPointQty * tmpDataNo ;
		}
	}
}

void DopplerDrawSScanTrueDepth::DrawPixbuff(QImage* pImage_)
{
	m_hMutex.lock();

	if(MatrixBuffValid() == false) {
		m_hMutex.unlock();
		return;
	}

    U8* _pImageBits = pImage_->bits();
    int _nWidthStep = pImage_->bytesPerLine();

	ParameterProcess* _process = ParameterProcess::Instance();
    int _nLawSize	= m_cInfo.nPointQty + 32;
    m_nScanPos		= _process->GetScanIndexPos();
    m_nFrameOffset	= _process->GetTotalDataSize();
    m_nGroupOffset	= _process->GetGroupDataOffset(m_cInfo.nGroupId);

    volatile WDATA* _pData  = _process->GetShadowDataPointer();
    if(!_pData) {
        m_hMutex.unlock();
        return;
    }

	int _nIndex = _process->GetRealScanIndex(m_cInfo.nGroupId, m_nScanPos);
	_pData += m_nFrameOffset * _nIndex + m_nGroupOffset;

	float  _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
	bool _bRectify = (_process->GetRectifierMode(m_cInfo.nGroupId) == setup_RECTIFIER_RF ) ;

	{
		int _idx1, _idx2, _iData, i , j ;
		U8* _pImg1, *_pImg2;
		for(i = 0; i< m_nHeight; i++)
		{
			_pImg1 = _pImageBits + _nWidthStep * i;
			for(j = 0; j < m_nWidth; j++)
			{
				_idx1 = i * m_nWidth + j ;
				if(m_pDraw[_idx1] != 0)
				{
					_idx2 = (int)(m_pAngleZoom[_idx1] * _nLawSize + m_pDataNo[_idx1]);
					_iData = (int)(_pData[_idx2] * (COLOR_STEP - m_pDrawRate[_idx1]) +
					_pData[_idx2 + _nLawSize] * m_pDrawRate[_idx1] ) ;
                    _iData = _iData>>COLOR_SHIFT ;  //右移
					_pImg2 = _pImg1 + j * 3 ;
					_iData = _process->GetRefGainScaleData(_iData, _fScale, _bRectify);

                    memcpy(_pImg2, &m_pColor[_iData], 3);
				}
			}
		}
	}

	m_hMutex.unlock();
}
