#include <sesstype/session.h>
#include <sesstype/parameterised/const.h>
#include <sesstype/parameterised/session.h>

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

void st_tree_add_const(st_tree *tree, st_const *con);
void st_tree_add_role_group(st_tree *tree, const st_role_grp *grp);
bool st_tree_has_constant(st_tree *tree, const char *name);

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif
