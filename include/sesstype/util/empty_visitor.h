#ifndef SESSTYPE__UTIL__EMPTY_VISITOR_H__
#define SESSTYPE__UTIL__EMPTY_VISITOR_H__

#include "sesstype/node.h"
#include "sesstype/util/node_visitor.h"

#ifdef __cplusplus
namespace sesstype {
namespace util {
#endif

#ifdef __cplusplus
/**
 * \brief Empty visitor for mocking transversal of all Nodes.
 */
class EmptyVisitor : public NodeVisitor {
  public:
    virtual void visit(Node *node) override { }
    virtual void visit(BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) override { }
    virtual void visit(InteractionNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) override { }
    virtual void visit(ChoiceNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) override { }
    virtual void visit(RecurNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) override { }
    virtual void visit(ContinueNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) override { }
    virtual void visit(ParNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) override { }
    virtual void visit(NestedNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) override { }
    virtual void visit(InterruptibleNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) override { }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace sesstype
#endif

#endif//SESSTYPE__UTIL__EMPTY_VISITOR_H__
