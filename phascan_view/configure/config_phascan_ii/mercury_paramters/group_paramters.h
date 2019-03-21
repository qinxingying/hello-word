#ifndef __GROUP_PARAMTERS_H__
#define __GROUP_PARAMTERS_H__

#include <QObject>

#include "sample_paramters.h"
#include "transceiver_paramters.h"
#include "focallawer_paramters.h"
#include "gate_paramters.h"
#include "cscan_paramters.h"
#include "cursor_paramters.h"
#include "probe_paramters.h"
#include "wedge_paramters.h"
#include "specimen_paramters.h"
#include "thickness_paramters.h"
#include "sizing_paramters.h"

namespace Paramters {

class Group : public QObject
{
    Q_OBJECT

public:
    enum GroupMode {
        UT,
        PA,
        UT1,
        UT2
    };

    enum UtUnit {
        Time,       /* 时间 */
        SoundPath,  /* 声程 */
        TruePath    /* 真实深度 */
    };

    explicit Group(QObject *parent = 0);
    ~Group();

private:
    GroupMode m_mode;
    UtUnit m_utUnit;
    bool m_highestTrack;
    Sample m_sample;
    Transceiver m_transceiver;
    Focallawer m_focallawer;
    Gate m_gateA;
    Gate m_gateB;
    Gate m_gateI;
    CScan m_cScan;
    Cursor m_cursor;
    Probe m_probe;
    Wedge m_wedge;
    Specimen m_specimen;
    Thickness m_thickness;
    Sizing m_sizing;

    friend class Config;

};

}

#endif // __GROUP_PARAMTERS_H__
