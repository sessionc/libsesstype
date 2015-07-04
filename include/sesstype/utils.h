/**
 * \file sesstype/utils.h
 * \brief Utility functions for working with Session Types.
 */
#ifndef SESSTYPE__UTILS_H__
#define SESSTYPE__UTILS_H__

#ifdef __cplusplus
#include <stack>
#include <ostream>
#endif

#include "sesstype/node.h"
#include "sesstype/role.h"

#include "sesstype/parameterised/expr.h"
#include "sesstype/parameterised/node.h"
#include "sesstype/parameterised/role.h"

#include "sesstype/utils/expr.h"
#include "sesstype/utils/node.h"
#include "sesstype/utils/role.h"

#ifdef __cplusplus
namespace sesstype {
/**
 * \brief Namespace for utilities and non-datastructure classes.
 */
namespace utils {
#endif

#ifdef __cplusplus
/**
 * \brief Protocol and Expression printer.
 */
class Printer : public NodeVisitor, public RoleVisitor, public ExprVisitor {
 public:
  /// \brief Printer constructor with output to std::out as default.
  Printer();

  /// \brief Printer constructor.
  /// \param[in] os output stream.
  Printer(std::ostream &os);

  /// \brief Output prefix based on current line#, indent level and character.
  void prefix();

  void reset_line_num();

  void visit(BlockNode *node) override;
  void visit(InteractionNode *node) override;
  void visit(RecurNode *node) override;
  void visit(ContinueNode *node) override;
  void visit(ChoiceNode *node) override;
  void visit(ParNode *node) override;
  void visit(NestedNode *node) override;
  void visit(InterruptibleNode *node) override;
  void visit(parameterised::InteractionNode *node) override;
  void visit(parameterised::AllReduceNode *node) override;
  void visit(parameterised::ForNode *node) override;
  void visit(parameterised::OneofNode *node) override;
  void visit(parameterised::IfNode *node) override;

  void visit(Role *role) override;
  void visit(parameterised::Role *role) override;
  void visit(parameterised::RoleGrp *role) override;

  void visit(parameterised::VarExpr *expr) override;
  void visit(parameterised::ValExpr *expr) override;
  void visit(parameterised::AddExpr *expr) override;
  void visit(parameterised::SubExpr *expr) override;
  void visit(parameterised::MulExpr *expr) override;
  void visit(parameterised::DivExpr *expr) override;
  void visit(parameterised::ModExpr *expr) override;
  void visit(parameterised::ShlExpr *expr) override;
  void visit(parameterised::ShrExpr *expr) override;
  void visit(parameterised::SeqExpr *expr) override;
  void visit(parameterised::RngExpr *expr) override;

 private:
  std::ostream &os_;
  unsigned int indent_lvl_;
  std::string indent_str_;
  unsigned int line_count_;
};

/**
 * \brief Expression simplifier.
 */
class Simplifier : public ExprVisitor {
  void visit(parameterised::VarExpr *expr) override;
  void visit(parameterised::ValExpr *expr) override;
  void visit(parameterised::AddExpr *expr) override;
  void visit(parameterised::SubExpr *expr) override;
  void visit(parameterised::MulExpr *expr) override;
  void visit(parameterised::DivExpr *expr) override;
  void visit(parameterised::ModExpr *expr) override;
  void visit(parameterised::ShlExpr *expr) override;
  void visit(parameterised::ShrExpr *expr) override;
  void visit(parameterised::SeqExpr *expr) override;
  void visit(parameterised::RngExpr *expr) override;
};

/**
 * \brief Endpoint projection.
 */
class Projection : public NodeVisitor {
 public:
  Projection(Role *role);

  Node *get_root();

  void visit(BlockNode *node) override;
  void visit(InteractionNode *node) override;
  void visit(RecurNode *node) override;
  void visit(ContinueNode *node) override;
  void visit(ChoiceNode *node) override;
  void visit(ParNode *node) override;
  void visit(NestedNode *node) override;
  void visit(InterruptibleNode *node) override;
  void visit(parameterised::InteractionNode *node) override;
  void visit(parameterised::AllReduceNode *node) override;
  void visit(parameterised::ForNode *node) override;
  void visit(parameterised::OneofNode *node) override;
  void visit(parameterised::IfNode *node) override;

 private:
  Role *project_role_;
  std::stack<Node *> stack_;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace utils
#endif

#ifdef __cplusplus
namespace parameterised {
#endif

#ifdef __cplusplus
extern "C" {
#endif

/// \brief Print an expression to stdout.
/// @param[in] expr Expression to print.
void st_expr_print(st_expr *expr);

/// \brief Print an expression to a string.
/// \param[out] str Output string.
/// \param[in] expr Expression to print.
void st_expr_sprint(char **str, st_expr *expr);

/// \brief Print an expression to a given output stream.
/// \param[out] stream Output stream.
/// \param[in] expr Expression to print.
void st_expr_fprint(FILE *stream, st_expr *expr);

/// \brief Pretty print an expression.
/// \param[in] e Expression to print.
void st_expr_print(st_expr *expr);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif // __cplusplus

#endif//SESSTYPE__UTILS_H__
