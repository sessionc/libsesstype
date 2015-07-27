/**
 * \file sesstype/parameterised/util/role_visitor.h
 * \brief Utities for Roles.
 */
#ifndef SESSTYPE__PARAMETERISED__UTIL__ROLE_VISITOR_H__
#define SESSTYPE__PARAMETERISED__UTIL__ROLE_VISITOR_H__

#include "sesstype/util/role_visitor.h"

#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/role_grp.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {

class Role;
class RoleGrp;

} // namespace parameterised
} // namespace sesstype
#endif

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
namespace util {
#endif

#ifdef __cplusplus
/**
 * \brief Abstract class for building Role visitors.
 */
class RoleVisitor : public sesstype::util::RoleVisitor {
  public:
    using sesstype::util::RoleVisitor::visit;
    virtual void visit(sesstype::parameterised::Role *role) = 0;
    virtual void visit(sesstype::parameterised::RoleGrp *role) = 0;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__UTILS__ROLE_VISITOR_H__
