#ifndef DXF_HEADERINTERFACE_H
#define DXF_HEADERINTERFACE_H

#include <string.h>

#include "dl_global.h"
#include "dxf_header_type.h"

//namespace DplDxf {
class DXFLIB_EXPORT Dxf_HeaderInterface {
public:
    Dxf_HeaderInterface() {

    }

    virtual ~Dxf_HeaderInterface() {

    }

    virtual void processCodeValuePair(unsigned int groupCode, const std::string& groupValue) = 0;

    virtual void add_version(const DXF_HEADER_ACADVER& data) = 0;
    virtual void add_angle_dir(const DXF_HEADER_ANGDIR& data) = 0;
    virtual void add_unit(const DXF_HEADER_INSUNITS& data) = 0;

    virtual void add_PUCS_name(const DXF_HEADER_PUCSNAME& data) = 0;
    virtual void add_point_PUCSORG(const DXF_HEADER_PUCSORG& data) = 0;
    virtual void add_point_PUCSXDIR(const DXF_HEADER_PUCSXDIR& data) = 0;
    virtual void add_point_PUCSYDIR(const DXF_HEADER_PUCSYDIR& data) = 0;

    virtual void add_UCS_name(const DXF_HEADER_UCSNAME& data) = 0;
    virtual void add_point_UCSORG(const DXF_HEADER_UCSORG& data) = 0;
    virtual void add_point_UCSXDIR(const DXF_HEADER_UCSXDIR& data) = 0;
    virtual void add_point_UCSYDIR(const DXF_HEADER_UCSYDIR& data) = 0;

    virtual void add_line_scale(const DXF_HEADER_LTSCALE& data) = 0;
};
//}



#endif // DXF_HEADERINTERFACE_H
