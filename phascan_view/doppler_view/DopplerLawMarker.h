#ifndef DOPPLERLAWMARKER_H
#define DOPPLERLAWMARKER_H
#include <QObject>
#include <QColor>
#include <QVector>
#include <QLineF>
#include <QPainterPath>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "DopplerGraphicsItem.h"

#define MAX_MARKER_QTY   3

class DopplerLawMarker :public QObject, public DopplerGraphicsItem
{
    Q_OBJECT

public:
    enum DIRECTION
    {
        VERTICAL =0 ,
        HORIZENTAL
    };
    DopplerLawMarker();
    QVector<QLineF>* GetMarkerVector();
    void SetupMarkers(QVector<QLineF>* pLines_) ;
    void SetupStringMarker(QVector<QString>* pMarker_);
    void SetMarkerColor(int nId_ , QColor* pColor_) ;
    void SetWeldColor(const QColor& color_) ;
    void EnableMarkerQty(unsigned int nQty_);
    void SetMarkerPos(int nMarker_ , int nMarkerPos_) ;
    QRectF boundingRect() const;
    QPainterPath shape() const;
    virtual void SetItemGeometry (QRectF& rect_);
    int GetMarkerQty() const ;
    int GetMarkerPos(int nId) const;
    int GetMarkerId() const ;
    int GetMarkerLinesCount();
    void SetWeldInfo(bool bShow_ , int brushHAZ, QPainterPath* path, QPainterPath* HAZpath);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    void DrawLabel(QPainter *painter , int nIndex_) ;
    void DrawWeld(QPainter *painter) ;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent (QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void   GetCurrentLineIndex(QPointF pos_ , int* nIndex_ , int* nZoom_ ,float* fScale_ );
    QLineF GetCurrentPosLine( int nIndex_ , float fScale_) ;

    QVector<QLineF>    m_cMarkers ;
    QVector<QString>   m_strMarker ;
    int    m_nMarkerQty;
    int    m_anMarkerId[MAX_MARKER_QTY] ;
    QColor m_aColor[MAX_MARKER_QTY] ;
    QColor m_cColorWeld  ;
    int    m_nSelectedMarker ;
    int    m_nPostSelect     ;
    QLineF dotLine           ;
    DIRECTION  m_eDirection  ;

    bool   m_bShowWeld     ;
    bool   m_brushHAZ;
    QPainterPath weld      ;
    QPainterPath HAZBrush  ;
public slots:
    void SlotChangeLinePos(int nNewLineIndex);

};

#endif // DOPPLERLAWMARKER_H
