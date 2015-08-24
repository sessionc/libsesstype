#ifndef SESSTYPE__PARAMETERISED__COND_H__
#define SESSTYPE__PARAMETERISED__COND_H__

#include "sesstype/parameterised/role.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef sesstype::parameterised::Role MsgCond;
typedef sesstype::parameterised::st_param_role st_cond;
#else
typedef struct Role MsgCond;
typedef st_param_role st_cond;
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__COND_H__
