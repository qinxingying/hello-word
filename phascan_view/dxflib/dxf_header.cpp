#include "dxf_header.h"

#include <algorithm>
#include <string>
#include <cstdio>
#include <cassert>
#include <cmath>

#include <QDebug>
#include "dxf_headeradapter.h"

//namespace DplDxf {

DxfHeader::DxfHeader()
{

}

DxfHeader::~DxfHeader()
{

}

/**
 * @brief Reads the given file and calls the appropriate functions in
 * the given creation interface for every entity found in the file.
 *
 * @param file Input
 *      Path and name of file to read
 * @param creationInterface
 *      Pointer to the class which takes care of the entities in the file.
 *
 * @retval true If \p file could be opened.
 * @retval false If \p file could not be opened.
 */
bool DxfHeader::in(const std::string& file, Dxf_HeaderInterface* headerInterface) {
    FILE *fp;
    firstCall = true;
    currentObjectType = 0;

    fp = fopen(file.c_str(), "rt");
    if (fp) {
        while (readDxfGroups(fp, headerInterface)) {}
        fclose(fp);
        return true;
    }

    return false;
}


/**
 * Reads a DXF file from an existing stream.
 *
 * @param stream The string stream.
 * @param creationInterface
 *      Pointer to the class which takes care of the entities in the file.
 *
 * @retval true If \p file could be opened.
 * @retval false If \p file could not be opened.
 */
bool DxfHeader::in(std::stringstream& stream,
                   Dxf_HeaderInterface* headerInterface) {
    if (stream.good()) {
        firstCall=true;
        currentObjectType = 0;
        while (readDxfGroups(stream, headerInterface)) {}
        return true;
    }
    return false;
}



/**
 * @brief Reads a group couplet from a DXF file.  Calls another function
 * to process it.
 *
 * A group couplet consists of two lines that represent a single
 * piece of data.  An integer constant on the first line indicates
 * the type of data.  The value is on the next line.\n
 *
 * This function reads a couplet, determines the type of data, and
 * passes the value to the the appropriate handler function of
 * \p creationInterface.\n
 *
 * \p fp is advanced so that the next call to \p readDXFGroups() reads
 * the next couplet in the file.
 *
 * @param fp Handle of input file
 * @param creationInterface Handle of class which processes entities
 *      in the file
 *
 * @retval true If EOF not reached.
 * @retval false If EOF reached.
 */
bool DxfHeader::readDxfGroups(FILE *fp, Dxf_HeaderInterface* headerInterface) {
    static int line = 1;

    // Read one group of the DXF file and strip the lines:
    if (DxfHeader::getStrippedLine(groupCodeTmp, DL_DXF_MAXLINE, fp) &&
           DxfHeader::getStrippedLine(groupValue, DL_DXF_MAXLINE, fp, false) ) {

        groupCode = (unsigned int)toInt(groupCodeTmp);

        headerInterface->processCodeValuePair(groupCode, groupValue);
        line+=2;
        processDXFGroup(headerInterface, groupCode, groupValue);
    }

    return !feof(fp);
}



/**
 * Same as above but for stringstreams.
 */
bool DxfHeader::readDxfGroups(std::stringstream& stream,
                              Dxf_HeaderInterface* headerInterface) {

    static int line = 1;

    // Read one group of the DXF file and chop the lines:
    if (DxfHeader::getStrippedLine(groupCodeTmp, DL_DXF_MAXLINE, stream) &&
            DxfHeader::getStrippedLine(groupValue, DL_DXF_MAXLINE, stream, false) ) {

        groupCode = (unsigned int)toInt(groupCodeTmp);

        line+=2;
        processDXFGroup(headerInterface, groupCode, groupValue);
    }
    return !stream.eof();
}



