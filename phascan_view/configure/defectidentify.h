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
    bool analysisDefect();
    void getDefectInfo(int scanPos, QVector<QPointF> &MaxPoint, QVector<QRectF> &rect);
    void setLengthMeasureMethod(int methodId) {m_lengthMeasureMethod = methodId;}
    void setHeightMeasureMethod(int methodId) {m_heightMeasureMethod = methodId;}
    void getDefectInfo(QVector<QRectF> &rectL, QVector<QRectF> &rectH, QVector<int> &scanId, QVector<int> &lawId);
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
        QRect _rect;                // 缺陷范围
        specialDefect special;
        bool bMergedStatus;         // 若为true 表示被合并了，不需再考虑这个缺陷
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
    void calViA( int scanId, int lawId, float *pResult);
    void calDA( int scanId, int lawId, float *pResult);
    float getRectFArea(QRectF &rect) { return rect.width() * rect.height();}
    void getDefectInfo(int scanPos, QVector<QPointF> &MaxPoint, QVector<QRectF> &rect, QVector<defectRect> &defectRects);
    void findMaxSpecialDefect(int maxValue, const QVector<specialDefect> &specils, specialDefect &_out);
    void measureLength();
    void mergeDefects();
    void calDefectRect();

    int m_groupId;
    int m_pointQty;
    int m_lawQty;
    bool m_identifyDone;
    QMap<int, QVector<defectRect> > m_frameDefects;
    QVector<defectsBetweenFrames> m_defectsBetweenFrames;

    int m_lengthMeasureMethod {0};
    int m_heightMeasureMethod {0};
    float m_scale {0.5};
    QVector<QRectF> m_defectsRectL;
    QVector<QRectF> m_defectsRectH;
    QVector<int> m_scanIds; // 特征點所在幀
    QVector<int> m_lawIds; // 特征點所在beam
};

#endif // DEFECTIDENTIFY_H
