/**
 * @file dxf_map.h
 * @brief dxf映射表封装
 * @author JakeYang <add358@gmail.com>
 * @version 0.2
 * @date 2015-04-14
 */

#ifndef __DXF_MAP_H__
#define __DXF_MAP_H__

#include "dxfile.h"

/* 定义解析、删除、打印函数的类型 */
typedef void * (*parse_fun_t)(Dxfile *f);
typedef void (*delete_fun_t)(void * e);
typedef char *(*print_fun_t)(void * e);

/* 定义映射表和映射表项目 类型 */
typedef GHashTable DxfMap;
typedef struct _DxfMapItem DxfMapItem;
struct _DxfMapItem {
    parse_fun_t parse_f;
    delete_fun_t delete_f;
    print_fun_t print_f;
};

extern DxfMap *dxf_map_new();
extern void dxf_map_insert(DxfMap *map,
                            &key,
                            * parse_f,
                            * delete_f,
                            * print_f);
extern void dxf_map_destroy(DxfMap *map);

#endif /* End of __DXF_MAP_H__ */
