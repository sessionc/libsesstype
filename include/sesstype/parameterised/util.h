#ifndef SESSTYPE__PARAMETERISED__UTIL_H__
#define SESSTYPE__PARAMETERISED__UTIL_H__

#ifdef __cplusplus
#include <stack>
#include <ostream>
#endif

#include "sesstype/parameterised/expr.h"

#include "sesstype/parameterised/util/expr_visitor.h"
#include "sesstype/parameterised/util/node_visitor.h"
#include "sesstype/parameterised/util/role_visitor.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
/**
 * \brief Namespace for utilities and non-datastructure classes.
 */
namespace util {
#endif

class Printer : public sesstype::parameterised::util::NodeVisitor,
                public sesstype::parameterised::util::RoleVisitor,
                public sesstype::parameterised::util::ExprVisitor {
  public:
    Printer();
    Printer(std::ostream &os);
    void prefix();
    void reset_line_num();

    void visit(sesstype::parameterised::Node *node) override;
    void visit(sesstype::parameterised::BlockNode *node) override;
    void visit(sesstype::parameterised::InteractionNode *node) override;
    void visit(sesstype::parameterised::RecurNode *node) override;
    void visit(sesstype::parameterised::ContinueNode *node) override;
    void visit(sesstype::parameterised::ChoiceNode *node) override;
    void visit(sesstype::parameterised::ParNode *node) override;
    void visit(sesstype::parameterised::NestedNode *node) override;
    void visit(sesstype::parameterised::InterruptibleNode *node) override;
    void visit(sesstype::parameterised::ForNode *node) override;
    void visit(sesstype::parameterised::AllReduceNode *node) override;
    void visit(sesstype::parameterised::OneofNode *node) override;
    void visit(sesstype::parameterised::IfNode *node) override;

    void visit(sesstype::parameterised::Role *role) override;
    void visit(sesstype::parameterised::RoleGrp *role) override;

    void visit(sesstype::parameterised::VarExpr *expr) override;
    void visit(sesstype::parameterised::ValExpr *expr) override;
    void visit(sesstype::parameterised::AddExpr *expr) override;
    void visit(sesstype::parameterised::SubExpr *expr) override;
    void visit(sesstype::parameterised::MulExpr *expr) override;
    void visit(sesstype::parameterised::DivExpr *expr) override;
    void visit(sesstype::parameterised::ModExpr *expr) override;
    void visit(sesstype::parameterised::ShlExpr *expr) override;
    void visit(sesstype::parameterised::ShrExpr *expr) override;
    void visit(sesstype::parameterised::SeqExpr *expr) override;
    void visit(sesstype::parameterised::RngExpr *expr) override;

  private:
    std::ostream &os_;
    unsigned int indent_lvl_;
    std::string indent_str_;
    unsigned int line_count_;
};

class Projection : public sesstype::parameterised::util::NodeVisitor {
  public:
    Projection(Role *role);
    Node *get_root();

    void visit(sesstype::parameterised::Node *node) override;
    void visit(sesstype::parameterised::BlockNode *node) override;
    void visit(sesstype::parameterised::InteractionNode *node) override;
    void visit(sesstype::parameterised::RecurNode *node) override;
    void visit(sesstype::parameterised::ContinueNode *node) override;
    void visit(sesstype::parameterised::ChoiceNode *node) override;
    void visit(sesstype::parameterised::ParNode *node) override;
    void visit(sesstype::parameterised::NestedNode *node) override;
    void visit(sesstype::parameterised::InterruptibleNode *node) override;
    void visit(sesstype::parameterised::ForNode *node) override;
    void visit(sesstype::parameterised::AllReduceNode *node) override;
    void visit(sesstype::parameterised::OneofNode *node) override;
    void visit(sesstype::parameterised::IfNode *node) override;

  private:
    Role *project_role_;
    std::stack<Node *> stack_;
};

class Simplifier : public sesstype::parameterised::util::ExprVisitor {
  public:
    void visit(sesstype::parameterised::VarExpr *expr) override;
    void visit(sesstype::parameterised::ValExpr *expr) override;
    void visit(sesstype::parameterised::AddExpr *expr) override;
    void visit(sesstype::parameterised::SubExpr *expr) override;
    void visit(sesstype::parameterised::MulExpr *expr) override;
    void visit(sesstype::parameterised::DivExpr *expr) override;
    void visit(sesstype::parameterised::ModExpr *expr) override;
    void visit(sesstype::parameterised::ShlExpr *expr) override;
    void visit(sesstype::parameterised::ShrExpr *expr) override;
    void visit(sesstype::parameterised::SeqExpr *expr) override;
    void visit(sesstype::parameterised::RngExpr *expr) override;
};

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__UTIL_H__
