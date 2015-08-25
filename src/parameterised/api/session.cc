#include <sesstype/session.h>
#include <sesstype/parameterised/const.h>
#include <sesstype/parameterised/session.h>

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

st_param_tree *st_param_tree_mk_init(const char *name)
{
    return new Session(name);
}

st_param_tree *st_param_tree_add_role(st_param_tree *const tree, st_param_role *role)
{
    tree->add_role(role);
    return tree;
}

st_param_tree *st_param_tree_set_root(st_param_tree *const tree, st_param_node *root)
{
    tree->set_root(root);
    return tree;
}

st_param_node *st_param_tree_get_root(st_param_tree *const tree)
{
    return tree->root();
}

st_param_tree *st_param_tree_add_role_grp(st_param_tree *const tree, st_role_grp *grp)
{
    tree->add_group(grp);
    return tree;
}

bool st_param_tree_has_role_grp(st_param_tree *const tree, const char *grp_name)
{
    return tree->has_role_grp(grp_name);
}

st_role_grp *st_param_tree_get_role_grp(st_param_tree *const tree, const char *grp_name)
{
    return tree->group(grp_name);
}

void st_param_tree_free(st_param_tree *const tree)
{
    delete tree;
}

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif
