/**
 * @file entities_spline.h
 * @brief dxf entities层, spline对象
 * @author JakeYang <add358@gmail.com>
 * @version 0.2
 * @date 2015-04-14
 */

#ifndef __ENTITIES_SPLINE_H__
#define __ENTITIES_SPLINE_H__

#include "dxfile.h"

typedef struct _DxfSpline DxfSpline;
struct _DxfSpline {
    DxfPointData vector;            /*210,220,230 Normal vector (omitted if the spline is nonplanar)*/
    int flag;                    /*70 Spline flag*/
    int degree;                  /*71 Degree of the spline curve*/
    int knotsNum;                /*72 Number of knots*/
    int ctrlPointsNum;           /*73 Number of control points*/
    int fitPointsNum;            /*74 Number of fit points (if any)*/
    double knotTolerance;          /*42 Knot tolerance (default = 0.0000001)*/
    double ctrlPointTolerance;     /*43 Control-point tolerance (default = 0.0000001)*/
    double fitTolerance;           /*44 Fit tolerance (default = 0.0000000001)*/
    double *knotValues;            /*40 Knot value (one entry per knot)*/
    DxfPointData *ctrlPoints;       /*10,20,30 Control points (in WCS); one entry per control point*/
};

extern DxfSpline *dxf_spline_parse(Dxfile *f);
extern void dxf_spline_delete(DxfSpline *e);
extern char *dxf_spline_print(DxfSpline *e);

#endif /* End of __ENTITIES_SPLINE_H__ */
