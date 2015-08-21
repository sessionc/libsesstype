#ifndef SESSTYPE__PARAMETERISED__EXPR__LOG_H__
#define SESSTYPE__PARAMETERISED__EXPR__LOG_H__

#include "sesstype/parameterised/expr.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
class LogExpr : public Expr {
    Expr *value_;
    Expr *base_;

  public:
    LogExpr(Expr *val, Expr *base) : Expr(ST_EXPR_LOG), value_(), base_() { }

    LogExpr(const LogExpr &expr)
        : Expr(ST_EXPR_LOG), value_(expr.value_->clone()), base_(expr.base_->clone()) { }

    ~LogExpr() override
    {
        delete value_;
        delete base_;
    }

    LogExpr *clone() const override
    {
        return new LogExpr(*this);
    }

    Expr *value()
    {
        return value_;
    }

    Expr *base()
    {
        return base_;
    }

    void virtual accept(util::ExprVisitor &v) override;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__EXPR__LOG_H__
