/***************************
  Name:  DopplerOverlays
  Copyright: Sheng Shen
  Date : 2013-08-26
  Description:   管理  数据显示窗口中 所有的 overlay
                 包括：
                   闸门   ， 当前声束 ， 光标 ， 厚度标识
                 .............
************************************/


#ifndef DOPPLEROVERLAYS_H
#define DOPPLEROVERLAYS_H

#include <QObject>
#include <DopplerView/DopplerDataView.h>
#include <DopplerView/DopplerViewItems.h>
#include <process/ParameterProcess.h>
#include <QVector>

class DopplerOverlays : public QObject
{
    Q_OBJECT
public:
    explicit DopplerOverlays(QObject *parent = 0);
    void CreateOverlays();
    void CreateOverlaysAH();
    void CreateOverlaysAV();
    void CreateOverlaysBH();
    void CreateOverlaysBV();
    void CreateOverlaysCH();
    void CreateOverlaysCV();
    void CreateOverlaysSS();
    void CreateOverlaysSA();
    void CreateOverlaysSL();
    void UpdateOverlays();
    void UpdateGate();
    void UpdateCursor() ;
    void GetCurrentLawMarkerPos(QVector<QLineF>* pVector_);
    void GetLawMarkers(QVector<QString>* pVector_) ;

protected:
	DopplerDataView*	m_pView ;
	DopplerConfigure*	m_pConfigure;
	ParameterProcess*	m_pProcess;
	int m_nGroup ;
    int m_nLaw   ;
    int m_eDisp  ;

signals:

public slots:

};

#endif // DOPPLEROVERLAYS_H
