#ifndef SESSTYPE__PARAMETERISED__UTIL__EXPR_APPLY_H__
#define SESSTYPE__PARAMETERISED__UTIL__EXPR_APPLY_H__

#include "sesstype/parameterised/expr/rng.h"
#include "sesstype/parameterised/util/expr_visitor.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
namespace util {
#endif


#ifdef __cplusplus
/**
 * \brief ExprApply implements Pabble's <tt>apply(b, e)</tt>
 *
 * For example:
 *   apply(i:1..N, i+1) --> i:2..N+1
 *   i.e. Replace occurence of *bindvar* in e with *from* and *to*
 */
class ExprApply : public ExprVisitor {
    std::string var_;
    Expr *from_;
    Expr *to_;
    Expr *result_from_;
    Expr *result_to_;
    bool error_;

  public:
    ExprApply(RngExpr *bindexpr) : var_(bindexpr->bindvar()),
                                   from_(bindexpr->from()),
                                   to_(bindexpr->to()),
                                   error_(false) { }

    Expr *apply()
    {
        if (is_valid()) {
            return new RngExpr(std::string(var_), result_from_, result_to_);
        }
        return nullptr;
    }

    bool is_valid()
    {
        return !error_;
    }

    virtual void visit(Expr *expr)
    {
        // Nothing.
    }

    virtual void visit(VarExpr *expr)
    {
        if (expr->name() == var_) {
            // Replace var with from and to.
            result_from_ = from_->clone();
            result_to_ = to_->clone();
        } else {
            result_from_ = new VarExpr(expr->name());
            result_to_ = new VarExpr(expr->name());
        }
    }

    virtual void visit(ValExpr *expr)
    {
        result_from_ = new ValExpr(expr->num());
        result_to_ = new ValExpr(expr->num());
    }

    virtual void visit(AddExpr *expr)
    {
        expr->lhs()->accept(*this);
        Expr *lhs_from_ = result_from_;
        Expr *lhs_to_ = result_to_;

        expr->rhs()->accept(*this);
        Expr *rhs_from_ = result_from_;
        Expr *rhs_to_ = result_to_;

        result_from_ = new AddExpr(lhs_from_, rhs_from_);
        result_to_ = new AddExpr(lhs_to_, rhs_to_);
    }

    virtual void visit(SubExpr *expr)
    {
        expr->lhs()->accept(*this);
        Expr *lhs_from_ = result_from_;
        Expr *lhs_to_ = result_to_;

        expr->rhs()->accept(*this);
        Expr *rhs_from_ = result_from_;
        Expr *rhs_to_ = result_to_;

        result_from_ = new AddExpr(lhs_from_, rhs_from_);
        result_to_ = new AddExpr(lhs_to_, rhs_to_);
    }

    virtual void visit(MulExpr *expr)
    {
        expr->lhs()->accept(*this);
        Expr *lhs_from_ = result_from_;
        Expr *lhs_to_ = result_to_;

        expr->rhs()->accept(*this);
        Expr *rhs_from_ = result_from_;
        Expr *rhs_to_ = result_to_;

        result_from_ = new AddExpr(lhs_from_, rhs_from_);
        result_to_ = new AddExpr(lhs_to_, rhs_to_);
    }

    virtual void visit(DivExpr *expr)
    {
        expr->lhs()->accept(*this);
        Expr *lhs_from_ = result_from_;
        Expr *lhs_to_ = result_to_;

        expr->rhs()->accept(*this);
        Expr *rhs_from_ = result_from_;
        Expr *rhs_to_ = result_to_;

        result_from_ = new AddExpr(lhs_from_, rhs_from_);
        result_to_ = new AddExpr(lhs_to_, rhs_to_);
    }

    virtual void visit(ModExpr *expr)
    {
        expr->lhs()->accept(*this);
        Expr *lhs_from_ = result_from_;
        Expr *lhs_to_ = result_to_;

        expr->rhs()->accept(*this);
        Expr *rhs_from_ = result_from_;
        Expr *rhs_to_ = result_to_;

        result_from_ = new AddExpr(lhs_from_, rhs_from_);
        result_to_ = new AddExpr(lhs_to_, rhs_to_);
    }

    virtual void visit(ShlExpr *expr)
    {
        expr->lhs()->accept(*this);
        Expr *lhs_from_ = result_from_;
        Expr *lhs_to_ = result_to_;

        expr->rhs()->accept(*this);
        Expr *rhs_from_ = result_from_;
        Expr *rhs_to_ = result_to_;

        result_from_ = new AddExpr(lhs_from_, rhs_from_);
        result_to_ = new AddExpr(lhs_to_, rhs_to_);
    }

    virtual void visit(ShrExpr *expr)
    {
        expr->lhs()->accept(*this);
        Expr *lhs_from_ = result_from_;
        Expr *lhs_to_ = result_to_;

        expr->rhs()->accept(*this);
        Expr *rhs_from_ = result_from_;
        Expr *rhs_to_ = result_to_;

        result_from_ = new AddExpr(lhs_from_, rhs_from_);
        result_to_ = new AddExpr(lhs_to_, rhs_to_);
    }

    virtual void visit(SeqExpr *expr)
    {
        error_ = true;
    }

    virtual void visit(RngExpr *expr)
    {
        error_ = true;
    }

    virtual void visit(LogExpr *expr)
    {
        error_ = true;
    }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__UTIL__EXPR_APPLY_H__
