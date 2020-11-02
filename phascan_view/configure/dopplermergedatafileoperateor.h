#ifndef DOPPLERMERGEDATAFILEOPERATEOR_H
#define DOPPLERMERGEDATAFILEOPERATEOR_H

#include <QObject>
#include "DopplerDataFileOperateor.h"

#define GROUP_INFO_MAX           8

class DopplerMergeDataFileOperateor : public QObject
{
    Q_OBJECT
public:
    explicit DopplerMergeDataFileOperateor(QObject *parent = nullptr);
    ~DopplerMergeDataFileOperateor();

    int TestData(const QStringList &lst);
    int TestMergeFile(const QStringList &lst);
    int TryWriteData(const QString &fileName);

    enum FORMATDATA{
        FORMATDATA_NONE = 0,
        FORMATDATA_I,
        FORMATDATA_II
    };

    struct dataIIInfo{
        uint groupQty;
        uint drivingType;
        uint rate;
        double resolution;
        double start;
        double end;
        int frameSize;
    };

private:
    int LoadDataI(const QStringList &lst);
    int LoadDataII(const QStringList &lst);
    int MergeFileI();
    int MergeFileII(const QStringList &lst);
    int WriteDataIToFile(const QString &fileName);
    int WriteDataIIToFile(const QString &fileName);
    int MergeDrawInfoPackAndGroupInfo();
    int MergeFileHead();
    int MergeData();
    int RectifyScanLength(unsigned char *);
    int GetTotalDataSize(int groupQty, int beamQty[], ushort pointQty[]) const;
    int GetGroupDataSize(int beamQty, ushort pointQty) const;

    void CreateBeamData();
    bool isDataII(QString& strPath, dataIIInfo &info);
private:
    int m_count;
    DopplerDataFileOperateor *m_pRFileOp;
    int m_nMaxFrameLen;
    int m_version;
    FORMATDATA m_DataType;

    INSPEC_DATA_FILE m_wFileHead;
    DRAW_INFO_PACK   m_wDrawInfoPack;
    GROUP_INFO       m_wGroupInfo[GROUP_INFO_MAX];
    unsigned char    *m_pWBeamData;
    QVector< dataIIInfo> m_dataIIinfo;
    QByteArray m_dataIIMark;
    QByteArray m_dataIISource;
};

#endif // DOPPLERMERGEDATAFILEOPERATEOR_H
