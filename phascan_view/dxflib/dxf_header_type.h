#ifndef DXF_HEADER_TYPE_H
#define DXF_HEADER_TYPE_H

#include "dl_global.h"

#include <string>
#include <vector>

//namespace DplDxf {
struct DXFLIB_EXPORT DXF_HEADER_ACADVER {
    DXF_HEADER_ACADVER(const std::string& version) :
        version(version) {}

    /* 图形数据库版本号 */
    std::string version;
};

struct DXFLIB_EXPORT DXF_HEADER_ANGDIR {
    DXF_HEADER_ANGDIR(int flags) :
        flags(flags) {}

    /* 角度方向 */
    int flags;  /* 1 = 顺时针角度
                   0 = 逆时针角度 */
};

struct DXFLIB_EXPORT DXF_HEADER_INSUNITS {
    DXF_HEADER_INSUNITS(int flags) :
        flags(flags) {}

    /* AutoCAD 设计中心块的默认图形单位 */
    int flags;
};

struct DXFLIB_EXPORT DXF_HEADER_PUCSNAME {
    DXF_HEADER_PUCSNAME(const std::string& name) :
        name(name) {}

    /* 当前图纸空间 UCS 名称 */
    std::string name;
};

struct DXFLIB_EXPORT DXF_HEADER_PUCSORG {
    /* 当前图纸空间 UCS 原点 */
    DXF_HEADER_PUCSORG(double px=0.0, double py=0.0, double pz=0.0) {
        x = px;
        y = py;
        z = pz;
    }

    /*! X Coordinate of the point. */
    double x;
    /*! Y Coordinate of the point. */
    double y;
    /*! Z Coordinate of the point. */
    double z;
};

struct DXFLIB_EXPORT DXF_HEADER_PUCSXDIR {
    /* 当前图纸空间的 UCS X 轴 */
    DXF_HEADER_PUCSXDIR(double px=0.0, double py=0.0, double pz=0.0) {
        x = px;
        y = py;
        z = pz;
    }

    /*! X Coordinate of the point. */
    double x;
    /*! Y Coordinate of the point. */
    double y;
    /*! Z Coordinate of the point. */
    double z;
};

struct DXFLIB_EXPORT DXF_HEADER_PUCSYDIR {
    /* 当前图纸空间的 UCS Y 轴 */
    DXF_HEADER_PUCSYDIR(double px=0.0, double py=0.0, double pz=0.0) {
        x = px;
        y = py;
        z = pz;
    }

    /*! X Coordinate of the point. */
    double x;
    /*! Y Coordinate of the point. */
    double y;
    /*! Z Coordinate of the point. */
    double z;
};

struct DXFLIB_EXPORT DXF_HEADER_UCSNAME {
    DXF_HEADER_UCSNAME(const std::string& name) :
        name(name) {}

    /* 当前UCS 名称 */
    std::string name;
};

struct DXFLIB_EXPORT DXF_HEADER_UCSORG {
    /* 当前UCS 原点 */
    DXF_HEADER_UCSORG(double px=0.0, double py=0.0, double pz=0.0) {
        x = px;
        y = py;
        z = pz;
    }

    /*! X Coordinate of the point. */
    double x;
    /*! Y Coordinate of the point. */
    double y;
    /*! Z Coordinate of the point. */
    double z;
};

struct DXFLIB_EXPORT DXF_HEADER_UCSXDIR {
    /* 当前 UCS X 轴的方向（在 WCS 中） */
    DXF_HEADER_UCSXDIR(double px=0.0, double py=0.0, double pz=0.0) {
        x = px;
        y = py;
        z = pz;
    }

    /*! X Coordinate of the point. */
    double x;
    /*! Y Coordinate of the point. */
    double y;
    /*! Z Coordinate of the point. */
    double z;
};

struct DXFLIB_EXPORT DXF_HEADER_UCSYDIR {
    /* 当前 UCS Y 轴的方向（在 WCS 中） */
    DXF_HEADER_UCSYDIR(double px=0.0, double py=0.0, double pz=0.0) {
        x = px;
        y = py;
        z = pz;
    }

    /*! X Coordinate of the point. */
    double x;
    /*! Y Coordinate of the point. */
    double y;
    /*! Z Coordinate of the point. */
    double z;
};

struct DXFLIB_EXPORT DXF_HEADER_LTSCALE {
    DXF_HEADER_LTSCALE(double lineScale) :
        lineScale(lineScale) {}

    /* 全局线型比例 */
    double lineScale;
};

//}


#endif // DXF_HEADER_TYPE_H
