#include "DopplerDrawSScanTrueDepth.h"
#include <process/ParameterProcess.h>
#include <QImage>
#include <math.h>
#include <gHeader.h>
#include "defectidentify.h"
#include <QApplication>
#include "DopplerDataView.h"
#include "gHeader.h"
#include <process/ParameterProcess.h>
#include <QtGlobal>
#include<QtConcurrent/QtConcurrent>
#define WAVE_HALF		125
static unsigned char COMPOSITION_COLOR[4] = {255,0,0,40};
//int m_cursorOffset=1;
//QVector <QVector<int>>m_tempdata;
//QVector <QVector<int>>m_RefTempdata;
DopplerDrawSScanTrueDepth::DopplerDrawSScanTrueDepth() :
	DopplerDrawScan()
{

    m_nWidth = m_nHeight  = 0;
    m_pDraw	   = NULL;
    m_pAngleZoom = NULL;
    m_pDrawRate  = NULL;
    m_pColRate   = NULL;
    m_pDataNo	 = NULL;
    m_bClear	 = false;
    m_cursorOffset=1;


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
    if (pImage_->isNull()) return;
    int _nHeight	  = pImage_->height();
    int _nWidth	   = pImage_->width();

    if((m_nWidth !=  _nWidth) || (m_nHeight != _nHeight) || (m_bWeldRemainingHeightAffect != m_pGroup->bWeldRemainingHeight)
            || m_bWeldRemainingHeightAffect) {
        m_nWidth  =  _nWidth ;
        m_nHeight =  _nHeight ;
        m_bWeldRemainingHeightAffect = m_pGroup->bWeldRemainingHeight;
        UpdateDrawInfo() ;
    }
    /***********工件厚度或者反射类型或者1:1显示更改后刷新图像*************/

    if ( m_thickness != m_pGroup->part.afSize[0] || m_reType != m_pGroup->m_Retype||m_Shows!=m_pGroup->m_Shows) {
        m_thickness =  m_pGroup->part.afSize[0];
        m_reType = m_pGroup->m_Retype;
        m_Shows=m_pGroup->m_Shows;
        m_bClear = true;
    }

   /***********工件厚度或者反射类型更改后刷新图像*************/
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
    qDebug("%s:[%s](%d), %d", __FILE__,__FUNCTION__,__LINE__, _nSize);

	m_pDraw       =  (U8*)malloc(_nSize);
	m_pAngleZoom  =  (U8*)malloc(_nSize);
	m_pDrawRate   =  (U8*)malloc(_nSize);
    m_pColRate    =  (U8*)malloc(_nSize);
	m_pDataNo     =  (int*)malloc(_nSize * sizeof(int));
    memset((void*)(m_pDraw) , 0 , _nSize) ;
}

void DopplerDrawSScanTrueDepth::ReleaseMatrixBuff()
{
	if(m_pDraw)	  {free(m_pDraw); m_pDraw = NULL;}
	if(m_pAngleZoom) {free(m_pAngleZoom); m_pAngleZoom = NULL;}
	if(m_pDrawRate)  {free(m_pDrawRate); m_pDrawRate = NULL;}
    if(m_pColRate)   {free(m_pColRate); m_pColRate = NULL;}
    if(m_pDataNo)	 {free(m_pDataNo); m_pDataNo = NULL;}
}

