#include <sesstype/role.h>
#include <sesstype/parameterised/role.h>
#include <sesstype/parameterised/role_grp.h>
#include <sesstype/parameterised/util/role_visitor.h>

namespace sesstype {
namespace parameterised {

void Role::accept(sesstype::parameterised::util::RoleVisitor &v)
{
  v.visit(this);
}

void RoleGrp::accept(sesstype::parameterised::util::RoleVisitor &v)
{
  v.visit(this);
}

} // namespace parameterised

} // namespace sesstype
