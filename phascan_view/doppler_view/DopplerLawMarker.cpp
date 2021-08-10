#include "DopplerLawMarker.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QPen>
#include <QPolygon>
#include <gHeader.h>

DopplerLawMarker::DopplerLawMarker()
{
    setZValue(300);
    setFlags(ItemIsSelectable);
    m_cMarkers.clear();
    m_cMarkers.append(QLineF(10 , 10  , 50, 50));

    m_nMarkerQty = 1;
    m_anMarkerId[0] = 0   ;
    m_anMarkerId[1] = 1   ;
    m_anMarkerId[2] = 2   ;

	m_aColor[2] = LAW_3_COLOR;
	m_aColor[1] = LAW_2_COLOR;
	m_aColor[0] = LAW_1_COLOR;
    m_cColorWeld= QColor(255 , 255 , 0)  ;
    m_nWidth = 600;
    m_nHeight= 480;
    m_nSelectedMarker = -1 ;
    m_nPostSelect = 0 ;

    m_eDirection = VERTICAL  ;
    m_bShowWeld  = false     ;

     m_nGroup  = 0 ;

}

QVector<QLineF>* DopplerLawMarker::GetMarkerVector()
{
    return &m_cMarkers ;
}

void DopplerLawMarker::SetupMarkers(QVector<QLineF>* pLines_)
{
    m_eDirection = VERTICAL  ;
    m_cMarkers.clear();
    for(int i = 0 ; i < pLines_->count() ; i++)
    {
        m_cMarkers.append(pLines_->at(i));
        if(FLOAT_EQ((pLines_->at(i).y1() - pLines_->at(i).y2()) , 0))  m_eDirection = HORIZENTAL  ;
    }
    m_anMarkerId[0] = m_anMarkerId[0] < pLines_->count()  ? m_anMarkerId[0] : 0;
    m_anMarkerId[1] = m_anMarkerId[1] < pLines_->count()  ? m_anMarkerId[1] : 0;
    m_anMarkerId[2] = m_anMarkerId[2] < pLines_->count()  ? m_anMarkerId[2] : 0;
}

void DopplerLawMarker::SetupStringMarker(QVector<QString>* pMarker_)
{
    m_strMarker.clear() ;
    for(int i = 0 ; i < pMarker_->count() ; i++)
    {
        m_strMarker.append(pMarker_->at(i));
    }
}

void DopplerLawMarker::SetMarkerColor(int nId_ , QColor* pColor_)
{
    m_aColor[nId_] = *pColor_ ;
}

void DopplerLawMarker::SetWeldColor(const QColor& color_)
{
    m_cColorWeld = color_ ;
}

void DopplerLawMarker::EnableMarkerQty(unsigned int nQty_)
{
    if(nQty_ >= 3 )  nQty_ = 3 ;
    m_nMarkerQty  = nQty_ ;
    int _nLineQty = m_cMarkers.count() ;

    m_anMarkerId[0] = 0   ;
    m_anMarkerId[1] = 1 >= _nLineQty ? 1 : 0  ;
    m_anMarkerId[2] = 2 >= _nLineQty ? 2 : 0  ;
}

void DopplerLawMarker::SetMarkerPos(int nMarker_ , int nMarkerPos_)
{
    if(nMarker_ < 0) return ;
    if(nMarker_ > 2) return ;
    m_anMarkerId[nMarker_] = nMarkerPos_ ;
    update();
}

QRectF DopplerLawMarker::boundingRect () const
{
    QRectF _rect(0 , 0 , 0 , 0) ;
    _rect = QRectF(0 , 0 , m_nWidth , m_nHeight) ;
    return _rect ;
}

