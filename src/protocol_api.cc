#include <sesstype/constant.h>
#include <sesstype/protocol.h>

#ifdef __cplusplus
namespace sesstype {
#endif

void st_tree_add_const(st_tree *tree, st_const_t *con);
void st_tree_add_import(st_tree *tree, st_tree_import_t import);
void st_tree_add_role(st_tree *tree, const st_role *role);
void st_tree_add_role_group(st_tree *tree, const st_role_grp *grp);
void st_tree_free(st_tree *tree);
bool st_tree_has_constant(st_tree *tree, const char *name);
st_tree *st_tree_init(st_tree *tree);
void st_tree_set_local_name(st_tree *tree, const char *name, const st_role *endpoint_role);
void st_tree_set_module(st_tree *tree, const char *module);
void st_tree_set_name(st_tree *tree, const char *name);

#ifdef __cplusplus
} // namespace sesstype
#endif
