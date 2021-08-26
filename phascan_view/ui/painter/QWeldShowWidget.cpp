#include "QWeldShowWidget.h"
#include "gHeader.h"
//#include "DopplerPart.h"
#include "DrawDxf.h"
#include "DrawDxfHeader.h"

#include <QPointF>

QWeldShowWidget::QWeldShowWidget(QWidget *parent) :
	QWidget(parent)
{
	m_pPart = NULL;
	m_fThickness = 20;
    m_zoom = 1.0;
}

void QWeldShowWidget::paintEvent (QPaintEvent*)
{
    QPainter painter(this);
    UpdateDisplayRangle();

    QPen pen = painter.pen();
    QPen NewPen(pen);
    NewPen.setWidth(2);
    NewPen.setColor(QColor(255, 0, 0));
    painter.setPen(NewPen);
    //painter.setRenderHint(QPainter::Antialiasing, true);

    if(m_pPart->weld.eType == setup_WELD_DXF) {
        QVector<qreal> dashes;
        dashes << 3 << 5;
        NewPen.setWidth(1);
        NewPen.setDashPattern(dashes);
        NewPen.setColor(QColor(0, 0, 255));
        painter.setPen(NewPen);

        double _zoom = int(m_zoom * 100) / 100;

        if(m_lastPoint.isNull()) {
            m_lastPoint = QPoint(width() / 2, height() / 2);
        }

        int x = m_lastPoint.x() + m_endPoint.x() - m_startPoint.x();
        int y = m_lastPoint.y() + m_endPoint.y() - m_startPoint.y();

        DplDxf::DrawDxf* drawDxf = DplDxf::DrawDxf::Instance(m_groupId);
        drawDxf->set_part(m_pPart);
        drawDxf->set_axis_orientation(DplDxf::DrawDxf::Axis_Normal);

        drawDxf->set(width(), height(), x, y, _zoom, _zoom);


        drawDxf->draw_dxf_header(painter);

        QPen dxf_pen(pen);
        dxf_pen.setWidth(2);
        dxf_pen.setColor(QColor(0, 255, 0));
//        dxf_pen.setStyle(Qt::DashLine);
        painter.setPen(dxf_pen);

        drawDxf->draw_dxf_part(painter);

    }/* else if(m_pPart->weld.eType == setup_WELD_NCC) {
        DRAW_PART_INFO info;
        info.fWidth = m_cRange.fWidth;
        info.fHeight = m_cRange.fHeight;
        info.fX = m_cRange.fWidth / 10;
        info.fY = m_cRange.fStartY;
        info.fScaleX = m_cRange.fPixelSize;
        info.fScaleY = m_cRange.fPixelSize;

        DopplerPart* _pPart = DopplerPart::Instance();
        _pPart->SetPart(m_pPart);
        _pPart->SetInfo(info);
        _pPart->AdaptiveArea();
        _pPart->DrawNccPart(painter);

        QVector<qreal> dashes;
        dashes << 3 << 5;
        NewPen.setWidth(1);
        NewPen.setDashPattern(dashes);
        NewPen.setColor(QColor(0, 0, 255));
        painter.setPen(NewPen);

        _pPart->DrawOriginLine(painter);

    } */else {
        painter.drawLine (0, m_cRange.fStartY, m_cRange.fWidth, m_cRange.fStartY);
        painter.drawLine (0, m_cRange.fStopY, m_cRange.fWidth, m_cRange.fStopY);

        DrawWeld(painter);

        QVector<qreal> dashes;
        dashes << 3 << 5;
        NewPen.setWidth(1);
        NewPen.setDashPattern(dashes);
        NewPen.setColor(QColor(0, 0, 255));
        painter.setPen(NewPen);
        painter.drawLine (m_cRange.fWidth / 2, 0, m_cRange.fWidth / 2, m_cRange.fHeight);
    }
 //   painter.setPen(pen);
}

