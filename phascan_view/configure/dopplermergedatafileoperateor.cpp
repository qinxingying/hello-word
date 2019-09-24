#include <QMessageBox>
#include "dopplermergedatafileoperateor.h"
#include "const.h"

DopplerMergeDataFileOperateor::DopplerMergeDataFileOperateor(QObject *parent)
    : QObject(parent)
    , m_count(-1)
    , m_pRFileOp(nullptr)
    , m_nMaxFrameLen(-1)
    , m_pWBeamData(nullptr)
{
    memset(&m_wFileHead, 0, sizeof (INSPEC_DATA_FILE));
    memset(&m_wDrawInfoPack, 0, sizeof(DRAW_INFO_PACK));
    memset(m_wGroupInfo, 0, sizeof(GROUP_INFO) * GROUP_INFO_MAX);
}

DopplerMergeDataFileOperateor::~DopplerMergeDataFileOperateor()
{
    if (m_pRFileOp) {
        delete []m_pRFileOp;
        m_pRFileOp = nullptr;
    }
}

int DopplerMergeDataFileOperateor::LoadData(const QStringList &lst)
{
    if (lst.isEmpty()) return -1;

    m_count = lst.size();
    m_pRFileOp = new DopplerDataFileOperateor[m_count];
    for (int i = 0; i < m_count; i ++) {
        int ret = m_pRFileOp[i].LoadDataFile(const_cast<QString &>(lst.at(i)));
        if(ret)  return -1;
    }

    return 0;
}

int DopplerMergeDataFileOperateor::MergeDrawInfoPackAndGroupInfo()
{
    if (m_count <= 1) return -1;

    int mergeGroupNum = 0;
    for (int i = 0; i < m_count; i ++) {
        if (0 == i) {
            m_wDrawInfoPack.nScanStart = m_pRFileOp[i].GetDrawInfo()->nScanStart;
            m_wDrawInfoPack.nScanEnd = m_pRFileOp[i].GetDrawInfo()->nScanEnd;
            m_wDrawInfoPack.nScanResolution = m_pRFileOp[i].GetDrawInfo()->nScanResolution;
            m_wDrawInfoPack.nInspecStart = m_pRFileOp[i].GetDrawInfo()->nInspecStart;
            m_wDrawInfoPack.nInspecEnd = m_pRFileOp[i].GetDrawInfo()->nInspecEnd;
            m_wDrawInfoPack.nInspecResolution = m_pRFileOp[i].GetDrawInfo()->nInspecResolution;
            m_wDrawInfoPack.nEncodeType = m_pRFileOp[i].GetDrawInfo()->nEncodeType;
            memcpy(m_wDrawInfoPack.bScanMark, m_pRFileOp[i].GetDrawInfo()->bScanMark, setup_MAX_REC_LEN);
        } else {
           if (m_wDrawInfoPack.nEncodeType != m_pRFileOp[i].GetDrawInfo()->nEncodeType) return - 2;
           if (m_wDrawInfoPack.nScanResolution != m_pRFileOp[i].GetDrawInfo()->nScanResolution) return -3;
           if (m_wDrawInfoPack.nInspecResolution != m_pRFileOp[i].GetDrawInfo()->nInspecResolution) return -4;

           if (m_wDrawInfoPack.nScanStart > m_pRFileOp[i].GetDrawInfo()->nScanStart) {
               m_wDrawInfoPack.nScanStart = m_pRFileOp[i].GetDrawInfo()->nScanStart;
           }
           if (m_wDrawInfoPack.nScanEnd < m_pRFileOp[i].GetDrawInfo()->nScanEnd) {
               m_wDrawInfoPack.nScanEnd = m_pRFileOp[i].GetDrawInfo()->nScanEnd;
           }

           if (m_wDrawInfoPack.nInspecStart > m_pRFileOp[i].GetDrawInfo()->nInspecStart) {
               m_wDrawInfoPack.nInspecStart = m_pRFileOp[i].GetDrawInfo()->nInspecStart;
           }
           if (m_wDrawInfoPack.nInspecEnd < m_pRFileOp[i].GetDrawInfo()->nInspecEnd) {
               m_wDrawInfoPack.nInspecEnd = m_pRFileOp[i].GetDrawInfo()->nInspecEnd;
           }
           for (int var = 0; var < setup_MAX_REC_LEN; ++var) {
               if (m_wDrawInfoPack.bScanMark[var] == 0xff) continue ;
               if (m_pRFileOp[i].GetDrawInfo()->bScanMark[var] == 0) break ;
               m_wDrawInfoPack.bScanMark[var] = m_pRFileOp[i].GetDrawInfo()->bScanMark[var];
           }
        }
        int groupNum = m_pRFileOp[i].GetDrawInfo()->nGroupNum;
        mergeGroupNum += groupNum;
        if (mergeGroupNum > GROUP_INFO_MAX) {
            QMessageBox::information(NULL, "merge Group number.", "Maximum 8 group");
            return -1;
        }
        for (int j = 0; j < groupNum; j ++) {
            m_wDrawInfoPack.nBeamNum[mergeGroupNum + j - 1] = m_pRFileOp[i].GetDrawInfo()->nBeamNum[j];
            memcpy(&(m_wGroupInfo[mergeGroupNum + j -1]),
                    m_pRFileOp[i].GetGroupInfo(j), sizeof (GROUP_INFO));
        }

    }
    m_wDrawInfoPack.nGroupNum = mergeGroupNum;

    return 0;
}

