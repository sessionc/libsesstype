#ifndef SESSTYPE__UTIL__EMPTY_VISITOR_HPP__
#define SESSTYPE__UTIL__EMPTY_VISITOR_HPP__

#include "sesstype/node.h"
#include "sesstype/util/node_visitor.h"

namespace sesstype {
namespace util {

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

} // namespace util
} // namespace sesstype

#endif//SESSTYPE__UTIL__EMPTY_VISITOR_HPP__
