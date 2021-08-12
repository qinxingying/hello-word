#include "DopplerDataFileOperateor.h"
#include "DopplerConfigure.h"

#include <QDataStream>
#include <QFileInfo>
#include <QCoreApplication>

DopplerDataFileOperateor::DopplerDataFileOperateor(QObject *parent) :
    QObject(parent)
{
    m_file = NULL ;
    m_pBeamData  = NULL ;
}

DopplerDataFileOperateor::~DopplerDataFileOperateor()
{
    if(m_file)
    {
        m_file->unmap(m_pBeamData);
        m_file->close ();
        DopplerConfigure::Instance()->SaveEvn();
    }
    delete m_file;
    m_file = NULL ;
    m_pBeamData  = NULL ;
}

/*!
  \brief 读取数据文件的数据，顺序将文件数据拷贝到m_cFileHead，m_cDrawInfoPack，m_cGroupInfo中，
         然后把A扫数据映射到内存

  \param strPath_ 数据文件路径

  \return 成功返回 0；失败返回 -1

*/
int DopplerDataFileOperateor::LoadDataFile(QString& strPath_)
{
    if(m_file)
    {
        m_file->unmap(m_pBeamData);
        m_file->close ();
        delete m_file;
        m_file = NULL;
        DopplerConfigure::Instance()->SaveEvn();
    }
    m_file = new QFile(strPath_);
    m_file->open (QIODevice::ReadOnly);
    QDataStream reader(m_file);
    int ret  , _nTmp;
    _nTmp = sizeof(INSPEC_DATA_FILE) ;
    ret = reader.readRawData((char*)&m_cFileHead , _nTmp) ;
    if(ret != _nTmp)
        return -1 ;
    int Phascan_Version = m_cFileHead.version - m_cFileHead.size - m_cFileHead.reserved;
    _nTmp = sizeof(DRAW_INFO_PACK) ;
    ret = reader.readRawData((char*)&m_cDrawInfoPack , _nTmp) ;
    if(ret != _nTmp)
        return -1 ;
    _nTmp = sizeof(GROUP_INFO) * m_cDrawInfoPack.nGroupNum ;
    ret = reader.readRawData((char*)&m_cGroupInfo , _nTmp) ;
    if(ret != _nTmp)
        return -1 ;
    //得到采样数据,存在数据实际大小比m_cFileHead.version小的情况
    QFileInfo info1( *m_file);
    qint64 fileSize = info1.size();
    qint64 reservedSize;
    if( m_cFileHead.version > fileSize){
        if(Phascan_Version >= 6){
            return -1;
        }
        reservedSize = fileSize - m_cFileHead.size - 1;
    }
    else{
        reservedSize = m_cFileHead.reserved;
    }

    if(Phascan_Version >= 6){//有CAD信息
        _nTmp = m_cFileHead.reserved;
        ret = reader.skipRawData(_nTmp);
        if(ret != _nTmp){
            return -1;
        }
        if (Phascan_Version >=8) {
            _nTmp = sizeof(_ExtConfig2);
            ret = reader.readRawData((char*)&m_extConfig, _nTmp);
        } else {
            _nTmp = sizeof(_ExtConfig);
            ret = reader.skipRawData(_nTmp);
        }
        if(ret != _nTmp){
            return -1;
        }
        _nTmp = sizeof(int) * 8;
        ret = reader.readRawData((char*)&m_cadInfo, _nTmp);
        if(ret != _nTmp){
            return -1;
        }
        int cadTotalData = 0;
        for(int i = 0; i < 8; i++){
            cadTotalData += m_cadInfo[i];
        }
        if(cadTotalData && fileSize < (m_cFileHead.size + m_cFileHead.reserved + sizeof(_ExtConfig) + sizeof(int) * 8 + cadTotalData)){
            return -1;
        }
        for(int i = 0; i < 8; i++){
            if(m_cadInfo[i]){
                int caddataSize = m_cadInfo[i];
                QString g_filePath = QCoreApplication::applicationDirPath() + QString("/temp/%1.dxf").arg(i);
                QFile file(g_filePath);
                if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)){
                    return -1;
                }
                if(!file.resize(caddataSize)){
                    return -1;
                }
                uchar *buff = file.map(0, caddataSize);
                ret = reader.readRawData((char*)buff, caddataSize);
                file.unmap(buff);
                file.close();
                if(ret != caddataSize){
                    return -1;
                }
            }
        }
    }

    m_pBeamData = m_file->map(m_cFileHead.size , reservedSize) ;
    m_mapdataSize = reservedSize;

    return 0 ;
}


unsigned char* DopplerDataFileOperateor::GetData() const
{
    return m_pBeamData  ;
}

qint64 DopplerDataFileOperateor::GetDataSize() const
{
    return m_mapdataSize;
}

INSPEC_DATA_FILE* DopplerDataFileOperateor::GetFileHeader()
{
    return &m_cFileHead ;
}

DRAW_INFO_PACK* DopplerDataFileOperateor::GetDrawInfo()
{
    return &m_cDrawInfoPack ;
}

GROUP_INFO* DopplerDataFileOperateor::GetGroupInfo(int nGroupId_)
{
    if(nGroupId_ > 7)  return 0 ;
    if(nGroupId_ < 0)  return 0 ;
    return &(m_cGroupInfo[nGroupId_]);
}

bool DopplerDataFileOperateor::GetCADExist(int nGroupId_)
{
    if(m_cadInfo[nGroupId_]){
        return true;
    }else{
        return false;
    }
}

ExtConfig2 *DopplerDataFileOperateor::GetExtConfig2()
{
    return &m_extConfig;
}
