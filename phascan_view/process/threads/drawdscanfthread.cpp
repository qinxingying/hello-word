#include "drawdscanfthread.h"
#include "DataRefreshThread.h"
#include "DopplerDataView.h"
#include "gHeader.h"
#include <process/ParameterProcess.h>
#include <QtGlobal>
#include <QList>
#include <configure/DopplerConfigure.h>

DrawDscanfTHread::DrawDscanfTHread(QObject *parent) :
    QThread(parent)
{

}

DrawDscanfTHread::~DrawDscanfTHread(){}

DrawDscanfTHread* DrawDscanfTHread::_pThread =  NULL;

DrawDscanfTHread* DrawDscanfTHread::Instance()
{
    if (!_pThread)
    {
        _pThread= new DrawDscanfTHread() ;
    }
    return _pThread ;
}

/****************************************************************************
  Description: 刷新所有显示窗口数据
*****************************************************************************/
void DrawDscanfTHread::UpdateAllWidgetDrawing()
{
        static DopplerDataView* _pDraw ;
        QList<QWidget*>* _list = g_pMainWnd->GetCurrentDisplayTableWidgetList();

        if(_list && _list->count())
        {
            for(int i = 0 ;  i < _list->count() ; i++)
            {
                _pDraw = (DopplerDataView*)_list->at(i) ;
                _pDraw->UpdateDSDrawing();
            }
        }
}

void DrawDscanfTHread::run()
{

    QList<QWidget*>* _list = g_pMainWnd->GetCurrentDisplayTableWidgetList();
    if(!_list->count()) return ;

    UpdateAllWidgetDrawing() ;

}







