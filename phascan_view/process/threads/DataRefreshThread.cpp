#include "DataRefreshThread.h"
#include "DopplerDataView.h"
#include "gHeader.h"

#include <QtGlobal>
#include <QList>

DataRefreshThread* DataRefreshThread::m_pThread =  new DataRefreshThread ;

DataRefreshThread* DataRefreshThread::Instance()
{
    if (!m_pThread)
    {
        m_pThread= new DataRefreshThread() ;
    }
    return m_pThread ;
}

DataRefreshThread::DataRefreshThread(QObject *parent) :
    QThread(parent)
{
    m_bStop = false ;
    m_nRunOnce = 0 ;
}


DataRefreshThread::~DataRefreshThread(){}

void DataRefreshThread::StopThread(bool bStop_)
{
    m_bStop = bStop_ ;
}

void DataRefreshThread::run()
{
    QList<QWidget*>* _list = g_pMainWnd->GetCurrentDisplayTableWidgetList();
    if(!_list->count())  return ;
    // run once and get out
    if(m_nRunOnce)
    {
        msleep(0) ;
        UpdateAllWidgetDrawing() ;
        m_nRunOnce -- ;
        return ;
    }
    m_bStop = false ;
    while(!m_bStop)
    {
        UpdateAllWidgetDrawing() ;
        msleep(1000) ;
    }
}

#include <configure/DopplerConfigure.h>
/****************************************************************************
  Description: ˢ��������ʾ��������
*****************************************************************************/
void DataRefreshThread::UpdateAllWidgetDrawing()
{
    static DopplerDataView* _pDraw ;
    QList<QWidget*>* _list = g_pMainWnd->GetCurrentDisplayTableWidgetList();
    if(_list && _list->count())
    {
		for(int i = 0 ;  i < _list->count() ; i++)
        {
            _pDraw = (DopplerDataView*)_list->at(i) ;
            _pDraw->UpdateDrawing();
        }
    }
}

/****************************************************************************
  Name:  RunOnce
  Copyright: Sheng Shen
  Description:   ˢ����ʾ���ڲ��� 1 ��
*****************************************************************************/
void DataRefreshThread::RunOnce(THREAD_RUN_MODE eMode_)
{
    if(eMode_ == RUN_IN_MAIN_THREAD)
        UpdateAllWidgetDrawing() ;
    else
    {
        if(m_nRunOnce)
            m_nRunOnce = 1 ;
        else
            m_nRunOnce = 2 ;
        start();
    }
}
