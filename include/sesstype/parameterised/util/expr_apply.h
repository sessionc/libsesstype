#ifndef SESSTYPE__PARAMETERISED__UTIL__EXPR_APPLY_H__
#define SESSTYPE__PARAMETERISED__UTIL__EXPR_APPLY_H__

#ifdef __cplusplus
#include <stack>
#endif

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
    std::string findvar_;
    Expr *replacefrom_;
    Expr *replaceto_;
    std::stack<Expr *> from_;
    std::stack<Expr *> to_;
    bool error_;

  public:
    ExprApply(RngExpr *bindexpr) : findvar_(bindexpr->bindvar()),
                                   replacefrom_(bindexpr->from()),
                                   replaceto_(bindexpr->to()),
                                   from_(),
                                   to_(),
                                   error_(false) { }

    Expr *apply()
    {
        if (!error_) {
            return new RngExpr(std::string(findvar_), from_.top(), to_.top());
        }
        return nullptr;
    }

    virtual void visit(Expr *expr)
    {
        // Nothing.
    }

    virtual void visit(ValExpr *expr)
    {
        from_.push(expr->clone());
        to_.push(expr->clone());
    }

    virtual void visit(VarExpr *expr)
    {
        if (expr->name() == findvar_) { // Base case, start building
            // Replace var with from and to.
            from_.push(replacefrom_->clone());
            to_.push(replaceto_->clone());
        } else {
            from_.push(expr->clone());
            to_.push(expr->clone());
        }
    }

    virtual void visit(AddExpr *expr)
    {
        expr->lhs()->accept(*this);
        Expr *lhs_from = from_.top();
        from_.pop();
        Expr *lhs_to = to_.top();
        to_.pop();

        expr->rhs()->accept(*this);
        Expr *rhs_from = from_.top();
        from_.pop();
        Expr *rhs_to = to_.top();
        to_.pop();

        from_.push(new AddExpr(lhs_from, rhs_from));
        to_.push(new AddExpr(lhs_to, rhs_to));
    }

    virtual void visit(SubExpr *expr)
    {
        expr->lhs()->accept(*this);
        Expr *lhs_from = from_.top();
        from_.pop();
        Expr *lhs_to = to_.top();
        to_.pop();

        expr->rhs()->accept(*this);
        Expr *rhs_from = from_.top();
        from_.pop();
        Expr *rhs_to = to_.top();
        to_.pop();

        from_.push(new SubExpr(lhs_from, rhs_from));
        to_.push(new SubExpr(lhs_to, rhs_to));
    }

    virtual void visit(MulExpr *expr)
    {
        expr->lhs()->accept(*this);
        Expr *lhs_from = from_.top();
        from_.pop();
        Expr *lhs_to = to_.top();
        to_.pop();

        expr->rhs()->accept(*this);
        Expr *rhs_from = from_.top();
        from_.pop();
        Expr *rhs_to = to_.top();
        to_.pop();

        from_.push(new MulExpr(lhs_from, rhs_from));
        to_.push(new MulExpr(lhs_to, rhs_to));
    }

    virtual void visit(DivExpr *expr)
    {
        expr->lhs()->accept(*this);
        Expr *lhs_from = from_.top();
        from_.pop();
        Expr *lhs_to = to_.top();
        to_.pop();

        expr->rhs()->accept(*this);
        Expr *rhs_from = from_.top();
        from_.pop();
        Expr *rhs_to = to_.top();
        to_.pop();

        from_.push(new DivExpr(lhs_from, rhs_from));
        to_.push(new DivExpr(lhs_to, rhs_to));
    }

    virtual void visit(ModExpr *expr)
    {
        expr->lhs()->accept(*this);
        Expr *lhs_from = from_.top();
        from_.pop();
        Expr *lhs_to = to_.top();
        to_.pop();

        expr->rhs()->accept(*this);
        Expr *rhs_from = from_.top();
        from_.pop();
        Expr *rhs_to = to_.top();
        to_.pop();

        from_.push(new ModExpr(lhs_from, rhs_from));
        to_.push(new ModExpr(lhs_to, rhs_to));
    }

    virtual void visit(ShlExpr *expr)
    {
        expr->lhs()->accept(*this);
        Expr *lhs_from = from_.top();
        from_.pop();
        Expr *lhs_to = to_.top();
        to_.pop();

        expr->rhs()->accept(*this);
        Expr *rhs_from = from_.top();
        from_.pop();
        Expr *rhs_to = to_.top();
        to_.pop();

        from_.push(new ShlExpr(lhs_from, rhs_from));
        to_.push(new ShlExpr(lhs_to, rhs_to));
    }

    virtual void visit(ShrExpr *expr)
    {
        expr->lhs()->accept(*this);
        Expr *lhs_from = from_.top();
        from_.pop();
        Expr *lhs_to = to_.top();
        to_.pop();

        expr->rhs()->accept(*this);
        Expr *rhs_from = from_.top();
        from_.pop();
        Expr *rhs_to = to_.top();
        to_.pop();

        from_.push(new ShrExpr(lhs_from, rhs_from));
        to_.push(new ShrExpr(lhs_to, rhs_to));
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
