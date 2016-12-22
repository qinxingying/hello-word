/*************************************
 * @brief : dxf entities层, 3dsolid对象
 * @author: Yshy
 * @date  : 2016-12-19
 *************************************/

#include "entities_3dsolid.h"

static inline Dxf3Dsolid *dxf3dsolid_new_item()
{
    return malloc(sizeof(Dxf3Dsolid));
}

Dxf3Dsolid *dxf_3dsolid_parse(Dxfile *f)
{
    Dxf3Dsolid *e = NULL;
    char *data = NULL;
    DxfPropData *propData = NULL;

    e = dxf3dsolid_new_item();

    SWITCH_CODE_BEGIN(f);
    SWITCH_CODE_DO( DXF_3DSOLID_CODE_VERSION )
            dxfile_get_int16(f, &e->version);
    SWITCH_CODE_DO( DXF_3DSOLID_CODE_PROPRIETARY_DATA )
    SWITCH_CODE_DO_FOLLOW( DXF_3DSOLID_CODE_ADDITIONAL_PROPRIETARY_DATA ) {
        data = NULL;
        dxfile_get_line(f, &data, NULL);
        if (NULL == propData) {
            propData = malloc(sizeof(DxfPropData));
            e->proprietaryData = propData;
        } else {
            propData->next = malloc(sizeof(DxfPointData));
            propData = propData->next;
        }
        propData->data = data;
    }
    SWITCH_CODE_END(f);

    return e;
}

void dxf_3dsolid_delete(Dxf3Dsolid *e)
{
    DxfPropData *propData = NULL;

    g_return_if_fail( e != NULL );

    while(e->proprietaryData) {
        propData = e->proprietaryData->next;
        free(e->proprietaryData->data);
        free(e->proprietaryData);
        e->proprietaryData = propData;
    }

    free(e);
}

char *dxf_3dsolid_print(Dxf3Dsolid *e)
{
    DxfPropData *d;
    QString *msg = NULL;

    g_return_val_if_fail( e != NULL, NULL );
    g_return_val_if_fail( e->proprietaryData != NULL, NULL);

    msg = g_string_sized_new(1024);
    g_string_append_printf(msg,
                           "Version       : %d\n"
                           "Data          :\n",
                           e->version);

    for (d = e->proprietaryData; d; d = d->next) {
        g_string_append_printf(msg, "%s\n", d->data);
    }

    return g_strinfree(msg, FALSE);
}