/**
 * @brief Reads line from file & strips whitespace at start and newline
 * at end.
 *
 * @param s Output\n
 *      Pointer to character array that chopped line will be returned in.
 * @param size Size of \p s.  (Including space for NULL.)
 * @param fp Input\n
 *      Handle of input file.
 *
 * @retval true if line could be read
 * @retval false if \p fp is already at end of file
 *
 * @todo Change function to use safer FreeBSD strl* functions
 * @todo Is it a problem if line is blank (i.e., newline only)?
 *      Then, when function returns, (s==NULL).
 */
bool DxfHeader::getStrippedLine(std::string& s, unsigned int size, FILE *fp, bool stripSpace) {
    if (!feof(fp)) {
        // The whole line in the file.  Includes space for NULL.
        char* wholeLine = new char[size];
        // Only the useful part of the line
        char* line;

        line = fgets(wholeLine, size, fp);

        if (line!=NULL && line[0] != '\0') { // Evaluates to fgets() retval
            // line == wholeLine at this point.
            // Both guaranteed to be NULL terminated.

            // Strip leading whitespace and trailing CR/LF.
            stripWhiteSpace(&line, stripSpace);

            s = line;
            assert(size > s.length());
        }

        delete[] wholeLine; // Done with wholeLine

        return true;
    } else {
        s = "";
        return false;
    }
}



/**
 * Same as above but for stringstreams.
 */
bool DxfHeader::getStrippedLine(std::string &s, unsigned int size,
                            std::stringstream& stream, bool stripSpace) {

    if (!stream.eof()) {
        // Only the useful part of the line
        char* line = new char[size+1];
        char* oriLine = line;
        stream.getline(line, size);
        stripWhiteSpace(&line, stripSpace);
        s = line;
        assert(size > s.length());
        delete[] oriLine;
        return true;
    } else {
        s[0] = '\0';
        return false;
    }
}



/**
 * @brief Strips leading whitespace and trailing Carriage Return (CR)
 * and Line Feed (LF) from NULL terminated string.
 *
 * @param s Input and output.
 *      NULL terminates string.
 *
 * @retval true if \p s is non-NULL
 * @retval false if \p s is NULL
 */
bool DxfHeader::stripWhiteSpace(char** s, bool stripSpace) {
    // last non-NULL char:
    int lastChar = strlen(*s) - 1;

    // Is last character CR or LF?
    while ( (lastChar >= 0) &&
            (((*s)[lastChar] == 10) || ((*s)[lastChar] == 13) ||
             (stripSpace && ((*s)[lastChar] == ' ' || ((*s)[lastChar] == '\t')))) ) {
        (*s)[lastChar] = '\0';
        lastChar--;
    }

    // Skip whitespace, excluding \n, at beginning of line
    if (stripSpace) {
        while ((*s)[0]==' ' || (*s)[0]=='\t') {
            ++(*s);
        }
    }

    return ((*s) ? true : false);
}

/**
 * Processes a group (pair of group code and value).
 *
 * @param creationInterface Handle to class that creates entities and
 * other CAD data from DXF group codes
 *
 * @param groupCode Constant indicating the data type of the group.
 * @param groupValue The data value.
 *
 * @retval true if done processing current entity and new entity begun
 * @retval false if not done processing current entity
*/
bool DxfHeader::processDXFGroup(Dxf_HeaderInterface* headerInterface, int groupCode, const std::string& groupValue) {

    //printf("%d\n", groupCode);
    //printf("%s\n", groupValue.c_str());

    // Init values on first call
    if (firstCall) {
        firstCall=false;
    }

/*    // Indicates comment or dxflib version:
    if (groupCode==999) {
        if (!groupValue.empty()) {
            if (groupValue.substr(0, 6)=="dxflib") {
                libVersion = getLibVersion(groupValue.substr(7));
            }

//            addComment(creationInterface, groupValue);
        }
    }

    // Indicates start of new entity or variable:
    else */if (groupCode==0 || groupCode==9) {
        // If new entity is encountered, the last one is complete.
        // Prepare default attributes for next entity:
//        std::string layer = getStringValue(8, "0");

//        int width;
//        // Compatibility with qcad1:
//        if (hasValue(39) && !hasValue(370)) {
//            width = getIntValue(39, -1);
//        }
//        // since autocad 2002:
//        else if (hasValue(370)) {
//            width = getIntValue(370, -1);
//        }
//        // default to BYLAYER:
//        else {
//            width = -1;
//        }

//        int color;
//        color = getIntValue(62, 256);
//        int color24;
//        color24 = getIntValue(420, -1);
//        int handle;
//        handle = getIntValue(5, -1);

//        std::string linetype = getStringValue(6, "BYLAYER");

//        attrib = DL_Attributes(layer,                   // layer
//                               color,                   // color
//                               color24,                 // 24 bit color
//                               width,                   // width
//                               linetype,                // linetype
//                               handle);                 // handle
//        attrib.setInPaperSpace((bool)getIntValue(67, 0));
//        attrib.setLinetypeScale(getRealValue(48, 1.0));
//        creationInterface->setAttributes(attrib);

//        int elevationGroupCode=30;
//        if (currentObjectType==DL_ENTITY_LWPOLYLINE ) {
//            // see lwpolyline group codes reference
//            elevationGroupCode=38;
//        }
//        else {
//            // see polyline group codes reference
//            elevationGroupCode=30;
//        }

//        creationInterface->setExtrusion(getRealValue(210, 0.0),
//                                        getRealValue(220, 0.0),
//                                        getRealValue(230, 1.0),
//                                        getRealValue(elevationGroupCode, 0.0));

        switch (currentObjectType) {
        case HEADER_ACADVER:
            add_version(headerInterface);
            break;

        case HEADER_ANGDIR:
            add_angle_dir(headerInterface);
            break;

        case HEADER_INSUNITS:
            add_unit(headerInterface);
            break;

        case HEADER_PUCSNAME:
            add_PUCS_name(headerInterface);
            break;

        case HEADER_PUCSORG:
            add_point_PUCSORG(headerInterface);
            break;

        case HEADER_PUCSXDIR:
            add_point_PUCSXDIR(headerInterface);
            break;

        case HEADER_PUCSYDIR:
            add_point_PUCSYDIR(headerInterface);
            break;

        case HEADER_UCSNAME:
            add_UCS_name(headerInterface);
            break;

        case HEADER_UCSORG:
            add_point_UCSORG(headerInterface);
            break;

        case HEADER_UCSXDIR:
            add_point_UCSXDIR(headerInterface);
            break;

        case HEADER_UCSYDIR:
            add_point_UCSYDIR(headerInterface);
            break;

        case HEADER_LTSCALE:
            add_line_scale(headerInterface);
            break;

        default:
            break;
        }

        values.clear();

        if (groupValue == "$ACADVER") {
            currentObjectType = HEADER_ACADVER;
        } else if (groupValue == "$ANGDIR") {
            currentObjectType = HEADER_ANGDIR;
        } else if (groupValue == "$INSUNITS") {
            currentObjectType = HEADER_INSUNITS;
        } else if (groupValue == "$PUCSNAME") {
            currentObjectType = HEADER_PUCSNAME;
        } else if (groupValue == "$PUCSORG") {
            currentObjectType = HEADER_PUCSORG;
        } else if (groupValue == "$PUCSXDIR") {
            currentObjectType = HEADER_PUCSXDIR;
        } else if (groupValue == "$PUCSYDIR") {
            currentObjectType = HEADER_PUCSYDIR;
        } else if (groupValue == "$UCSNAME") {
            currentObjectType = HEADER_UCSNAME;
        } else if (groupValue == "$UCSORG") {
            currentObjectType = HEADER_UCSORG;
        } else if (groupValue == "$UCSXDIR") {
            currentObjectType = HEADER_UCSXDIR;
        } else if (groupValue == "$UCSYDIR") {
            currentObjectType = HEADER_UCSYDIR;
        } else if (groupValue == "$LTSCALE") {
            currentObjectType = HEADER_LTSCALE;
        } else {
            currentObjectType = 0;
        }

        // Add the previously parsed entity via creationInterface


//        creationInterface->endSection();

        // reset all values (they are not persistent and only this
        //  way we can set defaults for omitted values)
//        for (int i=0; i<DL_DXF_MAXGROUPCODE; ++i) {
//            values[i][0] = '\0';
//        }


        // Last DXF entity or setting has been handled
        // Now determine what the next entity or setting type is

//        int prevEntity = currentObjectType;

//         Read DXF variable:
//        if (groupValue[0]=='$') {
//            currentObjectType = DL_SETTING;
//            settingKey = groupValue;
//        }




        // TODO: end of SPLINE entity
        //if (prevEntity==DL_ENTITY_CONTROLPOINT && currentEntity!=DL_ENTITY_CONTROLPOINT) {
        //    endEntity(creationInterface);
        //}

        return true;

    } else {

        values[groupCode] = groupValue;
    }

    /* else {
        // Group code does not indicate start of new entity or setting,
        // so this group must be continuation of data for the current
        // one.
        if (groupCode<DL_DXF_MAXGROUPCODE) {

            bool handled = false;

            switch (currentObjectType) {
            case DL_ENTITY_MTEXT:
                handled = handleMTextData(creationInterface);
                break;

            case DL_ENTITY_LWPOLYLINE:
                handled = handleLWPolylineData(creationInterface);
                break;

            case DL_ENTITY_SPLINE:
                handled = handleSplineData(creationInterface);
                break;

            case DL_ENTITY_LEADER:
                handled = handleLeaderData(creationInterface);
                break;

            case DL_ENTITY_HATCH:
                handled = handleHatchData(creationInterface);
                break;

            case DL_XRECORD:
                handled = handleXRecordData(creationInterface);
                break;

            case DL_DICTIONARY:
                handled = handleDictionaryData(creationInterface);
                break;

            case DL_LINETYPE:
                handled = handleLinetypeData(creationInterface);
                break;

            default:
                break;
            }

            // Always try to handle XData, unless we're in an XData record:
            if (currentObjectType!=DL_XRECORD) {
                handled = handleXData(creationInterface);
            }

            if (!handled) {
                // Normal group / value pair:
                values[groupCode] = groupValue;
            }
        }

        return false;
    }*/
    return false;
}

