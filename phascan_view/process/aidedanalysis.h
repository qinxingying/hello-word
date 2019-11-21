#ifndef AIDEDANALYSIS_H
#define AIDEDANALYSIS_H

#include <QObject>
#include <QVector>
#include "Instrument.h"
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
    void setOrient(VIEW_ORIENT orient){m_orient = orient;}
    QVector<QPoint> getDefectCentre(){return defectInImage;}
    QVector<QRect>  getDefectRect(){return RectInImage;}
private:
    void calculateSrcData();
    quint8 getDataMax();
    void getAmpData(int &leftAmp, int &rightAmp);
    void getAmpDataWatershed(int &leftAmp, int &rightAmp);
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
    QVector<QRect>  defectRect;
    QVector<QRect>  RectInImage;
    SELECTRECTINFO  slectRectInfo;
    unsigned char	(*m_pColor)[3];
    VIEW_ORIENT     m_orient;
};

#endif // AIDEDANALYSIS_H
