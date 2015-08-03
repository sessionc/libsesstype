/**
 * \file sesstype/util/role_visitor.h
 * \brief Utities for Roles.
 */
#ifndef SESSTYPE__UTIL__ROLE_VISITOR_H__
#define SESSTYPE__UTIL__ROLE_VISITOR_H__

#include "sesstype/util/visitor_tmpl.h"

#ifdef __cplusplus
namespace sesstype {
class Role;
} // namespace sesstype
#endif

#ifdef __cplusplus
namespace sesstype {
namespace util {
#endif

#ifdef __cplusplus
/**
 * \brief Abstract class for building Role visitors.
 */
class RoleVisitor {
  public:
    virtual void visit(Role *node) = 0;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace sesstype
#endif

#endif//SESSTYPE__UTILS__ROLE_VISITOR_H__
