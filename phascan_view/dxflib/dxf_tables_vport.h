/**
 * @file dxf_tables_vport.h
 * @brief dxf tables层, vport封装
 * @author JakeYang <add358@gmail.com>
 * @version 0.2
 * @date 2015-04-14
 */

#ifndef __DXF_TABLES_VPORT_H__
#define __DXF_TABLES_VPORT_H__

#include "dxfile.h"

typedef struct _DxfTablesVport DxfTablesVport;
struct _DxfTablesVport {
        char *name;                    /*2:Viewport name*/
        int standardFlag;            /*70:Standard flag values*/
        DxfPointData lowerLeftCorner;   /*10,20:Lower-left corner of viewport*/
        DxfPointData upperRightCorner;  /*11,21:Upper-right corner of viewport*/
        DxfPointData viewCenter;        /*12,22:View Center Point*/
        DxfPointData snapBase;          /*13,23:snap base point*/
        DxfPointData snapSpacing;       /*14,24:Snap spacing X and Y*/
        DxfPointData gridSpacing;       /*15,25:Grid spacing X and Y*/
        DxfPointData direction;         /*16,26,36:View direction from target
                                          point*/
        DxfPointData target;            /*17,27,37:View target point*/
        double aspectRatio;            /*41:Viewport aspect ratio*/
        double lensLenght;             /*42:Lens length*/
        double frontPlaneOffset;       /*43:Front clipping plane (offset from
                                          target point) */
        double backPlaneOffset;        /*44:Back clipping plane (offset from
                                          target point) */
        double viewHeight;             /*40or45:View height*/
        double snapRotationAngle;      /*50:Snap rotation angle*/
        double viewTwistAngle;         /*51:View twist angle*/
        int viewMode;                /*71:View Mode*/
        int circleSides;             /*72:Circle sides*/
        int fastZoomSetting;         /*73:Fast zoom setting*/
//        int ucsiconSetting;          /*74:UCSICON setting*/
//        int snapOn;                  /*75:Snap on/off*/
//        int gridOn;                  /*76:Grid on/off*/
//        int snap_style;              /*77:Snap style*/
//        int snapIsopair;             /*78:Snap isopair*/

        char *frozenLayerSoftPointer;  /*331:Soft-pointer ID/handle to frozen
                                          layer objects*/
        char *frozenLayerHardPointer;  /*441:hard-pointer ID/handle to frozen
                                          layer objects*/
};

extern DxfTablesVport *dxf_tables_vport_parse(Dxfile *f);
extern void dxf_tables_vport_delete(DxfTablesVport *e);
extern char *dxf_tables_vport_print(DxfTablesVport *e);

#endif /* End of __DXF_TABLES_VPORT_H__ */
