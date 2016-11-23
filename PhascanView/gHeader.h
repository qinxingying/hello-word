

#ifndef GHEADER_H
#define GHEADER_H

#include "configure/Struct.h"
#include "ui/MainWindow.h"
#include <math.h>
#include <QtGui>

#define D_PI  3.141592654
#define DEGREE_TO_ARCH(a)  ((a) * D_PI / 180.0)
#define ARCH_TO_DEGREE(a)  ((a) * 180.0 / D_PI)

#define EPSILON_E4 (float)(1E-4)
#define FLOAT_EQ(a,b)            ((fabs(a-b)<EPSILON_E4) ? 1 : 0)


#define MM_TO_INCH(a)    ( a * 0.03937 )
#define INCH_TO_MM(a)    ( a / 0.03937 )

#define A_DB_B(a , b)    (20 * log10(a / b))

#define GYMAX(a , b)     ((a > b) ? a : b)
#define GYMIN(a , b)     ((a < b) ? a : b)

#endif // GHEADER_H