void DxfHeader::add_version(Dxf_HeaderInterface* headerInterface)
{
    DXF_HEADER_ACADVER d(getStringValue(1, ""));
    headerInterface->add_version(d);
//    qDebug() << "version" << d->m_dataACadVer->version.c_str();
}

void DxfHeader::add_angle_dir(Dxf_HeaderInterface* headerInterface)
{
//    d->m_dataAngDir->flags = getIntValue(70, 0);
    DXF_HEADER_ANGDIR d(getIntValue(70, 0));
    headerInterface->add_angle_dir(d);
//    qDebug() << "angle flag" << d->m_dataAngDir->flags;
}

void DxfHeader::add_unit(Dxf_HeaderInterface* headerInterface)
{
//    d->m_dataInsUnits->flags = getIntValue(70, 0);
    DXF_HEADER_INSUNITS d(getIntValue(70, 0));
    headerInterface->add_unit(d);
//    qDebug() << "ins unit flag" << d->m_dataInsUnits->flags;
}

void DxfHeader::add_PUCS_name(Dxf_HeaderInterface* headerInterface)
{
    DXF_HEADER_PUCSNAME d(getStringValue(2, ""));
    headerInterface->add_PUCS_name(d);
//    d->m_dataPUCSName->name = getStringValue(2, "");
//    qDebug() << "pucs name" << d->m_dataPUCSName->name.c_str();
}

