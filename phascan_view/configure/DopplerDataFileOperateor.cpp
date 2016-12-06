#include "DopplerDataFileOperateor.h"

#include <QDataStream>

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
    }
    m_file = NULL ;
    m_pBeamData  = NULL ;
}



int DopplerDataFileOperateor::LoadDataFile(QString& strPath_)
{
    if(m_file)
    {
        m_file->unmap(m_pBeamData);
        m_file->close ();
    }
    m_file = new QFile(strPath_);
    m_file->open (QIODevice::ReadOnly);
    QDataStream reader(m_file);
    int ret  , _nTmp;
    _nTmp = sizeof(INSPEC_DATA_FILE) ;
    ret = reader.readRawData((char*)&m_cFileHead , _nTmp) ;
    if(ret != _nTmp)
        return -1 ;
    _nTmp = sizeof(DRAW_INFO_PACK) ;
    ret = reader.readRawData((char*)&m_cDrawInfoPack , _nTmp) ;
    if(ret != _nTmp)
        return -1 ;
    _nTmp = sizeof(GROUP_INFO) * m_cDrawInfoPack.nGroupNum ;
    ret = reader.readRawData((char*)&m_cGroupInfo , _nTmp) ;
    if(ret != _nTmp)
        return -1 ;
    //得到采样数据
    m_pBeamData = m_file->map(m_cFileHead.size , m_cFileHead.reserved) ;
    return 0 ;
}


unsigned char* DopplerDataFileOperateor::GetData() const
{
    return m_pBeamData  ;
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
