#ifndef SESSTYPE__PARAMETERISED__NODE__PAR_H__
#define SESSTYPE__PARAMETERISED__NODE__PAR_H__

#include "sesstype/node/par.h"
#include "sesstype/util/visitor_tmpl.h"

#include "sesstype/parameterised/msg.h"
#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
using ParNode = ParNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
#endif

#ifdef __cplusplus
} // parameterised
} // sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__NODE__PAR_H__
