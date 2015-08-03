#ifndef SESSTYPE__PARAMETERISED__UTIL__ROLE_VISITOR_H__
#define SESSTYPE__PARAMETERISED__UTIL__ROLE_VISITOR_H__

#include "sesstype/util/role_visitor.h"

#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/role_grp.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
namespace util {
#endif // __cplusplus

#ifdef __cplusplus
class RoleVisitor {
  public:
    virtual void visit(Role *role) = 0;
    virtual void visit(RoleGrp *role) = 0;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__UTIL__ROLE_VISITOR_H__
