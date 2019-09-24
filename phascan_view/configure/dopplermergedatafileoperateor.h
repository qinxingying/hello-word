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

    int  LoadData(const QStringList &lst);
    int  MergeFile();
    int WriteDataToFile(const QString &fileName);

private:
    int MergeDrawInfoPackAndGroupInfo();
    int MergeFileHead();
    int MergeData();

    int RectifyScanLength(unsigned char *);
    int  GetTotalDataSize(int groupQty, int beamQty[], ushort pointQty[]) const;
    int  GetGroupDataSize(int beamQty, ushort pointQty) const;
    void CreateBeamData();
private:
    int m_count;
    DopplerDataFileOperateor *m_pRFileOp;
    int m_nMaxFrameLen;
    int m_version;

    INSPEC_DATA_FILE m_wFileHead;
    DRAW_INFO_PACK   m_wDrawInfoPack;
    GROUP_INFO       m_wGroupInfo[GROUP_INFO_MAX];
    unsigned char    *m_pWBeamData;
};

#endif // DOPPLERMERGEDATAFILEOPERATEOR_H
