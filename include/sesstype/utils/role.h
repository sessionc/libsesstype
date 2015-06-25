/**
 * \file sesstype/utils/role.h
 * \brief Utities for Roles.
 */
#ifndef SESSTYPE__UTILS__ROLE_H__
#define SESSTYPE__UTILS__ROLE_H__

#include "sesstype/role.h"
#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/role_grp.h"

#ifdef __cplusplus
namespace sesstype {
namespace utils {
#endif

#ifdef __cplusplus
/**
 * \brief Abstract class for building Role visitors.
 */
class RoleVisitor {
  public:
    virtual void visit(Role *role) = 0;
    virtual void visit(parameterised::Role *role) = 0;
    virtual void visit(parameterised::RoleGrp *role) = 0;
};

#endif // __cplusplus

#ifdef __cplusplus
} // namespace utils
} // namespace sesstype
#endif

#endif//SESSTYPE__UTILS__ROLE_H__
