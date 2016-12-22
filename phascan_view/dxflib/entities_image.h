/**
 * @file entities_image.h
 * @brief dxf entities层, image对象
 * @author JakeYang <add358@gmail.com>
 * @version 0.2
 * @date 2015-04-14
 */

#ifndef __ENTITIES_IMAGE_H__
#define __ENTITIES_IMAGE_H__

#include "dxfile.h"

typedef struct _DxfImage DxfImage;
struct _DxfImage {
    int classVersion;            /*90 Class version*/
    DxfPointData insertionPoint;    /*10,20,30 Insertion point (in WCS)*/
    DxfPointData uVectorPoint;      /*11,21,31 U-vector (in WCS)*/
    DxfPointData vVectorPoint;      /*12,22,32 V-vector (in WCS)*/
    double usize;                  /*13 U value of Image size in pixels*/
    double vSize;                  /*23 V value of image size in pixels*/
    char *hdRef2Imgdef;            /*340 Hard reference to imagedef object*/
    int displayProperties;       /*70 Image display properties*/
    int clippingState;           /*280 Clipping state: 0 = Off; 1 = On*/
    int brightness;              /*281 Brightness value (0-100; default = 50)*/
    int contrast;                /*282 Contrast value (0-100; default = 50)*/
    int fade;                    /*283 Fade value (0-100; default = 0)*/
    char *hdRef2ImgdefReactor;     /*360 Hard reference to imagedef_reactor object*/
    int clipBoundaryType;        /*71 Clipping boundary type. 1 = Rectangular; 2 = Polygonal*/
    int vertexNum;               /*91 Number of clip boundary vertices that follow*/
    DxfPointData *vertexes;         /*14,24 Clip boundary vertex (in OCS)*/
    int clipMode;                /*290 Clip Mode: 0 = Outside Mode; 1 = Inside Mode */
};

extern DxfImage *dxf_image_parse(Dxfile *f);
extern void dxf_image_delete(DxfImage *e);
extern char *dxf_image_print(DxfImage *e);

#endif /* End of __ENTITIES_IMAGE_H__ */
