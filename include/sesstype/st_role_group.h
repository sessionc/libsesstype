#ifndef SESSTYPE__ST_ROLE_GROUP__H__
#define SESSTYPE__ST_ROLE_GROUP__H__
/**
 * @file
 * This file contains the data structures and access function to a session type
 * role group.
 */


#ifdef __cplusplus
extern "C" {
#endif


/**
 * Group roles.
 */
typedef struct {
  char *name;         /**< Group name. */
  unsigned int nmemb; /**< Number of Roles in group. */
  st_role **membs;    /**< List of Role pointers. */
} st_role_group;


/**
 * @brief Initialise session type role group.
 *
 * @param[in,out] grp Role group to initialise.
 *
 * @returns Initialised role group.
 */
st_role_group *st_role_group_init(st_role_group *grp);


/**
 * @brief set name of role group.
 *
 * @param[in,out] grp  Role group to update.
 * @param[in]     name Name of the role group.
 *
 * @returns Updated role group.
 */
st_role_group *st_role_group_set_name(st_role_group *grp, char *name);


/**
 * @brief Copy a role to a group.
 *
 * @param[in,out] grp  Role group to update.
 * @param[in]     role Role to add to group.
 *
 * @returns Updated role group.
 */
st_role_group *st_role_group_add_role(st_role_group *grp, st_role *role);


/**
 * @brief Deep copy a role group.
 *
 * @param[in] grp Role group to copy.
 *
 * @returns Pointer to copy of role group.
 */
st_role_group *st_role_group_copy(st_role_group const *grp);


/**
 * @brief Cleanup session type role group.
 * 
 * @param[in,out] grp Role group to free.
 */
void st_role_group_free(st_role_group *grp);


#ifdef __cplusplus
}
#endif

#endif // SESSTYPE__ST_ROLE_GROUP__H__
