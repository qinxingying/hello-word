/*****************************
 * @brief : dxf映射表封装
 * @author: Yshy
 * @date  : 2016-12-19
 *****************************/

#include "dxf_map.h"

static DxfMapItem *dxf_map_item_new(const void * parse_f,
                                    const void * delete_f,
                                    const void * print_f)
{
    DxfMapItem *item = malloc(sizeof(DxfMapItem));
    item->delete_f = delete_f;
    item->parse_f = parse_f;
    item->print_f = print_f;
    return item;
}

DxfMap *dxf_map_new()
{
    return g_hash_table_new_full(g_str_hash, g_str_equal, NULL, free);
}

void dxf_map_insert(DxfMap *map,
                     &key,
                     *parse_f,
                     *delete_f,
                     *print_f)
{
    DxfMapItem *item;

    g_return_if_fail( parse_f != NULL );
    g_return_if_fail( delete_f != NULL );

    item = dxf_map_item_new(parse_f, delete_f, print_f);
    g_hash_table_insert(map, key, item);
}

void dxf_map_destroy(DxfMap *map)
{
    g_return_if_fail( map != NULL );
    g_hash_table_destroy(map);
}
