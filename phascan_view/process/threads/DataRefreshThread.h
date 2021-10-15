/************************************
  Description:   波形数据绘制线程
                 调用各显示窗口的绘图函数
************************************/



#ifndef DATAREFRESHTHREAD_H
#define DATAREFRESHTHREAD_H

#include <QThread>
#include <QList>


enum THREAD_RUN_MODE{
    RUN_IN_MAIN_THREAD = 0,
    RUN_IN_DRAW_THREAD
} ;

class DopplerDataView ;

class DataRefreshThread : public QThread
{
    Q_OBJECT
public:
    static DataRefreshThread* Instance();
    ~DataRefreshThread() ;
    void StopThread(bool bStop_ = true);
    bool IsStoped();
    void RunOnce(THREAD_RUN_MODE eMode_ = RUN_IN_MAIN_THREAD);
protected:
    explicit DataRefreshThread(QObject *parent = 0);
    void run();
    void UpdateAllWidgetDrawing() ;

    volatile bool m_bStop;
    volatile int  m_nRunOnce ;
    static DataRefreshThread* m_pThread ;

public slots:

};

#endif // DATAREFRESHTHREAD_H