int DopplerMergeDataFileOperateor::MergeFileHead()
{
    if (m_count <= 1) return -1;

    m_wFileHead.type = m_pRFileOp[0].GetFileHeader()->type;
    m_wFileHead.size = sizeof(INSPEC_DATA_FILE) + sizeof (DRAW_INFO_PACK)
                       + sizeof (GROUP_INFO) * m_wDrawInfoPack.nGroupNum;

    int groupQty = m_wDrawInfoPack.nGroupNum;
    int beamQty[GROUP_INFO_MAX] = {0};
    ushort pointQty[GROUP_INFO_MAX] = {0};
    for (int i = 0; i < groupQty; i ++) {
        beamQty[i] = m_wDrawInfoPack.nBeamNum[i];
        pointQty[i] = m_wGroupInfo[i].point_qty;
    }
    int _nFrameSize = GetTotalDataSize(groupQty, beamQty, pointQty);
    float fScanStart = 0.0;
    float fScanStop  = 0.0;
    float fScanStep  = 0.0;
    if(m_wDrawInfoPack.nEncodeType) {
        fScanStart  =  m_wDrawInfoPack.nScanStart		/ 1000.0;
        fScanStop	=  m_wDrawInfoPack.nScanEnd		    / 1000.0;
        fScanStep	=  m_wDrawInfoPack.nScanResolution   / 1000.0;
    } else {
        fScanStop	=  m_wDrawInfoPack.nScanEnd / 1000.0  ;
        fScanStep	=  1 ;
    }
    m_nMaxFrameLen = (fScanStop - fScanStart) / fScanStep + 1.5 ;
    m_wFileHead.reserved = m_nMaxFrameLen * _nFrameSize;

    m_wFileHead.version = m_wFileHead.size + m_wFileHead.reserved;
    return 0;
}

int DopplerMergeDataFileOperateor::MergeData()
{
    if (m_count <= 1) return -1;

    CreateBeamData();

    int groupQty = m_wDrawInfoPack.nGroupNum;
    int wbeamQty[GROUP_INFO_MAX] = {0};
    ushort wpointQty[GROUP_INFO_MAX] = {0};
    for (int i = 0; i < groupQty; i ++) {
        wbeamQty[i] = m_wDrawInfoPack.nBeamNum[i];
        wpointQty[i] = m_wGroupInfo[i].point_qty;
    }
    int wFrameSize = GetTotalDataSize(groupQty, wbeamQty, wpointQty);

    int iMax = RectifyScanLength(m_wDrawInfoPack.bScanMark);
    int wGroupOffset = 0;
    int mergeGroupNum = 0;
    for (int i = 0; i < m_count; i ++) {
        int groupNum = m_pRFileOp[i].GetDrawInfo()->nGroupNum;
        int rbeamQty[GROUP_INFO_MAX] = {0};
        ushort rpointQty[GROUP_INFO_MAX] = {0};
        for (int m = 0; m < groupNum; m ++) {
            rbeamQty[m] = m_pRFileOp[i].GetDrawInfo()->nBeamNum[m];
            rpointQty[m] = m_pRFileOp[i].GetGroupInfo(m)->point_qty;
        }
        int rFrameSize = GetTotalDataSize(groupNum, rbeamQty, rpointQty);
        mergeGroupNum += groupNum;

        int rGroupOffset = 0;
        for (int j = 0; j < groupNum; j ++) {
            int rbeams = rbeamQty[j];
            int rPoints = rpointQty[j];
            int beamSize = setup_DATA_PENDIX_LENGTH + rPoints;
            for (int k = 0; k < rbeams; k ++) {
                for (int frameIndex = 0; frameIndex < iMax; ++frameIndex) {
                    int iRMax = RectifyScanLength(m_pRFileOp[i].GetDrawInfo()->bScanMark);
                    if (frameIndex >= iRMax) break;
                    unsigned char *pRBeamData = m_pRFileOp[i].GetData()
                                                + frameIndex * rFrameSize
                                                + rGroupOffset
                                                + k * beamSize;
                    unsigned char *pWBeamData = m_pWBeamData
                                                + frameIndex * wFrameSize
                                                + wGroupOffset
                                                + k * beamSize;
                    memcpy(pWBeamData, pRBeamData, beamSize);

                }
            }
            int rGroupSize = GetGroupDataSize(rbeams, rPoints);
            rGroupOffset += rGroupSize;
            int wGroupId = mergeGroupNum + j - 1;
            int wGroupSize = GetGroupDataSize(wbeamQty[wGroupId],
                                                wpointQty[wGroupId]);
            wGroupOffset += wGroupSize;
        }
    }
    return 0;
}

