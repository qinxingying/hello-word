/**
 * @file dxf_tables_ltype.h
 * @brief dxf tables层, ltype封装
 * @author JakeYang <add358@gmail.com>
 * @version 0.2
 * @date 2015-04-14
 */

#ifndef __DXF_TABLES_LTYPE_H__
#define __DXF_TABLES_LTYPE_H__

#include "dxfile.h"

/* Group Code ID */

typedef struct _DxfTablesLtype DxfTablesLtype;
struct _DxfTablesLtype {
    char *name;            /*2:Linetype name*/
    char *description;     /*3:Descriptive text for linetype*/
    char *text;            /*9:Text string (one per element if code 74 = 2)*/
    double totalPattenLength;/*40:total_pattern_length*/
    double xOffset;        /*44:X offset value*/
    double yOffset;        /*45:Y offset value*/
    double dashLength;     /*49:Dash, dot or space length*/
    double scale;          /*46:Scale value (optional);
                                multiple entries can exist */
    double rotation;       /*50:R = (relative) or A = (absolute) rotation value
                                in radians of embedded shape or text*/
    int flag;            /*70:Standard flag values*/
    int alignment;       /*72:Alignment code*/
    int elementsNum;     /*73:The number of linetype elements*/
    int complexElement;  /*74:Complex linetype element type (one per element)*/
    int shapeNum;        /*75:Shape number (one per element)*/
    char *stylePointer;    /*340:Pointer to STYLE object*/
};

extern DxfTablesLtype *dxf_tables_ltype_parse(Dxfile *f);
extern void dxf_tables_ltype_delete(DxfTablesLtype *l);
extern char *dxf_tables_ltype_print(DxfTablesLtype *l);

#endif /* End of __DXF_TABLES_LTYPE_H__ */
