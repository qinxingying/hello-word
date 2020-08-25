#include "weldshowdataiiwidget.h"
#include <QPainter>
#include "painter/DrawDxf.h"
#include <math.h>
#include <gHeader.h>

WeldShowDataIIWidget::WeldShowDataIIWidget(QWidget *parent) :
    QWidget(parent)
{
    m_pPart = NULL;
    m_zoom = 1.0;
}

void WeldShowDataIIWidget::SerPart(PART_CONFIG *pInfo_)
{
    m_pPart = pInfo_;
    m_fThickness = m_pPart->afSize[0];
}

void WeldShowDataIIWidget::clear_point()
{
    m_lastPoint = QPoint();
    m_startPoint = QPoint();
    m_endPoint = QPoint();
}

void WeldShowDataIIWidget::do_zoom_change(double value)
{
    if(m_zoom == value) return;
    m_zoom = value;
    update();
}

void WeldShowDataIIWidget::paintEvent( QPaintEvent *event)
{
    Q_UNUSED(event);
    if(m_pPart == 0){
        return;
    }

    QPainter painter(this);
    UpdateDisplayRangle();

    QPen pen = painter.pen();
    QPen NewPen(pen);
    NewPen.setWidth(2);
    NewPen.setColor(QColor(255, 0, 0));
    painter.setPen(NewPen);

    if(m_pPart->weld_ii.eType == DXF){
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

        DplDxf::DrawDxf* drawDxf = DplDxf::DrawDxf::Instance();
        drawDxf->set_part(m_pPart);
        drawDxf->set_axis_orientation(DplDxf::DrawDxf::Axis_Normal);

        drawDxf->set(width(), height(), x, y, _zoom, _zoom);


        drawDxf->draw_dxf_header(painter);

        QPen dxf_pen(pen);
        dxf_pen.setWidth(2);
        dxf_pen.setColor(QColor(0, 255, 0));
        painter.setPen(dxf_pen);

        drawDxf->draw_dxf_part(painter);
    }else{
        painter.drawLine(0, m_cRange.fStartY, m_cRange.fWidth, m_cRange.fStartY);
        painter.drawLine(0, m_cRange.fStopY, m_cRange.fWidth, m_cRange.fStopY);
        DrawWeld( painter);

        QVector<qreal> dashes;
        dashes << 3 << 5;
        NewPen.setWidth(1);
        NewPen.setDashPattern(dashes);
        NewPen.setColor(QColor(0, 0, 255));
        painter.setPen(NewPen);
        painter.drawLine(m_cRange.fWidth / 2, 0, m_cRange.fWidth / 2, m_cRange.fHeight);
    }
}

void WeldShowDataIIWidget::wheelEvent(QWheelEvent *event)
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
    update();
    emit zoom(m_zoom);
}

void WeldShowDataIIWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        m_lastPoint = m_lastPoint + m_endPoint - m_startPoint;
        m_startPoint = event->pos();
    }
}

void WeldShowDataIIWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        m_endPoint = event->pos();
        update();
    }
}

void WeldShowDataIIWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        m_endPoint = event->pos();
        update();
    }
}

void WeldShowDataIIWidget::UpdateDisplayRangle()
{
    double _fWidth = (double) width();
    double _fHeight= (double) height();
    if(TKY == m_pPart->weld_ii.eType){
        m_fThickness = m_pPart->weld_ii.eBottomThinkness;
    }else{
        m_fThickness = m_pPart->afSize[0];
    }
    m_cRange.fWidth	 = _fWidth;
    m_cRange.fHeight	= _fHeight;
    m_cRange.fPixelSize = m_fThickness * 3 / (2 * _fHeight);
    m_cRange.fStartY	= _fHeight / 6 ;
    m_cRange.fStopY	 = _fHeight * 5 / 6 ;
    double _fDefaultWidth = 3 * _fWidth * m_fThickness / (3 * _fHeight);
    _fDefaultWidth /=  3.0;

    switch (m_pPart->weld_ii.eType) {
    case NONE_TYPE:
        break;
    case I:
        if( m_pPart->weld_ii.I.w  > _fDefaultWidth)
        {
            m_cRange.fPixelSize = m_pPart->weld_ii.I.w * 3 / _fWidth;
            double _fThickness = m_fThickness / (2 * m_cRange.fPixelSize);
            m_cRange.fStartY = _fHeight / 2 - _fThickness;
            m_cRange.fStopY	 = _fHeight / 2 + _fThickness;
        }
        break;
    case V:
    case U:
    {
        double _fMaxWidth = ( m_pPart->weld_ii.V.w1 > m_pPart->weld_ii.V.w2) ? m_pPart->weld_ii.V.w1 : m_pPart->weld_ii.V.w2;
        if(_fMaxWidth > _fDefaultWidth){
            m_cRange.fPixelSize = _fMaxWidth * 3 / _fWidth;
            double _fThickness  = m_fThickness / (2 * m_cRange.fPixelSize);
            m_cRange.fStartY	= _fHeight / 2 - _fThickness;
            m_cRange.fStopY	 = _fHeight / 2 + _fThickness;
        }
    }
        break;
    case VY:
    case VV:
    case UU:
    case UV:
    {
        double _fMaxWidth = ( m_pPart->weld_ii.VY.w1 > m_pPart->weld_ii.VY.w2) ? m_pPart->weld_ii.VY.w1 : m_pPart->weld_ii.VY.w2;
        _fMaxWidth = ( _fMaxWidth > m_pPart->weld_ii.VY.w3) ? _fMaxWidth : m_pPart->weld_ii.VY.w3;
        if(_fMaxWidth > _fDefaultWidth){
            m_cRange.fPixelSize = _fMaxWidth * 3 / _fWidth;
            double _fThickness  = m_fThickness / (2 * m_cRange.fPixelSize);
            m_cRange.fStartY	= _fHeight / 2 - _fThickness;
            m_cRange.fStopY	 = _fHeight / 2 + _fThickness;
        }
    }
        break;
    case TKY:
    {
        double TKYAngle, tabx, maxwidth1, maxwidth2, _fMaxWidth;
        if(m_pPart->weld_ii.eAngle == 90){
            tabx = m_pPart->weld_ii.eTopThinkness / 2;
            maxwidth1 = tabx + m_pPart->weld_ii.TKY.w1;
            maxwidth2 = tabx + m_pPart->weld_ii.TKY.w2;
        }else{
            TKYAngle = DEGREE_TO_ARCH(m_pPart->weld_ii.eAngle);
            tabx = m_pPart->weld_ii.eTopThinkness / ( sin(TKYAngle) * 2);
            maxwidth1 = tabx + m_pPart->weld_ii.TKY.w1 - ( m_pPart->weld_ii.TKY.h1 / tan(TKYAngle));
            maxwidth2 = tabx + m_pPart->weld_ii.TKY.w2 + ( m_pPart->weld_ii.TKY.h2 / tan(TKYAngle));
        }
        _fMaxWidth = maxwidth1 > maxwidth2 ? maxwidth1 : maxwidth2;
        if(_fMaxWidth > _fDefaultWidth){
            m_cRange.fPixelSize = _fMaxWidth * 3 / _fWidth;
        }
        double buff = m_pPart->weld_ii.TKY.h1;
        if(m_pPart->weld_ii.TKY.h2 > buff){
            buff = m_pPart->weld_ii.TKY.h2;
        }
        if(m_fThickness > buff){
            buff = m_fThickness;
        }
        m_cRange.fStartY	= _fHeight / 2;
        m_cRange.fStopY	 = _fHeight / 2 + m_fThickness * _fHeight / ( 4 * buff);
    }
        break;
    default:
        break;
    }
}

void WeldShowDataIIWidget::DrawWeld( QPainter &painter)
{
    switch (m_pPart->weld_ii.eType) {
    case I:
        DrawWeldI( painter);
        break;
    case V:
        DrawWeldV( painter);
        break;
    case U:
        DrawWeldU( painter);
        break;
    case VY:
        DrawWeldVY( painter);
        break;
    case VV:
        DrawWeldVV( painter);
        break;
    case UU:
        DrawWeldUU( painter);
        break;
    case UV:
        DrawWeldUV( painter);
        break;
    case TKY:
        DrawWeldTKY( painter);
        break;
    default:
        break;
    }
}

