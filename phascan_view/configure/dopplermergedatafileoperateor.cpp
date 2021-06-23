#include <QMessageBox>
#include "dopplermergedatafileoperateor.h"
#include "const.h"
#include <config_phascan_ii/config.h>

DopplerMergeDataFileOperateor::DopplerMergeDataFileOperateor(QObject *parent)
    : QObject(parent)
    , m_count(-1)
    , m_pRFileOp(nullptr)
    , m_nMaxFrameLen(-1)
    , m_version(0)
    , m_DataType(FORMATDATA_NONE)
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

int DopplerMergeDataFileOperateor::LoadDataI(const QStringList &lst)
{
    if (lst.isEmpty()) return -1;

    m_count = lst.size();
    if(m_count > 8){
        return -1;
    }
    m_pRFileOp = new DopplerDataFileOperateor[m_count];
    for (int i = 0; i < m_count; i ++) {
        int ret = m_pRFileOp[i].LoadDataFile(const_cast<QString &>(lst.at(i)));
        if(ret)  return -1;
        INSPEC_DATA_FILE *pHeader = m_pRFileOp[0].GetFileHeader();
        int version = pHeader->version;
        int size = pHeader->size;
        int reserved = pHeader->reserved;
        int swVersion = version - size - reserved;
        if (i == 0) {
            m_version = swVersion;
        } else {
            if (m_version != swVersion) return -1;
        }
    }
    if(m_version == 6 || m_version == 7){
        m_version -= 2;
    }
    m_DataType = FORMATDATA_I;
    return 0;
}

int DopplerMergeDataFileOperateor::LoadDataII(const QStringList &lst)
{
    if (lst.isEmpty()) return -1;

    m_count = lst.size();
    if(m_count > 8){
        return -1;
    }
    m_dataIIinfo.resize(m_count);
    for(int i = 0; i < m_count; i++){
        if( !isDataII(const_cast<QString &>(lst.at(i)), m_dataIIinfo[i])){
            return -1;
        }
    }
    m_DataType = FORMATDATA_II;
    return 0;
}

