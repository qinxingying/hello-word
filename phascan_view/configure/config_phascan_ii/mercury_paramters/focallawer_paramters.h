#ifndef FOCALLAWER_H
#define FOCALLAWER_H

#include <QObject>
#include <QList>
#include "scan_paramters.h"
#include "focus_paramters.h"
#include "beamsinfo_paramters.h"

namespace Paramters {

class Focallawer : public QObject
{
    Q_OBJECT

public:
    enum ScanMode {
        Linear,     /* 线性扫查 */
        Sectorial   /* 扇性扫查 */
    };

    enum FocusMode {
        HALF_PATH,  /* 半声程 */
        TRUE_DEPTH, /* 真实深度 */
        PROJECTION, /* 投影 */
        FOCAL_PLANE,/* 任意面 */
        DDF         /* 动态聚焦 */
    };

    enum WaveType {
        Longitudinal,
        Shear
    };

    explicit Focallawer(QObject *parent = 0);

private:
    ScanMode m_scanMode;
    FocusMode m_focusMode;
    WaveType m_waveType;
    bool m_coupling;
    Scan m_scan;
    Focus m_focus;

    QList<float> m_delays;
    QList<float> m_fieldDistance;
    QList<float> m_gains;

    friend class Config;
};

}

#endif // FOCALLAWER_H
