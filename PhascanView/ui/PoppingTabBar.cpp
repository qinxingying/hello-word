#include "PoppingTabBar.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QSize>
#include <QWheelEvent>

PoppingTabBar::PoppingTabBar(QWidget *parent) : QTabBar(parent)
{
}

void PoppingTabBar::mouseDoubleClickEvent(QMouseEvent* event) 
{
    if(event->button() == Qt::LeftButton)
    {
        int _nId = tabAt(event->pos()) ;
        if(_nId < count() - 1)
        {
            emit shrink();
            event->ignore();
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        int _nId = tabAt(event->pos()) ;
        if(_nId == currentIndex())
            emit signalRightButtonDoubleClicked(_nId) ;
    }
}

void PoppingTabBar::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {

        int _nId = tabAt(event->pos()) ;
        if(_nId == count() - 1)
            emit signalLastTabButton(event->button());
        else
        {
            emit extend();
            QTabBar::mousePressEvent(event);
        }
    }
}

void PoppingTabBar::wheelEvent(QWheelEvent* event)
{
    //return ;
    //取消掉鼠标中键滚动
    int _nDegrees = event->delta() / 8;
    int _nSteps = _nDegrees / 15;
    int _nId  = currentIndex()  ;
    int _nQty = count() - 2;
    if(_nSteps > 0)
    {
        _nId-- ;
        if(_nId < 0)  _nId = _nQty  ;
    }
    else
    {
        _nId++ ;
        if(_nId > _nQty)  _nId = 0 ;
    }
    setCurrentIndex (_nId) ;

}
