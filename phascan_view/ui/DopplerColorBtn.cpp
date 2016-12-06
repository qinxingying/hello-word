#include "DopplerColorBtn.h"
#include <QPainter>

DopplerColorBtn::DopplerColorBtn(QWidget *parent) :
    QPushButton(parent)
{
    unsigned char _color[256][3]  ;
    for(int i = 0 ; i < 256 ; i++)
    {
        _color[i][0]  = i ;
        _color[i][1]  = i ;
        _color[i][2]  = i ;
    }
    SetColorIndex(_color);
}

void DopplerColorBtn::SetColorIndex(void* pColor_)
{
    memcpy(m_aColorIndex , pColor_ , 256 * 3) ;
    update();
}

void DopplerColorBtn::paintEvent (QPaintEvent* event)
{
    QPushButton::paintEvent (event);
    QPainter _painter(this);
    int _nWidth  = width() -  10;
    int _nHeight = height() - 5;
    _painter.save();
    QPen _pen;
    _pen.setWidth(1);
    int _nIndex ;
    for(int i =  0 ; i < _nWidth  ; i++ )
    {
        _nIndex = (i * 255) / _nWidth ;
        _pen.setColor(QColor(m_aColorIndex[_nIndex][0] , m_aColorIndex[_nIndex][1] , m_aColorIndex[_nIndex][2]));
        _painter.setPen(_pen);
        _painter.drawLine( QPoint(i + 5.5 , 5) ,QPoint(i + 5.5 , _nHeight ));
    }
    _painter.restore();
}