int DopplerMergeDataFileOperateor::RectifyScanLength(unsigned char *bScanMark)
{
    int _iMax = m_nMaxFrameLen;
    for(int i = m_nMaxFrameLen; i >= 0; i--)
    {
        if(bScanMark[i])
        {
            _iMax = i;
            break;
        }
    }

    return _iMax+1;
}

int DopplerMergeDataFileOperateor::GetTotalDataSize(int groupQty,
                                                    int beamQty[],
                                                    ushort pointQty[]) const
{
    int _nRet = setup_DATA_OFFSET ;
    for(int i = 0 ; i < groupQty ; i++)
    {
        if (beamQty[i] == 0) continue ;
        _nRet += GetGroupDataSize(beamQty[i], pointQty[i]) ;
    }
    _nRet  = (_nRet + setup_DATA_ALIAN - 1) / setup_DATA_ALIAN  ;
    _nRet  = setup_DATA_ALIAN * _nRet ;
    return _nRet ;
}

int DopplerMergeDataFileOperateor::GetGroupDataSize(int beamQty, ushort pointQty) const
{
    int _nRet = (setup_DATA_PENDIX_LENGTH + pointQty) * beamQty  ;
    return _nRet;
}

void DopplerMergeDataFileOperateor::CreateBeamData()
{
    try {
       m_pWBeamData = new unsigned char[m_wFileHead.reserved];
    } catch (...) {

    }

    if (nullptr == m_pWBeamData) {
        QMessageBox::information(NULL, "memory is not enough.", "need to change PC");
        return ;
    }
    memset(m_pWBeamData, 0x00, m_wFileHead.reserved);
}

int DopplerMergeDataFileOperateor::MergeFile()
{
    if (m_count <= 1) return -1;

    int _nRet = MergeDrawInfoPackAndGroupInfo();
    if (_nRet < 0) return _nRet;

    _nRet = MergeFileHead();
    if (_nRet < 0) return _nRet;

    _nRet = MergeData();
    if (_nRet < 0) return _nRet;
    return 0;
}

int DopplerMergeDataFileOperateor::WriteDataToFile(const QString &fileName)
{
    Q_ASSERT_X(!fileName.isNull(),
               "DopplerMergeDataFileOperateor::WriteDataToFile", "The file name is NULL");
    Q_ASSERT_X(!fileName.isEmpty(),
               "DopplerMergeDataFileOperateor::WriteDataToFile", "The file name is empty");

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return -6;
    }
    file.write((char *)&m_wFileHead, sizeof(INSPEC_DATA_FILE));
    file.write((char *)&m_wDrawInfoPack, sizeof(DRAW_INFO_PACK));
    file.write((char*)m_wGroupInfo,sizeof(GROUP_INFO) * m_wDrawInfoPack.nGroupNum);
//    if (m_type == EXTEND_BEAM_QTY) {
//        file.write((char *)m_extendGroupInfoArr, sizeof(EXTEND_GROUP_INFO)*m_drawInfoPack.nGroupNum);
//    }
    file.write((char *)m_pWBeamData, m_wFileHead.reserved);
    unsigned char cEndFile = 0xfe;
    file.write((char*)&cEndFile,1);
    file.close();
    return 0;
}
