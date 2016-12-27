#include "DplDxf.h"
#include "gHeader.h"
#include "DopplerPart.h"

#include <QPainter>
#include <QPen>
#include <QPointF>

DplDxf::DplDxf(QWidget *parent) :
	QWidget(parent)
{
	m_pPart = NULL;
	m_fThickness = 20;
}

void DplDxf::paintEvent (QPaintEvent*)
{
    QPainter _painter(this);
    UpdateDisplayRangle();

	QPen _pen = _painter.pen();

    QPen _NewPen(_pen);
	_NewPen.setWidth(2);
	_NewPen.setColor(QColor(255, 0, 0));
	_painter.setPen(_NewPen);

	_painter.setRenderHint(QPainter::Antialiasing, true);

    if(m_pPart->weld.eType == setup_WELD_NCC){
		DRAW_PART_INFO _info;
		DopplerPart* _pPart = DopplerPart::Instance();

		_info.fWidth = m_cRange.fWidth;
		_info.fHeight = m_cRange.fHeight;
		_info.fX = m_cRange.fWidth / 10;
		_info.fY = m_cRange.fStartY;
		_info.fScaleX = m_cRange.fPixelSize;
		_info.fScaleY = m_cRange.fPixelSize;

		_pPart->SetPart(m_pPart);
		_pPart->SetInfo(_info);
		_pPart->AdaptiveArea();

		_pPart->DrawNccPart(_painter);

		QVector<qreal> dashes;
        dashes << 3 << 5;
		_NewPen.setWidth(1);
		_NewPen.setDashPattern(dashes);
		_NewPen.setColor(QColor(0, 0, 255));
		_painter.setPen(_NewPen);

		_pPart->DrawOriginLine(_painter);

    }else{
        _painter.drawLine (0, m_cRange.fStartY, m_cRange.fWidth, m_cRange.fStartY);
        _painter.drawLine (0, m_cRange.fStopY, m_cRange.fWidth, m_cRange.fStopY);

        DrawWeld(_painter);

		QVector<qreal> dashes;
        dashes << 3 << 5;
		_NewPen.setWidth(1);
		_NewPen.setDashPattern(dashes);
		_NewPen.setColor(QColor(0, 0, 255));
		_painter.setPen(_NewPen);
        _painter.drawLine (m_cRange.fWidth / 2, 0, m_cRange.fWidth / 2, m_cRange.fHeight);
	}
	_painter.setPen(_pen);
}

void DplDxf::SerPart(PART_CONFIG* pInfo_)
{
	m_pPart = pInfo_;
	m_fThickness = m_pPart->afSize[0];
}

void DplDxf::DrawWeld(QPainter& painter)
{
    if(!m_pPart) return;

    switch (m_pPart->weld.eType){
	case setup_WELD_I :
        DrawWeldI(painter);
		break;
	case setup_WELD_V :
        DrawWeldV(painter);
		break;
	case setup_WELD_DV :
        DrawWeldDV(painter);
		break;
	case setup_WELD_U :
        DrawWeldU(painter);
		break;
	default:
		break;
	}
}

void DplDxf::DrawWeldI(QPainter& painter)
{
    QPointF _pos[2];
	_pos[0].setX(m_pPart->weld.weland_offset);
	_pos[0].setY(0);
	_pos[1].setX(m_pPart->weld.weland_offset);
	_pos[1].setY(m_pPart->weld.weland_height);
    PositionTransfer(_pos[0]);
    PositionTransfer(_pos[1]);

    double _fOrgX = m_cRange.fWidth / 2;
    double _fOrgY = m_cRange.fStartY;
    double _fX, _fY;

    if(m_pPart->weld.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld.eSymmetry == setup_WELD_LEFT){
		_fX = _fOrgX - _pos[0].x() ;
		_fY = _fOrgY + _pos[1].y() ;
        painter.drawLine( _fX, _fOrgY, _fX , _fY);
	}

    if(m_pPart->weld.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld.eSymmetry == setup_WELD_RIGHT){
        _fX = _fOrgX + _pos[0].x();
        _fY = _fOrgY + _pos[1].y();
        painter.drawLine( _fX, _fOrgY, _fX, _fY);
	}
}

