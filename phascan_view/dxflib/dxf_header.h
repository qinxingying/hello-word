#ifndef DXFHEADER_H
#define DXFHEADER_H

#include "dl_global.h"
#include "dxf_header_type.h"

#include <QString>

#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <map>

#define DL_DXF_MAXLINE 1024

//namespace DplDxf {

class Dxf_HeaderInterface;

class DXFLIB_EXPORT DxfHeader
{
public:

    enum DXF_HEADER_STYLE {
        HEADER_ACADMAINTVER  =  1,
        HEADER_ACADVER,
        HEADER_ANGBASE,
        HEADER_ANGDIR,
        HEADER_ATTMODE,
        HEADER_AUNITS,
        HEADER_AUPREC,
        HEADER_CECOLOR,
        HEADER_CELTSCALE,
        HEADER_CELTYPE,
        HEADER_CELWEIGHT,
        HEADER_CEPSNID,
        HEADER_CEPSNTYPE,
        HEADER_CHAMFERA,
        HEADER_CHAMFERB ,
        HEADER_CHAMFERC,
        HEADER_CHAMFERD,
        HEADER_CLAYER,
        HEADER_CMLJUST,
        HEADER_CMLSCALE,
        HEADER_CMLSTYLE,
        HEADER_CSHADOW,
        HEADER_DIMADEC,
        HEADER_DIMALT,
        HEADER_DIMALTD,
        HEADER_DIMALTF,
        HEADER_DIMALTRND,
        HEADER_DIMALTTD,
        HEADER_DIMALTTZ,
        HEADER_DIMALTU,
        HEADER_DIMALTZ,
        HEADER_DIMAPOST,
        HEADER_DIMASO,
        HEADER_DIMASSOC,
        HEADER_DIMASZ,
        HEADER_DIMATFIT,
        HEADER_DIMAUNIT,
        HEADER_DIMAZIN,
        HEADER_DIMBLK,
        HEADER_DIMBLK1,
        HEADER_DIMBLK2,
        HEADER_DIMCEN,
        HEADER_DIMCLRD,
        HEADER_DIMCLRE,
        HEADER_DIMCLRT,
        HEADER_DIMDE,
        HEADER_DIMDLE,
        HEADER_DIMDLI,
        HEADER_INSUNITS,
        HEADER_PUCSNAME,
        HEADER_PUCSORG,
        HEADER_PUCSXDIR,
        HEADER_PUCSYDIR,
        HEADER_UCSNAME,
        HEADER_UCSORG,
        HEADER_UCSXDIR,
        HEADER_UCSYDIR,
        HEADER_LTSCALE
    };

    DxfHeader();
    ~DxfHeader();

    bool in(const std::string& file,
            Dxf_HeaderInterface* headerInterface);
    bool readDxfGroups(FILE* fp,
                       Dxf_HeaderInterface* headerInterface);
    static bool getStrippedLine(std::string& s, unsigned int size,
                               FILE* stream, bool stripSpace = true);

    bool readDxfGroups(std::stringstream& stream,
                       Dxf_HeaderInterface* headerInterface);
    bool in(std::stringstream &stream,
            Dxf_HeaderInterface* headerInterface);
    static bool getStrippedLine(std::string& s, unsigned int size,
                               std::stringstream& stream, bool stripSpace = true);

    static bool stripWhiteSpace(char** s, bool stripSpaces = true);

    bool processDXFGroup(Dxf_HeaderInterface* headerInterface,
                         int groupCode, const std::string& groupValue);

    void add_version(Dxf_HeaderInterface* headerInterface);
    void add_angle_dir(Dxf_HeaderInterface* headerInterface);
    void add_unit(Dxf_HeaderInterface* headerInterface);

    void add_PUCS_name(Dxf_HeaderInterface* headerInterface);
    void add_point_PUCSORG(Dxf_HeaderInterface* headerInterface);
    void add_point_PUCSXDIR(Dxf_HeaderInterface* headerInterface);
    void add_point_PUCSYDIR(Dxf_HeaderInterface* headerInterface);

    void add_UCS_name(Dxf_HeaderInterface* headerInterface);
    void add_point_UCSORG(Dxf_HeaderInterface* headerInterface);
    void add_point_UCSXDIR(Dxf_HeaderInterface* headerInterface);
    void add_point_UCSYDIR(Dxf_HeaderInterface* headerInterface);

    void add_line_scale(Dxf_HeaderInterface* headerInterface);

    bool hasValue(int code) {
        return values.count(code)==1;
    }

    int getIntValue(int code, int def) {
        if (!hasValue(code)) {
            return def;
        }
        return toInt(values[code]);
    }

    int toInt(const std::string& str) {
        char* p;
        return strtol(str.c_str(), &p, 10);
    }

    bool toBool(const std::string& str) {
        char* p;
        return (bool)strtol(str.c_str(), &p, 10);
    }

    std::string getStringValue(int code, const std::string& def) {
        if (!hasValue(code)) {
            return def;
        }
        return values[code];
    }

    double getRealValue(int code, double def) {
        if (!hasValue(code)) {
            return def;
        }
        return toReal(values[code]);
    }

    double toReal(const std::string& str) {
        double ret;
        // make sure the real value uses '.' not ',':
        std::string str2 = str;
        std::replace(str2.begin(), str2.end(), ',', '.');
        // make sure c++ expects '.' not ',':
        std::istringstream istr(str2);
        istr.imbue(std::locale("C"));
        istr >> ret;
        return ret;
    }

private:
    // Only the useful part of the group code
    std::string groupCodeTmp;
    // ...same as integer
    unsigned int groupCode;
    // Only the useful part of the group value
    std::string groupValue;
    // Current entity type
    int currentObjectType;
    // Stores the group codes
    std::map<int, std::string> values;
    // First call of this method. We initialize all group values in
    //  the first call.
    bool firstCall;

};

//}


#endif // DXFHEADER_H
