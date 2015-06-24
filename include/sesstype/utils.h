/**
 * \file sesstype/utils.h
 * \brief Utility functions for working with Session Types.
 */
#ifndef SESSTYPE__UTILS_H__
#define SESSTYPE__UTILS_H__

#ifdef __cplusplus
#include <ostream>
#endif

#include "sesstype/expr.h"
#include "sesstype/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace utils {
#endif

#ifdef __cplusplus
/**
 * \brief Protocol and Expression printer.
 */
class Printer : public NodeVisitor, public ExprVisitor {
 public:
  /// \brief Printer constructor with output to std::out as default.
  Printer();

  /// \brief Printer constructor.
  /// \param[in] os output stream.
  Printer(std::ostream &os);

  /// \brief Output prefix based on current line#, indent level and character.
  void prefix();

  void visit(BlockNode *node) override;
  void visit(InteractionNode *node) override;
  void visit(RecurNode *node) override;
  void visit(ContinueNode *node) override;
  void visit(ChoiceNode *node) override;
  void visit(AllReduceNode *node) override;
  void visit(ForNode *node) override;
  void visit(OneofNode *node) override;
  void visit(IfNode *node) override;

  void visit(VarExpr *expr) override;
  void visit(ValExpr *expr) override;
  void visit(AddExpr *expr) override;
  void visit(SubExpr *expr) override;
  void visit(MulExpr *expr) override;
  void visit(DivExpr *expr) override;
  void visit(ModExpr *expr) override;
  void visit(ShlExpr *expr) override;
  void visit(ShrExpr *expr) override;
  void visit(SeqExpr *expr) override;
  void visit(RngExpr *expr) override;
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
  void visit(VarExpr *expr) override;
  void visit(ValExpr *expr) override;
  void visit(AddExpr *expr) override;
  void visit(SubExpr *expr) override;
  void visit(MulExpr *expr) override;
  void visit(DivExpr *expr) override;
  void visit(ModExpr *expr) override;
  void visit(ShlExpr *expr) override;
  void visit(ShrExpr *expr) override;
  void visit(SeqExpr *expr) override;
  void visit(RngExpr *expr) override;
};

/**
 * \brief Endpoint projection.
 */
class Projection : public NodeVisitor {
 public:
  Projection(Role *role);

  void visit(BlockNode *node) override;
  void visit(InteractionNode *node) override;
  void visit(RecurNode *node) override;
  void visit(ContinueNode *node) override;
  void visit(ChoiceNode *node) override;
  void visit(AllReduceNode *node) override;
  void visit(ForNode *node) override;
  void visit(OneofNode *node) override;
  void visit(IfNode *node) override;

 private:
  Role *project_role_;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace utils
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
} // namespace sesstype
#endif // __cplusplus

#endif//SESSTYPE__UTILS_H__
