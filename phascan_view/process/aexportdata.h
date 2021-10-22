#ifndef AEXPORTDATA_H
#define AEXPORTDATA_H

#include <QObject>
#include <QThread>
#include "ParameterProcess.h"
#include "ProcessDisplay.h"

class AExportData : public QObject
{
    Q_OBJECT
public:
    explicit AExportData(QObject *parent = 0);
    void setGroupId(int groupId) {m_iCurGroup = groupId;}
signals:
    void done();
public slots:
    void saveBScanData(QString filePath);
    void saveCScanData(QString filePath);
    void saveReport(QString filePath);
protected:
    void getPixValueInfo(int nScanPos, setup_GATE_NAME eGate, U32* pBuff);
    void getPixValueDistance(U32* pBuff1 , U32* pBuff2, float GainScale, U32 gateHeight1, U32 gateHeight2);
    void getPixValuePos(U32* pBuff, U32* pBuff2, float gainScale, U32 gateHeight1);
private:
    void savePhaseReport(QString filePath, QString reportFormPath);
    void saveTofdReport(QString filePath, QString reportFormPath);
private:
    int m_iCurGroup {0};
    int m_num {0};
};

#endif // AEXPORTDATA_H