void DxfHeader::add_point_PUCSORG(Dxf_HeaderInterface* headerInterface)
{
    DXF_HEADER_PUCSORG d(getRealValue(10, 0.0),
                         getRealValue(20, 0.0),
                         getRealValue(30, 0.0));
    headerInterface->add_point_PUCSORG(d);
//    d->m_dataPUCSOrg->x = getRealValue(10, 0.0);
//    d->m_dataPUCSOrg->y = getRealValue(20, 0.0);
//    d->m_dataPUCSOrg->z = getRealValue(30, 0.0);
//    qDebug() << "pucs org" << d->m_dataPUCSOrg->x << d->m_dataPUCSOrg->y << d->m_dataPUCSOrg->z;
}

void DxfHeader::add_point_PUCSXDIR(Dxf_HeaderInterface* headerInterface)
{
    DXF_HEADER_PUCSXDIR d(getRealValue(10, 0.0),
                          getRealValue(20, 0.0),
                          getRealValue(30, 0.0));
    headerInterface->add_point_PUCSXDIR(d);
//    d->m_dataPUCSXDir->x = getRealValue(10, 0.0);
//    d->m_dataPUCSXDir->y = getRealValue(20, 0.0);
//    d->m_dataPUCSXDir->z = getRealValue(30, 0.0);
//    qDebug() << "pucs x dir" << d->m_dataPUCSXDir->x << d->m_dataPUCSXDir->y << d->m_dataPUCSXDir->z;
}

void DxfHeader::add_point_PUCSYDIR(Dxf_HeaderInterface* headerInterface)
{
    DXF_HEADER_PUCSYDIR d(getRealValue(10, 0.0),
                          getRealValue(20, 0.0),
                          getRealValue(30, 0.0));
    headerInterface->add_point_PUCSYDIR(d);
//    d->m_dataPUCSYDir->x = getRealValue(10, 0.0);
//    d->m_dataPUCSYDir->y = getRealValue(20, 0.0);
//    d->m_dataPUCSYDir->z = getRealValue(30, 0.0);
//    qDebug() << "pucs y dir" << d->m_dataPUCSYDir->x << d->m_dataPUCSYDir->y << d->m_dataPUCSYDir->z;
}

void DxfHeader::add_UCS_name(Dxf_HeaderInterface* headerInterface)
{
    DXF_HEADER_UCSNAME d(getStringValue(2, ""));
    headerInterface->add_UCS_name(d);
//    d->m_dataUCSName->name = getStringValue(2, "");
//    qDebug() << "usc name" << d->m_dataUCSName->name.c_str();
}

void DxfHeader::add_point_UCSORG(Dxf_HeaderInterface* headerInterface)
{
    DXF_HEADER_UCSORG d(getRealValue(10, 0.0),
                        getRealValue(20, 0.0),
                        getRealValue(30, 0.0));
    headerInterface->add_point_UCSORG(d);
//    d->m_dataUCSOrg->x = getRealValue(10, 0.0);
//    d->m_dataUCSOrg->y = getRealValue(20, 0.0);
//    d->m_dataUCSOrg->z = getRealValue(30, 0.0);
//    qDebug() << "ucs org" << d->m_dataUCSOrg->x << d->m_dataUCSOrg->y << d->m_dataUCSOrg->z;
}

void DxfHeader::add_point_UCSXDIR(Dxf_HeaderInterface* headerInterface)
{
    DXF_HEADER_UCSXDIR d(getRealValue(10, 0.0),
                         getRealValue(20, 0.0),
                         getRealValue(30, 0.0));
    headerInterface->add_point_UCSXDIR(d);
//    d->m_dataUCSXDir->x = getRealValue(10, 0.0);
//    d->m_dataUCSXDir->y = getRealValue(20, 0.0);
//    d->m_dataUCSXDir->z = getRealValue(30, 0.0);
//    qDebug() << "ucs x dir" << d->m_dataUCSXDir->x << d->m_dataUCSXDir->y << d->m_dataUCSXDir->z;
}

