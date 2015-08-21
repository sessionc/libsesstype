#ifndef SESSTYPE__PARAMETERISED__EXPR__SHR_H__
#define SESSTYPE__PARAMETERISED__EXPR__SHR_H__

#include "sesstype/parameterised/expr.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Shift right expression.
 */
class ShrExpr : public BinExpr {
  public:
    /// \brief ShlExpr constructor.
    /// \param[in] lhs Expr.
    /// \param[in] rhs Expr.
    ShrExpr(Expr *lhs, Expr *rhs) : BinExpr(ST_EXPR_SHR, lhs, rhs) { }

    /// \brief ShrExpr copy constructor.
    ShrExpr(const ShrExpr &expr)
        : BinExpr(ST_EXPR_SHR, expr.lhs_->clone(), expr.rhs_->clone()) { }

    /// \brief clone a ShrExpr.
    ShrExpr *clone() const override
    {
        return new ShrExpr(*this);
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

#endif//SESSTYPE__PARAMETERISED__EXPR__SHR_H__
