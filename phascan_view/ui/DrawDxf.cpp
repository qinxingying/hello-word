#include "DrawDxf.h"
#include "dl_dxf.h"
#include "dl_creationadapter.h"
#include "gHeader.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

DrawDxf * g_pDrawDxf = NULL;

DrawDxf *DrawDxf::Instance()
{
    if(!g_pDrawDxf){
        g_pDrawDxf = new DrawDxf();
        qDebug()<<__func__<<__LINE__;
    }
    return g_pDrawDxf;
}

DrawDxf::DrawDxf(QWidget *parent) :
	QWidget(parent)
{
    m_pPart = NULL;
    m_fThickness = 20;
    m_zoom = 1.0;
}

QList<DL_LineData> DrawDxf::getLineList() const
{
    return m_lineList;
}

void DrawDxf::setLineList(const QList<DL_LineData> &lineList)
{
    m_lineList = lineList;
}

QList<DL_ArcData> DrawDxf::getArcList() const
{
    return m_arcList;
}

void DrawDxf::setArcList(const QList<DL_ArcData> &arcList)
{
    m_arcList = arcList;
}

QList<DL_MTextData> DrawDxf::getTextList() const
{
    return m_textList;
}

void DrawDxf::setTextList(const QList<DL_MTextData> &textList)
{
    m_textList = textList;
}

QList<DL_EllipseData> DrawDxf::getEllipseList() const
{
    return m_ellipseList;
}

void DrawDxf::setEllipseList(const QList<DL_EllipseData> &ellipseList)
{
    m_ellipseList = ellipseList;
}

QList<DL_CircleData> DrawDxf::getCircleList() const
{
    return m_circleList;
}

void DrawDxf::setCircleList(const QList<DL_CircleData> &circleList)
{
    m_circleList = circleList;
}

QList<DL_TextData> DrawDxf::getTextDataList() const
{
    return m_textDataList;
}

void DrawDxf::setTextDataList(const QList<DL_TextData> &textDataList)
{
    m_textDataList = textDataList;
}

QList<DL_VertexData> DrawDxf::getVertexList() const
{
    return m_vertexList;
}

void DrawDxf::setVertexList(const QList<DL_VertexData> &vertexList)
{
    m_vertexList = vertexList;
}

QList<DL_SplineData> DrawDxf::getSplineList() const
{
    return m_splineList;
}

void DrawDxf::setSplineList(const QList<DL_SplineData> &splineList)
{
    m_splineList = splineList;
}

QList<DL_ControlPointData> DrawDxf::getControlPointList() const
{
    return m_controlPointList;
}

void DrawDxf::setControlPointList(const QList<DL_ControlPointData> &controlPointList)
{
    m_controlPointList = controlPointList;
}

QList<DL_PointData> DrawDxf::getPointList() const
{
    return m_pointList;
}

void DrawDxf::setPointList(const QList<DL_PointData> &pointList)
{
    m_pointList = pointList;
}

QList<DL_PolylineData> DrawDxf::getPolyLineList() const
{
    return m_polyLineList;
}

void DrawDxf::setPolyLineList(const QList<DL_PolylineData> &polyLineList)
{
    m_polyLineList = polyLineList;
}

