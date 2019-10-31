#ifndef DOPPLERDRAWBSCAN_H
#define DOPPLERDRAWBSCAN_H

#include "DopplerDrawScan.h"

struct B_SCAN_DRAW_INFO
{
    int nPointQty ;
    int nFrameSize ;
    int nLawOffset ;
    //unsigned char* pData ;
} ;
//这里的水平是C扫里面的垂直，两个刚好反向
class DopplerDrawBScanH : public DopplerDrawScan
{
    Q_OBJECT
public:
    explicit DopplerDrawBScanH(QObject *parent = 0);
    void UpdateDrawInfo();
    virtual void Draw (QImage* pImage_);
protected:
    B_SCAN_DRAW_INFO m_BScanInfo ;
};

class DopplerDrawBScanV : public DopplerDrawBScanH
{
    Q_OBJECT
public:
    explicit DopplerDrawBScanV(QObject *parent = 0 );
    virtual void Draw (QImage* pImage_);
};

#endif // DOPPLERDRAWBSCAN_H
