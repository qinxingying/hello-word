#ifndef AIDEDANALYSIS_H
#define AIDEDANALYSIS_H

#include <QObject>
#include <QVector>
class AidedAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit AidedAnalysis(QObject *parent = 0);
    void setGroupId( int groupId);
    void setRange( double scanStart, double scanStop, double widthStart, double widthStop);
    int  analysisDefect();
    void paintDefectImage(QImage* pImage);
    bool setSelectDefectIndex(int index);
    QVector<QPoint> getDefectCentre(){return defectInImage;}
private:
    void calculateSrcData();
    quint8 getDataMax();
private:
    struct SELECTRECTINFO{
        int pixelWidthStart;
        int pixelWidthStop;
        int pixelHeightStart;
        int pixelHeightStop;
    };

    int m_groupId;
    int scanPixel;
    int topcWidthPixel;
    double m_scanStart;
    double m_scanStop;
    double m_TopcWidthStart;
    double m_TopcWidthStop;
    quint8 m_dataMax;
    bool   m_dataMaxStatus;
    QVector<quint8> srcData;    //储存TOPC选取范围的原始值
    QVector<QPoint> defectCentre;
    QVector<QPoint> defectInImage;
    SELECTRECTINFO  slectRectInfo;
    unsigned char	(*m_pColor)[3];
};

#endif // AIDEDANALYSIS_H
