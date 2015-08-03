#include <sesstype/role.h>
#include <sesstype/util/role_visitor.h>

namespace sesstype {

void Role::accept(util::RoleVisitor &v)
{
    v.visit(this);
}

} // namespace sesstype
