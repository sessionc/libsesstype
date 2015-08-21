#ifndef SESSTYPE__PARAMETERISED__EXPR__MOD_H__
#define SESSTYPE__PARAMETERISED__EXPR__MOD_H__

#include "sesstype/parameterised/expr.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Modulo expression.
 */
class ModExpr : public BinExpr {
  public:
    /// \brief ModExpr constructor.
    /// \param[in] lhs Expr.
    /// \param[in] rhs Expr.
    ModExpr(Expr *lhs, Expr *rhs) : BinExpr(ST_EXPR_MOD, lhs, rhs) { }

    /// \brief ModExpr copy constructor.
    ModExpr(const ModExpr &expr)
        : BinExpr(ST_EXPR_MOD, expr.lhs_->clone(), expr.rhs_->clone()) { }

    /// \brief clone a ModExpr.
    ModExpr *clone() const override
    {
        return new ModExpr(*this);
    }

    bool is_commutative() const override
    {
        return true;
    }

    bool is_associative() const override
    {
        return false;
    }

    void virtual accept(util::ExprVisitor &v) override;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__EXPR__MOD_H__
