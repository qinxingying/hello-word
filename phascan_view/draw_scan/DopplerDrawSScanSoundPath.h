#ifndef DOPPLERDRAWSSCANSOUNDPATH_H
#define DOPPLERDRAWSSCANSOUNDPATH_H

#include "DopplerDrawScan.h"


struct S_SCAN_DRAW_INFO
{
    int nPointQty ;
    int nLawQty   ;
    unsigned char* pMarker ;
} ;


struct SSCAN_DRAW_INFO
{
    int nScanPos   ;
    int nIndexPos  ;

    int nFrameSize ;
    int nGroupOffset ;
    char* pMarker ;
};

class DopplerDrawSScanSoundPath : public DopplerDrawScan
{
    Q_OBJECT
public:
    explicit DopplerDrawSScanSoundPath();
    void UpdateDrawInfo();
    virtual void Draw (QImage *pImage_) ;

protected:
    S_SCAN_DRAW_INFO m_SScanInfo ;

};

#endif // DOPPLERDRAWSSCANSOUNDPATH_H
