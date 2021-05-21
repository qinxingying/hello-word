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
        AbsoluteSensitivity,
        TipDiffraction  // 端点衍射法
    };

    explicit DefectIdentify(int groupId, QObject *parent = 0);
    ~DefectIdentify();
    bool analysisData(int scanStart, int scanStop, int beamStart, int beamStop);
    bool analysisDefect();
    void getDefectInfo(int scanPos, QVector<QPointF> &MaxPoint, QVector<QRectF> &rect);
    void setLengthMeasureMethod(int methodId) {m_lengthMeasureMethod = methodId;}
    void setHeightMeasureMethod(int methodId) {m_heightMeasureMethod = methodId;}
    void setScale(double _scale) {m_scale = _scale / 100.0;}
    void getDefectInfo(QVector<QRectF> &rectL, QVector<QRectF> &rectH, QVector<int> &scanId, QVector<int> &lawId);
    void setRange(int scanStart, int scanStop, int beamStart, int beamStop);
    void setSscanRange(QRectF _recet);
    void setSscanRangeValid(bool _isValid);
    void setIdentifyStatus(bool status);
    void setAutoMerge(bool _merge) {m_bAutoMerge = _merge;}
private:
    struct beamAmp{
        int lawId;
        int dataIndex;
        int value;
    };
    struct defectRect{
        int valueMax;
        int valueMaxCount;  // 缺陷区域内最大值的个数
        beamAmp _rect[3];  //0 最高点 1 左下角点  2 右上角点
//        float _DARange[2];     // da范围
//        float _ViARange[2];    // ViA范围
        bool bMergeStatus;  // 标志是否合并
    };
    struct beamData{
        int lawId;
        int dataIndex;
        int value;
        int leftValue;
        int rightValue;
    };

    struct specialDefect {
        int valueMax;               // 特征点最大值
        int scanId;                 // 特征点所在帧
        defectRect specialRect;     // 特征点所在的缺陷
        QRectF rect;                // 特征点缺陷矩形框
    };

    struct defectsBetweenFrames {
        int scanIdStart;            // 需要测长方法确定
        int scanIdEnd;
        int length;                 // 缺陷长度
        QRectF _rect;                // 缺陷范围
        specialDefect special;      // 缺陷内所有特征点集合中最大的特征点
        QVector<specialDefect> allSpecial; // 缺陷内所有特征点集合
        bool bMergedStatus;         // 若为true 表示被合并了，不需再考虑这个缺陷
    };

    struct _Amp {
        int lawId;
        int scanId;
        float value;
    };

    void captureBeamAmps( WDATA* Data, int lawId, int start, int width, int height, int beamdis, QMap<int, QVector<beamData> > &beamAmps);
//    void filterSameDefect(QVector<defectRect> &defectRects, QVector<defectRect> &_Rects);
    void captrueFrameAmps( int scanId, int beamdis, QMap<int, QVector<beamData> > &beamAmps, WDATA* Data);
    beamData filterValue(const QVector<beamData> &beamDatas, int maxValue, int *maxValueCount = nullptr);
    int findMaxValue(const QVector<beamData> &beamDatas);
    void findAllPeakDatas(const QVector<beamData> &beamDatas, QVector<beamData> &peakDatas);
    void findRectBorder( WDATA* Data, int maxValue, int beamdis, beamAmp *borders, const QVector<beamData> &data);
    void findMaxValueAndPos( WDATA* Data, int start, int end, int &value, int &postion);
    void transformPolarToCartesian(int lawId, int dataIndex, QPointF &postion);
    float transformCartesianToPolar(int lawId, float _xPos);
    void calViA( int scanId, int lawId, float *pResult);
    void calDA( int scanId, int lawId, float *pResult);
    float getRectFArea(QRectF &rect) { return rect.width() * rect.height();}
    void getDefectInfo(int scanPos, QVector<QPointF> &MaxPoint, QVector<QRectF> &rect, QVector<defectRect> &defectRects);
    void findMaxSpecialDefect(int maxValue, const QVector<specialDefect> &specils, specialDefect &_out);
    void measureLength();
    void mergeDefects();
    void calDefectRect();
    void forceMerge();
    void tipDiffractionMeasureHeight(specialDefect &_defect);
    int transformDistMmToDotPos(float fDist_);
    void mergeDefectsTipDiffraction();

    int m_groupId;
    int m_pointQty;
    int m_lawQty;
    bool m_identifyDone;
    QMap<int, QVector<defectRect> > m_frameDefects;
    QVector<defectsBetweenFrames> m_defectsBetweenFrames;

    int m_lengthMeasureMethod {0};
    int m_heightMeasureMethod {0};
    float m_scale {0.5};
    bool m_bAutoMerge {false};
    QVector<QRectF> m_defectsRectL; // 长度方向，表现在C扫上
    QVector<QRectF> m_defectsRectH; // 高度方向，表现在S扫上
    QVector<int> m_scanIds; // 特征點所在幀
    QVector<int> m_lawIds; // 特征點所在beam

    int m_scanStart {0};
    int m_scanStop  {0};
    int m_beamStart {0};
    int m_beamStop  {0};
    QRectF m_rectSscan;
    bool m_bSscanRangeIsSet {false};
};

#endif // DEFECTIDENTIFY_H
