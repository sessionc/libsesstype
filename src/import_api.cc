#include <sesstype/import.h>

#ifdef __cplusplus
namespace sesstype {
#endif

st_tree_import_t *st_mk_import(const char *name)
{
  return new Import(std::string(name));
}

st_tree_import_t *st_mk_import_from_as(const char *name, const char *from, const char *as)
{
  return new Import(std::string(name), std::string(from), std::string(as));
}

#ifdef __cplusplus
} // namespace sesstype
#endif