QPainterPath DopplerLawMarker::shape () const
{
    QPainterPath path ;
    QVector<QPoint> _vector ;
    for(int i = 0 ; i < m_nMarkerQty ; i++)
    {
        if(i == 1 && m_anMarkerId[1] == m_anMarkerId[0]) continue ;
        if(i == 2 && m_anMarkerId[2] == m_anMarkerId[0]) continue ;
        if(i == 2 && m_anMarkerId[2] == m_anMarkerId[1]) continue ;

        QLineF _line = m_cMarkers.at(m_anMarkerId[i]) ;
        if(m_eDirection == HORIZENTAL)
        {

            _vector << QPoint(0 , _line.y1()-4)
                    << QPoint(0 , _line.y1()+4)
                    << QPoint(m_nWidth , _line.y2()+4)
                    << QPoint(m_nWidth , _line.y2()-4)
                    << QPoint(0  , _line.y1() - 4)  ;
            path.moveTo(0 , _line.y1());
        }
        else
        {

            _vector << QPoint(_line.x1() - 4 , _line.y1())
                    << QPoint(_line.x1() + 4 , _line.y1())
                    << QPoint(_line.x2() + 4 , _line.y2())
                    << QPoint(_line.x2() - 4 , _line.y2())
                    << QPoint(_line.x1() - 4 , _line.y1())  ;
            path.moveTo(QPoint(_line.x1() - 4 , _line.y1()));

        }
    }
    QPolygon _polygon(_vector);
    path.addPolygon(_polygon);
    return path ;

}
void DopplerLawMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem* /*item*/, QWidget* /*widget*/)
{
    QPen _pen;
    _pen.setWidth(0);
    QPen _NewPen;
    _NewPen.setWidth(2);
    QVector<qreal> dashes;
    dashes << 1 << 4 << 1 <<4 ;
    _NewPen.setDashPattern(dashes);


    DopplerConfigure* pConfigure = DopplerConfigure::Instance();
    ParameterProcess* pProcess = ParameterProcess::Instance();
    if (m_pDataView) {
        m_nGroup = m_pDataView->GetGroupId();
    }
    GROUP_CONFIG& _group = pConfigure->group[m_nGroup];
    int  _nLawQty = pProcess->GetGroupLawQty(m_nGroup) ;

    for(int i = 0 ; i < m_nMarkerQty ; i++)
    {
        if(i == m_nSelectedMarker)
        {
           QColor _color = m_aColor[i].lighter()  ;
           _pen.setColor(_color);
           painter->setPen(_pen);
           QLineF _line = m_cMarkers.at(m_anMarkerId[i]);

           if(m_eDirection == HORIZENTAL)  _line = QLineF(0 , _line.y1() , m_nWidth, _line.y1());
           painter->drawLine(_line);
           _NewPen.setColor(_color);
           painter->setPen(_NewPen);

           if(m_eDirection == HORIZENTAL)
           {
               _line = QLineF(0 , dotLine.y1() , m_nWidth, dotLine.y1());
               painter->drawLine(_line);
           }
           else
               painter->drawLine(dotLine);

           /********m_Retype不为零***扫查轴翻转*************/
           if(_group.m_Retype)
           {

               _pen.setColor(_color);
               painter->setPen(_pen);
               QLineF _line2 = m_cMarkers.at(m_anMarkerId[i]+_nLawQty);
               if(m_eDirection == HORIZENTAL)  _line2 = QLineF(0 , _line2.y1() , m_nWidth, _line2.y1());
               painter->drawLine(_line2);

               _NewPen.setColor(_color);
               painter->setPen(_NewPen);
               painter->drawLine(_line2);
           }
           /******m_Retype不为零*****扫查轴翻转*************/
        }else
        {
            QColor _color = m_aColor[i];
            _pen.setColor(_color);
            painter->setPen(_pen);
            QLineF _line = m_cMarkers.at(m_anMarkerId[i]);

            if(m_eDirection == HORIZENTAL) _line = QLineF(0 , _line.y1() , m_nWidth, _line.y1());
            painter->drawLine(_line);
            _NewPen.setColor(_color);
            painter->setPen(_NewPen);
            painter->drawLine(_line);
           /***********扫查轴翻转*************/
           if(_group.m_Retype)
           {
           _pen.setColor(_color);
           painter->setPen(_pen);
           QLineF _line2 = m_cMarkers.at(m_anMarkerId[i]+_nLawQty);

           if(m_eDirection == HORIZENTAL)   _line = QLineF(0 , _line.y1() , m_nWidth, _line.y1());
           painter->drawLine(_line2);

           _NewPen.setColor(_color);
           painter->setPen(_NewPen);
           painter->drawLine(_line2);
          /***********扫查轴翻转*************/
           }

        }

        DrawLabel(painter , i) ;
    }
    if(m_bShowWeld)
        DrawWeld(painter) ;


}

void DopplerLawMarker::DrawLabel(QPainter *painter , int nIndex_)
{
//    if(m_cMarkers.size() == 0 || m_strMarker.size() == 0){
//        return;
//    }
    QLineF _line = m_cMarkers.at(m_anMarkerId[nIndex_]) ;
    double _fPos1 = 0.2 - nIndex_ * 0.05 ;
    double _fPos2 = 1 - _fPos1 ;
    float _fPosX = _line.p1().x() * _fPos1 + _line.p2().x() * _fPos2 ;
    float _fPosY = _line.p1().y() * _fPos1 + _line.p2().y() * _fPos2 ;
//    double scaleFactor = 1.0 / painter->matrix().m11();
//    painter->scale(scaleFactor, scaleFactor);
    //qDebug()<<"_fPosX"<<_fPosX<<"_fPosY"<<_fPosY<<"string"<<m_strMarker.at(m_anMarkerId[nIndex_]);
    painter->drawText(_fPosX , _fPosY , m_strMarker.at(m_anMarkerId[nIndex_]) );
}

