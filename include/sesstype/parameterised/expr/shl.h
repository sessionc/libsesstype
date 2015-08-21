#ifndef SESSTYPE__PARAMETERISED__EXPR__SHL_H__
#define SESSTYPE__PARAMETERISED__EXPR__SHL_H__

#include "sesstype/parameterised/expr.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Shift left expression.
 */
class ShlExpr : public BinExpr {
  public:
    /// \brief ShlExpr constructor.
    /// \param[in] lhs Expr.
    /// \param[in] rhs Expr.
    ShlExpr(Expr *lhs, Expr *rhs) : BinExpr(ST_EXPR_SHL, lhs, rhs) { }

    /// \brief ShlExpr copy constructor.
    ShlExpr(const ShlExpr &expr)
        : BinExpr(ST_EXPR_SHL, expr.lhs_->clone(), expr.rhs_->clone()) { }


    /// \brief clone a ShlExpr.
    ShlExpr *clone() const override
    {
        return new ShlExpr(*this);
    }

    bool is_commutative() const override
    {
        return false;
    }

    bool is_associative() const override
    {
        return false;
    }

    virtual void accept(util::ExprVisitor &v) override;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__EXPR__SHL_H__
