#include <sesstype/session.h>
#include <sesstype/parameterised/const.h>
#include <sesstype/parameterised/session.h>

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

st_tree *st_tree_add_role_grp(st_tree *tree, st_role_grp *grp)
{
    if (Session *ptree = dynamic_cast<Session *>(tree)) {
        ptree->add_group(grp);
    }
    return tree;
}

bool st_tree_has_role_grp(st_tree *const tree, const char *grp_name)
{
    if (Session *ptree = dynamic_cast<Session *>(tree)) {
        return ptree->has_role_grp(grp_name);
    }
    return false;
}

st_role_grp *st_tree_get_role_grp(st_tree *const tree, const char *grp_name)
{
    return dynamic_cast<Session *>(tree)->group(grp_name);
}

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif
