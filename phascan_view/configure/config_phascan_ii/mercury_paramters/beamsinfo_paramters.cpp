#include "beamsinfo_paramters.h"
#include <QDebug>

namespace Paramters {

BeamsInfo::BeamsInfo(QObject *parent) : QObject(parent)
{
    memset(m_delay, 0, setup_MAX_LAW_QTY);
    memset(m_fieldDistance, 0, setup_MAX_LAW_QTY);
}

}
