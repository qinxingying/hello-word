#include "DopplerColorBar.h"
#include <QPainter>
#include <assert.h>


DopplerColorBar::DopplerColorBar(QWidget *parent) :
    QWidget(parent)
{
    assert(parent) ;
    setFixedWidth(DOPPLER_COLOR_BAR_WIDTH);
    color = NULL ;

    //************ set back ground color
    setAutoFillBackground(true);
    QPalette pal = this->palette() ;
    pal.setColor(QPalette::Background , QColor(0 , 0 , 255));
    setPalette(pal);
    setAcceptDrops(true);
}

void DopplerColorBar::setColorIndex(void* color_)
{
    color  = (unsigned char (*)[3])color_ ;
    update();
}

void DopplerColorBar::paintEvent(QPaintEvent* /*event*/)
{
    if(!color)  return  ;

    int i   , _nColor;
    int _nWidth = width() - 1;
    int _nHeight= height() - 1;
    QPainter _painter(this) ;

    for(i = 0 ; i<= _nHeight ; i++)
    {
        _nColor = 255 - i * 255 / _nHeight ;
        _painter.setPen(QPen(QColor(color[_nColor][0] , color[_nColor][1] , color[_nColor][2]))) ;
        _painter.drawLine(QPointF(0 , i) , QPointF(_nWidth , i));
    }
}
