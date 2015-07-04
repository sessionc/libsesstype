#include <sesstype/import.h>

#ifdef __cplusplus
namespace sesstype {
#endif

st_import *st_import_mk_init(const char *name)
{
    return new Import(name);
}

st_import *st_import_mk_alias(const char *name, const char *from, const char *as)
{
    return new Import(name, from, as);
}

void st_import_free(st_import *import)
{
    delete import;
}

#ifdef __cplusplus
} // namespace sesstype
#endif
