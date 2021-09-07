#ifndef AEXPORTSCANDATATOEXCEL_H
#define AEXPORTSCANDATATOEXCEL_H

#include <QObject>
#include <QThread>
#include "ParameterProcess.h"
#include "ProcessDisplay.h"

class AExportScanDataToExcel : public QObject
{
    Q_OBJECT
public:
    explicit AExportScanDataToExcel(QObject *parent = 0);
    void setGroupId(int groupId) {m_iCurGroup = groupId;}
signals:
    void done();
public slots:
    void saveBScanData(QString filePath);
    void saveCScanData(QString filePath);
protected:
    void getPixValueInfo(int nScanPos, setup_GATE_NAME eGate, U32* pBuff);
    void getPixValueDistance(U32* pBuff1 , U32* pBuff2, float GainScale, U32 gateHeight1, U32 gateHeight2);
    void getPixValuePos(U32* pBuff, U32* pBuff2, float gainScale, U32 gateHeight1);
private:
    int m_iCurGroup {0};
};

#endif // AEXPORTSCANDATATOEXCEL_H
