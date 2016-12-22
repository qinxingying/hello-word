/*****************************
 * @brief : dxf tables层
 * @author: Yshy
 * @date  : 2016-12-19
 *****************************/

#include "dxf_tables.h"

/**
 * @brief table_new_item    创建DxfTable变量
 * @return                  返回DxfTable类型数据
 */
static inline DxfTable *table_new_item();

/**
 * @brief table_parse   单表解析
 * @param f             Dxfile类型
 * @return              成功返回DxfTable类型数据，失败返回NULL
 */
static DxfTable *table_parse(Dxfile *f);

/**
 * @brief table_print   单表打印
 * @param data          DxfTable类型
 * @param userData      保存输出数据
 */
static void table_print(void * data, void * userData);

/**
 * @brief table_delete  单表删除操作
 * @param data          DxfTable类型
 */
static void table_delete(void * data);

void dxf_tables_init()
{
    dxf_tables_entries_init();
}

void dxf_tables_uninit()
{
    dxf_tables_entries_uninit();
}

static inline DxfTable *table_new_item()
{
    return malloc(sizeof(DxfTable));
}

static DxfTable *table_parse(Dxfile *f)
{
    DxfTable *t = NULL;

    t = table_new_item();

    SWITCH_CODE_BEGIN(f);
    SWITCH_CODE_DO( 2 )
            /*表名*/
            dxfile_get_line(f, &t->name, NULL);
    SWITCH_CODE_DO( 5 )
            /*句柄*/
            dxfile_get_line(f, &t->handle, NULL);
    SWITCH_CODE_DO( 330 )
            dxfile_get_line(f, &t->softPointerHandler, NULL);
    SWITCH_CODE_DO( 100 ) {}
    SWITCH_CODE_DO_FOLLOW( 70 )
            dxfile_goto_nextline(f);
    SWITCH_CODE_END(f);

    t->entries = dxf_tables_entries_parse(f);

    return t;
}

DxfTables *dxf_tables_parse(Dxfile *f)
{
    DxfTables *tables = NULL;   /*表链表*/
    DxfTable *t = NULL;         /*表数据*/
    Section s;

    g_return_val_if_fail( f != NULL, NULL );

    if( !dxfile_lseek_section(f, DXF_SECTION_TABLES) ) {
        return NULL;
    }

    while (!dxfile_is_end(f)) {
        dxfile_get_section(f, &s);
        if (section_is_end(&s)) {
            break;
        }

        if (! section_check(&s, 0, "TABLE")) {
            c_log_warning("[%s] invalid section(%d:%s)", __func__, s.code, s.value);
            continue;
        }

        t = table_parse(f);
        if (NULL == t) {
            break;
        }

        tables = g_list_append(tables, t);
    }

    return tables;
}

static void table_delete(void * data)
{
    g_return_if_fail(data != NULL);

    DxfTable *t = (DxfTable *)data;

    free(t->handle);
    free(t->name);
    free(t->softPointerHandler);

    dxf_tables_entries_delete(t->entries);

    free(t);
}

void dxf_tables_delete(DxfTables *t)
{
    if ( t != NULL ) {
        g_list_free_full(t, table_delete);
    }
}

static void table_print(void * data, void * userData)
{
    DxfTable *t = (DxfTable *)data;
//    DxfTable *item = NULL;

    QString *str = (QString *)userData;
    char *tmp = NULL;

    g_return_if_fail( data != NULL );
    g_return_if_fail( userData != NULL );

    tmp = g_strdup_printf("----- Table %s-----\n"
                          "handle              : %s\n"
                          "soft pointer handle : %s\n",
                          t->name,
                          t->handle,
                          t->softPointerHandler);
    g_string_append(str, tmp);
    free(tmp);

    tmp = dxf_tables_entries_print(t->entries);
    g_string_append(str, tmp);
    free(tmp);
}

char *dxf_tables_print(DxfTables *ts)
{
    QString *out = NULL;

    g_return_val_if_fail( ts != NULL, NULL);

    out = g_string_sized_new(2048);

    g_list_foreach(ts, table_print, out);

    return g_strinfree(out, FALSE);
}
