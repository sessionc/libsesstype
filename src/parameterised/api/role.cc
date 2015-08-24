#include "sesstype/parameterised/expr.h"
#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/util/print.h"

namespace sesstype {
namespace parameterised {

unsigned int st_role_num_dimen(st_param_role *const role)
{
    return role->num_dimens();
}

st_param_role *st_role_add_param(st_param_role *const role, st_expr *param)
{
    role->add_param(param);
    return role;
}

std::ostream &operator<<(std::ostream &os, Role &role)
{
    sesstype::parameterised::util::PrintVisitor printer(os);
    role.accept(printer);
    return os;
}

void st_param_role_free(st_param_role *role)
{
  delete role;
}

} // namespace parameterised
} // namespace sesstype
