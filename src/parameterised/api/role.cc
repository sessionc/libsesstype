#include "sesstype/parameterised/expr.h"
#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/util/print.h"

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
