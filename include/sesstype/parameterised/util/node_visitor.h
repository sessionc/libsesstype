/**
 * \file sesstype/parameterised/util/node_visitor.h
 * \brief Utilities for Node.
 */
#ifndef SESSTYPE__PARAMETERISED__UTIL__NODE_VISITOR_H__
#define SESSTYPE__PARAMETERISED__UTIL__NODE_VISITOR_H__

#include "sesstype/util/node_visitor.h"

#include "sesstype/parameterised/node.h"
#include "sesstype/parameterised/node/interaction.h"
#include "sesstype/parameterised/node/choice.h"
#include "sesstype/parameterised/node/recur.h"
#include "sesstype/parameterised/node/continue.h"
#include "sesstype/parameterised/node/par.h"
#include "sesstype/parameterised/node/nested.h"
#include "sesstype/parameterised/node/interruptible.h"
#include "sesstype/parameterised/node/for.h"
#include "sesstype/parameterised/node/allreduce.h"
#include "sesstype/parameterised/node/oneof.h"
#include "sesstype/parameterised/node/if.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {

class InteractionNode;
class ForNode;
class AllReduceNode;
class OneofNode;
class IfNode;

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
class NodeVisitor : public sesstype::util::NodeVisitor {
  public:
    using sesstype::util::NodeVisitor::visit;

    virtual void visit(sesstype::parameterised::Node *node) = 0;
    virtual void visit(sesstype::parameterised::BlockNode *node) = 0;
    virtual void visit(sesstype::parameterised::InteractionNode *node) = 0;
    virtual void visit(sesstype::parameterised::ChoiceNode *node) = 0;
    virtual void visit(sesstype::parameterised::RecurNode *node) = 0;
    virtual void visit(sesstype::parameterised::ContinueNode *node) = 0;
    virtual void visit(sesstype::parameterised::ParNode *node) = 0;
    virtual void visit(sesstype::parameterised::NestedNode *node) = 0;
    virtual void visit(sesstype::parameterised::InterruptibleNode *node) = 0;
    virtual void visit(sesstype::parameterised::ForNode *node) = 0;
    virtual void visit(sesstype::parameterised::AllReduceNode *node) = 0;
    virtual void visit(sesstype::parameterised::OneofNode *node) = 0;
    virtual void visit(sesstype::parameterised::IfNode *node) = 0;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__UTIL__NODE_VISITOR_H__