void DrawDxf::paintEvent (QPaintEvent*)
{
    QPainter painter(this);
    UpdateDisplayRangle();
    QPen pen = painter.pen();
    QPen NewPen(pen);

    NewPen.setWidth(1);
    NewPen.setColor(QColor(0, 255, 0));
    painter.setPen(NewPen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if(m_pPart->weld.eType == setup_WELD_DXF){
        paint_line(painter);

        paint_text(painter);

        paint_arc(painter);

        paint_circle(painter);

        paint_point(painter);

        paint_ellipse(painter);
        painter.setPen(pen);

        QPainter painter1(this);
        QPen pen1 = painter.pen();
        QPen NewPen1(pen1);

        QVector<qreal> dashes;
        dashes << 3 << 5;
        NewPen1.setWidth(1);
        NewPen1.setDashPattern(dashes);
        NewPen1.setColor(QColor(0, 0, 255));
        painter1.setPen(NewPen1);
        painter1.drawLine(0, height()/2, width(), height()/2);
        painter1.drawLine(width()/2, 0, width()/2, height());
        painter1.setPen(pen1);
    }else{
        painter.drawLine (0, m_cRange.fStartY, m_cRange.fWidth, m_cRange.fStartY);
        painter.drawLine (0, m_cRange.fStopY, m_cRange.fWidth, m_cRange.fStopY);
        DrawWeld(painter);
        painter.setPen(pen);

        QPainter painter2(this);
        QPen pen2 = painter.pen();
        QPen NewPen2(pen2);

        QVector<qreal> dashes;
        dashes << 3 << 5;
        NewPen2.setWidth(1);
        NewPen2.setDashPattern(dashes);
        NewPen2.setColor(QColor(0, 0, 255));
        painter2.setPen(NewPen2);
        painter2.drawLine (m_cRange.fWidth / 2, 0, m_cRange.fWidth / 2, m_cRange.fHeight);
        painter2.setPen(pen2);
    }
}

void DrawDxf::paint_point(QPainter &painter)
{
    if(m_vertexList.size() > 0){
        for(int i = 0; i < m_vertexList.count(); i++){
            painter.drawPoint(m_zoom*m_vertexList.at(i).x + width()/2, -m_zoom*m_vertexList.at(i).y + height()/2);
        }
    }

    if(m_controlPointList.size() > 0){
        for(int i = 0; i < m_controlPointList.count(); i++){
            painter.drawPoint(m_zoom*m_controlPointList.at(i).x + width()/2, -m_zoom*m_controlPointList.at(i).y + height()/2);
        }
    }

    if(m_pointList.size() > 0){
        for(int i = 0; i < m_pointList.count(); i++){
            painter.drawPoint(m_zoom*m_pointList.at(i).x + width()/2, -m_zoom*m_pointList.at(i).y + height()/2);
        }
    }
}

void DrawDxf::paint_line(QPainter &painter)
{
    if (m_lineList.size() > 0){
        for(int i = 0; i < m_lineList.count(); i++){
            painter.drawLine(m_zoom*m_lineList.at(i).x1 + width()/2, -m_zoom*m_lineList.at(i).y1 + height()/2,
                             m_zoom*m_lineList.at(i).x2 + width()/2, -m_zoom*m_lineList.at(i).y2 + height()/2);
        }
    }

//    if(m_polyLineList.size() > 0){
//        for(int i = 0; i < m_polyLineList.count(); i++){
//            if(m_polyLineList.at(i).flags){
//                paint_polyLine_1(painter);
//            }else{
//                paint_polyLine_0(painter);
//            }
//        }
//    }
    paint_polyLine_0(painter);
}

void DrawDxf::paint_polyLine_0(QPainter &painter)
{
    if(m_vertexList.isEmpty()){
        return;
    }

    for(int i = 1; i < m_vertexList.count(); i++){
        painter.drawLine(m_zoom*m_vertexList.at(i-1).x + width()/2, -m_zoom*m_vertexList.at(i-1).y + height()/2,
                         m_zoom*m_vertexList.at(i).x + width()/2, -m_zoom*m_vertexList.at(i).y + height()/2);
    }
}

void DrawDxf::paint_polyLine_1(QPainter &painter)
{
    if(m_vertexList.isEmpty()){
        return;
    }

    for(int i = 1; i < m_vertexList.count(); i++){
        painter.drawLine(m_zoom*m_vertexList.at(i-1).x + width()/2, -m_zoom*m_vertexList.at(i-1).y + height()/2,
                         m_zoom*m_vertexList.at(i).x + width()/2, -m_zoom*m_vertexList.at(i).y + height()/2);
        painter.drawLine(m_zoom*m_vertexList.at(0).x + width()/2, -m_zoom*m_vertexList.at(0).y + height()/2,
                         m_zoom*m_vertexList.at(m_vertexList.count()-1).x + width()/2,
                         -m_zoom*m_vertexList.at(m_vertexList.count()-1).y + height()/2);
    }
}

void DrawDxf::paint_text(QPainter &painter)
{
    if(m_textList.size() > 0){
        for(int i = 0; i < m_textList.count(); i++){
            painter.drawText(m_zoom*(m_textList.at(i).ipx-2*m_textList.at(i).height) + width()/2,
                             -m_zoom*m_textList.at(i).ipy + height()/2,
                             m_zoom*4*m_textList.at(i).height, m_zoom*m_textList.at(i).height,
                             Qt::AlignLeft, m_textList.at(i).text.c_str());
        }
    }

    if(m_textDataList.size() > 0){
        for(int i = 0; i < m_textDataList.count(); i++){
            painter.drawText(m_zoom*m_textDataList.at(i).ipx + width()/2,
                            -m_zoom*m_textDataList.at(i).ipy - m_textDataList.at(i).height + height()/2,
                             m_zoom*9*m_textDataList.at(i).height, m_zoom*m_textDataList.at(i).height,
                             Qt::AlignLeft, m_textDataList.at(i).text.c_str());
        }
    }
}

void DrawDxf::paint_arc(QPainter &painter)
{
    if(m_arcList.isEmpty()){
        return;
    }

    for(int i = 0; i < m_arcList.count(); i++){
        double r = m_arcList.at(i).radius;
        double startAngle = m_arcList.at(i).angle1*16;
        double endAngle = m_arcList.at(i).angle2*16;

        painter.drawArc(m_zoom*m_arcList.at(i).cx -m_zoom*r + width()/2, -m_zoom*m_arcList.at(i).cy - m_zoom*r + height()/2,
                        m_zoom*2*r, m_zoom*2*r, startAngle, fabs(endAngle - startAngle));
    }
}

void DrawDxf::paint_circle(QPainter &painter)
{
    if(m_circleList.isEmpty()){
        return;
    }

    for(int i = 0; i < m_circleList.count(); i++){
        painter.drawEllipse(m_zoom*m_circleList.at(i).cx - m_zoom*m_circleList.at(i).radius + width()/2,
                            -m_zoom*m_circleList.at(i).cy - m_zoom*m_circleList.at(i).radius + height()/2,
                            2*m_zoom*m_circleList.at(i).radius, 2*m_zoom*m_circleList.at(i).radius);
    }

}

double DrawDxf::calc_rotateAngle(double cx, double cy, double mx, double my)
{
    double rotateAngle = 0;

    if ( fabs(mx-cx) < 1e-15 ) {
        if ( my-cy < -(1e-15) ) {
            rotateAngle = 3*M_PI/2;
        } else if ( my-cy > 1e-15 ) {
            rotateAngle = M_PI/2;
        }
    }

    rotateAngle = atan(fabs((my-cy)/(mx-cx)));

    if ( mx-cx > 1e-15 ) {
        if (my-cy > 1e-15) {
            /*第一象区*/
            rotateAngle = rotateAngle;
        } else if ( my-cy < -1e-15 ) {
            /*第四象区*/
            rotateAngle = 2*M_PI - rotateAngle;
        }
    } else if (mx-cx < -1e-15) {
        if (my-cy > 1e-15) {
            /*第二象区*/
            rotateAngle = M_PI - rotateAngle;
        } else if (my-cy < -1e-15) {
            /*第三象区*/
            rotateAngle = M_PI + rotateAngle;
        }
    }

    return rotateAngle;
}

void DrawDxf::paint_ellipse(QPainter &painter)
{
    if(m_ellipseList.isEmpty()){
        return;
    }

    for(int i = 0; i < m_ellipseList.count(); i++){
        double k  = m_ellipseList.at(i).ratio;
        double r1 = sqrt(pow((m_ellipseList.at(i).mx - m_ellipseList.at(i).cx), 2.0) +
                         pow((m_ellipseList.at(i).my - m_ellipseList.at(i).cy), 2.0));
        double rotateAngle = calc_rotateAngle(m_ellipseList.at(i).cx, m_ellipseList.at(i).cy,
                                              m_ellipseList.at(i).mx, m_ellipseList.at(i).my);
        double startAngle  = 16*m_ellipseList.at(i).angle1*180/M_PI;
        double endAngle    = 16*m_ellipseList.at(i).angle2*180/M_PI;

        painter.translate(width()/2, height()/2);
        painter.rotate(360 - rotateAngle*180/M_PI);

        painter.scale(1, k);

        double Angle = 16*360 - fabs(endAngle - startAngle);
        if(Angle < 1e-10){
            painter.drawArc(m_zoom*m_ellipseList.at(i).cx  - m_zoom*r1,
                            -m_zoom*m_ellipseList.at(i).cy  - m_zoom*r1,
                            m_zoom*2*r1, m_zoom*2*r1, startAngle, 16*360);
        }else{
            painter.drawArc(m_zoom*m_ellipseList.at(i).cx  - m_zoom*r1,
                            -m_zoom*m_ellipseList.at(i).cy  - m_zoom*r1,
                            m_zoom*2*r1, m_zoom*2*r1, startAngle, Angle);
        }

qDebug()<<"\n rotateAngle = "<<rotateAngle*180/M_PI<<"StartAngle = "<<startAngle/16<<"endAngle ="<<endAngle/16<<"r1="<<r1;
qDebug()<<"\n Angle = "<<fabs(endAngle - startAngle)/16<<Angle/16;
    }
}

void DrawDxf::wheelEvent(QWheelEvent *event)
{
    if(event->delta() >0){
        m_zoom += 1;

    }else{
        if(m_zoom > 1){
            m_zoom -= 1;

        }else if(0 < m_zoom && m_zoom <= 1){
            m_zoom = 0.5*m_zoom;
        }
    }

    update();
    emit zoom(m_zoom);
}

void DrawDxf::SerPart(PART_CONFIG* pInfo_)
{
    m_pPart = pInfo_;
    m_fThickness = m_pPart->afSize[0];
}

void DrawDxf::DrawWeld(QPainter& painter)
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
    default:
        break;
    }
}

