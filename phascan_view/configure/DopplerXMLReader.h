/***************************
  Name:  DopplerXMLReader
  Description:    用于加载XML格式文件
************************************/


#ifndef DOPPLERMATERIALSET_H
#define DOPPLERMATERIALSET_H

#include <QObject>


#include "Struct.h"

class DopplerXMLReader : public QObject
{
    Q_OBJECT
public:
    explicit DopplerXMLReader(QObject *parent = 0);
    static void LoadMaterial(QString* str_ ,  QList<MATERIAL*>* list_);
    static void LoadWedgeFile(QString* str_ , WEDGE_CONFIG* wedge_) ;
    static void LoadProbeFile(QString* str_ , PROBE_CONFIG* probe_) ;
    static void SaveWedgeFile(QString* str_ , WEDGE_CONFIG* wedge_) ;
    static void SaveProbeFile(QString* str_ , PROBE_CONFIG* probe_) ;
signals:

public slots:

};

#endif // DOPPLERMATERIALSET_H