void QWeldShowWidget::SerPart(PART_CONFIG* pInfo_)
{
	m_pPart = pInfo_;
    m_fThickness = m_pPart->afSize[0];
}

void QWeldShowWidget::DrawWeld(QPainter& painter)
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
    case setup_WELD_DIFF_DV://New Add
        DrawWeldDiffDV(painter);
        break;
    case setup_WELD_J: //New Add
        DrawWeldJ(painter);
        break;
    case setup_WELD_VY: //New Add
        DrawWeldVY(painter);
        break;
    case setup_WELD_TKY:
        DrawWeldTKY(painter);
        break;
	default:
		break;
	}
}

void QWeldShowWidget::DrawWeldI(QPainter& painter)
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
    double _fX, _fY ;

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

void QWeldShowWidget::DrawWeldV(QPainter& painter)
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

void QWeldShowWidget::DrawWeldDV(QPainter& painter)
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

void QWeldShowWidget::DrawWeldU (QPainter& painter)
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

void QWeldShowWidget::DrawWeldDiffDV(QPainter &painter)
{
    QPointF _pos[4];

    _pos[0].setX(m_pPart->weld.weland_offset + tan(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)) * m_pPart->weld.fizone_height);
    _pos[0].setY(0);
    _pos[1].setX(m_pPart->weld.weland_offset);
    _pos[1].setY(m_pPart->weld.fizone_height);
    _pos[2].setX(m_pPart->weld.weland_offset);
    _pos[2].setY(m_pPart->weld.fizone_height + m_pPart->weld.weland_height);
    _pos[3].setX(m_pPart->weld.weland_offset + tan(DEGREE_TO_ARCH(m_pPart->weld.fizone_down_angle)) * m_pPart->weld.fizone_down_height);
    _pos[3].setY(m_pPart->weld.fizone_height + m_pPart->weld.fizone_down_height + m_pPart->weld.weland_height);

    PositionTransfer(_pos[0]);
    PositionTransfer(_pos[1]);
    PositionTransfer(_pos[2]);
    PositionTransfer(_pos[3]);

    double _fOrgX = m_cRange.fWidth / 2;
    double _fOrgY = m_cRange.fStartY;
    double _fXTop, _fXWeldand,  _fYFizone, _fYWeland, _fXBootom, _fYBottom;

    if(m_pPart->weld.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld.eSymmetry == setup_WELD_LEFT){
        _fXTop	 = _fOrgX - _pos[0].x();
        _fXWeldand = _fOrgX - _pos[1].x();
        _fYFizone  = _fOrgY + _pos[1].y();
        _fYWeland  = _fOrgY + _pos[2].y();
        _fXBootom  = _fOrgX - _pos[3].x();
        _fYBottom  = _fOrgY + _pos[3].y();
        painter.drawLine( _fXTop, _fOrgY, _fXWeldand, _fYFizone);
        painter.drawLine( _fXWeldand, _fYFizone, _fXWeldand, _fYWeland);
        painter.drawLine( _fXWeldand, _fYWeland, _fXBootom, _fYBottom);
    }

    if(m_pPart->weld.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld.eSymmetry == setup_WELD_RIGHT){
        _fXTop	 = _fOrgX + _pos[0].x();
        _fXWeldand = _fOrgX + _pos[1].x();
        _fYFizone  = _fOrgY + _pos[1].y();
        _fYWeland  = _fOrgY + _pos[2].y();
        _fXBootom  = _fOrgX + _pos[3].x();
        _fYBottom  = _fOrgY + _pos[3].y();
        painter.drawLine( _fXTop, _fOrgY, _fXWeldand, _fYFizone);
        painter.drawLine( _fXWeldand, _fYFizone, _fXWeldand, _fYWeland);
        painter.drawLine( _fXWeldand, _fYWeland, _fXBootom, _fYBottom);
    }
}

