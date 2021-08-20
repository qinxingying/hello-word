﻿#ifndef DRAWDSCANFTHREAD_H
#define DRAWDSCANFTHREAD_H
#include <QThread>
#include <QList>

class DopplerDataView ;

class DrawDscanfTHread : public QThread
{
    Q_OBJECT
public:

    static DrawDscanfTHread* Instance();
    ~DrawDscanfTHread() ;
    void StopThread(bool bStop_ = true);
    bool IsStoped();
    void RunOnce();

protected:
    explicit DrawDscanfTHread(QObject *parent = 0);
    void run();
    void UpdateAllWidgetDrawing();

    static DrawDscanfTHread* _pThread ;
    volatile int  m_nRunOnce ;
signals:

public slots:
};

#endif // DRAWDSCANFTHREAD_H
