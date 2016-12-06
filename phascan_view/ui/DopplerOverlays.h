/***************************
  Name:  DopplerOverlays
  Date : 2013-08-26
  Description:   ����  ������ʾ������ ���е� overlay
                 ������
                   բ��   �� ��ǰ���� �� ��� �� ��ȱ�ʶ
                 .............
************************************/


#ifndef DOPPLEROVERLAYS_H
#define DOPPLEROVERLAYS_H

#include "DopplerDataView.h"
#include "DopplerViewItems.h"
#include "ParameterProcess.h"

#include <QObject>
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