void QWeldShowWidget::DrawWeldJ(QPainter &painter)
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

    QPointF _pos[5];
    _pos[0].setX(_fPosX + tan(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)) * _fPosY);
    _pos[0].setY(0);
    _pos[1].setX(_fPosX);
    _pos[1].setY(_fPosY);
    _pos[2].setX(m_pPart->weld.weland_offset);
    _pos[2].setY(m_pPart->weld.fizone_height);
    _pos[3].setX(m_pPart->weld.weland_offset);
    _pos[3].setY(m_pPart->weld.fizone_height + m_pPart->weld.weland_height);
    _pos[4].setX(m_pPart->weld.weland_offset + tan(DEGREE_TO_ARCH(m_pPart->weld.fizone_down_angle)) * m_pPart->weld.fizone_down_height);
    _pos[4].setY(m_pPart->weld.fizone_height + m_pPart->weld.fizone_down_height + m_pPart->weld.weland_height);

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
    PositionTransfer(_pos[4]);
    double _fXTop, _fXFizone, _fYFizone, _fXWeland, _fYWeland, _fXBottom, _fYBottom_0, _fYBottom;

    if(m_pPart->weld.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld.eSymmetry == setup_WELD_LEFT){
        _fXTop = _fOrgX - _pos[0].x() ;
        _fXFizone  = _fOrgX - _pos[1].x() ;
        _fYFizone  = _fOrgY + _pos[1].y() ;
        _fXWeland  = _fOrgX - _pos[2].x() ;
        _fYWeland  = _fOrgY + _pos[2].y() ;
        _fYBottom_0  = _fOrgY + _pos[3].y() ;
        _fXBottom  = _fOrgX - _pos[4].x();
        _fYBottom  = _fOrgY + _pos[4].y();

        painter.drawLine(_fXTop, _fOrgY, _fXFizone, _fYFizone);
        painter.drawLine(_fXWeland, _fYWeland, _fXWeland , _fYBottom_0);
        painter.drawArc(rectangle, _fAngleStart, _fAngleStop);
        painter.drawLine( _fXWeland, _fYBottom_0, _fXBottom, _fYBottom);
    }

    if(m_pPart->weld.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld.eSymmetry == setup_WELD_RIGHT){
        _fXTop	 = _fOrgX + _pos[0].x();
        _fXFizone  = _fOrgX + _pos[1].x();
        _fYFizone  = _fOrgY + _pos[1].y();
        _fXWeland  = _fOrgX + _pos[2].x();
        _fYWeland  = _fOrgY + _pos[2].y();
        _fYBottom_0  = _fOrgY + _pos[3].y();
        _fXBottom  = _fOrgX + _pos[4].x();
        _fYBottom  = _fOrgY + _pos[4].y();

        painter.drawLine( _fXTop, _fOrgY, _fXFizone, _fYFizone);
        painter.drawLine( _fXWeland, _fYWeland, _fXWeland, _fYBottom_0);
        painter.drawArc (rectangle, 180 * 16 - _fAngleStart, -_fAngleStop);
        painter.drawLine( _fXWeland, _fYBottom_0, _fXBottom, _fYBottom);
    }
}

