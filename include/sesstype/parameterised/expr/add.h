#ifndef SESSTYPE__PARAMETERISED__EXPR__ADD_H__
#define SESSTYPE__PARAMETERISED__EXPR__ADD_H__

#include "sesstype/parameterised/expr.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Addition expression.
 */
class AddExpr : public BinExpr {
  public:
    /// \brief AddExpr constructor.
    /// \param[in] lhs Expr.
    /// \param[in] rhs Expr.
    AddExpr(Expr *lhs, Expr *rhs) : BinExpr(ST_EXPR_ADD, lhs, rhs) { }

    /// \brief AddExpr copy constructor.
    AddExpr(const AddExpr &expr)
        : BinExpr(ST_EXPR_ADD, expr.lhs_, expr.rhs_) { }

    /// \brief clone an AddExpr.
    AddExpr *clone() const override
    {
        return new AddExpr(*this);
    }

    bool is_commutative() const override
    {
        return true;
    }

    bool is_associative() const override
    {
        return true;
    }

    virtual void accept(util::ExprVisitor &v) override;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__EXPR__ADD_H__
