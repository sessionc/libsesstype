#ifndef SESSTYPE__PARAMETERISED__EXPR__SUB_H__
#define SESSTYPE__PARAMETERISED__EXPR__SUB_H__

#include "sesstype/parameterised/expr.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Subtraction expression.
 */
class SubExpr : public BinExpr {
  public:
    /// \brief SubExpr constructor.
    /// \param[in] lhs Expr.
    /// \param[in] rhs Expr.
    SubExpr(Expr *lhs, Expr *rhs) : BinExpr(ST_EXPR_SUB, lhs, rhs) { }

    /// \brief SubExpr copy constructor.
    SubExpr(const SubExpr &expr)
        : BinExpr(ST_EXPR_SUB, expr.lhs_->clone(), expr.rhs_->clone()) { }

    /// \brief clone a SubExpr.
    SubExpr *clone() const override
    {
        return new SubExpr(*this);
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

#endif//SESSTYPE__PARAMETERISED__EXPR__SUB_H__