void QWeldShowWidget::DrawWeldVY(QPainter &painter)
{
    QPointF _pos[4];

    _pos[0].setX(m_pPart->weld.weland_offset + tan(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)) * m_pPart->weld.fizone_height
                 + tan(DEGREE_TO_ARCH(m_pPart->weld.fizone_down_angle)) * m_pPart->weld.fizone_down_height);
    _pos[0].setY(0);
    _pos[1].setX(m_pPart->weld.weland_offset + tan(DEGREE_TO_ARCH(m_pPart->weld.fizone_down_angle)) * m_pPart->weld.fizone_down_height);
    _pos[1].setY(m_pPart->weld.fizone_height);
    _pos[2].setX(m_pPart->weld.weland_offset);
    _pos[2].setY(m_pPart->weld.fizone_height + m_pPart->weld.fizone_down_height);
    _pos[3].setX(m_pPart->weld.weland_offset);
    _pos[3].setY(m_pPart->weld.fizone_height + m_pPart->weld.fizone_down_height + m_pPart->weld.weland_height);

    PositionTransfer(_pos[0]);
    PositionTransfer(_pos[1]);
    PositionTransfer(_pos[2]);
    PositionTransfer(_pos[3]);

    double _fOrgX = m_cRange.fWidth / 2;
    double _fOrgY = m_cRange.fStartY;
    double _fXTop, _fXWeldand,  _fYFizone, _fYWeland, _fXBottom, _fYBottom;

    if(m_pPart->weld.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld.eSymmetry == setup_WELD_LEFT){
        _fXTop	 = _fOrgX - _pos[0].x();
        _fXWeldand = _fOrgX - _pos[1].x();
        _fYFizone  = _fOrgY + _pos[1].y();
        _fYWeland  = _fOrgY + _pos[2].y();
        _fXBottom  = _fOrgX - _pos[3].x();
        _fYBottom  = _fOrgY + _pos[3].y();
        painter.drawLine( _fXTop, _fOrgY, _fXWeldand, _fYFizone);
        painter.drawLine( _fXWeldand, _fYFizone, _fXBottom, _fYWeland);
        painter.drawLine(_fXBottom, _fYWeland, _fXBottom, _fYBottom);
    }

    if(m_pPart->weld.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld.eSymmetry == setup_WELD_RIGHT){
        _fXTop = _fOrgX + _pos[0].x();
        _fXWeldand = _fOrgX + _pos[1].x();
        _fYFizone  = _fOrgY + _pos[1].y();
        _fYWeland  = _fOrgY + _pos[2].y();
        _fXBottom  = _fOrgX + _pos[3].x();
        _fYBottom  = _fOrgY + _pos[3].y();
        painter.drawLine( _fXTop, _fOrgY, _fXWeldand, _fYFizone);
        painter.drawLine( _fXWeldand, _fYFizone, _fXBottom, _fYWeland);
        painter.drawLine(_fXBottom, _fYWeland, _fXBottom, _fYBottom);
    }
}

