#ifndef SAMPLE_H
#define SAMPLE_H

#include <QObject>

namespace Paramters {

class Sample : public QObject
{
    Q_OBJECT
public:
    explicit Sample(QObject *parent = 0);
    ~Sample();

private:
    double m_gain;
    bool m_refGainStatus;
    double m_refGain;
    double m_start;
    double m_range;
    double m_maxGain;
    uint m_pointQty;
    bool m_autoCalcPointQty;

    friend class Config;
};

}

#endif // SAMPLE_H
