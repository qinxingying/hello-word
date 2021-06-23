#ifndef CSCAN_H
#define CSCAN_H

#include <QObject>

namespace Paramters {

class CScan : public QObject
{
    Q_OBJECT

    enum CScanMode {
        ANGLE,
        TOPC
    };

    enum SourceType {
        GATE_A,
        GATE_B,
        GATE_I,
        THICKNESS
    };

public:
    explicit CScan(QObject *parent = 0);

private:
    CScanMode m_mode;
    SourceType m_sourceType;
    double m_topCWidth;

    friend class Config;
};

}

#endif // CSCAN_H
