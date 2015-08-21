#ifndef SESSTYPE__PARAMETERISED__UTIL__EMPTY_VISITOR_HPP__
#define SESSTYPE__PARAMETERISED__UTIL__EMPTY_VISITOR_HPP__

#include "sesstype/parameterised/util/expr_visitor.h"
#include "sesstype/parameterised/util/node_visitor.h"

namespace sesstype {
namespace parameterised {
namespace util {

class EmptyVisitor : public NodeVisitor, public ExprVisitor {
  public:
    virtual void visit(Node *node) { }
    virtual void visit(BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) { }
    virtual void visit(sesstype::parameterised::InteractionNode *node) { }
    virtual void visit(ChoiceNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) { }
    virtual void visit(RecurNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) { }
    virtual void visit(ContinueNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) { }
    virtual void visit(ParNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) { }
    virtual void visit(NestedNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) { }
    virtual void visit(InterruptibleNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) { }
    virtual void visit(ForNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node)  { }
    virtual void visit(OneofNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) { }
    virtual void visit(IfNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) { }
    virtual void visit(AllReduceNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *node) { }
    virtual void visit(Expr    *expr) { }
    virtual void visit(VarExpr *expr) { }
    virtual void visit(ValExpr *expr) { }
    virtual void visit(AddExpr *expr) { }
    virtual void visit(SubExpr *expr) { }
    virtual void visit(MulExpr *expr) { }
    virtual void visit(DivExpr *expr) { }
    virtual void visit(ModExpr *expr) { }
    virtual void visit(ShlExpr *expr) { }
    virtual void visit(ShrExpr *expr) { }
    virtual void visit(SeqExpr *expr) { }
    virtual void visit(RngExpr *expr) { }
    virtual void visit(LogExpr *expr) { }
};

} // namespace util
} // namespace parameterised
} // namespace sesstype


#endif//SESSTYPE__PARAMETERISED__UTIL__EMPTY_VISITOR_HPP__
