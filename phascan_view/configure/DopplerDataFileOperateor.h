#ifndef DOPPLERDATAFILEOPERATEOR_H
#define DOPPLERDATAFILEOPERATEOR_H

#include <QObject>
#include <QFile>
#include "DopplerDataFileConfigure.h"

class Config;

class DopplerDataFileOperateor : public QObject
{
    Q_OBJECT
public:
    explicit DopplerDataFileOperateor(QObject *parent = 0);
    ~DopplerDataFileOperateor() ;
    int LoadDataFile (QString& strPath_);
    unsigned char* GetData() const ;
    qint64 GetDataSize() const ;
    qint64 GetDataPos() const ;
    INSPEC_DATA_FILE* GetFileHeader() ;
    DRAW_INFO_PACK*   GetDrawInfo() ;
    GROUP_INFO*       GetGroupInfo(int nGroupId_)  ;
    bool GetCADExist(int nGroupId_);
    ExtConfig2*   GetExtConfig2();
    void close();

protected:
    INSPEC_DATA_FILE m_cFileHead;
    DRAW_INFO_PACK m_cDrawInfoPack;
    GROUP_INFO m_cGroupInfo[8];
    unsigned char* m_pBeamData;
    QFile* m_file ;
    qint64 m_mapdataSize;
    qint64 m_dataFilePos {0};
    int m_cadInfo[8];
    ExtConfig2 m_extConfig;
signals:

public slots:
    friend class Config;
};

#endif // DOPPLERDATAFILEOPERATEOR_H
