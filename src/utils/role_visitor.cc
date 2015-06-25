#include <sesstype/role.h>
#include <sesstype/parameterised/role.h>
#include <sesstype/parameterised/role_grp.h>
#include <sesstype/utils/role.h>

namespace sesstype {

void Role::accept(utils::RoleVisitor &v)
{
  v.visit(this);
}

namespace parameterised {

void Role::accept(utils::RoleVisitor &v)
{
  v.visit(this);
}

void RoleGrp::accept(utils::RoleVisitor &v)
{
  v.visit(this);
}

} // namespace parameterised

} // namespace sesstype
