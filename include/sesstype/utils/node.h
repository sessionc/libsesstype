/**
 * \file sesstype/utils/role.h
 * \brief Utilities for Node.
 */
#ifndef SESSTYPE__UTILS__NODE_H__
#define SESSTYPE__UTILS__NODE_H__

#include "sesstype/node.h"
#include "sesstype/parameterised/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace utils {
#endif

#ifdef __cplusplus
/**
 * \brief Abstract class for building Node AST-based visitors.
 */
class NodeVisitor {
  public:
    //virtual void visit(Node *node) = 0;
    virtual void visit(InteractionNode *node) = 0;
    virtual void visit(BlockNode *node) = 0;
    virtual void visit(RecurNode *node) = 0;
    virtual void visit(ContinueNode *node) = 0;
    virtual void visit(ChoiceNode *node) = 0;
    virtual void visit(parameterised::InteractionNode *node) = 0;
    virtual void visit(parameterised::AllReduceNode *node) = 0;
    virtual void visit(parameterised::ForNode *node) = 0;
    virtual void visit(parameterised::OneofNode *node) = 0;
    virtual void visit(parameterised::IfNode *node) = 0;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace utils
} // namespace sesstype
#endif

#endif//SESSTYPE__UTILS__NODE_H__
