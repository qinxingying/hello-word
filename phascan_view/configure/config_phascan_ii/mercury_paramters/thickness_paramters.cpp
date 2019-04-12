#include "thickness_paramters.h"

namespace Paramters {

Thickness::Thickness(QObject *parent) : QObject(parent),
    m_min(0.5),
    m_max(50)
{

}

}