void QWeldShowWidget::DrawWeldTKY(QPainter &painter)
{
    QPointF _pos[8];
    double fx0,fx1,fx2,fx3,fx4,fx5,fx6,fx7,fy0,fy1,fy2,fy3,fy4,fy5,fy6,fy7;
    double width1 = m_pPart->weld.weland_height + 0.5 * m_pPart->weld.Diameter/sin(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle));
    double width2 = m_pPart->weld.fizone_height + 0.5 * m_pPart->weld.Diameter/sin(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle));
    double R = 4 * m_pPart->weld.weland_offset + m_fThickness + 20;
    if(m_pPart->weld.eSymmetry == 0 || m_pPart->weld.eSymmetry == 1 || m_pPart->weld.eSymmetry == 2 || m_pPart->weld.eSymmetry == 3 || m_pPart->weld.eSymmetry == 6 )
    {
    _pos[0].setX(width1);
    _pos[0].setY(0);
    _pos[1].setX(width2);
    _pos[1].setY(0);
    _pos[2].setX(0.5 * m_pPart->weld.Diameter/sin(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle))-m_pPart->weld.fizone_radius/tan(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)));
    _pos[2].setY(m_pPart->weld.fizone_radius);
    _pos[3].setX(R * cos(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle))-(m_pPart->weld.Diameter/2.0)*sin(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)));
    _pos[3].setY(R * sin(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle))+(m_pPart->weld.Diameter/2.0)*cos(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)));
    _pos[4].setX(R * cos(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle))+(m_pPart->weld.Diameter/2.0)*sin(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)));
    _pos[4].setY(R * sin(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle))-(m_pPart->weld.Diameter/2.0)*cos(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)));
    _pos[5].setX(0.5 * m_pPart->weld.Diameter/sin(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle))+m_pPart->weld.weland_offset/tan(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)));
    _pos[5].setY(m_pPart->weld.weland_offset);
    PositionTransfer(_pos[0]);
    PositionTransfer(_pos[1]);
    PositionTransfer(_pos[2]);
    PositionTransfer(_pos[3]);
    PositionTransfer(_pos[4]);
    PositionTransfer(_pos[5]);
    }
    else if(m_pPart->weld.eSymmetry == 4 || m_pPart->weld.eSymmetry == 5)
    {
        double _nFizoneAngle = m_pPart->weld.fizone_angle;
        double X1 = m_pPart->weld.weland_height;
        double X2 = m_pPart->weld.fizone_height;
        double Y1 = m_pPart->weld.weland_offset;
        double Y2 = m_pPart->weld.fizone_radius;
        double T2 = m_pPart->weld.Diameter;
        double tempX,tempY,firswidth,w1,w2,w3,w4,w5,l1,h1,h2;

        if((m_pPart->weld.eSymmetry == 4 && m_pPart->weld.fizone_angle >= 90.0) || ( m_pPart->weld.eSymmetry == 5 && m_pPart->weld.fizone_angle <90.0))
        {
            if(m_pPart->weld.fizone_angle >= 90.0)
                _nFizoneAngle = m_pPart->weld.fizone_angle - 90.0;
            else if(m_pPart->weld.fizone_angle < 90.0)
            {
                _nFizoneAngle = 180.0 - m_pPart->weld.fizone_angle - 90.0;
                tempX = X1;
                tempY = Y1;
                X1 = X2;
                Y1 = Y2;
                X2 = tempX;
                Y2 = tempY;
            }
            firswidth = T2 * tan(DEGREE_TO_ARCH(_nFizoneAngle));
            w1 = firswidth / 2;
            w2 = Y2 / cos(DEGREE_TO_ARCH(_nFizoneAngle)) + w1;
            w3 = X2 * sin(DEGREE_TO_ARCH(_nFizoneAngle)) + w1;
            R = 6 * w1 + 30;
            l1 = T2 / cos(DEGREE_TO_ARCH(_nFizoneAngle));
            w4 = Y1 / cos(DEGREE_TO_ARCH(_nFizoneAngle)) - T2 *  tan(DEGREE_TO_ARCH(_nFizoneAngle)) + w1;
            w5 = (l1 + X1) * sin(DEGREE_TO_ARCH(_nFizoneAngle)) - w1;
            h1 = X2 * cos(DEGREE_TO_ARCH(_nFizoneAngle));
            h2 = (l1 + X1) * cos(DEGREE_TO_ARCH(_nFizoneAngle));

            _pos[0].setX(w1);
            _pos[1].setX(-w3);
            _pos[2].setX(-w2);
            _pos[3].setX(-R);
            _pos[4].setX(-w1);
            _pos[5].setX(w5);
            _pos[6].setX(-w4);
            _pos[7].setX(-R);
            _pos[0].setY(0);
            _pos[1].setY(h1 + T2);
            _pos[2].setY(T2);
            _pos[3].setY(T2);
            _pos[4].setY(T2);
            _pos[5].setY(h2 + T2);
            _pos[6].setY(2 * T2);
            _pos[7].setY(2 * T2);

            PositionTransfer(_pos[0]);
            PositionTransfer(_pos[1]);
            PositionTransfer(_pos[2]);
            PositionTransfer(_pos[3]);
            PositionTransfer(_pos[4]);
            PositionTransfer(_pos[5]);
            PositionTransfer(_pos[6]);
            PositionTransfer(_pos[7]);

        }

        if((m_pPart->weld.eSymmetry == 5 && m_pPart->weld.fizone_angle >= 90.0) || (m_pPart->weld.eSymmetry == 4 && m_pPart->weld.fizone_angle < 90.0))
        {
            if(m_pPart->weld.fizone_angle >= 90.0)
                _nFizoneAngle = m_pPart->weld.fizone_angle - 90.0;
            else if(m_pPart->weld.fizone_angle < 90.0)
        {
                _nFizoneAngle = 180.0 - m_pPart->weld.fizone_angle - 90.0;
                tempX = X1;
                tempY = Y1;
                X1 = X2;
                Y1 = Y2;
                X2 = tempX;
                Y2 = tempY;
        }
                firswidth = T2 * tan(DEGREE_TO_ARCH(_nFizoneAngle));
                w1 = firswidth / 2;
                w2 = Y1 / cos(DEGREE_TO_ARCH(_nFizoneAngle)) - w1;
                w3 = X1 * sin(DEGREE_TO_ARCH(_nFizoneAngle)) + w1;
                R = 6 * w1 + 30;
                w4 = Y2 / cos(DEGREE_TO_ARCH(_nFizoneAngle)) + T2 * tan(DEGREE_TO_ARCH(_nFizoneAngle)) - w1;
                l1 = T2 / cos(DEGREE_TO_ARCH(_nFizoneAngle));
                w5 = (l1 + X2) * sin(DEGREE_TO_ARCH(_nFizoneAngle)) - w1;
                h1 = (l1 + X1) * cos(DEGREE_TO_ARCH(_nFizoneAngle));
                h2 = (l1 + X2) * cos(DEGREE_TO_ARCH(_nFizoneAngle));

                //fx0 = w1;
                //fx1 = R;
                //fx2 = R;
                //fx3 = w2;
                //fx4 = w3;
                //fx5 = w4;
                //fx6 = w5;
                //fy0 = T2;
                //fy1 = h1;
                //fy2 = T2 / 2;
                //fy3 = T2 + h2;
                _pos[0].setX(-w1);
                _pos[1].setX(w3);
                _pos[2].setX(-w2);
                _pos[3].setX(-R);
                _pos[4].setX(w1);
                _pos[5].setX(-w5);
                _pos[6].setX(-w4);
                _pos[7].setX(-R);
                _pos[0].setY(0);
                _pos[1].setY(h1);
                _pos[2].setY(T2);
                _pos[3].setY(T2);
                _pos[4].setY(T2);
                _pos[5].setY(T2+h2);
                _pos[6].setY(2 * T2);
                _pos[7].setY(2 * T2);
                PositionTransfer(_pos[0]);
                PositionTransfer(_pos[1]);
                PositionTransfer(_pos[2]);
                PositionTransfer(_pos[3]);
                PositionTransfer(_pos[4]);
                PositionTransfer(_pos[5]);
                PositionTransfer(_pos[6]);
                PositionTransfer(_pos[7]);

        }

    }
    double _fOrgX = m_cRange.fWidth / 2;
    double _fOrgY = m_cRange.fStartY; 
    if(m_pPart->weld.eSymmetry == 0 || m_pPart->weld.eSymmetry == 1 || m_pPart->weld.eSymmetry == 2 || m_pPart->weld.eSymmetry == 3 || m_pPart->weld.eSymmetry == 6 )
    {
    fx0 = _fOrgX - _pos[0].x();
    fy0 = _fOrgY;
    fx1 = _fOrgX + _pos[1].x();
    fy1 = _fOrgY;
    fx2 = _fOrgX + _pos[2].x();
    fy2 = _fOrgY + _pos[2].y();
    fx3 = _fOrgX - _pos[3].x();
    fy3 = _fOrgY + _pos[3].y();
    fx4 = _fOrgX - _pos[4].x();
    fy4 = _fOrgY + _pos[4].y();
    fx5 = _fOrgX - _pos[5].x();
    fy5 = _fOrgY + _pos[5].y();
    painter.drawLine(fx0,fy0,fx1,fy1);
    painter.drawLine(fx1,fy1,fx2,fy2);
    painter.drawLine(fx2,fy2,fx3,fy3);
    painter.drawLine(fx3,fy3,fx4,fy4);
    painter.drawLine(fx4,fy4,fx5,fy5);
    painter.drawLine(fx0,fy0,fx5,fy5);

}
    else if(m_pPart->weld.eSymmetry == 4 || m_pPart->weld.eSymmetry == 5)
    {
        fx0 = _fOrgX + _pos[0].x();
        fy0 = _fOrgY + _pos[0].y();
        fx1 = _fOrgX + _pos[1].x();
        fy1 = _fOrgY + _pos[1].y();
        fx2 = _fOrgX + _pos[2].x();
        fy2 = _fOrgY + _pos[2].y();
        fx3 = _fOrgX + _pos[3].x();
        fy3 = _fOrgY + _pos[3].y();
        fx4 = _fOrgX + _pos[4].x();
        fy4 = _fOrgY + _pos[4].y();
        fx5 = _fOrgX + _pos[5].x();
        fy5 = _fOrgY + _pos[5].y();
        fx6 = _fOrgX + _pos[6].x();
        fy6 = _fOrgY + _pos[6].y();
        fx7 = _fOrgX + _pos[7].x();
        fy7 = _fOrgY + _pos[7].y();
        painter.drawLine(fx0,fy0,fx1,fy1);
        painter.drawLine(fx1,fy1,fx2,fy2);
        painter.drawLine(fx2,fy2,fx3,fy3);

        painter.drawLine(fx4,fy4,fx5,fy5);
        painter.drawLine(fx5,fy5,fx6,fy6);
        painter.drawLine(fx6,fy6,fx7,fy7);

    }

}