void DplDxf::DrawWeldV(QPainter& painter)
{
    QPointF _pos[3];

	_pos[0].setX(m_pPart->weld.weland_offset + tan(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)) * m_pPart->weld.fizone_height);
	_pos[0].setY(0);
	_pos[1].setX(m_pPart->weld.weland_offset);
	_pos[1].setY(m_pPart->weld.fizone_height);
	_pos[2].setX(m_pPart->weld.weland_offset);
	_pos[2].setY(m_pPart->weld.fizone_height + m_pPart->weld.weland_height);

    PositionTransfer(_pos[0]);
    PositionTransfer(_pos[1]);
    PositionTransfer(_pos[2]);

    double _fOrgX = m_cRange.fWidth / 2;
    double _fOrgY = m_cRange.fStartY;
    double _fXTop, _fXWeldand,  _fYFizone, _fYWeland;

    if(m_pPart->weld.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld.eSymmetry == setup_WELD_LEFT){
        _fXTop	 = _fOrgX - _pos[0].x();
        _fXWeldand = _fOrgX - _pos[1].x();
        _fYFizone  = _fOrgY + _pos[1].y();
        _fYWeland  = _fOrgY + _pos[2].y();
        painter.drawLine( _fXTop, _fOrgY, _fXWeldand, _fYFizone);
        painter.drawLine( _fXWeldand, _fYFizone, _fXWeldand, _fYWeland);
	}

    if(m_pPart->weld.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld.eSymmetry == setup_WELD_RIGHT){
        _fXTop = _fOrgX + _pos[0].x();
        _fXWeldand = _fOrgX + _pos[1].x();
        _fYFizone  = _fOrgY + _pos[1].y();
        _fYWeland  = _fOrgY + _pos[2].y();
        painter.drawLine( _fXTop, _fOrgY, _fXWeldand, _fYFizone);
        painter.drawLine( _fXWeldand, _fYFizone, _fXWeldand, _fYWeland);
	}
}

void DplDxf::DrawWeldDV(QPainter& painter)
{
    QPointF _pos[4];

	_pos[0].setX(m_pPart->weld.weland_offset + tan(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)) * m_pPart->weld.fizone_height);
	_pos[0].setY(0);
	_pos[1].setX(m_pPart->weld.weland_offset);
	_pos[1].setY(m_pPart->weld.fizone_height);
	_pos[2].setX(m_pPart->weld.weland_offset);
	_pos[2].setY(m_pPart->weld.fizone_height + m_pPart->weld.weland_height);
	_pos[3].setX(m_pPart->weld.weland_offset + tan(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)) * m_pPart->weld.fizone_height);
	_pos[3].setY(m_pPart->weld.fizone_height * 2 + m_pPart->weld.weland_height);

    PositionTransfer(_pos[0]);
    PositionTransfer(_pos[1]);
    PositionTransfer(_pos[2]);
    PositionTransfer(_pos[3]);

    double _fOrgX = m_cRange.fWidth / 2;
    double _fOrgY = m_cRange.fStartY;
    double _fXTop, _fXWeldand,  _fYFizone, _fYWeland, _fYBottom;

    if(m_pPart->weld.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld.eSymmetry == setup_WELD_LEFT){
        _fXTop	 = _fOrgX - _pos[0].x();
        _fXWeldand = _fOrgX - _pos[1].x();
        _fYFizone  = _fOrgY + _pos[1].y();
        _fYWeland  = _fOrgY + _pos[2].y();
        _fYBottom  = _fOrgY + _pos[3].y();
        painter.drawLine( _fXTop, _fOrgY, _fXWeldand, _fYFizone);
        painter.drawLine( _fXWeldand, _fYFizone, _fXWeldand, _fYWeland);
        painter.drawLine( _fXWeldand, _fYWeland, _fXTop, _fYBottom);
	}

    if(m_pPart->weld.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld.eSymmetry == setup_WELD_RIGHT){
        _fXTop	 = _fOrgX + _pos[0].x();
        _fXWeldand = _fOrgX + _pos[1].x();
        _fYFizone  = _fOrgY + _pos[1].y();
        _fYWeland  = _fOrgY + _pos[2].y();
        _fYBottom  = _fOrgY + _pos[3].y();
        painter.drawLine( _fXTop, _fOrgY, _fXWeldand, _fYFizone);
        painter.drawLine( _fXWeldand, _fYFizone, _fXWeldand, _fYWeland);
        painter.drawLine( _fXWeldand, _fYWeland, _fXTop, _fYBottom);
	}
}

