#ifndef GATE_H
#define GATE_H

#include <QObject>

namespace Paramters {

class Gate : public QObject
{
    Q_OBJECT

    /**
     * @brief The MeasureMode enum  闸门测量模式
     */
    enum MeasureMode {
        EDGE,
        PEAK
    };

    enum GateMode {
        DEPTH,
        SOUND_PATH
    };

    /**
     * @brief The SynchroMode enum  闸门同步模式
     */
    enum SynchroMode {
        SYNCHRO_PULSER,
        SYNCHRO_I,
        SYNCHRO_A,
        SYNCHRO_B,
    };

public:
    explicit Gate(QObject *parent = 0);

private:
    MeasureMode m_measureMode;
    GateMode m_gateMode;
    SynchroMode m_synchroMode;
    bool m_visible;
    float m_start;
    float m_width;
    uint m_height;
    unsigned m_color;

    friend class Config;
};

}

#endif // GATE_H