bool DopplerDrawSScanTrueDepth::MatrixBuffValid()
{
	bool _bValid = true;

	if(m_pDraw == NULL)	  _bValid = false;
	if(m_pAngleZoom == NULL) _bValid = false;
	if(m_pDrawRate == NULL)  _bValid = false;
    if(m_pColRate == NULL) _bValid = false;
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

    float _nStartX , _nStopX , _nStartY , _nStopY ;

	ParameterProcess* _process = ParameterProcess::Instance();
	_process->GetSImageHorizentalRange(m_cInfo.nGroupId , &_nStartX , &_nStopX) ;
	_process->GetSImageVerticalRange(m_cInfo.nGroupId , &_nStartY , &_nStopY);

    if(!m_pGroup->m_Retype)
    {
        _nStartY=_nStartY;
        _nStopY=_nStopY;
    }else
    {
        _nStartY=_nStartY+OFFSET_Y;
        _nStopY=_nStopY+OFFSET_Y ;
    }

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
    int i, j, k, t, _index, _indexBuff;
    float _fX, _fY, _nTmp, _nbuff;

    // weld remaining height
    float thickness = m_pGroup->part.afSize[0];
    int reflectCount = _nStopY / thickness;
    float weldBottomWidth = _width;
    float weldTopWidth = _width;
    bool bWeldLeft = false;
    bool bWeldRight = false;
    if (m_pGroup->part.weldFormat) { // 二代
        if (m_pGroup->part.weld_ii.eSymmetry == setup_WELD_LEFT) {
            bWeldLeft = true;
        } else if (m_pGroup->part.weld_ii.eSymmetry == setup_WELD_RIGHT) {
            bWeldRight = true;
        }
        switch (m_pGroup->part.weld_ii.eType){
        case I:
            weldBottomWidth = m_pGroup->part.weld_ii.I.w + m_pGroup->part.weld_ii.bottomCapOverlap;
            weldTopWidth = m_pGroup->part.weld_ii.I.w + m_pGroup->part.weld_ii.topCapOverlap;
            break;
        case V:
            weldTopWidth = m_pGroup->part.weld_ii.V.w1 + m_pGroup->part.weld_ii.topCapOverlap;
            weldBottomWidth = m_pGroup->part.weld_ii.V.w2 + m_pGroup->part.weld_ii.bottomCapOverlap;
            break;
        case U:
            weldTopWidth = m_pGroup->part.weld_ii.U.w1 + m_pGroup->part.weld_ii.topCapOverlap;
            weldBottomWidth = m_pGroup->part.weld_ii.U.w2 + m_pGroup->part.weld_ii.bottomCapOverlap;
            break;
        case VY:
            weldTopWidth = m_pGroup->part.weld_ii.VY.w1 + m_pGroup->part.weld_ii.topCapOverlap;
            weldBottomWidth = m_pGroup->part.weld_ii.VY.w3 + m_pGroup->part.weld_ii.bottomCapOverlap;
            break;
        case VV:
            weldTopWidth = m_pGroup->part.weld_ii.VV.w1 + m_pGroup->part.weld_ii.topCapOverlap;
            weldBottomWidth = m_pGroup->part.weld_ii.VV.w3 + m_pGroup->part.weld_ii.bottomCapOverlap;
            break;
        case UU:
            weldTopWidth = m_pGroup->part.weld_ii.UU.w1 + m_pGroup->part.weld_ii.topCapOverlap;
            weldBottomWidth = m_pGroup->part.weld_ii.UU.w3 + m_pGroup->part.weld_ii.bottomCapOverlap;
            break;
        case UV:
            weldTopWidth = m_pGroup->part.weld_ii.UV.w1 + m_pGroup->part.weld_ii.topCapOverlap;
            weldBottomWidth = m_pGroup->part.weld_ii.UV.w3 + m_pGroup->part.weld_ii.bottomCapOverlap;
            break;
        case TKY:

            break;
        case DXF:

            break;
        default:

            break;
        }
    } else {
        if (m_pGroup->part.weld.eSymmetry == setup_WELD_LEFT) {
            bWeldLeft = true;
        } else if (m_pGroup->part.weld.eSymmetry == setup_WELD_RIGHT) {
            bWeldRight = true;
        }
        switch (m_pGroup->part.weld.eType)
        {
        case setup_WELD_I :
            weldBottomWidth = m_pGroup->part.weld.weland_offset;
            weldTopWidth = m_pGroup->part.weld.weland_offset;
            break;
        case setup_WELD_V :
            weldBottomWidth = m_pGroup->part.weld.weland_offset;
            weldTopWidth = m_pGroup->part.weld.weland_offset + tan(DEGREE_TO_ARCH(m_pGroup->part.weld.fizone_angle)) * m_pGroup->part.weld.fizone_height;
            break;
        case setup_WELD_DV :
            weldTopWidth = m_pGroup->part.weld.weland_offset + tan(DEGREE_TO_ARCH(m_pGroup->part.weld.fizone_angle)) * m_pGroup->part.weld.fizone_height;
            weldBottomWidth = weldTopWidth;
            break;
        case setup_WELD_U : {
            float fFizoneAngle = DEGREE_TO_ARCH(m_pGroup->part.weld.fizone_angle) ;
            float nTmpY2 = sin(fFizoneAngle) * m_pGroup->part.weld.fizone_radius  ;
            float nTmpY1 = sqrt(m_pGroup->part.weld.fizone_radius * m_pGroup->part.weld.fizone_radius - m_pGroup->part.weld.weland_offset * m_pGroup->part.weld.weland_offset );
            if(nTmpY2 > nTmpY1)
            {
                weldBottomWidth = m_pGroup->part.weld.weland_offset;
                weldTopWidth = m_pGroup->part.weld.weland_offset + tan(DEGREE_TO_ARCH(m_pGroup->part.weld.fizone_angle)) * m_pGroup->part.weld.fizone_height;
            } else {
                float fPosX = cos(fFizoneAngle) * m_pGroup->part.weld.fizone_radius;
                double fPosY = m_pGroup->part.weld.fizone_height - nTmpY1 + nTmpY2;
                weldTopWidth = fPosX + tan(fFizoneAngle) * fPosY;
                weldBottomWidth = m_pGroup->part.weld.weland_offset;
            }
            break;
        }
        case setup_WELD_DIFF_DV:
            weldBottomWidth = m_pGroup->part.weld.weland_offset + tan(DEGREE_TO_ARCH(m_pGroup->part.weld.fizone_down_angle)) * m_pGroup->part.weld.fizone_down_height;
            weldTopWidth = m_pGroup->part.weld.weland_offset + tan(DEGREE_TO_ARCH(m_pGroup->part.weld.fizone_angle)) * m_pGroup->part.weld.fizone_height;
            break;
        case setup_WELD_J: {
            float fFizoneAngle = DEGREE_TO_ARCH(m_pGroup->part.weld.fizone_angle) ;
            float nTmpY2 = sin(fFizoneAngle) * m_pGroup->part.weld.fizone_radius  ;
            float nTmpY1 = sqrt(m_pGroup->part.weld.fizone_radius * m_pGroup->part.weld.fizone_radius - m_pGroup->part.weld.weland_offset * m_pGroup->part.weld.weland_offset );
            if(nTmpY2 > nTmpY1)
            {
                weldBottomWidth = m_pGroup->part.weld.weland_offset;
                weldTopWidth = m_pGroup->part.weld.weland_offset + tan(DEGREE_TO_ARCH(m_pGroup->part.weld.fizone_angle)) * m_pGroup->part.weld.fizone_height;
            } else {
                float fPosX = cos(fFizoneAngle) * m_pGroup->part.weld.fizone_radius;
                double fPosY = m_pGroup->part.weld.fizone_height - nTmpY1 + nTmpY2;
                weldTopWidth = fPosX + tan(fFizoneAngle) * fPosY;
                weldBottomWidth = m_pGroup->part.weld.weland_offset + tan(DEGREE_TO_ARCH(m_pGroup->part.weld.fizone_down_angle)) * m_pGroup->part.weld.fizone_down_height;
            }
        }
        case setup_WELD_VY:
            weldBottomWidth = m_pGroup->part.weld.weland_offset;
            weldTopWidth = m_pGroup->part.weld.weland_offset + tan(DEGREE_TO_ARCH(m_pGroup->part.weld.fizone_angle)) * m_pGroup->part.weld.fizone_height
                    + tan(DEGREE_TO_ARCH(m_pGroup->part.weld.fizone_down_angle)) * m_pGroup->part.weld.fizone_down_height;
            break;
        case setup_WELD_TKY:

            break;
        case setup_WELD_DXF:

            break;
        default:
            break;
        }

    }

    int lawIdStart[10] = {0};
    int lawIdStop[10] = {0};
    for (int index = 0; index < reflectCount; ++index) {
        float height = thickness * (index + 1);
        float width  = 0.0;
        if (index % 2 == 0) {
            width = weldBottomWidth;
        } else {
            width = weldTopWidth;
        }
        float leftBoder  =  -width;
        float rightBoder = width;
        if (bWeldLeft) {
            rightBoder = 0;
        } else if(bWeldRight) {
            leftBoder = 0;
        }
        lawIdStart[index] = -2;
        lawIdStop[index]  = -2;
        for(int i = 0 ; i < _nBeamQty ; i++)
        {
            float angle = _nAngleStart + i * _nAngleStep ;
            if (!_nDirection) {
                float x = tan(angle) * height + _pExitPoint[i] + m_pGroup->fIndexOffset;
                if (x >= leftBoder && lawIdStart[index] == -2) {
                    lawIdStart[index] = i;
                }
                if (x >= rightBoder && lawIdStop[index] == -2) {
                    lawIdStop[index] = i - 1;
                }
                if ((i == _nBeamQty - 1) && lawIdStop[index] == -2 && lawIdStart[index] != -2) {
                    lawIdStop[index] = i;
                }
            } else {
                float x = -(tan(angle) * height + _pExitPoint[i] - m_pGroup->fIndexOffset);
                if (x <= rightBoder && lawIdStart[index] == -2) {
                    lawIdStart[index] = i;
                }
                if (x <= leftBoder && lawIdStop[index] == -2) {
                    lawIdStop[index] = i - 1;
                }
                if ((i == _nBeamQty - 1) && lawIdStop[index] == -2 && lawIdStart[index] != -2) {
                    lawIdStop[index] = i;
                }
            }
        }
    } // end

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
                    // 焊缝余高
                    bool bAffect = false;
                    if (m_bWeldRemainingHeightAffect) {
                        bool bDraw = true;
                        for (int index = 0; index < reflectCount; ++index) {
                            float h = thickness * (index + 1);
                            if ((_fY > h) && (t >= lawIdStart[index] && t < lawIdStop[index])) {
                                bDraw = false;
                                break;
                            }
                        }
                        if (!bDraw) {
                            bAffect = true;
                        }
                    } // end of 焊缝余高
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
                    _nbuff = _nPointQty * (_nTmp - _nSampleStart) / _nSampleRange;
                    _indexBuff = qFloor(_nbuff);
                    if(_indexBuff >= _nPointQty - 1){
                        m_pDataNo[_index] = _nPointQty - 1;
                        m_pColRate[_index] = 0;
                    }else{
                        m_pDataNo[_index] = _indexBuff;
                        _nTmp = 1 - _nbuff + _indexBuff;
                        m_pColRate[_index] = _nTmp * COLOR_STEP;
                    }
                    //m_pDataNo[_index] = _nPointQty * (_nTmp - _nSampleStart) / _nSampleRange ;

                    if((_nPosJunction[t+1] - _fX) < FLOAT_ZERO_GATE)
					{
						m_pDrawRate[_index] = COLOR_STEP  ;
					}else{
                        //_nTmp = ( atan((_fX - _nTopLocation[t]) / _fY) - _nAngles[t]) / _nAngleStep;
                        _nTmp = cos(_nAngles[t]) * (_fX - _nPosJunction[t])
                            / ( cos(_nAngles[t+1]) * (_nPosJunction[t+1] - _fX))  ;
                        _nTmp = _nTmp / (1 + _nTmp) ;
						m_pDrawRate[_index] =  _nTmp * COLOR_STEP ;
					}
                    if (bAffect) {
                        m_pDraw[_index]  = WAVE_HALF;
                    } else {
                        m_pDraw[_index]  =  WAVE_MAX;
                    }
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

    double _real_height = _fRange * cos(_angle); // 实际高度
    double  _real_width = fabs(_fStopPos - _fStartPos) + _fRange * sin(_angle) ;
    double	    _xScale = _width / _real_width ;// X轴比例(像素/实际)
    double	     _xVacc = tan(_angle) * _real_height * _xScale;// 角度横向偏移量(像素)
    double	    _fScale = _xVacc / _height ;	// [角度横向偏移量(像素)]/[角度纵向偏移量(像素)]
    double  _beam_width = _width - _xVacc ;		// 波束宽度(像素)

	bool _bWedgeRev = (_fStopPos - _fStartPos) > 0 ? false : true ;

    double tmpX , xxx, _indexBuff, _nbuff;  // 波束索引 中间变量
    double tmpDrawRate;	// 波束索引
    double tmpDataNo;	// 数据位置索引

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
                m_pDraw[index] = WAVE_MAX;
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
            _nbuff = _nPointQty * tmpDataNo;
            _indexBuff = qFloor(_nbuff);
            if(_indexBuff >= _nPointQty - 1){
                m_pDataNo[index] = _nPointQty - 1;
                m_pColRate[index] = 0;
            }else{
                m_pDataNo[index] = _indexBuff;
                m_pColRate[index] = (1- _nbuff + _indexBuff) * COLOR_STEP;
            }
            //m_pDataNo[index]   = (int) _nPointQty * tmpDataNo ;
		}
	}
}