void WeldShowDataIIWidget::DrawWeldI( QPainter &painter)
{
    QPainterPath path;
    QPointF _pos[2];
    double w = m_pPart->weld_ii.I.w;
    if( m_pPart->weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld_ii.eSymmetry == setup_WELD_LEFT){
        _pos[0].setX(-w);
        _pos[0].setY(0);
        _pos[1].setX(-w);
        _pos[1].setY(m_fThickness);
        PositionTransfer(_pos[0]);
        PositionTransfer(_pos[1]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
    }

    if( m_pPart->weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld_ii.eSymmetry == setup_WELD_RIGHT){
        _pos[0].setX(w);
        _pos[0].setY(0);
        _pos[1].setX(w);
        _pos[1].setY(m_fThickness);
        PositionTransfer(_pos[0]);
        PositionTransfer(_pos[1]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
    }

    painter.drawPath(path);
}

void WeldShowDataIIWidget::DrawWeldV( QPainter &painter)
{
    QPainterPath path;
    QPointF _pos[3];
    if( m_pPart->weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld_ii.eSymmetry == setup_WELD_LEFT){
        _pos[0].setX(-m_pPart->weld_ii.V.w1);
        _pos[0].setY(0);
        _pos[1].setX(-m_pPart->weld_ii.V.w2);
        _pos[1].setY(m_pPart->weld_ii.V.h);
        _pos[2].setX(-m_pPart->weld_ii.V.w2);
        _pos[2].setY(m_fThickness);
        PositionTransfer(_pos[0]);
        PositionTransfer(_pos[1]);
        PositionTransfer(_pos[2]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.lineTo(_pos[2]);
    }

    if( m_pPart->weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld_ii.eSymmetry == setup_WELD_RIGHT){
        _pos[0].setX(m_pPart->weld_ii.V.w1);
        _pos[0].setY(0);
        _pos[1].setX(m_pPart->weld_ii.V.w2);
        _pos[1].setY(m_pPart->weld_ii.V.h);
        _pos[2].setX(m_pPart->weld_ii.V.w2);
        _pos[2].setY(m_fThickness);
        PositionTransfer(_pos[0]);
        PositionTransfer(_pos[1]);
        PositionTransfer(_pos[2]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.lineTo(_pos[2]);
    }
    painter.drawPath(path);
}

void WeldShowDataIIWidget::DrawWeldU( QPainter &painter)
{
    if( m_pPart->weld_ii.U.w2 >= m_pPart->weld_ii.U.r)
    {
        DrawWeldV( painter);
        return;
    }
    QPainterPath path;
    QPointF _pos[4];
    double w1 = m_pPart->weld_ii.U.w1;
    double w2 = m_pPart->weld_ii.U.w2;
    double h  = m_pPart->weld_ii.U.h;
    double r  = m_pPart->weld_ii.U.r;
    double h1 = sqrt(pow(r,2) - pow(w2,2));
    double h2 = h - h1;
    double l1 = sqrt(pow(w1,2) + pow(h2,2));
    double l2 = sqrt(pow(l1,2) - pow(r,2));
    double angle1 = atan(h2 / w1);
    double angle2 = atan(r / l2);
    double h3 = l2 * sin(angle1 + angle2);
    double w3 = w1 - l2 * cos(angle1 + angle2);
    angle1  = M_PI/2  - (angle1 + angle2) ;
    angle2 = asin(w2 / r);
    int b = (int)(angle1 * 180 / M_PI);
    int e = (90 - b - (int)(angle2 * 180 / M_PI));

    QPointF _lefttop , _rightbottom;
    _lefttop.setX(-r);
    _lefttop.setY(h2 - r);
    _rightbottom.setX(r);
    _rightbottom.setY(h2 + r);
    PositionTransfer(_lefttop) ;
    PositionTransfer(_rightbottom);
    QRectF rectangle( _lefttop, _rightbottom);

    if( m_pPart->weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld_ii.eSymmetry == setup_WELD_LEFT){
        _pos[0].setX(-w1);
        _pos[0].setY(0);
        _pos[1].setX(-w3);
        _pos[1].setY(h3);
        _pos[2].setX(-w2);
        _pos[2].setY(h);
        _pos[3].setX(-w2);
        _pos[3].setY(m_fThickness);

        PositionTransfer(_pos[0]);
        PositionTransfer(_pos[1]);
        PositionTransfer(_pos[2]);
        PositionTransfer(_pos[3]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.arcTo( rectangle, 180+b, e);
        path.moveTo(_pos[2]);
        path.lineTo(_pos[3]);
    }

    if( m_pPart->weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld_ii.eSymmetry == setup_WELD_RIGHT){
        _pos[0].setX(w1);
        _pos[0].setY(0);
        _pos[1].setX(w3);
        _pos[1].setY(h3);
        _pos[2].setX(w2);
        _pos[2].setY(h);
        _pos[3].setX(w2);
        _pos[3].setY(m_fThickness);

        PositionTransfer(_pos[0]);
        PositionTransfer(_pos[1]);
        PositionTransfer(_pos[2]);
        PositionTransfer(_pos[3]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.arcTo( rectangle, -b, -e);
        path.moveTo(_pos[2]);
        path.lineTo(_pos[3]);
    }

    painter.drawPath(path);
}

void WeldShowDataIIWidget::DrawWeldVY( QPainter &painter)
{
    QPainterPath path;
    QPointF _pos[4];

    double w1 = m_pPart->weld_ii.VY.w1;
    double h1 = m_pPart->weld_ii.VY.h1;
    double w2 = m_pPart->weld_ii.VY.w2;
    double h2 = m_pPart->weld_ii.VY.h2;
    double w3 = m_pPart->weld_ii.VY.w3;

    if( m_pPart->weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld_ii.eSymmetry == setup_WELD_LEFT){
        _pos[0].setX(-w1);
        _pos[0].setY(0);
        _pos[1].setX(-w2);
        _pos[1].setY(h1);
        _pos[2].setX(-w3);
        _pos[2].setY(h1 + h2);
        _pos[3].setX(-w3);
        _pos[3].setY(m_fThickness);
        PositionTransfer( _pos[0]);
        PositionTransfer( _pos[1]);
        PositionTransfer( _pos[2]);
        PositionTransfer( _pos[3]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.lineTo(_pos[2]);
        path.lineTo(_pos[3]);

    }

    if( m_pPart->weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld_ii.eSymmetry == setup_WELD_RIGHT){
        _pos[0].setX(w1);
        _pos[0].setY(0);
        _pos[1].setX(w2);
        _pos[1].setY(h1);
        _pos[2].setX(w3);
        _pos[2].setY(h1 + h2);
        _pos[3].setX(w3);
        _pos[3].setY(m_fThickness);
        PositionTransfer( _pos[0]);
        PositionTransfer( _pos[1]);
        PositionTransfer( _pos[2]);
        PositionTransfer( _pos[3]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.lineTo(_pos[2]);
        path.lineTo(_pos[3]);
    }

    painter.drawPath(path);
}

void WeldShowDataIIWidget::DrawWeldVV( QPainter &painter)
{
    QPainterPath path;
    QPointF _pos[4];

    double w1 = m_pPart->weld_ii.VV.w1;
    double h1 = m_pPart->weld_ii.VV.h1;
    double w2 = m_pPart->weld_ii.VV.w2;
    double h2 = m_pPart->weld_ii.VV.h2;
    double w3 = m_pPart->weld_ii.VV.w3;

    if( m_pPart->weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld_ii.eSymmetry == setup_WELD_LEFT){
        _pos[0].setX(-w1);
        _pos[0].setY(0);
        _pos[1].setX(-w2);
        _pos[1].setY(h1);
        _pos[2].setX(-w2);
        _pos[2].setY(m_fThickness - h2);
        _pos[3].setX(-w3);
        _pos[3].setY(m_fThickness);
        PositionTransfer( _pos[0]);
        PositionTransfer( _pos[1]);
        PositionTransfer( _pos[2]);
        PositionTransfer( _pos[3]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.lineTo(_pos[2]);
        path.lineTo(_pos[3]);
    }

    if( m_pPart->weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld_ii.eSymmetry == setup_WELD_RIGHT){
        _pos[0].setX(w1);
        _pos[0].setY(0);
        _pos[1].setX(w2);
        _pos[1].setY(h1);
        _pos[2].setX(w2);
        _pos[2].setY(m_fThickness - h2);
        _pos[3].setX(w3);
        _pos[3].setY(m_fThickness);
        PositionTransfer( _pos[0]);
        PositionTransfer( _pos[1]);
        PositionTransfer( _pos[2]);
        PositionTransfer( _pos[3]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.lineTo(_pos[2]);
        path.lineTo(_pos[3]);
    }

    painter.drawPath(path);
}

void WeldShowDataIIWidget::DrawWeldUU( QPainter &painter)
{
    if( m_pPart->weld_ii.UU.w2 >= m_pPart->weld_ii.UU.r1 && m_pPart->weld_ii.UU.w2 >= m_pPart->weld_ii.UU.r2)
    {
        DrawWeldVV( painter);
        return;
    }
    QPainterPath path;
    QPointF _pos[6];

    double w1 = m_pPart->weld_ii.UU.w1;
    double h1 = m_pPart->weld_ii.UU.h1;
    double r1 = m_pPart->weld_ii.UU.r1;
    double w2 = m_pPart->weld_ii.UU.w2;
    double h2 = m_pPart->weld_ii.UU.h2;
    double r2 = m_pPart->weld_ii.UU.r2;
    double w3 = m_pPart->weld_ii.UU.w3;
    double h3 =  sqrt(pow(r1,2) - pow(w2,2));
    double h4 = h1 - h3;
    double l1 = sqrt(pow(w1,2) + pow(h4,2));
    double l2 = sqrt(pow(l1,2) - pow(r1,2));
    double angle1 = atan(h4 / w1);
    double angle2 = atan(r1 / l2);
    double h5 = l2 * sin(angle1 + angle2);
    double w4 = w1 - l2 * cos(angle1 + angle2);
    angle1  = M_PI/2  - (angle1 + angle2);
    angle2 = asin(w2 / r1);
    int a1 = (int)(angle1 * 180 / M_PI);
    int a2 = (90 - a1 - (int)(angle2 * 180 / M_PI));
    double h6 = sqrt(pow(r2, 2) - pow(w2, 2));
    double h7 = h2 - h6;
    double l3 = sqrt(pow(w3, 2) + pow(h7, 2));
    double l4 = sqrt(pow(l3, 2) - pow(r2, 2));
    double angle3 = atan(h7 / w3);
    double angle4 = atan(r2 / l4);
    double h8 = l4 * sin(angle3 + angle4);
    double w5 = w3 - l4 * cos(angle3 + angle4);
    angle3 = M_PI/2 - (angle3 + angle4);
    angle4 = asin(w2 / r2);
    int a3 = (int)(angle3 * 180 / M_PI);
    int a4 = (90 - a3 - (int)(angle4 * 180 / M_PI));

    QPointF _lefttop, _rightbottom;
    _lefttop.setX(-r1);
    _lefttop.setY(h4 - r1);
    _rightbottom.setX(r1);
    _rightbottom.setY(h4 + r1);
    PositionTransfer( _lefttop) ;
    PositionTransfer( _rightbottom);
    QRectF rectangle1( _lefttop, _rightbottom);
    _lefttop.setX(-r2);
    _lefttop.setY(m_fThickness - h7 - r2);
    _rightbottom.setX(r2);
    _rightbottom.setY(m_fThickness - h7 + r2);
    PositionTransfer( _lefttop) ;
    PositionTransfer( _rightbottom);
    QRectF rectangle2( _lefttop, _rightbottom);

    if( m_pPart->weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld_ii.eSymmetry == setup_WELD_LEFT){
        _pos[0].setX(-w1);
        _pos[0].setY(0);
        _pos[1].setX(-w4);
        _pos[1].setY(h5);
        _pos[2].setX(-w2);
        _pos[2].setY(h1);
        _pos[3].setX(-w2);
        _pos[3].setY(m_fThickness - h2);
        _pos[4].setX(-w5);
        _pos[4].setY(m_fThickness - h8);
        _pos[5].setX(-w3);
        _pos[5].setY(m_fThickness);
        PositionTransfer( _pos[0]);
        PositionTransfer( _pos[1]);
        PositionTransfer( _pos[2]);
        PositionTransfer( _pos[3]);
        PositionTransfer( _pos[4]);
        PositionTransfer( _pos[5]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.arcTo( rectangle1, 180+a1, a2);
        path.moveTo(_pos[2]);
        path.lineTo(_pos[3]);
        path.moveTo(_pos[5]);
        path.lineTo(_pos[4]);
        path.arcTo( rectangle2, 180-a3, -a4);
    }

    if( m_pPart->weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld_ii.eSymmetry == setup_WELD_RIGHT){
        _pos[0].setX(w1);
        _pos[0].setY(0);
        _pos[1].setX(w4);
        _pos[1].setY(h5);
        _pos[2].setX(w2);
        _pos[2].setY(h1);
        _pos[3].setX(w2);
        _pos[3].setY(m_fThickness - h2);
        _pos[4].setX(w5);
        _pos[4].setY(m_fThickness - h8);
        _pos[5].setX(w3);
        _pos[5].setY(m_fThickness);
        PositionTransfer( _pos[0]);
        PositionTransfer( _pos[1]);
        PositionTransfer( _pos[2]);
        PositionTransfer( _pos[3]);
        PositionTransfer( _pos[4]);
        PositionTransfer( _pos[5]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.arcTo( rectangle1, -a1, -a2);
        path.moveTo(_pos[2]);
        path.lineTo(_pos[3]);
        path.moveTo(_pos[5]);
        path.lineTo(_pos[4]);
        path.arcTo( rectangle2, a3, a4);
    }

    painter.drawPath(path);
}

void WeldShowDataIIWidget::DrawWeldUV( QPainter &painter)
{
    if( m_pPart->weld_ii.UV.w2 >= m_pPart->weld_ii.UV.r)
    {
        DrawWeldVV( painter);
        return;
    }
    QPainterPath path;
    QPointF _pos[5];

    double w1 = m_pPart->weld_ii.UV.w1;
    double h1 = m_pPart->weld_ii.UV.h1;
    double r  = m_pPart->weld_ii.UV.r;
    double w2 = m_pPart->weld_ii.UV.w2;
    double h2 = m_pPart->weld_ii.UV.h2;
    double w3 = m_pPart->weld_ii.UV.w3;
    double h3 =  sqrt(pow(r,2) - pow(w2,2));
    double h4 = h1 - h3;
    double l1 = sqrt(pow(w1,2) + pow(h4,2));
    double l2 = sqrt(pow(l1,2) - pow(r,2));
    double angle1 = atan(h4 / w1);
    double angle2 = atan(r / l2);
    double h5 = l2 * sin(angle1 + angle2);
    double w4 = w1 - l2 * cos(angle1 + angle2);
    angle1  = M_PI/2  - (angle1 + angle2);
    angle2 = asin(w2 / r);
    int b = (int)(angle1 * 180 / M_PI);
    int e = (90 - b - (int)(angle2 * 180 / M_PI));

    QPointF _lefttop , _rightbottom;
    _lefttop.setX(-r);
    _lefttop.setY(h4 - r);
    _rightbottom.setX(r);
    _rightbottom.setY(h4 + r);
    PositionTransfer( _lefttop) ;
    PositionTransfer( _rightbottom);
    QRectF rectangle( _lefttop, _rightbottom);

    if( m_pPart->weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld_ii.eSymmetry == setup_WELD_LEFT){
        _pos[0].setX(-w1);
        _pos[0].setY(0);
        _pos[1].setX(-w4);
        _pos[1].setY(h5);
        _pos[2].setX(-w2);
        _pos[2].setY(h1);
        _pos[3].setX(-w2);
        _pos[3].setY(m_fThickness - h2);
        _pos[4].setX(-w3);
        _pos[4].setY(m_fThickness);
        PositionTransfer( _pos[0]);
        PositionTransfer( _pos[1]);
        PositionTransfer( _pos[2]);
        PositionTransfer( _pos[3]);
        PositionTransfer( _pos[4]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.arcTo( rectangle, 180+b, e);
        path.moveTo(_pos[2]);
        path.lineTo(_pos[3]);
        path.lineTo(_pos[4]);
    }

    if( m_pPart->weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_pPart->weld_ii.eSymmetry == setup_WELD_RIGHT){
        _pos[0].setX(w1);
        _pos[0].setY(0);
        _pos[1].setX(w4);
        _pos[1].setY(h5);
        _pos[2].setX(w2);
        _pos[2].setY(h1);
        _pos[3].setX(w2);
        _pos[3].setY(m_fThickness - h2);
        _pos[4].setX(w3);
        _pos[4].setY(m_fThickness);
        PositionTransfer( _pos[0]);
        PositionTransfer( _pos[1]);
        PositionTransfer( _pos[2]);
        PositionTransfer( _pos[3]);
        PositionTransfer( _pos[4]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.arcTo( rectangle, -b, -e);
        path.moveTo(_pos[2]);
        path.lineTo(_pos[3]);
        path.lineTo(_pos[4]);
    }

    painter.drawPath(path);
}

void WeldShowDataIIWidget::DrawWeldTKY( QPainter &painter)
{
    QPainterPath path;
    QPointF _pos[4];
    QPointF _topPos[2];
    double w1 = m_pPart->weld_ii.TKY.w1;
    double h1 = m_pPart->weld_ii.TKY.h1;
    double a1 = DEGREE_TO_ARCH(m_pPart->weld_ii.TKY.a1);
    double w2 = m_pPart->weld_ii.TKY.w2;
    double h2 = m_pPart->weld_ii.TKY.h2;
    double a2 = DEGREE_TO_ARCH(m_pPart->weld_ii.TKY.a2);
    double topT = m_pPart->weld_ii.eTopThinkness / 2;
    double tkyH = m_pPart->weld_ii.TKY.h1;
    //m_pPart->weld_ii.eAngle = 120;
    double TKYAngle = DEGREE_TO_ARCH(m_pPart->weld_ii.eAngle);
    if(m_pPart->weld_ii.TKY.h2 > tkyH){
        tkyH = m_pPart->weld_ii.TKY.h2;
    }
    if(m_fThickness > tkyH){
        tkyH = m_fThickness;
    }
    tkyH *= 2;

    if(m_pPart->weld_ii.eAngle == 90){
        _pos[0].setX(-w1 - topT);
        _pos[0].setY(0);
        _pos[1].setX(- topT);
        _pos[1].setY(-h1);
        _pos[2].setX(- topT + tan(a1)*h1);
        _pos[2].setY(0);
        PositionTransfer(_pos[0]);
        PositionTransfer(_pos[1]);
        PositionTransfer(_pos[2]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.lineTo(_pos[2]);

        _pos[3].setX(- topT);
        _pos[3].setY(- tkyH);
        PositionTransfer(_pos[3]);
        _topPos[0] = _pos[3];
        path.moveTo(_pos[1]);
        path.lineTo(_pos[3]);

        _pos[0].setX( w2 + topT);
        _pos[0].setY(0);
        _pos[1].setX( topT);
        _pos[1].setY( -h2);
        _pos[2].setX( topT - tan(a2)*h2);
        _pos[2].setY(0);
        PositionTransfer(_pos[0]);
        PositionTransfer(_pos[1]);
        PositionTransfer(_pos[2]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.lineTo(_pos[2]);

        _pos[3].setX( topT);
        _pos[3].setY( - tkyH);
        PositionTransfer(_pos[3]);
        _topPos[1] = _pos[3];
        path.moveTo(_pos[1]);
        path.lineTo(_pos[3]);
    }else{
        double TKYA1X = h1 / tan( TKYAngle);
        double topTx = topT / sin(TKYAngle);
        double _a1X, _a2X;
        double tkyHx = tkyH / tan( TKYAngle);
        double a1a = 180 - m_pPart->weld_ii.eAngle - m_pPart->weld_ii.TKY.a1;
        if(a1a == 90){
            _a1X = 0;
        }else{
            double a1aArch = DEGREE_TO_ARCH(a1a);
            _a1X = h1 / tan(a1aArch);
        }

        _pos[0].setX( TKYA1X - w1 - topTx);
        _pos[0].setY(0);
        _pos[1].setX( TKYA1X - topTx);
        _pos[1].setY(-h1);
        _pos[2].setX( TKYA1X - topTx + _a1X);
        _pos[2].setY(0);
        PositionTransfer(_pos[0]);
        PositionTransfer(_pos[1]);
        PositionTransfer(_pos[2]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.lineTo(_pos[2]);

        _pos[3].setX( tkyHx - topTx);
        _pos[3].setY( - tkyH);
        PositionTransfer(_pos[3]);
        _topPos[0] = _pos[3];
        path.moveTo(_pos[1]);
        path.lineTo(_pos[3]);

        double TKYA2X = h2 / tan( TKYAngle);
        double a2a = m_pPart->weld_ii.eAngle - m_pPart->weld_ii.TKY.a2;
        double a2aArch = DEGREE_TO_ARCH(a2a);
        _a2X = h2 / tan(a2aArch);
        _pos[0].setX( TKYA2X + w2 + topTx);
        _pos[0].setY(0);
        _pos[1].setX( TKYA2X + topTx);
        _pos[1].setY(-h2);
        _pos[2].setX( TKYA2X + topTx - _a2X);
        _pos[2].setY(0);
        PositionTransfer(_pos[0]);
        PositionTransfer(_pos[1]);
        PositionTransfer(_pos[2]);
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.lineTo(_pos[2]);

        _pos[3].setX( tkyHx + topTx);
        _pos[3].setY( - tkyH);        
        PositionTransfer(_pos[3]);
        _topPos[1] = _pos[3];
        path.moveTo(_pos[1]);
        path.lineTo(_pos[3]);
    }
    painter.drawPath(path);

    QPen pen = painter.pen();
    QPen NewPen(pen);
    NewPen.setWidth(1);
    NewPen.setColor(QColor(0, 255, 0));
    painter.setPen(NewPen);
    painter.save();
    QPainterPath pathProbe;
    double BotT = abs(m_cRange.fStopY - m_cRange.fStartY) / 2;
    QPolygonF polygon1;
    polygon1 << QPointF( 0.5 * BotT, 0) << QPointF( 2 * BotT, 0) << QPointF( 2 * BotT, BotT)
            << QPointF( 0, BotT) << QPointF( 0, 0.5 * BotT) << QPointF( 0.5 * BotT, 0);
    QPolygonF polygon2;
    polygon2 << QPointF( 0, 0) << QPointF( 1.5 * BotT, 0) << QPointF( 2 * BotT, 0.5 * BotT)
            << QPointF( 2 * BotT, BotT) << QPointF( 0, BotT) << QPointF( 0, 0);

    switch (m_pPart->weld_ii.eProbePos) {
    case KTY_WED_1:
    {
        double temptopx;
        if(m_pPart->weld_ii.eAngle == 90){
            temptopx = _topPos[0].x();
        }else{
            temptopx = _topPos[0].x() + _topPos[0].y() / tan(TKYAngle);
        }
        double tempx = temptopx - BotT / sin(TKYAngle) - 2 * BotT * cos(TKYAngle);
        double tempy = 2 * BotT * sin(TKYAngle);
        painter.translate( tempx - 2, tempy + 2);
        painter.rotate(-m_pPart->weld_ii.eAngle);
        pathProbe.addPolygon(polygon2);
        painter.drawPath(pathProbe);
    }
        break;
    case KTY_WED_2:
    {
        double temptopx;
        if(m_pPart->weld_ii.eAngle == 90){
            temptopx = _topPos[1].x();
        }else{
            temptopx = _topPos[1].x() + _topPos[1].y() / tan(TKYAngle);
        }
        double tempx = temptopx + BotT * sin(TKYAngle);
        double tempy = BotT * cos(TKYAngle);

        painter.translate( tempx + 3, tempy + 1);
        painter.rotate(180 - m_pPart->weld_ii.eAngle);
        pathProbe.addPolygon(polygon1);
        painter.drawPath(pathProbe);
    }
        break;
    case KTY_WING_1:
        painter.translate(2, m_cRange.fStartY - BotT - 2);
        pathProbe.addPolygon(polygon1);
        painter.drawPath(pathProbe);
        break;
    case KTY_WING_2:
        painter.translate( m_cRange.fWidth - 2 * BotT - 2, m_cRange.fStartY - BotT - 2);
        pathProbe.addPolygon(polygon2);
        painter.drawPath(pathProbe);
        break;
    case KTY_WING_3:
        painter.translate( 2 * BotT + 2, m_cRange.fStopY + BotT + 1);
        painter.rotate(180);
        pathProbe.addPolygon(polygon2);
        painter.drawPath(pathProbe);
        break;
    case KTY_WING_4:
        painter.translate( m_cRange.fWidth - 2, m_cRange.fStopY + BotT + 1);
        painter.rotate(180);
        pathProbe.addPolygon(polygon1);
        painter.drawPath(pathProbe);
        break;
    default:
        break;
    }
    painter.restore();
}

void WeldShowDataIIWidget::PositionTransfer( QPointF &pos_)
{
    double _fOrgX = m_cRange.fWidth / 2;
    double _fOrgY = m_cRange.fStartY;
    double _fX = (pos_.x() / m_cRange.fPixelSize) + _fOrgX;
    double _fY = (pos_.y() / m_cRange.fPixelSize) + _fOrgY;
    pos_.setX(_fX);
    pos_.setY(_fY);
}
