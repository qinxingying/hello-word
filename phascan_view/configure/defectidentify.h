#ifndef DEFECTIDENTIFY_H
#define DEFECTIDENTIFY_H

#include <QObject>
#include "ParameterProcess.h"
#define BEAMDIS 2
class DefectIdentify : public QObject
{
    Q_OBJECT
public:
    explicit DefectIdentify(int groupId, QObject *parent = 0);
    ~DefectIdentify();
    bool analysisData();
private:
    struct beamAmp{
        int lawId;
        int dataIndex;
    };
    struct beamData{
        int dataIndex;
        int value;
        int leftValue;
        int rightValue;
    };

    void captureBeamAmps( WDATA* Data, int lawId, int start, int width, int height, int beamdis, QVector<beamAmp> &beamAmps);
    beamData filterValue(QVector<beamData> &beamDatas, int maxValue);
    int m_groupId;
    bool m_identifyDone;
};

#endif // DEFECTIDENTIFY_H
