#include <sesstype/protocol.h>
#include <sesstype/parameterised/constant.h>
#include <sesstype/parameterised/protocol.h>

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

void st_tree_add_const(st_tree *tree, st_const_t *con);
void st_tree_add_role_group(st_tree *tree, const st_role_grp *grp);
bool st_tree_has_constant(st_tree *tree, const char *name);

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif
