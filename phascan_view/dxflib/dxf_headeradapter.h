#ifndef DXF_HEADERADAPTER_H
#define DXF_HEADERADAPTER_H

#include "dl_global.h"
#include "dxf_headerinterface.h"

//namespace DplDxf {

class DXFLIB_EXPORT Dxf_HeaderAdapter : public Dxf_HeaderInterface {
public:
    Dxf_HeaderAdapter() {}
    virtual ~Dxf_HeaderAdapter() {}

    virtual void processCodeValuePair(unsigned int, const std::string&) {}

    virtual void add_version(const DXF_HEADER_ACADVER&) {}
    virtual void add_angle_dir(const DXF_HEADER_ANGDIR&) {}
    virtual void add_unit(const DXF_HEADER_INSUNITS&) {}

    virtual void add_PUCS_name(const DXF_HEADER_PUCSNAME&) {}
    virtual void add_point_PUCSORG(const DXF_HEADER_PUCSORG&) {}
    virtual void add_point_PUCSXDIR(const DXF_HEADER_PUCSXDIR&) {}
    virtual void add_point_PUCSYDIR(const DXF_HEADER_PUCSYDIR&) {}

    virtual void add_UCS_name(const DXF_HEADER_UCSNAME&) {}
    virtual void add_point_UCSORG(const DXF_HEADER_UCSORG&) {}
    virtual void add_point_UCSXDIR(const DXF_HEADER_UCSXDIR&) {}
    virtual void add_point_UCSYDIR(const DXF_HEADER_UCSYDIR&) {}

    virtual void add_line_scale(const DXF_HEADER_LTSCALE&) {}
};
//}


#endif // DXF_HEADERADAPTER_H
