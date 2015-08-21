#ifndef SESSTYPE__PARAMETERISED__EXPR__DIV_H__
#define SESSTYPE__PARAMETERISED__EXPR__DIV_H__

#include "sesstype/parameterised/expr.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Division expression.
 */
class DivExpr : public BinExpr {
  public:
    /// \brief DivExpr constructor.
    /// \param[in] lhs Expr.
    /// \param[in] rhs Expr.
    DivExpr(Expr *lhs, Expr *rhs) : BinExpr(ST_EXPR_DIV, lhs, rhs) { }

    /// \brief DivExpr copy constructor.
    DivExpr(const DivExpr &expr)
        : BinExpr(ST_EXPR_DIV, expr.lhs_->clone(), expr.rhs_->clone()) { }

    /// \brief clone a DivExpr.
    DivExpr *clone() const override
    {
        return new DivExpr(*this);
    }

    bool is_commutative() const override
    {
        return true;
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

#endif//SESSTYPE__PARAMETERISED__EXPR__DIV_H__