void DplDxf::DrawWeldU (QPainter& painter)
{
    if(m_pPart->weld.weland_offset >= m_pPart->weld.fizone_radius){
        DrawWeldV(painter);
        return;
	}

    double _fFizoneAngle = DEGREE_TO_ARCH(m_pPart->weld.fizone_angle);
    double _nTmpY2 = sin(_fFizoneAngle) * m_pPart->weld.fizone_radius;
    double _nTmpY1 = sqrt(m_pPart->weld.fizone_radius * m_pPart->weld.fizone_radius
                          - m_pPart->weld.weland_offset * m_pPart->weld.weland_offset);

    if(_nTmpY2 > _nTmpY1){
        DrawWeldV( painter );
        return;
	}

    double _fPosX = cos(_fFizoneAngle) * m_pPart->weld.fizone_radius;
    double _fPosY = m_pPart->weld.fizone_height - _nTmpY1 + _nTmpY2;

    QPointF _pos[4];
	_pos[0].setX(_fPosX + tan(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)) * _fPosY);
	_pos[0].setY(0);
	_pos[1].setX(_fPosX);
	_pos[1].setY(_fPosY);
	_pos[2].setX(m_pPart->weld.weland_offset);
	_pos[2].setY(m_pPart->weld.fizone_height);
	_pos[3].setX(m_pPart->weld.weland_offset);
	_pos[3].setY(m_pPart->weld.fizone_height + m_pPart->weld.weland_height);


    double _fOrgX = m_cRange.fWidth / 2;
    double _fOrgY = m_cRange.fStartY;
    QPointF _center;
	_center.setX(m_pPart->weld.fizone_radius);
	_center.setY(m_pPart->weld.fizone_height - _nTmpY1);
    PositionTransfer(_center);
    QRectF rectangle(_fOrgX - _center.x(), _fOrgY + _center.y() - _center.x(), _center.x() * 2,  _center.x() * 2);
    double _fAngleStart = (m_pPart->weld.fizone_angle + 180) * 16;
    double _asine = ARCH_TO_DEGREE(asin(m_pPart->weld.weland_offset / m_pPart->weld.fizone_radius));
	double _fAngleStop  = (270 - _asine ) * 16 - _fAngleStart ;

    PositionTransfer(_pos[0]);
    PositionTransfer(_pos[1]);
    PositionTransfer(_pos[2]);
    PositionTransfer(_pos[3]);
    double _fXTop, _fXFizone, _fYFizone, _fXWeland, _fYWeland, _fYBottom;

    if(m_pPart->weld.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld.eSymmetry == setup_WELD_LEFT){
        _fXTop = _fOrgX - _pos[0].x() ;
		_fXFizone  = _fOrgX - _pos[1].x() ;
		_fYFizone  = _fOrgY + _pos[1].y() ;
		_fXWeland  = _fOrgX - _pos[2].x() ;
		_fYWeland  = _fOrgY + _pos[2].y() ;
		_fYBottom  = _fOrgY + _pos[3].y() ;
        painter.drawLine(_fXTop, _fOrgY, _fXFizone, _fYFizone);
        painter.drawLine(_fXWeland, _fYWeland, _fXWeland , _fYBottom);
		painter.drawArc(rectangle, _fAngleStart, _fAngleStop);
	}

    if(m_pPart->weld.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld.eSymmetry == setup_WELD_RIGHT){
        _fXTop	 = _fOrgX + _pos[0].x();
        _fXFizone  = _fOrgX + _pos[1].x();
        _fYFizone  = _fOrgY + _pos[1].y();
        _fXWeland  = _fOrgX + _pos[2].x();
        _fYWeland  = _fOrgY + _pos[2].y();
        _fYBottom  = _fOrgY + _pos[3].y();
        painter.drawLine( _fXTop, _fOrgY, _fXFizone, _fYFizone);
        painter.drawLine( _fXWeland, _fYWeland, _fXWeland, _fYBottom);
        painter.drawArc (rectangle, 180 * 16 - _fAngleStart, -_fAngleStop);
	}
}

