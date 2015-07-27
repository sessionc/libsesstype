#include <sesstype/role.h>
#include <sesstype/parameterised/expr.h>
#include <sesstype/parameterised/role.h>

namespace sesstype {
namespace parameterised {

unsigned int st_role_num_dimen(st_role *const role)
{
    if (parameterised::Role *paramrole = dynamic_cast<parameterised::Role *>(role)) {
        return paramrole->num_dimen();
    }
    return 0;
}

st_role *st_role_add_param(st_role *role, st_expr *param)
{
    if (parameterised::Role *paramrole = dynamic_cast<parameterised::Role *>(role)) {
        paramrole->add_param(param);
        return paramrole;
    }
    return role;
}

void st_role_free(st_role *role)
{
  delete role;
}

} // namespace parameterised
} // namespace sesstype
