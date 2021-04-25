#include "DopplerCoupleBar.h"
#include <assert.h>
#include <QPainter>
#include <process/ParameterProcess.h>

DopplerCoupleSScanBar::DopplerCoupleSScanBar( QWidget *parent) :
    QWidget(parent)
{
    assert(parent);
    setFixedWidth(DOPPLER_COUPLE_BAR_WIDTH);
    color = NULL ;
    nGroupId = 0;
    m_pConfig = DopplerConfigure::Instance();

    //************ set back ground color
    setAutoFillBackground(true);
    QPalette pal = this->palette();
    pal.setColor( QPalette::Background, Qt::black);
    setPalette(pal);
    setAcceptDrops(true);
}

void DopplerCoupleSScanBar::setColorIndex( void* color_)
{
    color  = (unsigned char (*)[3])color_;
    update();
}

void DopplerCoupleSScanBar::setGroupId( int groupId)
{
    nGroupId = groupId;
    update();
}

void DopplerCoupleSScanBar::paintEvent(QPaintEvent *)
{
    ParameterProcess* _process = ParameterProcess::Instance();
    WDATA* _pData = _process->GetCoupleDataPointer( nGroupId);
    if(!_pData)  return ;
    if(!color)  return;

    int _nWidth = width() - 1;
    int _nHeight = height() - 1;

    int dataQty = m_pConfig->group[nGroupId].nPointQty;
    float _fS, _fE;
    _process->GetSScanVerticalRange( nGroupId, &_fS , &_fE);
    float maxDepth = _fE - _fS;

    float coupleStart = m_pConfig->group[nGroupId].coupleMonitoringVelocity * m_pConfig->group[nGroupId].nTimeStart/2000000.0;
    float coupleDepth = m_pConfig->group[nGroupId].coupleMonitoringVelocity * m_pConfig->group[nGroupId].nTimeRange/2000000.0;    
    if( maxDepth <= 0 || coupleDepth <= 0)
    {
        return;
    }
    if( coupleStart + coupleDepth < _fS || coupleStart > _fE){
        return;
    }

    int start;
    int loopQty;
    float step;
    //开始处截断
    if( _fS > coupleStart){
        start = 0;
        dataQty = (coupleDepth - ( _fS - coupleStart))/coupleDepth*dataQty;
        coupleDepth = coupleDepth - ( _fS - coupleStart);
    }else{
        start = ( coupleStart - _fS)/maxDepth * _nHeight;
        _nHeight -= start;
        maxDepth = maxDepth - ( coupleStart - _fS);
    }

    //尾部截断
    if( maxDepth > coupleDepth){
        loopQty = _nHeight * coupleDepth / maxDepth;
        step = (float)dataQty / loopQty;
    }else{
        loopQty = _nHeight;
        int dataSize = dataQty * maxDepth / coupleDepth;
        step = (float)dataSize / loopQty;
    }

    QPainter _painter( this);
    int _nColor;
    float  _fScale = pow(10.0, CUR_RES.Couple_Com_Gain[nGroupId]/20.0);
    for( int i = start, j = 0; i < loopQty + start; i++, j++){
        _nColor = _process->correctionPdata(_pData[(int)(j*step)]) * _fScale;
        if(_nColor > WAVE_MAX){
            _nColor = WAVE_MAX;
        }
        _painter.setPen(QPen(QColor(color[_nColor][0] , color[_nColor][1] , color[_nColor][2])));
        _painter.drawLine(QPointF(0, i) , QPointF(_nWidth , i));
    }
}

DopplerCoupleCScanBar::DopplerCoupleCScanBar( BarOrientation direction, QWidget *parent) : m_dirction(direction),
    QWidget(parent)
{
    assert(parent);
    if(m_dirction)
    {
        setFixedWidth(DOPPLER_COUPLE_BAR_WIDTH);
    }
    else
    {
        setFixedHeight(DOPPLER_COUPLE_BAR_WIDTH);
    }

    color = NULL;
    nGroupId = 0;
    start = 0;
    end = 0;

    ParameterProcess* _process = ParameterProcess::Instance();
    scanRange = _process->GetRealScanRange();

    setAutoFillBackground(true);
    QPalette pal = this->palette();
    pal.setColor( QPalette::Background, Qt::white);
    setPalette(pal);
    setAcceptDrops(true);
}

void DopplerCoupleCScanBar::setColorIndex( void* color_)
{
    color  = (unsigned char (*)[3])color_;
    update();
}

void DopplerCoupleCScanBar::setGroupId( int groupId)
{
    nGroupId = groupId;
    update();
}