void DplDxf::UpdateDisplayRangle()
{
    double _fWidth = (double) width();
    double _fHeight= (double) height();
	m_cRange.fWidth	 = _fWidth;
	m_cRange.fHeight	= _fHeight;
    m_cRange.fPixelSize = m_fThickness * 3 / (2 * _fHeight);
	m_cRange.fStartY	= _fHeight / 6 ;
	m_cRange.fStopY	 = _fHeight * 5 / 6 ;
	if(!m_pPart)		return ;

    double _fDefaultWidth = 3 * _fWidth * m_fThickness / (3 * _fHeight);
    _fDefaultWidth /=  3.0;

    switch (m_pPart->weld.eType){
	case setup_WELD_I :
        if(m_pPart->weld.weland_offset > _fDefaultWidth){
            m_cRange.fPixelSize = m_pPart->weld.weland_offset * 3 / _fWidth;
            double _fThickness = m_fThickness / (2 * m_cRange.fPixelSize);
            m_cRange.fStartY = _fHeight / 2 - _fThickness;
            m_cRange.fStopY	 = _fHeight / 2 + _fThickness;
		}
		break;
	case setup_WELD_V :
	case setup_WELD_DV:
	{
        double _fMaxWidth = m_pPart->weld.weland_offset
                          + tan(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)) * m_pPart->weld.fizone_height;

        if(_fMaxWidth > _fDefaultWidth){
            m_cRange.fPixelSize = _fMaxWidth * 3 / _fWidth;
            double _fThickness  = m_fThickness / (2 * m_cRange.fPixelSize);
            m_cRange.fStartY	= _fHeight / 2 - _fThickness;
            m_cRange.fStopY	 = _fHeight / 2 + _fThickness;
		}
	}
		break;
	case setup_WELD_U :
	{
        double _fAngle = DEGREE_TO_ARCH(m_pPart->weld.fizone_angle);
        double _fMaxWidth = m_pPart->weld.fizone_radius * cos(_fAngle) + tan(_fAngle) * m_pPart->weld.fizone_height;

        if(_fMaxWidth > _fDefaultWidth){
            m_cRange.fPixelSize = _fMaxWidth * 3 / _fWidth;
            double _fThickness = m_fThickness / (2 * m_cRange.fPixelSize);
            m_cRange.fStartY = _fHeight / 2 - _fThickness;
            m_cRange.fStopY	 = _fHeight / 2 + _fThickness;
		}
	}
		break;
	default:
		break;
	}
}

void DplDxf::PositionTransfer(QPointF& pos_)
{
    double _fX = pos_.x() / m_cRange.fPixelSize;
    double _fY = pos_.y() / m_cRange.fPixelSize;

	pos_.setX(_fX);
	pos_.setY(_fY);
}
