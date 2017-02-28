#include "DopplerDrawSScanSoundPath.h"
#include <process/ParameterProcess.h>
#include <QImage>

DopplerDrawSScanSoundPath::DopplerDrawSScanSoundPath() :
    DopplerDrawScan()
{
}

void DopplerDrawSScanSoundPath::UpdateDrawInfo()
{
    ParameterProcess* _process = ParameterProcess::Instance();
    m_SScanInfo.nPointQty  = _process->GetGroupPointQty(m_cInfo.nGroupId);
    m_SScanInfo.nLawQty    = _process->GetGroupLawQty(m_cInfo.nGroupId) ;
	m_SScanInfo.pMarker    = _process->GetScanMarker(m_cInfo.nGroupId);
}

void DopplerDrawSScanSoundPath::Draw (QImage *pImage_)
{
    int _nHeight      = pImage_->height() - 1;
    int _nWidth       = pImage_->width() - 1 ;

    U8* _pImageBits = pImage_->bits() ;
    U8* _pImg1  , *_pImg2;

    int _nWidthStep   = pImage_->bytesPerLine()      ;
    ParameterProcess* _process = ParameterProcess::Instance();
    int _nLawQty      = m_SScanInfo.nLawQty   - 1    ;
    int _nPointQty    = m_SScanInfo.nPointQty - 1    ;
    int _nLawSize     = m_SScanInfo.nPointQty + 32   ;

    WDATA* _pData = _process->GetGroupDataPointer(m_cInfo.nGroupId) ;
    if(!_pData)  return ;

    WDATA* _pLawData;
	//int _nScanPos = _process->GetScanIndexPos()  ;

    int i , j , k, _nLawCurrent , _nPointPos;
    int _nLawOld  = -1;

    float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
    int _nTmpValue ;
    bool _bRectify = (_process->GetRectifierMode(m_cInfo.nGroupId) == setup_RECTIFIER_RF ) ;
	//if(m_SScanInfo.pMarker[_nScanPos])
    {
        for(i = 0 , k = _nHeight ; i <= _nHeight ; i++ , k--)
        {
            _pImg1       = _pImageBits + k * _nWidthStep ;
            _nLawCurrent = (i * _nLawQty)  / _nHeight;
            if(_nLawOld == _nLawCurrent)
            {
                memcpy(_pImg1 , _pImg1 + _nWidthStep , _nWidthStep) ;
            }
            else
            {
                _nLawOld  = _nLawCurrent ;
                _pLawData = _pData + _nLawSize * _nLawCurrent  ;
                for(j = 0 ; j <= _nWidth ; j++)
                {
                    _nPointPos  = (j * _nPointQty) / _nWidth ;
                    _pImg2 = j * 3 + _pImg1   ;
                    _nTmpValue  = _process->GetRefGainScaleData(_pLawData[_nPointPos], _fScale, _bRectify);
                    memcpy(_pImg2, &m_pColor[_nTmpValue], 3);
                }
            }
        }
    }
	//else
	//{
	//    memset(_pImageBits , 0 , _nHeight * _nWidthStep) ;
	//}
}
