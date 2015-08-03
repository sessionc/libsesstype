#ifndef SESSTYPE__PARAMETERISED__EXPR__VAL_H__
#define SESSTYPE__PARAMETERISED__EXPR__VAL_H__

#include "sesstype/parameterised/expr.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Value expression.
 */
class ValExpr : public Expr {
    int num_;

  public:
    /// \brief ValExpr constructor.
    /// \param[in] num value.
    ValExpr(int num) : Expr(ST_EXPR_CONST), num_(num) { }

    /// \brief ValExpr copy constructor.
    ValExpr(const ValExpr &expr) : Expr(ST_EXPR_CONST), num_(expr.num_) { }

    /// \brief clone a ValExpr.
    ValExpr *clone() const override
    {
        return new ValExpr(*this);
    }

    /// \returns value of expression.
    int num() const
    {
        return num_;
    }

    virtual void accept(util::ExprVisitor &v) override;
};
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif
#endif//SESSTYPE__PARAMETERISED__EXPR__VAL_H__