void DopplerDrawSScanTrueDepth::DrawPixbuff(QImage* pImage_)
{
    QMutexLocker locker(&m_hMutex);

	if(MatrixBuffValid() == false) {
		return;
	}

    QImage weldRemainHeightAffectImage(pImage_->width(), pImage_->height(), QImage::Format_RGBA8888);
    U8* pAffectImageBits = weldRemainHeightAffectImage.bits();
    memset(pAffectImageBits, 0, weldRemainHeightAffectImage.byteCount());
    int affectImgWidthStep = weldRemainHeightAffectImage.bytesPerLine();

    ParameterProcess* _process = ParameterProcess::Instance();

    setup_PROBE_ANGLE _eAngle = _process->GetProbeAngle(m_cInfo.nGroupId);

    int _nFrameOffset = _process->GetTotalDataSize() ;//一帧数据偏移量

//    QImage* pImage=new QImage(pImage_->width(),pImage_->height(),QImage::Format_RGB888);
    U8* _pImageBits = pImage_->bits();// 获取图像的首地址 https://blog.csdn.net/lengyuezuixue/article/details/80656358
    int _nWidthStep = pImage_->bytesPerLine();// 获取图像每行字节数
    float _fStart , _fStop;
    _process->GetSScanVerticalRange(m_cInfo.nGroupId , &_fStart ,  &_fStop);

    if(m_pGroup->m_mode==D_MODE&&m_pGroup->afCursor[ setup_CURSOR_S_MES ]<m_pConfig->comTmp.nRecMax&& m_pGroup->afCursor[setup_CURSOR_S_REF]<m_pConfig->comTmp.nRecMax)
     {
        m_cursorOffset=m_pGroup->afCursor[ setup_CURSOR_S_MES ]- m_pGroup->afCursor[setup_CURSOR_S_REF];
        if(m_cursorOffset<0)m_cursorOffset=-m_cursorOffset;
        if(m_cursorOffset==0)m_cursorOffset=1;
      }else if(m_pGroup->m_mode==S_MODE)
        {
          m_cursorOffset=1;
        }
    QVector< QFuture<void>> future;
    future.resize(m_cursorOffset+1);
    int _nLawSize;
    _nLawSize	= m_cInfo.nPointQty + setup_DATA_PENDIX_LENGTH;

    WDATA* _pData,*_ptemData;

    if( m_pConfig->common.scanner.eScanType == setup_SCAN_TYPE_ONE_LINE){
        if(m_pGroup->m_mode==D_MODE)
            {
            _pData =_process->GetGroupDataDscanPointer(m_cInfo.nGroupId);
//            _pData = _process->GetGroupDataPointer(m_cInfo.nGroupId);
           _ptemData=_pData;
            }
        else{
            _pData = _process->GetGroupDataPointer(m_cInfo.nGroupId);
            _ptemData=_pData;
            }
    }else{
        _pData = _process->GetGroupDataPointerRaster(m_cInfo.nGroupId);
        _ptemData=_pData;
    }


    if(!_pData){
        return;
    }
	float  _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
	bool _bRectify = (_process->GetRectifierMode(m_cInfo.nGroupId) == setup_RECTIFIER_RF ) ;
    {
        int _idx1, _idx2, _iData, i , j,k;
        U8* _pImg1, *_pImg2;
        U8* _pImgAffect1, *_pImgAffect2;
        QVector < QVector < U8*> > Img2; //记录存储一次波位置数据

        /*****************1:1比例显示*************/
        if(m_pGroup->m_Shows==ON&&(_eAngle==setup_PROBE_PART_SKEW_0||_eAngle==setup_PROBE_PART_SKEW_90))
        {
            m_zoomFactor=m_nWidth/(float)m_nHeight;
            m_width=m_nHeight ;
            m_xoffset= 0;
            if(m_nHeight>m_nWidth)
            {
                m_zoomFactor=m_nHeight/(float)m_nWidth;
                m_pGroup->zoomFactor=1/m_zoomFactor;
                m_width=m_nWidth*1/m_zoomFactor;
            }
        }
        else if(m_pGroup->m_Shows==ON&&(_eAngle==setup_PROBE_PART_SKEW_180||_eAngle==setup_PROBE_PART_SKEW_270) )
        {
            m_zoomFactor=m_nWidth/(float) m_nHeight;
            m_width=m_nWidth ;
            m_xoffset= m_nWidth-m_nHeight;
        }else
        {
           m_zoomFactor =1;
           m_width=m_nWidth;
           m_xoffset= 0;
        }
       /*****************1:1比例显示*************/
         m_tempdata.resize(m_nHeight);//行-高
         for(int j=0;j<m_tempdata.size();j++)
         {
             m_tempdata[j].resize(m_nWidth);//列-宽
         }

         m_RefTempdata.resize(m_nHeight);//行-高
         for(int j=0;j<m_RefTempdata.size();j++)
         {
             m_RefTempdata[j].resize(m_nWidth);//列-宽
         }

         int m_Offsety=OFFSET_Y/_nStepY; //坐标偏移
         int m_i=(m_thickness-(_fStart+OFFSET_Y))/_nStepY+m_Offsety;//一次波截止纵坐标
         if(!m_pGroup->m_Retype)//不翻转
         {
//             QElapsedTimer timer;
//             timer.start();

             //开启线程计算数据
             for(k=0;k<m_cursorOffset;k++)
             {
                 _pData=_ptemData+_nFrameOffset*k;//注意叠加
                 if(k==0)
                 {
                    future[k]=QtConcurrent::run(this,&DopplerDrawSScanTrueDepth::CalcDscanDate,_pData,pImage_,k);
                    future[k].waitForFinished();
                 }
                 else
                 {
                   future[k]=QtConcurrent::run(this,&DopplerDrawSScanTrueDepth::CalcDscanDate,_pData,pImage_,k);
                 }
             }
             //等待线程结束
             for(k=0;k<m_cursorOffset;k++)
             {
              if(future[k].isFinished())
                    continue;
              else
                    future[k].waitForFinished();
             }

             //绘制图像
             for(i = 0; i< m_nHeight; i++)
             {
                 _pImg1 = _pImageBits + _nWidthStep * i;//每行数据的起点位置
                 _pImgAffect1 = pAffectImageBits + affectImgWidthStep * i;
                 for(j = 0+m_xoffset; j < m_width; j++)
                 {
                  _idx1 = i * m_nWidth + (j-m_xoffset)*m_zoomFactor ; //图像每个像素点位置(颜色索引)
                  if(m_pDraw[_idx1] == WAVE_MAX || m_pDraw[_idx1] == WAVE_HALF)
                  {
                  _pImg2 = _pImg1 + j * 3;
                  memcpy(_pImg2, &m_pColor[m_tempdata[i][j]], 3); //将数据拷贝到图像地址中
                  }
                  if (m_pDraw[_idx1]  == WAVE_HALF) {
                    _pImgAffect2 = _pImgAffect1 + j * 4;
                     memcpy(_pImgAffect2, COMPOSITION_COLOR, 4);
                     }
                 }
             }
//             int timeCost = timer.elapsed();
//             qDebug() << "save cost:"<< timeCost << "ms";
         }else{//反射
             for(k=0;k<m_cursorOffset;k++)
             {
                _pData=_ptemData+_nFrameOffset*k;//注意叠加
             if(k==0)
             {
                future[k]=QtConcurrent::run(this,&DopplerDrawSScanTrueDepth::CalcDscanDateReflect,_pData,pImage_,k);
                future[k].waitForFinished();
             }
             else
               {
                 future[k]=QtConcurrent::run(this,&DopplerDrawSScanTrueDepth::CalcDscanDateReflect,_pData,pImage_,k);
               }
            }
             //等待线程结束
             for(k=0;k<m_cursorOffset;k++)
             {
              if(future[k].isFinished())
                    continue;
              else
                    future[k].waitForFinished();
             }
             //绘制图像
             //一次波图像
             for(i = m_Offsety;i<m_i&&i<m_nHeight; i++)
             {
                 _pImg1 = _pImageBits + _nWidthStep * i;//每行数据的起点位置
                 for(j = 0+m_xoffset; j < m_width; j++)
                 {
                    _idx1 = (i-m_Offsety) * m_nWidth + (j-m_xoffset)*m_zoomFactor ; //图像每个像素点位置(颜色索引)
                     if(m_pDraw[_idx1] == WAVE_MAX || m_pDraw[_idx1] == WAVE_HALF)
                     {
                     _pImg2 = _pImg1 + j * 3 ;
                     memcpy(_pImg2, &m_pColor[m_tempdata[i][j]],3);
                  }
               }
             }
             //二次波图像
             int m_AxisHeight=((m_thickness+OFFSET_Y-(_fStart+OFFSET_Y))/_nStepY)*2; //翻转轴高度
             int m_DateOffset=m_nHeight+m_Offsety; //颜色数据偏移后高度
             for(i = m_i; i<m_AxisHeight&&i<m_DateOffset;i++)//底波范围
             {
                _pImg1 = _pImageBits + _nWidthStep * (m_AxisHeight-i);//每行数据的起点位置
                 _pImgAffect1 = pAffectImageBits + affectImgWidthStep * (m_AxisHeight-i);
                 for(j = 0+m_xoffset; j < m_width; j++)
                 {
                   _idx1 = (i-m_Offsety) * m_nWidth + (j-m_xoffset)*m_zoomFactor ; //图像每个像素点位置(颜色索引)
                  if(m_pDraw[_idx1] == WAVE_MAX || m_pDraw[_idx1] == WAVE_HALF)
                  {
                  _pImg2 = _pImg1 + j * 3;
                  memcpy(_pImg2, &m_pColor[m_RefTempdata[m_AxisHeight-i][j]],3); //将数据拷贝到图像地址中
                  }
                  if (m_pDraw[_idx1]  == WAVE_HALF) {
                    _pImgAffect2 = _pImgAffect1 + j * 4;
                     memcpy(_pImgAffect2, COMPOSITION_COLOR, 4);
                     }
                }
            }
        }
        if (m_bWeldRemainingHeightAffect) {
          // blend
          QPainter imagepainter(pImage_);
          imagepainter.setCompositionMode(QPainter::CompositionMode_SourceOver);
          imagepainter.drawImage(0,0, weldRemainHeightAffectImage);
          imagepainter.end();
        }
        //1:1开启更新LAW
        if(m_pGroup->m_Shows==ON)
        {
        if(m_nHeight>m_nWidth)
            m_pGroup->zoomFactor=m_nWidth/(float) m_nHeight;
        else
            m_pGroup->zoomFactor = m_nHeight/(float)m_nWidth;
        emit updateAllItem();
        }
    }
}
void DopplerDrawSScanTrueDepth::CalcDscanDate(WDATA* _pData,QImage* pImage_,int num)
{
    int _idx1, _idx2, _iData, i , j;
     U8* _pImg1, *_pImg2;
     static int count;
    ParameterProcess* _process = ParameterProcess::Instance();
    U8* _pImageBits = pImage_->bits();// 获取图像的首地址 https://blog.csdn.net/lengyuezuixue/article/details/80656358
    int _nWidthStep = pImage_->bytesPerLine();// 获取图像每行字节数
    float  _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
    bool _bRectify = (_process->GetRectifierMode(m_cInfo.nGroupId) == setup_RECTIFIER_RF );
    int _nLawSize;
    _nLawSize	= m_cInfo.nPointQty + setup_DATA_PENDIX_LENGTH;

    QImage weldRemainHeightAffectImage(pImage_->width(), pImage_->height(), QImage::Format_RGBA8888);
    U8* pAffectImageBits = weldRemainHeightAffectImage.bits();
    memset(pAffectImageBits, 0, weldRemainHeightAffectImage.byteCount());
    for(i = 0; i< m_nHeight; i++)
    {
        _pImg1 = _pImageBits + _nWidthStep * i;//每行数据的起点位置
        for(j = 0+m_xoffset; j < m_width; j++)
        {
           _idx1 = i * m_nWidth + (j-m_xoffset)*m_zoomFactor ; //图像每个像素点位置(颜色索引)
           if(m_pDraw[_idx1] == WAVE_MAX || m_pDraw[_idx1] == WAVE_HALF)
            {
              //当前一共多少个采样点
                _idx2  = (int)(m_pAngleZoom[_idx1] * _nLawSize + m_pDataNo[_idx1]);
                _pImg2 = _pImg1 + j * 3;
                _iData = (int)((_pData[_idx2]) * (COLOR_STEP - m_pDrawRate[_idx1]) * m_pColRate[_idx1] +
                         _pData[_idx2 + 1] * (COLOR_STEP - m_pDrawRate[_idx1]) * ( COLOR_STEP - m_pColRate[_idx1]) +
                         _pData[_idx2 + _nLawSize] * m_pDrawRate[_idx1] * m_pColRate[_idx1] +
                         _pData[_idx2 + _nLawSize + 1] * m_pDrawRate[_idx1] * ( COLOR_STEP - m_pColRate[_idx1]));
                _iData = _iData>>(COLOR_SHIFT * 2);  //右移
                _iData = _process->GetRefGainScaleData(_iData, _fScale, _bRectify);
                    if(num==0)
                     {
                           m_tempdata[i][j]=_iData;
                     }else{
                         if(m_tempdata[i][j]<_iData)
                         {
                            m_tempdata[i][j]=_iData;
                        }
                   }
              }
          }
     }
}

