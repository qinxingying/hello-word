#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include "display_paramters.h"
#include "global_transceiver_paramters.h"
#include "scanner_paramters.h"
#include "version_paramters.h"

namespace Paramters {

class Global : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief The SoundMode enum    蜂鸣器工作频率
     */
    enum SoundMode {
        SOUND_OFF   = 0b000,
        SOUND_300HZ = 0b001,
        SOUND_600HZ = 0b010,
        SOUND_1000HZ= 0b011,
        SOUND_5000HZ= 0b100,
    };

    enum PrfMode {
        MAX,
        MAX_HALF,
        OPTIMUM,
        USER_DEF
    };

    explicit Global(QObject *parent = 0);

private:
    Version m_version;
    Display m_display;
    GlobalTransceiver m_transceiver;
    Scanner m_scanner;
//    Alarm m_alarm[3];
    SoundMode m_sound;
    uint m_groupQty;
    PrfMode m_prfMode;

    friend class Config;
};

}

#endif // GLOBAL_H
