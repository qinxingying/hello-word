#ifndef DEFECTIDENTIFY_H
#define DEFECTIDENTIFY_H

#include <QObject>
#include "ParameterProcess.h"
#include <QMap>
#define BEAMDIS 1   // 判断两个点是否相关的阈值，单位mm
class DefectIdentify : public QObject
{
    Q_OBJECT
public:
    enum {
        HalfWave = 0,
        EndPointHalfWave,
        AbsoluteSensitivity
    };

    explicit DefectIdentify(int groupId, QObject *parent = 0);
    ~DefectIdentify();
    bool analysisData();
    void getDefectInfo(int scanPos, QVector<QPointF> &MaxPoint, QVector<QRectF> &rect);
    void setLengthMeasureMethod(int methodId) {m_lengthMeasureMethod = methodId;}
    void setHeightMeasureMethod(int methodId) {m_heightMeasureMethod = methodId;}
private:
    struct beamAmp{
        int lawId;
        int dataIndex;
        int value;
    };
    struct defectRect{
        int valueMax;
        beamAmp _rect[3];  //0 最高点 1 左下角点  2 右上角点
    };
    struct beamData{
        int lawId;
        int dataIndex;
        int value;
        int leftValue;
        int rightValue;
    };
    void captureBeamAmps( WDATA* Data, int lawId, int start, int width, int height, int beamdis, QMap<int, QVector<beamData> > &beamAmps);
    void captrueFrameAmps( int scanId, int beamdis, QMap<int, QVector<beamData> > &beamAmps, WDATA* Data);
    beamData filterValue(const QVector<beamData> &beamDatas, int maxValue);
    int findMaxValue(const QVector<beamData> &beamDatas);
    void findAllPeakDatas(const QVector<beamData> &beamDatas, QVector<beamData> &peakDatas);
    void findRectBorder( WDATA* Data, int maxValue, int beamdis, beamAmp *borders, const QVector<beamData> &data);
    void findMaxValueAndPos( WDATA* Data, int start, int end, int &value, int &postion);
    void transformPolarToCartesian(int lawId, int dataIndex, QPointF &postion);

    int m_groupId;
    int m_pointQty;
    int m_lawQty;
    bool m_identifyDone;
    QMap<int, QVector<defectRect> > m_frameDefects;

    int m_lengthMeasureMethod {0};
    int m_heightMeasureMethod {0};
};

#endif // DEFECTIDENTIFY_H
