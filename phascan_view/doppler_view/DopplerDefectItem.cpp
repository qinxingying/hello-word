#include "DopplerDefectItem.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "configure/DopplerConfigure.h"
#include "mainwindow.h"
const int g_nRectSize = 0 ;
static int g_nDfZValue = 50 ;
DopplerDefectItem::DopplerDefectItem(const QColor& cColor_)
{

	m_nWidth  = 100;
	m_nHeight = 100;

	double _nPos1  = 10 ;
	double _nPos2  = 10 ;
	m_rect.setLeft(_nPos1 - g_nRectSize) ;
	m_rect.setRight(_nPos1 + g_nRectSize);
	m_rect.setTop(_nPos2 - g_nRectSize);
	m_rect.setBottom(_nPos2 + g_nRectSize);

	m_cColor   = cColor_;
	setZValue(g_nDfZValue);
//	SetMoveType(LINE_MOVE_NO) ;
	m_eStype = Qt::SolidLine  ;
    setFlags(ItemIsSelectable);
    IsSelected = -1;
}

void DopplerDefectItem::SetLineStyle(Qt::PenStyle eStype_)
{
	m_eStype = eStype_  ;
	update() ;
}

QRectF DopplerDefectItem::boundingRect() const
{
	QRectF _rect ;
	_rect = QRectF(-g_nRectSize , -g_nRectSize , m_nWidth+ g_nRectSize, m_nHeight+ g_nRectSize);
	return _rect;
}

QPainterPath DopplerDefectItem::shape() const
{
	QPainterPath path;
	QRectF _rct(0 , 0 , 0 , 0 ) ;
	if(!(flags() & QGraphicsItem::ItemIsPanel))
	_rct = boundingRect () ;
	path.addRect(_rct) ;
	return path;
}

void DopplerDefectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget* /*widget*/)
{
	bool _bSel = false;
	if(option->state & QStyle::State_Selected)
	_bSel = true;

	QColor fillColor = _bSel ? m_cColor.dark(50) : m_cColor;

//	if (option->state & QStyle::State_MouseOver)
//	fillColor = fillColor.light(50);

//	if (option->state & QStyle::State_MouseOver)
//	fillColor = fillColor.light(50);

	painter->save();
	QPen _NewPen ;
	QVector<qreal> dashes;

    dashes << 15 << 10 << 15 << 10 ;
    static int id = 0;
	_NewPen.setWidth(0);
    if(id<400)
    {
        fillColor.setHsv(0,255,191);
        id++;
    }
    else if(id<800)
    {
        fillColor.setHsv(60,255,191);
        id++;
    }
    else if(id < 1200)
    {
        fillColor.setHsv(120,255,191);
        id++;
    }
    else if(id < 1600)
    {
        fillColor.setHsv(180,255,191);
        id++;
    }
    else if(id < 2000)
    {
        fillColor.setHsv(240,255,191);
        id++;
    }
    else
    {
        id = 0;
    }
	_NewPen.setColor(fillColor);
	_NewPen.setStyle(m_eStype);
	_NewPen.setDashPattern(dashes);
	painter->setPen(_NewPen);

	int _nGroup , _nLaw , _nDisp ;
	m_pDataView->GetDataViewConfigure(&_nGroup , &_nLaw , &_nDisp);
	DopplerConfigure* _pConfig = DopplerConfigure::Instance();
	int _nBmpNo = _pConfig->m_nCutBmpNo[_nGroup];

    if(_nBmpNo == 0 || (_nBmpNo > 0 && _nBmpNo == m_nId+1)) {
        painter->drawLine(0, 0 , 0 , m_nHeight );
        painter->drawLine(0, m_nHeight , m_nWidth , m_nHeight );
        painter->drawLine(m_nWidth, m_nHeight , m_nWidth , 0 );
        painter->drawLine(m_nWidth, 0 , 0, 0 );
    }
    dashes.clear();
    dashes << 10 << 15 << 10 << 15 ;
    _NewPen.setColor(QColor(255,0,0));
    _NewPen.setDashPattern(dashes);
    painter->setPen(_NewPen);
    if(_nBmpNo == 0 || (_nBmpNo > 0 && _nBmpNo == m_nId+1)) {
        if(m_nHeight > 15)
        {
            painter->drawLine(0, 15 , 0 , m_nHeight );
            painter->drawLine(m_nWidth, m_nHeight-15 , m_nWidth , 0 );
        }
        if(m_nWidth > 15)
        {
            painter->drawLine(15, m_nHeight , m_nWidth , m_nHeight );
            painter->drawLine(m_nWidth-15, 0 , 0, 0 );
        }
    }
	if(_nBmpNo == 0)
		DrawLabel(painter, fillColor, _bSel);
	painter->restore();

}
void DopplerDefectItem::DrawLabel(QPainter *painter, QColor& cColor_, bool bSel_)
{
    Q_UNUSED(bSel_);
	QPen _pen = painter->pen();
	_pen.setColor(cColor_) ;
	painter->setPen(_pen);
    QBrush _brush(QColor(0,0,0));
    painter->setBackground(_brush);
    if(g_pMainWnd->DefectBackMode()) {
        painter->setPen(QPen(Qt::white));
        painter->setBackgroundMode(Qt::OpaqueMode);
    } else {
        painter->setPen(_pen);
        painter->setBackgroundMode(Qt::TransparentMode);
    }
	QString _str ;
/*	if(bSel_ && m_pDataView)
	{
		int _nGroup , _nLaw , _nDisp ;
		m_pDataView->GetDataViewConfigure(&_nGroup , &_nLaw , &_nDisp);

		DopplerConfigure* _pConfig = DopplerConfigure::Instance();

		float _fSStart;
		float _fSData = _pConfig->DefectLength(_nGroup, &_fSStart, m_nId);

		float _fUStart;
		float _fUData = _pConfig->DefectHeight(_nGroup, &_fUStart, m_nId);

		float _fDepth = _pConfig->DefectDepth(_nGroup, m_nId);
		if(_fDepth >= 0)
		{
			_fUStart = _fDepth;
		}
		_str.sprintf("%d: %.2f(%.2f) , %.2f(%.2f)", m_nId+1, _fSStart, _fSData, _fUStart, _fUData);
	}
	else*/

		int _nGroup , _nLaw , _nDisp ;
		m_pDataView->GetDataViewConfigure(&_nGroup , &_nLaw , &_nDisp);
		DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
		char *_pInfo = _pConfig->GetDefectInfo(_nGroup, m_nId);

		_str.sprintf("%d:%s", m_nId+1, _pInfo)  ;
    if(this->y()>30)
        painter->drawText(0 , -4 , _str );
    else if(this->y()+ m_nHeight <scene()->height() - 30)
        painter->drawText(0 , this->y() + m_nHeight + 4 , _str );
    else if(this->x() + m_nWidth < scene()->width() - 30)
        painter->drawText(this->x() + m_nWidth + 4 , 0 , _str );
    if(IsSelected == GetItemId())
    {
        float start = 0;
        float length = 0;
        float depth = 0;
        float height = 0;
        length = _pConfig->DefectLengthValue(m_pDataView->GetGroupId(),&start,IsSelected);
        height = _pConfig->DefectHeightValue(m_pDataView->GetGroupId(),&depth,IsSelected);
        float _fDepth = _pConfig->DefectDepthValue(m_pDataView->GetGroupId(), IsSelected);
        if(_fDepth >= 0){
            length = _fDepth;
        }
        _str.sprintf("%.1f(%.1f) %.1f(%.1f)",start,length,depth,height);
        if(this->y()>30)
            painter->drawText(0 , -15 , _str );
        else if(this->y()+ m_nHeight <scene()->height() - 30)
            painter->drawText(0 , this->y() + m_nHeight + 15 , _str );
        else if(this->x() + m_nWidth < scene()->width() - 30)
            painter->drawText(this->x() + m_nWidth + 15 , 0 , _str );
    }
}

//void DopplerDefectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
//{
//	//setSelected(false);
//	//update();
//}

void DopplerDefectItem::SetItemGeometry (QRectF& rect_)
{
	QRectF _rect = rect_;
	int _w = _rect.width();
	int _h = _rect.height();
	int _x = _rect.left();
	int _y = _rect.top();

	if(_w < 0)
	{
		_x += _w;
		_w = abs(_w);
		_rect.setLeft(_x);
		_rect.setRight(_x+_w);
	}
	if(_h < 0)
	{
		_y += _h;
		_h = abs(_h);
		_rect.setTop(_y);
		_rect.setBottom(_y+_h);
	}

	m_nWidth  = _rect.width();
	m_nHeight = _rect.height();
	this->setPos(_rect.topLeft());
}

void DopplerDefectItem::SetScenceSize(QSize size_)
{
	m_cSize = size_ ;
}

