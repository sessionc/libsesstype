#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "sesstype/st_node.h"


#ifdef __cplusplus
extern "C" {
#endif


st_role_group *st_role_group_init(st_role_group *grp)
{
  assert(grp != NULL);
  grp->name = NULL;
  grp->nmemb = 0;
  grp->membs = NULL;

  return grp;
}


st_role_group *st_role_group_set_name(st_role_group *grp, char *name)
{
  assert(grp != NULL);
  if (grp->name != NULL) free(grp->name);
  grp->name = strdup(name);

  return grp;
}


st_role_group *st_role_group_add_role(st_role_group *grp, st_role *role)
{
  assert(grp != NULL && role != NULL);
  grp->membs = (st_role **)realloc(grp->membs, sizeof(st_role *) * (grp->nmemb+1));
  grp->membs[grp->nmemb] = st_role_copy(role);
  grp->nmemb++;

  return grp;
}


st_role_group *st_role_group_copy(st_role_group const *grp)
{
  assert(grp != NULL);
  st_role_group *new_grp = st_role_group_init((st_role_group *)malloc(sizeof(st_role_group)));
  st_role_group_set_name(new_grp, grp->name);
  for (int p=0; p<grp->nmemb; p++) {
    st_role_group_add_role(new_grp, grp->membs[p]);
  }

  return new_grp;
}


void st_role_group_free(st_role_group *grp)
{
  for (int r=0; r<grp->nmemb; r++) {
    st_role_free(grp->membs[r]);
  }
  grp->nmemb = 0;
  if (grp->name != NULL) free(grp->name);
  free(grp);
}


#ifdef __cplusplus
}
#endif
