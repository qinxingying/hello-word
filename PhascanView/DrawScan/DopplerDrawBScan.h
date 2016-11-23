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

class DopplerDrawBScanH : public DopplerDrawScan
{
    Q_OBJECT
public:
    explicit DopplerDrawBScanH(QObject *parent = 0);
    void UpdateDrawInfo();
    virtual void Draw (QImage* pImage_);
protected:
	void UpdateDisplayRange(int nType_, int nRangle_ , int nPos_);

    B_SCAN_DRAW_INFO m_BScanInfo ;
    int m_PosStart ;
    int m_PosStop  ;
};

class DopplerDrawBScanV : public DopplerDrawBScanH
{
    Q_OBJECT
public:
    explicit DopplerDrawBScanV(QObject *parent = 0 ) :DopplerDrawBScanH(parent){}
    virtual void Draw (QImage* pImage_);
};

#endif // DOPPLERDRAWBSCAN_H
