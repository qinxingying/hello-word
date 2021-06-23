#ifndef FOCUS_H
#define FOCUS_H

#include <QObject>
//#include "focallawer_paramters.h"

namespace Paramters {

class Focus : public QObject
{
    Q_OBJECT
public:
    explicit Focus(QObject *parent = 0);

private:
//    Focallawer::FocusMode m_focusMode;
    /* FOCUS_HALF_PATH */
    double m_radius;
    /* FOCUS_TRUE_DEPTH */
    double m_depth;
    /* FOCUS_PROJECTION */
    double m_offset;
    /* FOCUS_FOCAL_PLANE */
    double m_beginOffset;
    double m_endOffset;
    double m_beginDepth;
    double m_endDepth;

    friend class Config;
};

}

#endif // FOCUS_H
