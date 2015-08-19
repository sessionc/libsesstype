#ifndef SESSTYPE__PARAMETERISED__UTIL__EXPR_EVAL_H__
#define SESSTYPE__PARAMETERISED__UTIL__EXPR_EVAL_H__

#ifdef __cplusplus
#include <stack>
#endif

#include "sesstype/parameterised/util/expr_visitor.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
namespace util {
#endif

#ifdef __cplusplus
class ExprEval : public ExprVisitor {
    std::stack<Expr *> stack_;
    bool invalid_;

  public:
    ExprEval() : stack_(), invalid_(false) { }

    Expr *eval()
    {
        return stack_.top();
    }

    bool is_valid()
    {
        return invalid_;
    }

    virtual void visit(Expr *expr) override
    {
        // Nothing.
    }

    virtual void visit(VarExpr *expr) override
    {
        stack_.push(expr->clone());
    }

    virtual void visit(ValExpr *expr) override
    {
        stack_.push(expr->clone());
    }

    virtual void visit(AddExpr *expr) override
    {
        expr->lhs()->accept(*this);
        Expr *lhs = stack_.top();
        stack_.pop();

        expr->rhs()->accept(*this);
        Expr *rhs = stack_.top();
        stack_.pop();

        if (auto lhs_ve = dynamic_cast<ValExpr *>(lhs)) {
            if (auto rhs_ve = dynamic_cast<ValExpr *>(rhs)) {
                stack_.push(new ValExpr(lhs_ve->num() + rhs_ve->num()));
                return;
            }
        }
        stack_.push(new AddExpr(lhs, rhs));
    }

    virtual void visit(SubExpr *expr) override
    {
        expr->lhs()->accept(*this);
        Expr *lhs = stack_.top();
        stack_.pop();

        expr->rhs()->accept(*this);
        Expr *rhs = stack_.top();
        stack_.pop();

        if (auto lhs_ve = dynamic_cast<ValExpr *>(lhs)) {
            if (auto rhs_ve = dynamic_cast<ValExpr *>(rhs)) {
                stack_.push(new ValExpr(lhs_ve->num() - rhs_ve->num()));
                return;
            }
        }
        stack_.push(new SubExpr(lhs, rhs));
    }

    virtual void visit(MulExpr *expr) override
    {
        expr->lhs()->accept(*this);
        Expr *lhs = stack_.top();
        stack_.pop();

        expr->rhs()->accept(*this);
        Expr *rhs = stack_.top();
        stack_.pop();

        if (auto lhs_ve = dynamic_cast<ValExpr *>(lhs)) {
            if (auto rhs_ve = dynamic_cast<ValExpr *>(rhs)) {
                stack_.push(new ValExpr(lhs_ve->num() * rhs_ve->num()));
                return;
            }
        }
        stack_.push(new MulExpr(lhs, rhs));
    }

    virtual void visit(DivExpr *expr) override
    {
        expr->lhs()->accept(*this);
        Expr *lhs = stack_.top();
        stack_.pop();

        expr->rhs()->accept(*this);
        Expr *rhs = stack_.top();
        stack_.pop();

        if (auto lhs_ve = dynamic_cast<ValExpr *>(lhs)) {
            if (auto rhs_ve = dynamic_cast<ValExpr *>(rhs)) {
                stack_.push(new ValExpr(lhs_ve->num() / rhs_ve->num()));
                return;
            }
        }
        stack_.push(new DivExpr(lhs, rhs));
    }

    virtual void visit(ModExpr *expr) override
    {
        expr->lhs()->accept(*this);
        Expr *lhs = stack_.top();
        stack_.pop();

        expr->rhs()->accept(*this);
        Expr *rhs = stack_.top();
        stack_.pop();

        if (auto lhs_ve = dynamic_cast<ValExpr *>(lhs)) {
            if (auto rhs_ve = dynamic_cast<ValExpr *>(rhs)) {
                stack_.push(new ValExpr(lhs_ve->num() % rhs_ve->num()));
                return;
            }
        }
        stack_.push(new ModExpr(lhs, rhs));
    }

    virtual void visit(ShlExpr *expr) override
    {
        expr->lhs()->accept(*this);
        Expr *lhs = stack_.top();
        stack_.pop();

        expr->rhs()->accept(*this);
        Expr *rhs = stack_.top();
        stack_.pop();

        if (auto lhs_ve = dynamic_cast<ValExpr *>(lhs)) {
            if (auto rhs_ve = dynamic_cast<ValExpr *>(rhs)) {
                stack_.push(new ValExpr(lhs_ve->num() << rhs_ve->num()));
                return;
            }
        }
        stack_.push(new ShlExpr(lhs, rhs));
    }

    virtual void visit(ShrExpr *expr) override
    {
        expr->lhs()->accept(*this);
        Expr *lhs = stack_.top();
        stack_.pop();

        expr->rhs()->accept(*this);
        Expr *rhs = stack_.top();
        stack_.pop();

        if (auto lhs_ve = dynamic_cast<ValExpr *>(lhs)) {
            if (auto rhs_ve = dynamic_cast<ValExpr *>(rhs)) {
                stack_.push(new ValExpr(lhs_ve->num() >> rhs_ve->num()));
                return;
            }
        }
        stack_.push(new ShrExpr(lhs, rhs));
    }

    virtual void visit(SeqExpr *expr) override
    {
        stack_.push(expr->clone());
        invalid_ = true;
    }

    virtual void visit(RngExpr *expr) override
    {
        expr->from()->accept(*this);
        Expr *from = stack_.top();
        stack_.pop();

        expr->to()->accept(*this);
        Expr *to = stack_.top();
        stack_.pop();

        stack_.push(new RngExpr(std::string(expr->bindvar()), from, to));
    }

    virtual void visit(LogExpr *expr) override
    {
        expr->value()->accept(*this);
        Expr *e = stack_.top();
        stack_.pop();

        expr->base()->accept(*this);
        Expr *base = stack_.top();
        stack_.pop();

        stack_.push(new LogExpr(e, base));
    }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SENDTYPE__PARAMETERISED__UTIL__EXPR_EVAL_H__
