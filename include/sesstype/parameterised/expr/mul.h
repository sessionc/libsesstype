#ifndef SESSTYPE__PARAMETERISED__EXPR__MUL_H__
#define SESSTYPE__PARAMETERISED__EXPR__MUL_H__

#include "sesstype/parameterised/expr.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Multiplication expression.
 */
class MulExpr : public BinExpr {
  public:
    /// \brief MulExpr constructor.
    /// \param[in] lhs Expr.
    /// \param[in] rhs Expr.
    MulExpr(Expr *lhs, Expr *rhs) : BinExpr(ST_EXPR_MUL, lhs, rhs) { }

    /// \brief MulExpr copy constructor.
    MulExpr(const MulExpr &expr)
        : BinExpr(ST_EXPR_MUL, expr.lhs_->clone(), expr.rhs_->clone()) { }

    /// \brief clone a MulExpr.
    MulExpr *clone() const override
    {
        return new MulExpr(*this);
    }

    bool is_commutative() const override
    {
        return true;
    }

    bool is_associative() const override
    {
        return true;
    }

    void virtual accept(util::ExprVisitor &v) override;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__EXPR__MUL_H__
