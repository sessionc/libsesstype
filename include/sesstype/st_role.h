#ifndef SESSTYPE__ST_ROLE__H__
#define SESSTYPE__ST_ROLE__H__
/**
 * @file
 * This file contains the data structures and access function to a session type
 * role.
 */

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Parameterised roles.
 */
typedef struct {
  char *name;         /**< Role prefix name (without parameters). */
  unsigned int dimen; /**< Role parameter dimension. 0 if non-parameterised. */
  st_expr **param;    /**< N-dimension expression. null if non-parametrised. */
} st_role;


/**
 * @brief Initialise session type role.
 *
 * @param[in,out] role Role to initialise.
 *
 * @returns Initalised role.
 */
st_role *st_role_init(st_role *role);


/**
 * @brief Set name of role.
 *
 * @param[in,out] role Role pointer to update.
 * @param[in]     name Name of the role.
 *
 * @returns Updated role.
 */
st_role *st_role_set_name(st_role *role, char *name);


/**
 * @brief Add a parameter to a role (as a new dimension).
 *
 * @param[in,out] role Role pointer to update.
 * @param[in]     param Parameter expression to add.
 *
 * @returns Updated role.
 */
st_role *st_role_add_param(st_role *role, st_expr *param);


/**
 * @brief Deep copy a role.
 *
 * @param[in] role Role to copy.
 *
 * @returns Pointer to copy of role.
 */
st_role *st_role_copy(st_role const *role);


/**
 * @brief Cleanup session type role.
 *
 * @param[in,out] role Role to free.
 */
void st_role_free(st_role *role);


#ifdef __cplusplus
}
#endif

#endif // SESSTYPE__ST_ROLE__H__
