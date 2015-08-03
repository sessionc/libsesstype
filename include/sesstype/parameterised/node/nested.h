#ifndef SESSTYPE__PARAMETERISED__NODE__NESTED_H__
#define SESSTYPE__PARAMETERISED__NODE__NESTED_H__

#include "sesstype/node/nested.h"
#include "sesstype/util/visitor_tmpl.h"

#include "sesstype/parameterised/msg.h"
#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
using NestedNode = NestedNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
#endif

#ifdef __cplusplus
} // parameterised
} // sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__NODE__NESTED_H__
