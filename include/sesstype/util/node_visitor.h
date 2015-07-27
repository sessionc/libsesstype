/**
 * \file sesstype/util/node_visitor.h
 * \brief Utilities for Node.
 */
#ifndef SESSTYPE__UTIL__NODE_VISITOR_H__
#define SESSTYPE__UTIL__NODE_VISITOR_H__

#include "sesstype/node.h"
#include "sesstype/node/interaction.h"
#include "sesstype/node/choice.h"
#include "sesstype/node/recur.h"
#include "sesstype/node/continue.h"
#include "sesstype/node/par.h"
#include "sesstype/node/nested.h"
#include "sesstype/node/interruptible.h"

#ifdef __cplusplus
namespace sesstype {

class Node;
class BlockNode;
class InteractionNode;
class ChoiceNode;
class RecurNode;
class ContinueNode;
class ParNode;
class NestedNode;
class InterruptibleNode;

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
    virtual void visit(BlockNode *node) = 0;
    virtual void visit(InteractionNode *node) = 0;
    virtual void visit(ChoiceNode *node) = 0;
    virtual void visit(RecurNode *node) = 0;
    virtual void visit(ContinueNode *node) = 0;
    virtual void visit(ParNode *node) = 0;
    virtual void visit(NestedNode *node) = 0;
    virtual void visit(InterruptibleNode *node) = 0;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace sesstype
#endif

#endif//SESSTYPE__UTIL__NODE_VISITOR_H__
