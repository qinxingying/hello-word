#ifndef VERSION_PARAMTERS_H
#define VERSION_PARAMTERS_H

#include <QObject>
#include <QVariantList>
namespace Paramters {

class Version : public QObject
{
    Q_OBJECT
public:
    explicit Version(QObject *parent = 0);

private:
    QString m_phascanVersion;
    QString m_FpgaCpuVersion;
    QString m_FpgaPaVersion;
    QString m_type; // 设备类型
    QString m_deviceSN; // 设备序列号
    QDateTime m_date;
    bool m_dxfExist;
    QByteArray m_dxfData;
    friend class Config;
};
}
#endif // VERSION_PARAMTERS_H