bool DopplerMergeDataFileOperateor::isDataII(QString& strPath, dataIIInfo &info)
{
    QFile file(strPath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    if(!Config::instance()->is_phascan_ii_file(file)){
        return false;
    }

    quint64 len = 0;
    file.read((char *)&len, sizeof(len));
    QByteArray data = file.read(len);
    QFile tmp("mercury.cfg");
    if (!tmp.open(QIODevice::WriteOnly|QIODevice::Truncate)) {
        return false;
    }
    tmp.write(data);
    tmp.close();
    QSettings src("mercury.cfg", QSettings::defaultFormat());
    info.groupQty = src.value("GroupQty").toUInt();
    QVariantMap map = src.value("Scanner").toMap();
    if(map["Mode"].toUInt() != 0){
        return false;
    }
    info.rate = map["Rate"].toUInt();

    QVariantMap scanmap = map["ScanAxis"].toMap();
    info.drivingType = scanmap["Driving"].toUInt();
    info.start = scanmap["Start"].toDouble();
    info.end = scanmap["End"].toDouble();
    info.resolution = scanmap["Resolution"].toDouble();
    info.frameSize = 0;
    for(uint i = 0; i < info.groupQty; i++){
        QVariantMap groupMap = src.value(QString("Group%1").arg(i)).toMap();
        uint groupMode = groupMap["Mode"].toUInt();
        QVariantMap SampleMap = groupMap["Sample"].toMap();
        int pointQty = SampleMap["PointQty"].toInt();
        QVariantMap FocallawerMap = groupMap["Focallawer"].toMap();
        uint scanMode = FocallawerMap["ScanMode"].toUInt();
        bool coupling = FocallawerMap["Coupling"].toBool();
        QVariantMap ScanMap = FocallawerMap["Scan"].toMap();
        int groupDataSize = 0;
        if(groupMode == 1){
            if(scanMode == 0){//线扫
                uint elemStart = ScanMap["PriStartElem"].toUInt();
                uint elemStop = ScanMap["PriStopElem"].toUInt();
                uint elemStep = ScanMap["PriElemStep"].toUInt();
                uint priApe = ScanMap["PriApe"].toUInt();
                int ret = (elemStop - elemStart - priApe + 1) / elemStep + 1;
                if(coupling){
                    ret++;
                }
                groupDataSize = ret * (pointQty + setup_DATA_PENDIX_LENGTH);
            }else if(scanMode == 1){//扇扫
                double angleStart = ScanMap["RefractStartAngle"].toDouble();
                double angleStop = ScanMap["RefractStopAngle"].toDouble();
                double angleStep = ScanMap["RefractStepAngle"].toDouble();
                int ret = (angleStop - angleStart) / angleStep + 1;
                if(coupling){
                    ret++;
                }
                groupDataSize = ret * (pointQty + setup_DATA_PENDIX_LENGTH);
            }else{//全聚焦
                int colQty = ScanMap["ColQty"].toInt();
                int rowQty = ScanMap["RowQty"].toInt();
                groupDataSize = colQty * ( rowQty + setup_DATA_PENDIX_LENGTH);
            }
        }else{
            int ret = 1;
            if(coupling){
                ret++;
            }
            groupDataSize = ret*(pointQty + setup_DATA_PENDIX_LENGTH);
        }
        info.frameSize += groupDataSize;
    }
    QFile::remove("mercury.cfg");
    return true;
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
            memcpy(m_wDrawInfoPack.bScanMark, m_pRFileOp[i].GetDrawInfo()->bScanMark, SETUP_SCAN_MARK_PHASCAN_I);
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
           for (int var = 0; var < SETUP_SCAN_MARK_PHASCAN_I; ++var) {
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

    m_wFileHead.version = m_wFileHead.size + m_wFileHead.reserved + m_version;
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

int  DopplerMergeDataFileOperateor::TestData(const QStringList &lst)
{
    int ret = LoadDataI(lst);
    if(ret != 0){
        ret = LoadDataII(lst);
    }
    return ret;
}

int DopplerMergeDataFileOperateor::TestMergeFile(const QStringList &lst)
{
    int ret = -1;
    switch (m_DataType) {
    case FORMATDATA_I:
        ret = MergeFileI();
        break;
    case FORMATDATA_II:
        ret = MergeFileII(lst);
        break;
    default:
        break;
    }
    return ret;
}

int DopplerMergeDataFileOperateor::TryWriteData(const QString &fileName)
{
    int ret = -1;
    switch (m_DataType) {
    case FORMATDATA_I:
        ret = WriteDataIToFile(fileName);
        break;
    case FORMATDATA_II:
        ret = WriteDataIIToFile(fileName);
        break;
    default:
        break;
    }
    return ret;
}

int DopplerMergeDataFileOperateor::MergeFileI()
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

int DopplerMergeDataFileOperateor::MergeFileII(const QStringList &lst)
{
    if (m_count <= 1) return -1;
    uint groupqty = m_dataIIinfo[0].groupQty;
    double start = m_dataIIinfo[0].start;
    double end = m_dataIIinfo[0].end;
    double range = end - start;

    for(int i = 1; i < m_count; i++){
        groupqty += m_dataIIinfo[i].groupQty;
        if(m_dataIIinfo[i].drivingType != m_dataIIinfo[0].drivingType){
            return -1;
        }
        if(m_dataIIinfo[i].drivingType == 0 && m_dataIIinfo[i].rate != m_dataIIinfo[0].rate){
            return -1;
        }
        if(m_dataIIinfo[i].drivingType != 0 && m_dataIIinfo[i].resolution != m_dataIIinfo[0].resolution){
            return -1;
        }
        if( m_dataIIinfo[i].end -  m_dataIIinfo[i].start > range){
            start = m_dataIIinfo[i].start;
            end = m_dataIIinfo[i].end;
            range = end - start;
        }
    }

    if(groupqty > 8){
        return -1;
    }

    QVector<QByteArray> dataIIMark;
    QVector<QByteArray> dataIISource;
    QVector<int> srcframeSize;
    srcframeSize.resize(m_count);
    QVector<int> dstframeSize;
    dstframeSize.resize(m_count);
    int lastGroupIndex = 0;
    quint64 markLen = 0;
    QFile tmpbuff("merge.cfg");
    if(!tmpbuff.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        return false;
    }
    tmpbuff.close();
    QSettings dst("merge.cfg",QSettings::defaultFormat());
    for(int i = 0; i < m_count; i++){
        QFile file(const_cast<QString &>(lst.at(i)));
        file.open(QIODevice::ReadOnly);
        quint64 len = 0;
        quint64 sMarkLen = 0;
        file.read((char *)&len, sizeof(len));
        QByteArray data = file.read(len);
        QFile tmp("mercury.cfg");
        if (!tmp.open(QIODevice::WriteOnly|QIODevice::Truncate)) {
            return false;
        }
        tmp.write(data);
        tmp.close();
        QSettings src("mercury.cfg", QSettings::defaultFormat());
        if(i == 0){
            src.setValue("GroupQty", groupqty);
            QVariantMap map = src.value("Scanner").toMap();
            QVariantMap scanmap = map["ScanAxis"].toMap();
            scanmap["Start"] = start;
            scanmap["End"] = end;
            map["ScanAxis"] = scanmap;
            src.setValue("Scanner", map);
            QStringList keys = src.allKeys();
            foreach (QString key, keys) {
                dst.setValue(key, src.value(key));
            }
            //lastGroupIndex += m_dataIIinfo[i].groupQty;
        }else{
            for(uint j = 0; j < m_dataIIinfo[i].groupQty; j++){
                QVariantMap map = src.value(QString("Group%1").arg(j)).toMap();
                dst.setValue(QString("Group%1").arg(j + lastGroupIndex), map);
            }
        }
        lastGroupIndex += m_dataIIinfo[i].groupQty;
        QFile::remove("mercury.cfg");

        file.read((char *)&len, sizeof(len));
        dataIIMark.append(file.read(len));
        sMarkLen = len;
        if(markLen < len){
            markLen = len;
        }

        file.read((char *)&len, sizeof(len));
        dataIISource.append(file.read(len));
        srcframeSize[i] = len / sMarkLen;
        file.close();
    }

    m_dataIIMark.resize(markLen);
    memset(m_dataIIMark.data(), 0x00, markLen);
    char *dstPtr = m_dataIIMark.data();
    for(int i = 0; i < m_count; i++){
        char *srcPtr = dataIIMark[i].data();
        for(int j = 0; j < dataIIMark[i].size(); j++){
            if(srcPtr[j]){
                dstPtr[j] = srcPtr[j];
            }

        }
    }

    int dstFrame = 0;
    for(int i = 0; i < m_count; i++){
        dstFrame += m_dataIIinfo[i].frameSize;
    }
    //字节对齐
    dstFrame = (dstFrame + 4 - 1) / 4;
    dstFrame  = 4 * dstFrame;

    quint64 sourceLen = dstFrame * markLen;
    m_dataIISource.resize(sourceLen);
    memset(m_dataIISource.data(), 0x00, sourceLen);

    int dstGroupOffset = 0;
    for(int i = 0; i < m_count; i++){
        char *dstDataPtr = m_dataIISource.data() + dstGroupOffset;
        char *markPtr = dataIIMark[i].data();
        int cpDataSize = m_dataIIinfo[i].frameSize;
        char *srcPtr = dataIISource[i].data();
        int srcFrameOffset = srcframeSize[i];
        for(int j = 0; j < dataIIMark[i].size(); j++){
            if(markPtr[j]){
                memcpy(dstDataPtr, srcPtr, cpDataSize);
            }
            srcPtr += srcFrameOffset;
            dstDataPtr += dstFrame;
        }
        dstGroupOffset += m_dataIIinfo[i].frameSize;
    }

    return 0;
}

int DopplerMergeDataFileOperateor::WriteDataIToFile(const QString &fileName)
{
    Q_ASSERT_X(!fileName.isNull(),
               "DopplerMergeDataFileOperateor::WriteDataToFile", "The file name is NULL");
    Q_ASSERT_X(!fileName.isEmpty(),
               "DopplerMergeDataFileOperateor::WriteDataToFile", "The file name is empty");

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate)) {
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

int DopplerMergeDataFileOperateor::WriteDataIIToFile(const QString &fileName)
{
    Q_ASSERT_X(!fileName.isNull(),
               "DopplerMergeDataFileOperateor::WriteDataToFile", "The file name is NULL");
    Q_ASSERT_X(!fileName.isEmpty(),
               "DopplerMergeDataFileOperateor::WriteDataToFile", "The file name is empty");

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate)) {
        return -6;
    }
    QFile tmpbuff("merge.cfg");
    if(!tmpbuff.open(QIODevice::ReadOnly)){
        return -6;
    }
    qint64 totalSize = tmpbuff.size();
    QByteArray data = tmpbuff.read(totalSize);
    file.write((char *)&totalSize, sizeof(qint64));
    file.write(data.data(), totalSize);
    totalSize = m_dataIIMark.size();
    file.write((char *)&totalSize, sizeof(qint64));
    file.write(m_dataIIMark.data(), totalSize);
    totalSize = m_dataIISource.size();
    file.write((char *)&totalSize, sizeof(qint64));
    file.write(m_dataIISource.data(), totalSize);
    file.close();
    tmpbuff.close();
    return 0;
}
