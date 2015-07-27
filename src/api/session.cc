#include <sesstype/import.h>
#include <sesstype/session.h>
#include <sesstype/role.h>

#ifdef __cplusplus
namespace sesstype {
#endif

st_tree *st_tree_mk_init(const char *name)
{
    return new Session(name);
}

st_tree *st_tree_add_role(st_tree *tree, st_role *role)
{
    tree->add_role(role);
    return tree;
}

st_tree *st_tree_set_root(st_tree *tree, st_node *root)
{
    tree->set_root(root);
    return tree;
}

void st_tree_free(st_tree *tree)
{
    delete tree;
}

#ifdef __cplusplus
} // namespace sesstype
#endif
