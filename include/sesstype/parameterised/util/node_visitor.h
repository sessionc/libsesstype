/**
 * \file sesstype/parameterised/util/node_visitor.h
 * \brief Utilities for Node.
 */
#ifndef SESSTYPE__PARAMETERISED__UTIL__NODE_VISITOR_H__
#define SESSTYPE__PARAMETERISED__UTIL__NODE_VISITOR_H__

#include "sesstype/parameterised/node.h"
#include "sesstype/parameterised/node/interaction.h"
#include "sesstype/parameterised/node/choice.h"
#include "sesstype/parameterised/node/recur.h"
#include "sesstype/parameterised/node/continue.h"
#include "sesstype/parameterised/node/par.h"
#include "sesstype/parameterised/node/nested.h"
#include "sesstype/parameterised/node/interruptible.h"
#include "sesstype/parameterised/node/for.h"
#include "sesstype/parameterised/node/oneof.h"
#include "sesstype/parameterised/node/if.h"
#include "sesstype/parameterised/node/allreduce.h"

#ifdef __cplusplus
/// Forward declaration of Node and friends.
namespace sesstype {

template class BlockNodeTmpl<parameterised::Node, parameterised::Role, parameterised::MsgSig, parameterised::util::NodeVisitor>;
template class InteractionNodeTmpl<parameterised::Node, parameterised::Role, parameterised::MsgSig, parameterised::util::NodeVisitor>;
template class ChoiceNodeTmpl<parameterised::Node, parameterised::Role, parameterised::MsgSig, parameterised::util::NodeVisitor>;
template class RecurNodeTmpl<parameterised::Node, parameterised::Role, parameterised::MsgSig, parameterised::util::NodeVisitor>;
template class ContinueNodeTmpl<parameterised::Node, parameterised::Role, parameterised::MsgSig, parameterised::util::NodeVisitor>;
template class ParNodeTmpl<parameterised::Node, parameterised::Role, parameterised::MsgSig, parameterised::util::NodeVisitor>;
template class NestedNodeTmpl<parameterised::Node, parameterised::Role, parameterised::MsgSig, parameterised::util::NodeVisitor>;
template class InterruptibleNodeTmpl<parameterised::Node, parameterised::Role, parameterised::MsgSig, parameterised::util::NodeVisitor>;

namespace parameterised {

template class ForNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
template class OneofNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
template class IfNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
template class AllReduceNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;

namespace util {
class NodeVisitor;
} // namespace util

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
 * \brief Abstract class for building Node AST-based visitors.
 */
class NodeVisitor {
  public:
    virtual void visit(Node *node) = 0;
    virtual void visit(BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(InteractionNode *node) = 0;
    virtual void visit(ChoiceNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(RecurNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(ContinueNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(ParNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(NestedNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(InterruptibleNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(ForNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node)  = 0;
    virtual void visit(OneofNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(IfNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
    virtual void visit(AllReduceNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) = 0;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__UTIL__NODE_VISITOR_H__
