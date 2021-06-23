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
    bool m_dxfExist;
    QByteArray m_dxfData;
    friend class Config;
};
}
#endif // VERSION_PARAMTERS_H
