#ifndef BEAMSINFO_H
#define BEAMSINFO_H

#include <QObject>
#include "../configure/Instrument.h"

namespace Paramters {

class BeamsInfo : public QObject
{
    Q_OBJECT

public:

    struct InlineInfo {
        float delay;
        float fieldDistance;
    };

    explicit BeamsInfo(QObject *parent = 0);

private:
    float m_delay[setup_MAX_LAW_QTY];
    float m_fieldDistance[setup_MAX_LAW_QTY];

    friend class Config;
};

}

#endif // BEAMSINFO_H
