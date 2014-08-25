#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "sesstype/st_node.h"


#ifdef __cplusplus
extern "C" {
#endif


st_role *st_role_init(st_role *role)
{
  assert(role != NULL);
  role->name = NULL;
  role->dimen = 0;
  role->param = NULL;

  return role;
}


st_role *st_role_set_name(st_role *role, char *name)
{
  assert(role != NULL);
  if (role->name != NULL) free(role->name);
  role->name = strdup(name);
  return role;
}


st_role *st_role_add_param(st_role *role, st_expr *param)
{
  assert(role != NULL && param != NULL);
  role->param = (st_expr **)realloc(role->param, sizeof(st_expr *) * (role->dimen+1));
  role->param[role->dimen] = param;
  role->dimen++;
  return role;
}


st_role *st_role_copy(st_role const *role)
{
  assert(role != NULL);
  st_role *new_role = st_role_init((st_role *)malloc(sizeof(st_role)));
  st_role_set_name(new_role, role->name);
  for (int p=0; p<role->dimen; p++) {
    st_role_add_param(new_role, st_expr_copy(role->param[p]));
  }

  return new_role;
}


void st_role_free(st_role *role)
{
  for (int r=0; r<role->dimen; r++) {
    st_expr_free(role->param[r]);
  }
  role->param = 0;
  if (role->name != NULL) free(role->name);
  free(role);
}

#ifdef __cplusplus
}
#endif