void DopplerLawMarker::DrawWeld(QPainter *painter)
{
    if(!m_bShowWeld) return  ;
    QPen _pen;
    QVector<qreal> dashes;
    dashes << 5 << 2  ;
    _pen.setDashPattern(dashes);
    _pen.setColor(m_cColorWeld);
    _pen.setWidth(2);
    painter->setPen(_pen);
    painter->drawPath(weld);
//    if(m_brushHAZ){
//        QBrush curBrush = painter->brush();
//        curBrush.setColor(m_cColorWeld);
//        curBrush.setStyle(Qt::Dense7Pattern);
//        painter->setBrush(curBrush);
//        _pen.setStyle(Qt::NoPen);
//        painter->setPen(_pen);
//        painter->drawPath(HAZBrush);
//        //painter->setBrush(Qt::Dense7Pattern);
//    }
}


void DopplerLawMarker::SetItemGeometry (QRectF&)
{
    setPos(0 , 0);
    m_nWidth = this->scene()->width();
    m_nHeight= this->scene()->height();
}


void DopplerLawMarker::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    int _nPos ;
    int _nZoom;
    float _fScale ;
    GetCurrentLineIndex(event->pos() , &_nPos , &_nZoom , &_fScale);
    m_nSelectedMarker = -1 ;
    for(int i = 0 ; i < m_nMarkerQty ; i++)
    {
        if(m_anMarkerId[i] == _nPos)
        {
            m_nPostSelect = m_nSelectedMarker = i ;
            dotLine = m_cMarkers.at(_nPos);
            setSelected(true);
            setCursor(QCursor(Qt::SizeAllCursor)) ;
        }
    }
}

void DopplerLawMarker::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    if(m_nSelectedMarker < 0)
        return ;
    int _nPos ;
    int _nZoom;
    float _fScale ;
    GetCurrentLineIndex(event->pos() , &_nPos , &_nZoom , &_fScale);
    ParameterProcess* pProcess = ParameterProcess::Instance();
   int  _nLawQty = pProcess->GetGroupLawQty(m_nGroup) ;
    if(_nPos>=_nLawQty-1)
    {
     _nPos=_nLawQty-1 ;

    }
    if(_nZoom>=_nLawQty-1)
    {
     _nZoom=_nLawQty-2 ; // GetCurrentPosLine 函数中有 +1操作，所以最大为29

    }
    m_anMarkerId[m_nSelectedMarker] = _nPos ;
    dotLine = GetCurrentPosLine( _nZoom , _fScale);
    update();
}


void DopplerLawMarker::mouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    setSelected(false);
    setCursor(QCursor(Qt::ArrowCursor)) ;
    m_nSelectedMarker = -1 ;
    update();
}