void DxfHeader::add_point_UCSYDIR(Dxf_HeaderInterface* headerInterface)
{
    DXF_HEADER_UCSYDIR d(getRealValue(10, 0.0),
                         getRealValue(20, 0.0),
                         getRealValue(30, 0.0));
    headerInterface->add_point_UCSYDIR(d);
//    d->m_dataUCSYDir->x = getRealValue(10, 0.0);
//    d->m_dataUCSYDir->y = getRealValue(20, 0.0);
//    d->m_dataUCSYDir->z = getRealValue(30, 0.0);
//    qDebug() << "ucs y dir" << d->m_dataUCSYDir->x << d->m_dataUCSYDir->y << d->m_dataUCSYDir->z;
}

void DxfHeader::add_line_scale(Dxf_HeaderInterface* headerInterface)
{
    DXF_HEADER_LTSCALE d(getRealValue(40, 1.0));
    headerInterface->add_line_scale(d);
//    d->m_dataLtScale->lineScale = getRealValue(40, 1.0);
//    qDebug() << "line scale" << d->m_dataLtScale->lineScale;
}

//}

//void DxfHeader::dxf_header_init()
//{
////    g_return_if_fail( headerMap == NULL );
////    headerMap = g_hash_table_new(g_str_hash, g_str_equal);

////    g_hash_table_insert(headerMap, HEADER_ACADVER, header_acadver);
////    g_hash_table_insert(headerMap, HEADER_ANGDIR, header_angdir);
////    g_hash_table_insert(headerMap, HEADER_INSUNITS, header_insunits);

////    g_hash_table_insert(headerMap, HEADER_PUCSNAME, header_pucsname);
////    g_hash_table_insert(headerMap, HEADER_PUCSORG, header_pucsorg);
////    g_hash_table_insert(headerMap, HEADER_PUCSXDIR, header_pucsxdir);
////    g_hash_table_insert(headerMap, HEADER_PUCSYDIR, header_pucsydir);

////    g_hash_table_insert(headerMap, HEADER_UCSNAME, header_ucsname);
////    g_hash_table_insert(headerMap, HEADER_UCSORG, header_ucsorg);
////    g_hash_table_insert(headerMap, HEADER_UCSXDIR, header_ucsxdir);
////    g_hash_table_insert(headerMap, HEADER_UCSYDIR, header_ucsydir);

////    g_hash_table_insert(headerMap, HEADER_LTSCALE, header_ltscale);
//}

//void dxf_header_uninit()
//{
////    g_return_if_fail( headerMap != NULL );
////    g_hash_table_destroy(headerMap);
//}

//DxfHeader * DxfHeader::dxf_header_parse(const std::string& f)
//{
//    QString varName = NULL;
//    VarFun var_f = NULL;

//    if(f == NULL) {
//       return NULL;
//    }

////    if(!dxfile_lseek_section(f, DXF_SECTION_HEADER) ) {
////        return NULL;
////    }

//    g_dxfHeader = dxf_header_new_item();

//    int code = 0;
//    long pos = dxfile_get_pos(f);
//    for(dxfile_get_code(f, &code); code && (code != DXF_CODE_INVALID); ) {
//        switch(code) {
//        case HEADER_ACADVER:
//            header_acadver(f, g_dxfHeader);
//            break;
//        case HEADER_ANGDIR:
//            header_angdir(f, g_dxfHeader);
//            break;
//        case HEADER_INSUNITS:
//            header_insunits(f, g_dxfHeader);
//            break;
//        case HEADER_PUCSNAME:
//            header_pucsname(f, g_dxfHeader);
//            break;
//        case HEADER_PUCSORG:
//            header_pucsorg(f, g_dxfHeader);
//            break;
//        case HEADER_PUCSXDIR:
//            header_pucsxdir(f, g_dxfHeader);
//            break;
//        case HEADER_PUCSYDIR:
//            header_pucsydir(f, g_dxfHeader);
//            break;
//        case HEADER_UCSNAME:
//            header_ucsname(f, g_dxfHeader);
//            break;
//        case HEADER_UCSORG:
//            header_ucsorg(f, g_dxfHeader);
//            break;
//        case HEADER_UCSXDIR:
//            header_ucsxdir(f, g_dxfHeader);
//            break;
//        case HEADER_UCSYDIR:
//            header_ucsydir(f, g_dxfHeader);
//            break;
//        case HEADER_LTSCALE:
//            header_ltscale(f, g_dxfHeader);
//            break;
//        default:
//            break;
//        }