void QWeldShowWidget::UpdateDisplayRangle()
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
    case setup_WELD_TKY :
    {
        double _fMaxWidth = ((0.5 * m_pPart->weld.Diameter/sin(DEGREE_TO_ARCH(m_pPart->weld.fizone_angle)))+((m_pPart->weld.weland_height>m_pPart->weld.fizone_height)?m_pPart->weld.weland_height:m_pPart->weld.fizone_height))*3;

        m_cRange.fPixelSize = _fMaxWidth/ _fWidth;
        double _fThickness = m_fThickness /   m_cRange.fPixelSize;
        if(m_pPart->weld.eSymmetry == 0 || m_pPart->weld.eSymmetry == 1 || m_pPart->weld.eSymmetry == 6)
        {
            m_cRange.fStartY = 0.25 * _fHeight;
            m_cRange.fStopY	 = 0.25 * _fHeight + _fThickness;
        }
        else if(m_pPart->weld.eSymmetry == 2 || m_pPart->weld.eSymmetry == 3)
        {
            m_cRange.fStartY = 0.25 * _fHeight;
            m_cRange.fStopY = 0.25 * _fHeight + _fThickness;
        }
    }
	default:
		break;
	}
}

void QWeldShowWidget::PositionTransfer(QPointF& pos_)
{
    double _fX = pos_.x() / m_cRange.fPixelSize;
    double _fY = pos_.y() / m_cRange.fPixelSize;

	pos_.setX(_fX);
    pos_.setY(_fY);
}

void QWeldShowWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() >0){
        m_zoom += 1;

    }else{
        if(m_zoom > 1){
            m_zoom -= 1;

        }else if(0 < m_zoom && m_zoom <= 1){
            m_zoom -= 0.5*m_zoom;
        }
    }
//    if(m_zoom <= 0) {
//        m_zoom = 0.01;
//    }

    update();
    emit zoom(m_zoom);
}

void QWeldShowWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        m_lastPoint = m_lastPoint + m_endPoint - m_startPoint;
        m_startPoint = event->pos();
    }
}

void QWeldShowWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        m_endPoint = event->pos();
        update();
    }
}

void QWeldShowWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        m_endPoint = event->pos();
        update();
    }
}

void QWeldShowWidget::clear_point()
{
    m_lastPoint = QPoint();
    m_startPoint = QPoint();
    m_endPoint = QPoint();
}

void QWeldShowWidget::do_zoom_change(double value)
{
    m_zoom = value;
    update();
}
