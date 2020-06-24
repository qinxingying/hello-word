#ifndef DOPPLERGRPHICSITEMLINE_H
#define DOPPLERGRPHICSITEMLINE_H

#include <QObject>
#include <configure/Instrument.h>
#include "DopplerGraphicsItem.h"
#include <QColor>
#include <QRectF>
#include <QDebug>

class DopplerLineItem : public DopplerGraphicsItem
{

public:
    enum LINE_MOVE_TYPE
    {
      LINE_MOVE_NO = 0 ,
      LINE_MOVE_VERTICAL ,
      LINE_MOVE_HORIZENTAL ,
      LINE_MOVE_ALL
    };
    enum LINE_TYPE
    {
        LINE_FREE,
        LINE_VERTICAL ,
        LINE_HORIZENTAL
    };
    DopplerLineItem(const QColor& cColor_);
    void SetLineType(LINE_TYPE eType_)  ;
    DopplerLineItem::LINE_TYPE GetLineType() const;
    void SetMoveType(LINE_MOVE_TYPE eType_) ;
    void SetLineStyle(Qt::PenStyle eStype_) ;
    void SetScenceSize(QSize);
    void SetTofdPCS(bool tofdDepth, float pcs){m_tofdDepth = tofdDepth;m_pcs = pcs;}
    virtual void SetItemGeometry (QRectF& rect_);
//----------------------------------------------------------
//  wuhan cursor 2015-05-19
    Qt::CursorShape GetCursorShape(QPointF posCursor_);
    QRectF GetCursorValidArea();
    void SetWndRect(QRect rect_) {m_rcWnd = rect_;}
//----------------------------------------------------------

protected:
    void DrawLabel(QPainter* painter);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) ;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    LINE_TYPE      m_eLineType   ;
    LINE_MOVE_TYPE m_eMoveType ;
    QRectF         m_rect   ;
    QColor         m_cColor ;
    Qt::PenStyle   m_eStype ;
    QSize          m_cSize ;
	QRect          m_rcWnd ;
    bool m_tofdDepth;
    float m_pcs;
};

class DopplerScanMarker :public QObject, public DopplerLineItem
{

public:
    DopplerScanMarker(const QColor& cColor_);

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);


};

class DopplerCalibrationMark : public DopplerLineItem
{

public:
    DopplerCalibrationMark(const QColor& cColor_);

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

	void DrawLabel(QPainter *painter, char* str);

};

#endif // DOPPLERGRPHICSITEMLINE_H
