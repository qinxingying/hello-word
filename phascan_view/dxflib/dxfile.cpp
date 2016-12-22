/*************************************
 * @brief : dxf文件操作
 * @author: Yshy
 * @date  : 2016-12-19
 *************************************/

#include "dxfile.h"

static inline Dxfile *dxfile_new_item() { return malloc(sizeof(Dxfile)); }
static int dxfile_encoding(const char *filename);

Dxfile *dxfile_open(const char *filename)
{
    g_return_val_if_fail( filename != NULL, NULL);

    Dxfile *dxfile = NULL;
    GMappedFile *mappedFile = NULL;
    GError *err = NULL;

    mappedFile = g_mapped_file_new(filename, FALSE, &err);
    if (err) {
        g_error("Unable to read file: %s", err->message);
        g_error_free(err);
        return NULL;
    }

    dxfile = dxfile_new_item();
    dxfile->mmpedFile = mappedFile;
    dxfile->contents = g_mapped_file_get_contents(mappedFile);
    dxfile->cur = dxfile->contents;
    dxfile->len = g_mapped_file_get_length(mappedFile);
    dxfile->enc = dxfile_encoding(filename);

    return dxfile;
}

void dxfile_get_line(Dxfile *f, char **str, unsigned int *len)
{
    g_return_if_fail( f != NULL );
    g_return_if_fail( str != NULL );
    g_return_if_fail( *str == NULL );

    char *end = f->cur;

    for (; *end
         && *end != '\n'
         && *end != '\r';
         ++end) {}

    if (len != NULL) {
        *len = end - f->cur;
    }

    if (f->cur == end) {
        *str = g_strdup("");
    } else {
        *str = g_strndup(f->cur, end-f->cur);
    }

    if (*end == '\r') {
        ++end;
    }
    if (*end == '\n') {
        ++end;
    }

    f->cur = end;
}

int dxfile_get_line_str(Dxfile *f, char *s, int size)
{
    g_return_val_if_fail( f != NULL, -1 );
    g_return_val_if_fail( s != NULL, -1);
    g_return_val_if_fail( size > 0, -1);

    char *tmp = s;

    for (;
         size--
         && *f->cur != '\n'
         && *f->cur != '\r';
         ++f->cur ) {
        *tmp++ = *f->cur;
    }
    *tmp = 0;

    if (*f->cur == '\r') {
        ++f->cur;
    }
    if (*f->cur == '\n') {
        ++f->cur;
    }

    return tmp - s;
}

void dxfile_get_section(Dxfile *f, Section *s)
{
    dxfile_get_code(f, &s->code);
    if (s->code == DXF_CODE_INVALID) {
        return;
    }
    dxfile_get_line_str(f, s->value, STR_MAX);
}


void dxfile_destory(Dxfile *f)
{
    g_return_if_fail( f != NULL );
    g_mapped_file_unref(f->mmpedFile);
    free(f);
}

bool dxfile_set_pos(Dxfile *f, long pos)
{
    g_return_val_if_fail( f != NULL, FALSE );
    if ( pos < 0 || pos > f->len ) {
        return FALSE;
    }
    f->cur = f->contents + pos;
    return TRUE;
}

bool dxfile_lseek_section(Dxfile *f, const DxfSectionFlag flag)
{
    char *str = NULL;
    char *needle = NULL;
    char tmp[3] = {0};

    if (f->enc) {
        tmp[0] = '\r';
        tmp[1] = '\n';
    } else {
        tmp[0] = '\n';
    }

    switch (flag) {
    case DXF_SECTION_HEADER:
        needle = g_strdup_printf("2%s%s%s",tmp, SECTION_HEADER, tmp);
        break;
    case DXF_SECTION_CLASSES:
        needle = g_strdup_printf("2%s%s%s",tmp, SECTION_CLASSES, tmp);
        break;
    case DXF_SECTION_TABLES:
        needle = g_strdup_printf("2%s%s%s",tmp, SECTION_TABLES, tmp);
        break;
    case DXF_SECTION_BLOCKS:
        needle = g_strdup_printf("2%s%s%s",tmp, SECTION_BLOCKS, tmp);
        break;
    case DXF_SECTION_ENTITIES:
        needle = g_strdup_printf("2%s%s%s",tmp, SECTION_ENTITIES, tmp);
        break;
    case DXF_SECTION_OBJECTS:
        needle = g_strdup_printf("2%s%s%s",tmp, SECTION_OBJECTS, tmp);
        break;
    default:
        break;
    }

    str = g_strstr_len(f->contents, -1, needle);
    if (NULL == str) {
        free(needle);
        return FALSE;
    }

    f->cur = str + strlen(needle);
    free(needle);
    return TRUE;
}

int dxfile_encoding(const char *filename)
{
    char *str = g_strdup_printf("file %s | grep CRLF", filename);
    int c = 0;
    FILE *fp = NULL;

    fp = popen(str, "r");
    free(str);
    if (fp == NULL) {
        return 0;
    }
    c = fgetc(fp);
    pclose(fp);
    if (c <= 0) {
        return 0;
    }
    return 1;
}