void DopplerDrawSScanTrueDepth::CalcDscanDateReflect(WDATA* _pData,QImage* pImage_,int num)
{
    int _idx1, _idx2, _iData, i , j;
    U8* _pImg1, *_pImg2;
    ParameterProcess* _process = ParameterProcess::Instance();
    U8* _pImageBits = pImage_->bits();// 获取图像的首地址 https://blog.csdn.net/lengyuezuixue/article/details/80656358
    int _nWidthStep = pImage_->bytesPerLine();// 获取图像每行字节数
    float  _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
    bool _bRectify = (_process->GetRectifierMode(m_cInfo.nGroupId) == setup_RECTIFIER_RF );
    int _nLawSize;
    _nLawSize	= m_cInfo.nPointQty + setup_DATA_PENDIX_LENGTH;

    U8* _pImgAffect1, *_pImgAffect2;
    QImage weldRemainHeightAffectImage(pImage_->width(), pImage_->height(), QImage::Format_RGBA8888);
    U8* pAffectImageBits = weldRemainHeightAffectImage.bits();
    memset(pAffectImageBits, 0, weldRemainHeightAffectImage.byteCount());
    int affectImgWidthStep = weldRemainHeightAffectImage.bytesPerLine();
    float _fStart , _fStop;
    _process->GetSScanVerticalRange(m_cInfo.nGroupId , &_fStart ,  &_fStop);
    int m_Offsety=OFFSET_Y/_nStepY; //坐标偏移
    int m_i=(m_thickness-(_fStart+OFFSET_Y))/_nStepY+m_Offsety;//一次波截止纵坐标
    QVector < QVector < U8*> > Img2; //记录存储一次波位置数据
    static QVector <QVector<int>> tempdata2;

    Img2.resize(m_nHeight);//设置向量行-高
    for(int j=0;j<Img2.size();j++)
    {
        Img2[j].resize(m_nWidth);//设置向量列-宽
    }
    tempdata2.resize(m_nHeight);//设置向量行-高
    for(int j=0;j<tempdata2.size();j++)
    {
        tempdata2[j].resize(m_nWidth);//设置向量列-宽
    }

    //显示和记录一次波数据
    for(i = m_Offsety;i<m_i&&i<m_nHeight; i++)
    {
        _pImg1 = _pImageBits + _nWidthStep * i;//每行数据的起点位置
        for(j = 0+m_xoffset; j < m_width; j++)
        {
            _idx1 = (i-m_Offsety) * m_nWidth + (j-m_xoffset)*m_zoomFactor ; //图像每个像素点位置(颜色索引)
                if(m_pDraw[_idx1] == WAVE_MAX || m_pDraw[_idx1] == WAVE_HALF)
                {
                    //当前一共多少个采样点
                    _idx2  = (int)(m_pAngleZoom[_idx1] * _nLawSize + m_pDataNo[_idx1]);

                    _iData = (int)((_pData[_idx2]) * (COLOR_STEP - m_pDrawRate[_idx1]) * m_pColRate[_idx1] +
                             _pData[_idx2 + 1] * (COLOR_STEP - m_pDrawRate[_idx1]) * ( COLOR_STEP - m_pColRate[_idx1]) +
                             _pData[_idx2 + _nLawSize] * m_pDrawRate[_idx1] * m_pColRate[_idx1] +
                             _pData[_idx2 + _nLawSize + 1] * m_pDrawRate[_idx1] * ( COLOR_STEP - m_pColRate[_idx1]));
                    _iData = _iData>>(COLOR_SHIFT * 2);  //右移
                    _pImg2 = _pImg1 + j * 3 ;
                    Img2[i][j]=_pImg2;//记录存储一次波数据位置
                    _iData = _process->GetRefGainScaleData(_iData, _fScale, _bRectify);
                    if(num==0)
                     {
                        m_tempdata[i][j]=_iData;
                        tempdata2[i][j]=_iData;
                     }else{
                         if(m_tempdata[i][j]<_iData)
                         {
                         m_tempdata[i][j]=_iData;
                         tempdata2[i][j]=_iData;
                         }
                     }
               }
          }
      }

    //翻转二次波(底波)图像-处理重叠部分 _fStart/_nStepY
    int m_AxisHeight=((m_thickness+OFFSET_Y-(_fStart+OFFSET_Y))/_nStepY)*2; //翻转轴高度
    int m_DateOffset=m_nHeight+m_Offsety; //颜色数据偏移后高度
    for(i = m_i; i<m_AxisHeight&&i<m_DateOffset;i++)//底波范围
        {
            _pImg1 = _pImageBits + _nWidthStep * (m_AxisHeight-i);//每行数据的起点位置
            _pImgAffect1 = pAffectImageBits + affectImgWidthStep * (m_AxisHeight-i);
            for(j = 0+m_xoffset; j < m_width; j++)
            {
                _idx1 = (i-m_Offsety) * m_nWidth + (j-m_xoffset)*m_zoomFactor ; //图像每个像素点位置
                if(m_pDraw[_idx1] == WAVE_MAX || m_pDraw[_idx1] == WAVE_HALF)
                {
                    //当前一共多少个采样点
                    _idx2  = (int)(m_pAngleZoom[_idx1] * _nLawSize + m_pDataNo[_idx1]);

                    _iData = (int)((_pData[_idx2]) * (COLOR_STEP - m_pDrawRate[_idx1]) * m_pColRate[_idx1] +
                             _pData[_idx2 + 1] * (COLOR_STEP - m_pDrawRate[_idx1]) * ( COLOR_STEP - m_pColRate[_idx1]) +
                             _pData[_idx2 + _nLawSize] * m_pDrawRate[_idx1] * m_pColRate[_idx1] +
                             _pData[_idx2 + _nLawSize + 1] * m_pDrawRate[_idx1] * ( COLOR_STEP - m_pColRate[_idx1]));
                    _iData = _iData>>(COLOR_SHIFT * 2);  //右移
                    _pImg2 = _pImg1 + j * 3 ;
                    if(m_pGroup->m_Retype==FIRST) //一次波优先
                    {
                        if(m_AxisHeight-i>=m_nHeight) continue;//防止超过下标范围
                        _iData = _process->GetRefGainScaleData(_iData, _fScale, _bRectify);
                        if(num==0)
                         {
                            m_RefTempdata[m_AxisHeight-i][j]=_iData;
                         }else{
                                 if(m_RefTempdata[m_AxisHeight-i][j]<_iData)
                                 {
                                   m_RefTempdata[m_AxisHeight-i][j]=_iData;
                                 }
                              }
                        if(_pImg2==Img2[m_AxisHeight-i][j])
                        {
                          m_RefTempdata[m_AxisHeight-i][j]=tempdata2[m_AxisHeight-i][j];
                        }
                    }
                    if(m_pGroup->m_Retype==LAST)//反射波优先
                    {
                      if(m_AxisHeight-i>=m_nHeight) continue;//防止超过下标范围
                      _iData = _process->GetRefGainScaleData(_iData, _fScale, _bRectify);
                      if(num==0)
                       {
                          m_RefTempdata[m_AxisHeight-i][j]=_iData;
                       }else{
                           if(m_RefTempdata[m_AxisHeight-i][j]<_iData)
                           {
                             m_RefTempdata[m_AxisHeight-i][j]=_iData;
                           }
                           }
                    }
                    if(m_pGroup->m_Retype==OVERLAY)//叠加
                    {
                        if(m_AxisHeight-i>=m_nHeight) continue;//防止超过下标范围
                        _iData = _process->GetRefGainScaleData(_iData, _fScale, _bRectify);
                        if(num==0)
                         {
                            m_RefTempdata[m_AxisHeight-i][j]=_iData;
                         }else{
                                 if(m_RefTempdata[m_AxisHeight-i][j]<_iData)
                                 {
                                   m_RefTempdata[m_AxisHeight-i][j]=_iData;
                                 }
                              }
                        if(_pImg2==Img2[m_AxisHeight-i][j])
                         {
                           m_RefTempdata[m_AxisHeight-i][j]= tempdata2[m_AxisHeight-i][j]>m_RefTempdata[m_AxisHeight-i][j]?tempdata2[m_AxisHeight-i][j]:m_RefTempdata[m_AxisHeight-i][j];
                        }
                   }
                }
                if (m_pDraw[_idx1]  == WAVE_HALF) {
                   _pImgAffect2 = _pImgAffect1 + j * 4;
                   memcpy(_pImgAffect2, COMPOSITION_COLOR, 4);
                }
           }
      }
 }
































