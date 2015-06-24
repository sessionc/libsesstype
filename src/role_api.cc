#include <sesstype/expr.h>
#include <sesstype/role.h>

namespace sesstype {

st_role *st_role_init(const char *name)
{
  return new Role(name);
}

st_role *st_role_copy(const st_role *const role)
{
  return new Role(*role);
}

const char *st_role_name(st_role *const role)
{
  return role->name().c_str();
}

st_role *st_role_set_name(st_role *const role, const char *name)
{
  role->set_name(name);
  return role;
}

unsigned int st_role_num_dimen(st_role *const role)
{
  return role->num_dimen();
}
st_role *st_role_add_param(st_role *const role, st_expr *param)
{
  role->add_param(param);
  return role;
}

void st_role_free(st_role *role)
{
  delete role;
}

} // namespace sesstype