void DopplerCoupleCScanBar::paintEvent(QPaintEvent *)
{
    ParameterProcess* _process = ParameterProcess::Instance();
    QVector<WDATA> buff = _process->GetCoupleCScanData(nGroupId);
    if(!color)
    {
       return;
    }

    if(start == 0 && end == 0) return;

    if(buff.size() == 0)
    {
        return;
    }

    DopplerConfigure* pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG& _group = pConfig->group[nGroupId];

    double scanStart;
    if(pConfig->common.scanner.eScanEncoderType){
        scanStart = _group.fScanOffset;
    }
    else{
        scanStart = _group.fScanOffset/pConfig->common.scanner.fPrf;
    }
    double scanEnd = scanStart + scanRange;

    int _nWidth = width() - 1;
    int _nHeight = height() - 1;
    int buffsize = buff.size() - 1;
    QPainter _painter( this);
    float step;
    int _nColor;
    float  _fScale = pow(10.0, CUR_RES.Couple_Com_Gain[nGroupId]/20.0);
    if( start < scanStart){
        //全白
        if(end <= scanStart){
            if(m_dirction){
                _painter.setPen(QPen(Qt::white));
                for( int i = 0; i <= _nHeight; i++)
                {
                    _painter.drawLine(QPointF(0, _nHeight-i) , QPointF( _nWidth-1, _nHeight-i));
                }
            }
            else{
                _painter.setPen(QPen(Qt::white));
                for( int i = 0; i <= _nWidth; i++)
                {
                    _painter.drawLine(QPointF(i, 1) , QPointF( i, _nHeight));
                }
            }

        }//前面部分白色
        else if( end <= scanEnd){
            if(m_dirction){
                int startIndex = ( scanStart - start)/( end - start)*_nHeight;
                step = (float)buffsize / (_nHeight - startIndex) *(end - scanStart) / scanRange;
                _painter.setPen(QPen(Qt::white));
                for( int i = 0; i < startIndex; i++)
                {
                    _painter.drawLine(QPointF(0, _nHeight-i) , QPointF( _nWidth-1, _nHeight-i));
                }
                for(int i = startIndex; i <= _nHeight; i++)
                {
                    _nColor = _process->correctionPdata(buff[(int)((i - startIndex)*step + 0.5)]);
                    if( _nColor > WAVE_MAX){
                        _nColor = WAVE_MAX;
                    }
                    _painter.setPen(QPen(QColor(color[_nColor][0] , color[_nColor][1] , color[_nColor][2])));
                    _painter.drawLine(QPointF(0, _nHeight-i) , QPointF( _nWidth-1, _nHeight-i));
                }
            }
            else{
                int startIndex = ( scanStart - start)/( end - start)*_nWidth;
                step = (float)buffsize / (_nWidth - startIndex) *(end - scanStart) / scanRange;
                _painter.setPen(QPen(Qt::white));
                for( int i = 0; i < startIndex; i++)
                {
                    _painter.drawLine(QPointF( i, 1) , QPointF( i, _nHeight));
                }
                for(int i = startIndex; i <= _nWidth; i++)
                {
                    _nColor = _process->correctionPdata(buff[(int)((i - startIndex)*step + 0.5)]);
                    if( _nColor > WAVE_MAX){
                        _nColor = WAVE_MAX;
                    }
                    _painter.setPen(QPen(QColor(color[_nColor][0] , color[_nColor][1] , color[_nColor][2])));
                    _painter.drawLine(QPointF( i, 1) , QPointF( i, _nHeight));
                }
            }

        }//前后都有白色
        else{
            if(m_dirction){
                int startIndex = ( scanStart - start)/( end - start)*_nHeight;
                int endIndex = ( scanEnd - start)/( end - start)*_nHeight;
                step = (float)buffsize / ( endIndex - startIndex);
                _painter.setPen(QPen(Qt::white));
                for( int i = 0; i < startIndex; i++)
                {
                    _painter.drawLine(QPointF(0, _nHeight-i) , QPointF( _nWidth-1, _nHeight-i));
                }
                for(int i = startIndex; i < endIndex; i++)
                {
                    _nColor = _process->correctionPdata(buff[(int)((i - startIndex)*step + 0.5)]);
                    if( _nColor > WAVE_MAX){
                        _nColor = WAVE_MAX;
                    }
                    _painter.setPen(QPen(QColor(color[_nColor][0] , color[_nColor][1] , color[_nColor][2])));
                    _painter.drawLine(QPointF(0, _nHeight-i) , QPointF( _nWidth-1, _nHeight-i));
                }
                _painter.setPen(QPen(Qt::white));
                for(int i = endIndex; i <= _nHeight; i++)
                {
                    _painter.drawLine(QPointF(0, _nHeight-i) , QPointF( _nWidth-1, _nHeight-i));
                }
            }
            else{
                int startIndex = ( scanStart - start)/( end - start)*_nWidth;
                int endIndex = ( scanEnd - start)/( end - start)*_nWidth;
                step = (float)buffsize / ( endIndex - startIndex);
                _painter.setPen(QPen(Qt::white));
                for( int i = 0; i < startIndex; i++)
                {
                    _painter.drawLine(QPointF( i, 1) , QPointF( i, _nHeight));
                }
                for(int i = startIndex; i < endIndex; i++)
                {
                    _nColor = _process->correctionPdata(buff[(int)((i - startIndex)*step + 0.5)]);
                    if( _nColor > WAVE_MAX){
                        _nColor = WAVE_MAX;
                    }
                    _painter.setPen(QPen(QColor(color[_nColor][0] , color[_nColor][1] , color[_nColor][2])));
                    _painter.drawLine(QPointF( i, 1) , QPointF( i, _nHeight));
                }
                _painter.setPen(QPen(Qt::white));
                for(int i = endIndex; i <= _nWidth; i++)
                {
                    _painter.drawLine(QPointF( i, 1) , QPointF( i, _nHeight));
                }
            }
        }
    }
    else if( start < scanEnd){
        //没有白色
        if( end < scanEnd){
            if(m_dirction){
                int startIndex = (start - scanStart)/scanRange * buffsize;
                step = (float)buffsize / _nHeight *(end - start) / scanRange;
                for(int i = 0; i <= _nHeight; i++)
                {
                    _nColor = _process->correctionPdata(buff[(int)(i*step + startIndex + 0.5)]) * _fScale;
                    if( _nColor > WAVE_MAX){
                        _nColor = WAVE_MAX;
                    }
                    _painter.setPen(QPen(QColor(color[_nColor][0] , color[_nColor][1] , color[_nColor][2])));
                    _painter.drawLine(QPointF(0, _nHeight-i) , QPointF( _nWidth-1, _nHeight-i));
                }
            }
            else{
                int startIndex = (start - scanStart)/scanRange * buffsize;
                step = (float)buffsize / _nWidth *(end - start) / scanRange;
                for(int i = 0; i <= _nWidth; i++)
                {
                    _nColor = _process->correctionPdata(buff[(int)(i*step + startIndex + 0.5)]) * _fScale;
                    if( _nColor > WAVE_MAX){
                        _nColor = WAVE_MAX;
                    }
                    _painter.setPen(QPen(QColor(color[_nColor][0] , color[_nColor][1] , color[_nColor][2])));
                    _painter.drawLine(QPointF(i, 1) , QPointF(  i, _nHeight));
                }
            }
        }//后面白色
        else{
            if(m_dirction){
                int startIndex = (start - scanStart)/scanRange*buffsize;
                int endIndex = ( scanEnd - start)/(end - start)*_nHeight;
                step = (float)buffsize / _nHeight *(end - start) / scanRange;
                for( int i = 0; i < endIndex; i++)
                {
                    _nColor = _process->correctionPdata(buff[(int)(i*step + startIndex + 0.5)]) * _fScale;
                    if( _nColor > WAVE_MAX){
                        _nColor = WAVE_MAX;
                    }
                    _painter.setPen(QPen(QColor(color[_nColor][0] , color[_nColor][1] , color[_nColor][2])));
                    _painter.drawLine(QPointF(0, _nHeight-i) , QPointF( _nWidth-1, _nHeight-i));
                }
                _painter.setPen(QPen(Qt::white));
                for( int i = endIndex; i <= _nHeight; i++)
                {
                    _painter.drawLine(QPointF(0, _nHeight-i) , QPointF( _nWidth-1, _nHeight-i));
                }
            }
            else{
                int startIndex = (start - scanStart)/scanRange*buffsize;
                int endIndex = ( scanEnd - start)/(end - start)*_nWidth;
                step = (float)buffsize / _nWidth *(end - start) / scanRange;
                for( int i = 0; i < endIndex; i++)
                {
                    int buffIndex = (int)(i*step + startIndex + 0.5);
                    if(buffIndex > buffsize)
                    {
                        buffIndex = buffsize;
                    }
                    _nColor = _process->correctionPdata(buff[buffIndex]) * _fScale;
                    if( _nColor > WAVE_MAX){
                        _nColor = WAVE_MAX;
                    }
                    _painter.setPen(QPen(QColor(color[_nColor][0] , color[_nColor][1] , color[_nColor][2])));
                    _painter.drawLine(QPointF(i, 1) , QPointF( i, _nHeight));
                }
                _painter.setPen(QPen(Qt::white));
                for( int i = endIndex; i <= _nWidth; i++)
                {
                    _painter.drawLine(QPointF(i, 1) , QPointF( i, _nHeight));
                }
            }
        }
    }//全白
    else{
        if(m_dirction){
            _painter.setPen(QPen(Qt::white));
            for( int i = 0; i <= _nHeight; i++)
            {
                _painter.drawLine(QPointF(0, _nHeight-i) , QPointF( _nWidth-1, _nHeight-i));
            }
        }
        else{
            _painter.setPen(QPen(Qt::white));
            for( int i = 0; i <= _nWidth; i++)
            {
                _painter.drawLine(QPointF(i, 1) , QPointF( i, _nHeight));
            }
        }
    }

}
