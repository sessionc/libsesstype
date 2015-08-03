#ifndef SESSTYPE__PARAMETERISED__EXPR__RNG_H__
#define SESSTYPE__PARAMETERISED__EXPR__RNG_H__

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
 * \brief Range expression with a binding variable.
 *
 * Specifies a binding variable <tt>bindvar</tt>,
 * a range begin Expr and a range end Expr with default of stride 1.
 */
class RngExpr : public Expr {
    std::string bindvar_;
    Expr *from_;
    Expr *to_;

  public:
    /// \brief RngExpr constructor with empty bind variable as default.
    /// \param[in] from Expr of RngExpr.
    /// \param[in] to Expr of RngExpr.
    RngExpr(Expr *from, Expr *to)
        : Expr(ST_EXPR_RNG),bindvar_(), from_(from), to_(to) { }

    /// \brief RngExpr constructor.
    /// \param[in] bindvar name.
    /// \param[in] start Expr of RngExpr.
    /// \param[in] end Expr of RngExpr.
    RngExpr(std::string bindvar, Expr *from, Expr *to)
        : Expr(ST_EXPR_RNG), bindvar_(bindvar), from_(from), to_(to) { }

    /// \brief RngExpr copy constructor.
    RngExpr(const RngExpr &expr)
        : Expr(ST_EXPR_RNG),
          bindvar_(expr.bindvar_), from_(expr.from_), to_(expr.to_) { }

    /// \brief RngExpr destructor.
    ~RngExpr() override
    {
        delete from_;
        delete to_;
    }

    /// \brief clone a RngExpr.
    RngExpr *clone() const override
    {
        return new RngExpr(*this);
    }

    /// Replace bind variable of RngExpr.
    /// \param[in] bindvar to replace with.
    void set_bindvar(std::string bindvar)
    {
        bindvar_ = bindvar;
    }

    /// \returns bind variable of RngExpr.
    std::string bindvar() const
    {
        return bindvar_;
    }

    /// \param[in] from Expr of the range.
    void set_from(Expr *from)
    {
        delete from_;
        from_ = from;
    }

    /// \returns from Expr of the range.
    Expr *from() const
    {
        return from_;
    }

    /// \param[in] to Expr of the range.
    void set_to(Expr *to)
    {
        delete to_;
        to_ = to;
    }

    /// \returns to Expr of the range.
    Expr *to() const
    {
        return to_;
    }

    virtual void accept(util::ExprVisitor &v) override;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef RngExpr st_rng_expr; /**< Range expression. */
#else
typedef struct RngExpr st_rng_expr; /**< Range expression. */
#endif

/// \brief Constructor for range expression.
/// \param[in] bindvar Binding variable name, NULL means plain range.
/// \param[in] from    LHS from expression.
/// \param[in] to      RHS to expression.
/// \returns Range exprssion.
st_expr *st_expr_mk_range(char *bindvar, st_expr *from, st_expr *to);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__EXPR__RNG_H__