//    }

////    SWITCH_CODE_BEGIN(f);
////    SWITCH_CODE_DO( 9 ) {
////        /*获取变量名称,并处理*/
////        dxfile_get_line(f, &varName, NULL);
////        var_f = g_hash_table_lookup(headerMap, varName);
////        g_free(varName);
////        varName = NULL;
////        if (var_f != NULL) {
////            var_f(f, h);
////        }
////    }
////    SWITCH_CODE_END(f);

//    return h;
//}

//void DxfHeader::dxf_header_delete(DxfHeader *h)
//{
//    g_return_if_fail( h != NULL );

//    g_free(h->acadver);
//    g_free(h->pucsname);
//    g_free(h->ucsname);

//    g_free(h);
//}

//QString DxfHeader::dxf_header_print(DxfHeader *h)
//{
//    g_return_val_if_fail( h != NULL, NULL );
//    return g_strdup_printf("----- Header -----\n"
//                           "$ACADVER    : %s\n"
//                           "$ANGDIR     : %d\n"
//                           "$INSUNITS   : %d\n"
//                           "$PUCSNAME   : %s\n"
//                           "$PUCSORG    : (%g, %g, %g)\n"
//                           "$PUCSXDIR   : (%g, %g, %g)\n"
//                           "$PUCSYDIR   : (%g, %g, %g)\n"
//                           "$UCSNAME    : %s\n"
//                           "$UCSORG     : (%g, %g, %g)\n"
//                           "$UCSXDIR    : (%g, %g, %g)\n"
//                           "$UCSYDIR    : (%g, %g, %g)\n"
//                           "$LTSCALE    : %g\n",
//                           h->acadver,
//                           h->angdir,
//                           h->insunits,
//                           h->pucsname,
//                           h->pucsorg.x, h->pucsorg.y, h->pucsorg.z,
//                           h->pucsxdir.x, h->pucsxdir.y, h->pucsxdir.z,
//                           h->pucsydir.x, h->pucsydir.y, h->pucsydir.z,
//                           h->ucsname,
//                           h->ucsorg.x, h->ucsorg.y, h->ucsorg.z,
//                           h->ucsxdir.x, h->ucsxdir.y, h->ucsxdir.z,
//                           h->ucsydir.x, h->ucsydir.y, h->ucsydir.z,
//                           h->ltscale);
//}

//static void DxfHeader::header_get_point(Dxfile *f, DxfPointData *p)
//{
//    gint code = 0;
//    glong pos = 0;
//    gboolean flag = TRUE;
//    while( flag ) {
//        pos = dxfile_get_pos(f);
//        dxfile_get_code(f, &code);
//        switch( code ) {
//        case 10:
//            dxfile_get_double(f, &p->x);
//            break;
//        case 20:
//            dxfile_get_double(f, &p->y);
//            break;
//        case 30:
//            dxfile_get_double(f, &p->z);
//            break;
//        default:
//            flag = FALSE;
//            break;
//        }
//    }
//    dxfile_set_pos(f, pos);
//}

//static inline void DxfHeader::header_get_line(Dxfile *f, gchar **str)
//{
//    dxfile_goto_nextline(f);
//    dxfile_get_line(f, str, NULL);
//}

//static DxfHeader* DxfHeader::dxf_header_new_item()
//{
//    DxfHeader *h = malloc(sizeof(DxfHeader));
//    h->d->angdir = DXF_ANGDIR_COUNTERCLOCKWISE;
//    h->d->insunits = DXF_UNIT_MM;
//    h->d->ucsxdir.x = DXF_AXIS_X_RIGHT;
//    h->d->ucsydir.y = DXF_AXIS_Y_UPWARD;
//    return h;
//}

//}


