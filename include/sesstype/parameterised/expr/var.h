#ifndef SESSTYPE__PARAMETERISED__EXPR__VAR_H__
#define SESSTYPE__PARAMETERISED__EXPR__VAR_H__

#ifdef __cplusplus
#include <string>
#endif

#include "sesstype/parameterised/expr.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Variable expression.
 */
class VarExpr : public Expr {
    std::string name_;

  public:
    /// \brief VarExpr constructor.
    /// \param[in] name of variable.
    VarExpr(std::string name) : Expr(ST_EXPR_VAR), name_(name) { }

    /// \brief VarExpr copy constructor.
    VarExpr(const VarExpr &expr) : Expr(ST_EXPR_VAR), name_(expr.name_) { }

    /// \brief clone a VarExpr.
    VarExpr *clone() const override
    {
        return new VarExpr(*this);
    }

    /// \returns variable name.
    std::string name() const
    {
        return name_;
    }

    virtual void accept(util::ExprVisitor &v) override;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__EXPR__VAR_H__