void DopplerLawMarker::GetCurrentLineIndex(QPointF pos_ , int* nIndex_ , int* nZoom_ ,float* fScale_ )
{
    int _nCount = m_cMarkers.count() ;
    // 如果  LAW 标识 是水平的
    if(m_eDirection == HORIZENTAL)
    {
        float _fYPos = pos_.y();
        if(_fYPos >= m_cMarkers.at(0).y1())
        {
            *nIndex_ = *nZoom_ = 0;
            *fScale_  = 0 ;
            return  ;
        }
        if(_fYPos <= m_cMarkers.at(_nCount - 1).y1())
        {
            *nIndex_ = *nZoom_ = _nCount - 1;
            *fScale_  = 0;
            return  ;
        }
        for(int i = 1; i < _nCount  ; i++)
        {
            if(_fYPos >= m_cMarkers.at(i).y1())
            {
                *nZoom_   = i - 1;
                *fScale_  = fabs(m_cMarkers.at(i-1).y1() - _fYPos) / fabs(m_cMarkers.at(i).y1() - m_cMarkers.at(i-1).y1()) ;
                *nIndex_ = (*fScale_ <= 0.5) ? *nZoom_ : i ;
                return ;
            }
        }
        *nIndex_ = *nZoom_ = _nCount -1;
        *fScale_  = 0;
    }
    else
    {
        // 如果  LAW 标识 不是水平的
        if(_nCount <= 1)
        {
            *nIndex_ = *nZoom_ = 0;
            *fScale_  = 0;
            return ;
        }

        float _fTmpX[256] ;
        QLineF _line = m_cMarkers.at(0) ;
        QLineF _line1= m_cMarkers.at(1) ;
        QPointF _pos1 = _line.p1();
        QPointF _pos2 = _line.p2();
        QPointF _pos3 = _line1.p2() ;
        if(_pos2.x() <= _pos3.x())
        {

            _fTmpX[0] = (_pos2.x() - _pos1.x()) * (pos_.y() - _pos1.y()) / (_pos2.y() - _pos1.y())  + _pos1.x() ;
            if(pos_.x() < _fTmpX[0])
            {
                *nIndex_ = *nZoom_ = 0;
                *fScale_  = 0;
                return ;
            }

            for(int i = 1; i < _nCount  ; i++)
            {
                _line = m_cMarkers.at(i) ;
                _pos1 = _line.p1();
                _pos2 = _line.p2();

                _fTmpX[i] = (_pos2.x() - _pos1.x()) * (pos_.y() - _pos1.y()) / (_pos2.y() - _pos1.y())  + _pos1.x() ;
                if((pos_.x() >= _fTmpX[i-1]) && (pos_.x() <= _fTmpX[i]))
                {
                    *fScale_ = fabs(_fTmpX[i-1] - pos_.x()) / fabs(_fTmpX[i]-_fTmpX[i-1]) ;
                    *nZoom_  = i-1  ;
                    *nIndex_ = (*fScale_ <= 0.5) ? *nZoom_ : i ;

                    return ;
                }
            }
            *nIndex_ = *nZoom_ = _nCount -1;
            *fScale_  = 0;
        }
        else
        {

            _fTmpX[0] = (_pos2.x() - _pos1.x()) * (pos_.y() - _pos1.y()) / (_pos2.y() - _pos1.y())  + _pos1.x() ;
            if(pos_.x() > _fTmpX[0])
            {
                *nIndex_ = *nZoom_ = 0;
                *fScale_  = 0;
                return ;
            }

            for(int i = 1; i < _nCount  ; i++)
            {
                _line = m_cMarkers.at(i) ;
                _pos1 = _line.p1();
                _pos2 = _line.p2();

                _fTmpX[i] = (_pos2.x() - _pos1.x()) * (pos_.y() - _pos1.y()) / (_pos2.y() - _pos1.y())  + _pos1.x() ;
                if((pos_.x() <= _fTmpX[i-1]) && (pos_.x() >= _fTmpX[i]))
                {
                    *fScale_ = fabs(_fTmpX[i-1] - pos_.x()) / fabs(_fTmpX[i]-_fTmpX[i-1]) ;
                    *nZoom_  = i-1  ;
                    *nIndex_ = (*fScale_ <= 0.5) ? *nZoom_ : i ;
                    return ;
                }
            }
            *nIndex_ = *nZoom_ = _nCount - 1;
            *fScale_  = 0;
        }
    }
}

int DopplerLawMarker::GetMarkerLinesCount()
{
    return m_cMarkers.count();
}

QLineF DopplerLawMarker::GetCurrentPosLine( int nIndex_ , float fScale_)
{
    int _nCount = m_cMarkers.count() ;
    QLineF _ret ;
    if(nIndex_ == _nCount - 1)
    {
        _ret = m_cMarkers.at(_nCount - 1) ;
        return _ret ;
    }
    QLineF _line1  = m_cMarkers.at(nIndex_) ;
    QLineF _line2  = m_cMarkers.at(nIndex_+1) ;
    float _line1X1 = _line1.p1().x() ;
    float _line1Y1 = _line1.p1().y() ;
    float _line1X2 = _line1.p2().x() ;
    float _line1Y2 = _line1.p2().y() ;

    float _line2X1 = _line2.p1().x() ;
    float _line2Y1 = _line2.p1().y() ;
    float _line2X2 = _line2.p2().x() ;
    float _line2Y2 = _line2.p2().y() ;

    float _fScaleInv = 1 - fScale_  ;
    float _fX1 = (_line1X1 * _fScaleInv) + (_line2X1 * fScale_)  ;
    float _fY1 = (_line1Y1 * _fScaleInv) + (_line2Y1 * fScale_)  ;
    float _fX2 = (_line1X2 * _fScaleInv) + (_line2X2 * fScale_)  ;
    float _fY2 = (_line1Y2 * _fScaleInv) + (_line2Y2 * fScale_)  ;

    _ret  = QLineF(_fX1 , _fY1, _fX2 , _fY2);
    return _ret ;
}

void DopplerLawMarker::SlotChangeLinePos(int nNewLineIndex)
{
    qDebug("**--**-- %s[%d],", __FUNCTION__, __LINE__);
    dotLine = m_cMarkers.at(nNewLineIndex) ;
}


int DopplerLawMarker::GetMarkerQty() const
{
    return m_nMarkerQty ;
}

int DopplerLawMarker::GetMarkerPos(int nId_) const
{
    return m_anMarkerId[nId_];
}

int DopplerLawMarker::GetMarkerId() const
{
    return m_nPostSelect ;
}

void DopplerLawMarker::SetWeldInfo(bool bShow_ , int brushHAZ, QPainterPath* path, QPainterPath* HAZpath)
{
    m_bShowWeld = bShow_ ;
    m_brushHAZ = brushHAZ;
    if(path)
    {
        weld = *path ;
    }
    if(HAZpath){
        HAZBrush = *HAZpath;
    }
}
