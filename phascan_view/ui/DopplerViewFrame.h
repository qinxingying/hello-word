
/************************
  Name:  DopplerViewFrame
  Copyright: Sheng Shen
  Date : 2013-08-26
  Description:   显示窗口的父窗口  提供拖拽功能
                 .............
************************/

#ifndef DopplerViewFrame_H
#define DopplerViewFrame_H

#include <QWidget>
#include <QList>
#include <QSize>





class QDragEnterEvent  ;
class QDragLeaveEvent  ;
class QDropEvent       ;
class DopplerViewFrame : public QWidget
{
    Q_OBJECT
public:
    explicit DopplerViewFrame(QWidget *parent = 0);
    ~DopplerViewFrame();
protected:
    void dragEnterEvent(QDragEnterEvent *)  ;
    void dragLeaveEvent(QDragLeaveEvent *)  ;
    void dropEvent(QDropEvent *)  ;

    void DropEventProcess(QDropEvent* event)  ;
public:
    void CreateDrawView(int nGroupId_, int nId_);
	void SetViewFrameId(int nId_) {m_nId = nId_;}

protected:
	int    m_nId;

signals:
    void signalDropEvent(int)  ;
    void signalCreateDrawWindow(QWidget* posWidget_ , int nId_ , int nGroupId_) ;
public slots:
    void slotCreateDrawWindow(QWidget* posWidget_ , int nId_ , int nGroupId_) ;

};

#endif // DOPPLERDROPVIEW_H
