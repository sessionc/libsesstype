#ifndef SESSTYPE__PARAMETERISED__UTIL__EXPR_INVERT_H__
#define SESSTYPE__PARAMETERISED__UTIL__EXPR_INVERT_H__

#ifdef __cplusplus
#include <stack>
#endif

#include "sesstype/parameterised/expr.h"
#include "sesstype/parameterised/expr/var.h"
#include "sesstype/parameterised/expr/val.h"
#include "sesstype/parameterised/expr/add.h"
#include "sesstype/parameterised/expr/sub.h"
#include "sesstype/parameterised/expr/mul.h"
#include "sesstype/parameterised/expr/div.h"
#include "sesstype/parameterised/expr/mod.h"
#include "sesstype/parameterised/expr/shl.h"
#include "sesstype/parameterised/expr/shr.h"
#include "sesstype/parameterised/expr/seq.h"
#include "sesstype/parameterised/expr/rng.h"
#include "sesstype/parameterised/expr/log.h"
#include "sesstype/parameterised/util/expr_visitor.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
namespace util {
#endif

#ifdef __cplusplus
/**
 * \brief Given f(x) = y, calculate its mathematical reverse f^-1(y) = x.
 *
 * The general approach is find which binary branch has variable and peel off
 * the other branch until var is reached.
 */
class ExprInvert : public ExprVisitor {
    bool error_;
    Expr *reversed_;
    std::string var_;

  public:
    ExprInvert(std::string var) : error_(false),
                                  reversed_(new VarExpr(var)),
                                  var_(var) { }

    Expr *invert()
    {
        if (is_valid()) {
            return reversed_;
        }
        return nullptr;
    }

    bool is_valid()
    {
        return !error_;
    }

    bool has_var(Expr *expr)
    {
        if (auto vare = dynamic_cast<VarExpr *>(expr)) {
            return (vare->name() == var_);
        } else if (auto bine = dynamic_cast<BinExpr *>(expr)) {
            return ( has_var(bine->lhs()) || has_var(bine->rhs()) );
        }
        return false;
    }

    virtual void visit(Expr *expr) override
    {
        // Nothing.
    }

    virtual void visit(VarExpr *expr) override
    {
    }

    virtual void visit(ValExpr *expr) override
    {
    }

    virtual void visit(AddExpr *expr) override
    {
        if (has_var(expr->lhs())) { // x + a = y --> x = y - a
            reversed_ = new SubExpr(reversed_, expr->rhs()->clone());
            expr->lhs()->accept(*this);
            return;
        }

        if (has_var(expr->rhs())) { // a + x = y --> x = y - a
            reversed_ = new SubExpr(reversed_, expr->lhs()->clone());
            expr->rhs()->accept(*this);
            return;
        }

        error_ = true;
    }

    virtual void visit(SubExpr *expr) override
    {
        if (has_var(expr->lhs())) { // x - a = y --> x = y + a
            reversed_ = new AddExpr(reversed_, expr->rhs()->clone());
            expr->lhs()->accept(*this);
            return;
        }

        if (has_var(expr->rhs())) { // a - x = y --> x = a - y
            reversed_ = new SubExpr(expr->lhs()->clone(), reversed_);
            expr->rhs()->accept(*this);
            return;
        }

        error_ = true;
    }

    virtual void visit(MulExpr *expr) override
    {
        if (has_var(expr->lhs())) { // x * a = y --> x = y / a
            reversed_ = new DivExpr(reversed_, expr->rhs()->clone());
            expr->lhs()->accept(*this);
            return;
        }

        if (has_var(expr->rhs())) { // a * x = y --> x = y / a
            reversed_ = new DivExpr(reversed_, expr->lhs()->clone());
            expr->lhs()->accept(*this);
            return;
        }

        error_ = true;
    }

    virtual void visit(DivExpr *expr) override
    {
        if (has_var(expr->lhs())) { // x / a = y --> x = y * a
            reversed_ = new MulExpr(reversed_, expr->rhs()->clone());
            expr->lhs()->accept(*this);
            return;
        }

        if (has_var(expr->rhs())) { // a / x = y --> x = a / y
            reversed_ = new DivExpr(expr->lhs()->clone(), reversed_);
            expr->rhs()->accept(*this);
            return;
        }

        error_ = true;
    }

    virtual void visit(ModExpr *expr) override
    {
        // Cannot reverse %
        error_ = true;
    }

    virtual void visit(ShlExpr *expr) override
    {
        if (has_var(expr->lhs())) { // x << a = x * 2^a = y --> x = y / (2^a)
            reversed_ = new DivExpr(reversed_, new ShlExpr(new ValExpr(1), expr->rhs()->clone()));
            expr->lhs()->accept(*this);
            return;
        }

        if (has_var(expr->rhs())) { // a << x = a * 2^x = y --> log(y / a, 2)
            reversed_ = new LogExpr(new DivExpr(reversed_, expr->lhs()->clone()), new ValExpr(2));
            expr->rhs()->accept(*this);
            return;
        }

        error_ = true;
    }

    virtual void visit(ShrExpr *expr) override
    {
        if (has_var(expr->lhs())) { // x << a = x / 2^a = y --> x = y * (2^a)
            reversed_ = new DivExpr(reversed_, new ShlExpr(new ValExpr(1), expr->rhs()->clone()));
            expr->lhs()->accept(*this);
            return;
        }

        if (has_var(expr->rhs())) { // a << x = a / 2^x = y --> log(a / y, 2)
            reversed_ = new LogExpr(new DivExpr(expr->lhs()->clone(), reversed_), new ValExpr(2));
            expr->rhs()->accept(*this);
            return;
        }

        error_ = true;
    }

    virtual void visit(SeqExpr *expr) override
    {
        error_ = true;
    }

    virtual void visit(RngExpr *expr) override
    {
        error_ = true;
    }

    virtual void visit(LogExpr *expr) override
    {
        reversed_ = new ShlExpr(new ValExpr(1), reversed_);
        expr->value()->accept(*this);
    }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__UTIL__EXPR_INVERT_H__
