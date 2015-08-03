#ifndef SESSTYPE__PARAMETERISED__NODE__BLOCK_H__
#define SESSTYPE__PARAMETERISED__NODE__BLOCK_H__

#include "sesstype/node/block.h"
#include "sesstype/util/visitor_tmpl.h"

#include "sesstype/parameterised/msg.h"
#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/node.h"


#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
using BlockNode = BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__NODE__BLOCK_H__
