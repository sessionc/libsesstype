/**
 * \file sesstype/parameterised/expr.h
 * \brief Expressions in a Role parameter or statement.
 */
#ifndef SESSTYPE__PARAMETERISED__EXPR__H__
#define SESSTYPE__PARAMETERISED__EXPR__H__

#ifdef __cplusplus
#include <string>
#include <vector>
#else
#include <stdbool.h>
#include <stdio.h>
#endif

#include "sesstype/util/clonable.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
namespace util {

class ExprVisitor;

} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#define ST_EXPR_CONST 1
#define ST_EXPR_VAR   2
#define ST_EXPR_ADD   3
#define ST_EXPR_SUB   4
#define ST_EXPR_MUL   5
#define ST_EXPR_DIV   6
#define ST_EXPR_MOD   7
#define ST_EXPR_SHL   8 // <<
#define ST_EXPR_SHR   9 // >>
#define ST_EXPR_SEQ   10 // , (Sequence)
#define ST_EXPR_RNG   11 // .. (Range)
#define ST_EXPR_LOG   12 // log(val, base)

#ifdef __cplusplus
/**
 * \brief Expression.
 */
class Expr : public sesstype::util::Clonable {
    int type_;

  public:
    /// \brief Expr destructor.
    virtual ~Expr() { }

    /// \brief clone an Expr (abstract).
    virtual Expr *clone() const = 0;

    /// \returns type of Expr.
    int type() const
    {
        return type_;
    }

    virtual void accept(util::ExprVisitor &v) = 0;

  protected:
    Expr(int type) : type_(type) { }
};

/**
 * \brief Binary expression (Abstract).
 */
class BinExpr : public Expr {
  public:
    /// \brief BinExpr destructor.
    virtual ~BinExpr() override
    {
        delete lhs_;
        delete rhs_;
    }

    /// \returns binary operator.
    int op() const
    {
        return type();
    }

    /// \returns left Expr.
    Expr *lhs() const
    {
        return lhs_;
    }

    /// \return right Expr.
    Expr *rhs() const
    {
        return rhs_;
    }

    /// \returns true if binary operator is commutative.
    virtual bool is_commutative() const = 0;

    /// \returns true if binary operator is associative.
    virtual bool is_associative() const = 0;

    virtual void accept(util::ExprVisitor &v) = 0;

  protected:
    /// \brief BinExpr constructor.
    BinExpr(int op, Expr *lhs, Expr *rhs)
        : Expr(op),
          lhs_(lhs), rhs_(rhs) { }

    Expr *lhs_;
    Expr *rhs_;
};

#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef Expr st_expr;        /**< Generic expression. */
typedef BinExpr st_bin_expr; /**< Binary expression. */
#else
typedef struct Expr st_expr;        /**< Generic expression. */
typedef struct BinExpr st_bin_expr; /**< Binary expression. */
#endif // __cplusplus

/// \brief Constructor for value expression.
/// \param[in] num Integer value.
/// \returns expression with constant value (dynamically allocated).
st_expr *st_expr_mk_const(int num);

/// \brief Constructor for variable expression.
/// \param[in] var Variable name.
/// \returns expression with variable (dynamically allocated).
st_expr *st_expr_mk_var(const char *var);

/// \brief Constructor for binary expression.
/// \param[in] left  LHS expression tree.
/// \param[in] type  Expression type as defined in st_node.h (ST_EXPR_TYPE_*)
/// \param[in] right RHS expression tree.
/// \returns expression with binary expression (dynamically allocated).
st_expr *st_expr_mk_binary(st_expr *lhs, int type, st_expr *rhs);


/// \brief Deep copy an expression.
/// \param[in] e Expression to copy.
/// \returns pointer to dynamically allocated copy of expression.
st_expr *st_expr_copy(const st_expr *e);

/// \brief Test if two expressions are identical.
/// \param[in] e0 Expression to compare.
/// \param[in] e1 Expression to compare.
/// \returns true if identical, false otherwise.
bool st_expr_is_identical(st_expr *e0, st_expr *e1);

/// \brief Evaluate an expression.
///
/// Simplify mathematical expressions and return a canonical form if possible.
/// \param[in,out] e Expression to evaluate.
void st_expr_eval(st_expr *e);

/// \brief Free an exprssion.
/// \param[in] e Expression to free.
void st_expr_free(st_expr *e);

/// \brief Apply a relative expression on a binding range.
/// \param[in] b Binding range.
/// \param[in] e Relative expression.
/// \returns pointer to dynamically allocated expression.
st_expr *st_expr_apply(const st_expr *b, const st_expr *e);

/// \brief Invert an expression.
///
/// Currently only work with + - * / expressions and with numeric value on RHS.
/// \param[in] e Expression to invert.
/// \returns an inverted expression or NULL if not possible.
st_expr *st_expr_inv(const st_expr *e);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__EXPR__H__
