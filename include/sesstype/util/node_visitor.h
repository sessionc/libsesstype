/**
 * \file sesstype/util/node_visitor.h
 * \brief Utilities for Node.
 */
#ifndef SESSTYPE__UTIL__NODE_VISITOR_H__
#define SESSTYPE__UTIL__NODE_VISITOR_H__

#include "sesstype/msg.h"
#include "sesstype/role.h"
#include "sesstype/node.h"
#include "sesstype/node/interaction.h"
#include "sesstype/node/choice.h"
#include "sesstype/node/recur.h"
#include "sesstype/node/continue.h"
#include "sesstype/node/par.h"
#include "sesstype/node/nested.h"
#include "sesstype/node/interruptible.h"

#ifdef __cplusplus
/// Forward declaration of Node and friends.
namespace sesstype {

namespace util {
class NodeVisitor;
} // namespace util

template class BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
template class InteractionNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
template class ChoiceNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
template class RecurNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
template class ContinueNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
template class ParNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
template class NestedNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
template class InterruptibleNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;

} // namespace sesstype
#endif

#ifdef __cplusplus
namespace sesstype {
namespace util {
#endif

#ifdef __cplusplus
/**
 * \brief Abstract class for building Node AST-based visitors.
 */
class NodeVisitor {
  public:
    virtual void visit(Node *node) = 0;
    virtual void visit(BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(InteractionNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(ChoiceNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(RecurNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(ContinueNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(ParNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(NestedNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(InterruptibleNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace sesstype
#endif

#endif//SESSTYPE__UTIL__NODE_VISITOR_H__
