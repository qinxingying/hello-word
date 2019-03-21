#ifndef PROBE_H
#define PROBE_H

#include <QObject>
#include <QString>

namespace Paramters {

class Probe : public QObject
{
    Q_OBJECT
public:
    enum ArrayMode {
        CURVED,         /* 曲型 */
        DUAL_LINEAR,    /* 双线性，一发一收 */
        DUAL_MATRIX,    /* 双矩阵，一发一收 */
        LINEAR,         /* 线性，自发自收 */
        MATRIX          /* 矩阵，自发自收 */
    };

    /**
     * @brief The Type enum 探头类型
     */
    enum ProbeType {
        CONTACT,    /* 直接接触式类型 */
        DELAY,      /* 延迟块式 */
        IMMERSION,  /* 水浸式 */
        ANGLE_BEAM, /* 角度声速类型 */
        DUAL,       /* 双晶探头，UT专有 */
        UT_TOFD     /* Tofd探头，UT专有 */
    };

    explicit Probe(QObject *parent = 0);
    ~Probe();

private:
    ArrayMode m_arrayMode;
    double m_freq;
    QString m_model;
    QString m_serial;
    uint m_priElemQty;
    uint m_secElemQty;
    double m_priPitch;
    double m_secPitch;
    double m_refPoint;
    double m_scanOffset;
    double m_indexOffset;
    uint m_skew;
    ProbeType m_type;

    friend class Config;
};

}

#endif // PROBE_H