void DrawDxf::DrawWeldI(QPainter& painter)
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

void DrawDxf::DrawWeldV(QPainter& painter)
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

void DrawDxf::DrawWeldDV(QPainter& painter)
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

void DrawDxf::DrawWeldU (QPainter& painter)
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

void DrawDxf::DrawWeldDiffDV(QPainter &painter)
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

void DrawDxf::DrawWeldJ(QPainter &painter)
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

void DrawDxf::DrawWeldVY(QPainter &painter)
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

void DrawDxf::UpdateDisplayRangle()
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

void DrawDxf::PositionTransfer(QPointF& pos_)
{
    double _fX = pos_.x() / m_cRange.fPixelSize;
    double _fY = pos_.y() / m_cRange.fPixelSize;

    pos_.setX(_fX);
    pos_.setY(_fY);
}

void DrawDxf::DrawDxfPart(QPainterPath &path)
{
    qDebug()<<__func__<<__LINE__<<m_lineList.size();
    if(m_lineList.size() > 0){
        for(int i = 0; i < m_lineList.count(); i++){
            path.moveTo(m_lineList.at(i).x1, m_lineList.at(i).y1);
            path.lineTo(m_lineList.at(i).x2, m_lineList.at(i).y2);
            qDebug()<<"line.P(X, Y) = "<<m_lineList.at(i).x1<<m_lineList.at(i).y1;
        qDebug()<<__func__<<__LINE__;
        }
    }
}
