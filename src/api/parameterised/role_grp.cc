#include <sesstype/role.h>
#include <sesstype/parameterised/role_grp.h>

namespace sesstype {
namespace parameterised {

st_role_grp *st_role_grp_init(const char *name)
{
    return new RoleGrp(name);
}

const char *st_role_grp_name(const st_role_grp *const role_grp)
{
    return role_grp->name().c_str();
}

st_role_grp *st_role_grp_set_name(st_role_grp *const role_grp, const char *name)
{
    role_grp->set_name(std::string(name));
    return role_grp;
}

void st_role_grp_add_member(st_role_grp *const role_grp, st_role *role)
{
    role_grp->add_member(role);
}

unsigned int st_role_grp_num_member(const st_role_grp *const role_grp)
{
    return role_grp->num_member();
}

void st_role_grp_free(st_role_grp *role_grp)
{
    delete role_grp;
}

} // namespace parameterised
} // namespace sesstype
