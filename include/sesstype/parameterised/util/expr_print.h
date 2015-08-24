#ifndef SESSTYPE__PARAMETERISED__UTIL__EXPR_PRINT_H__
#define SESSTYPE__PARAMETERISED__UTIL__EXPR_PRINT_H__

#ifdef __cplusplus
#include <iostream>
#include <string>
#endif

#include "sesstype/parameterised/exprs.h"
#include "sesstype/parameterised/util/expr_visitor.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
namespace util {
#endif

#ifdef __cplusplus
/**
 * \brief Protocol and Expression printer.
 */
class ExprPrintVisitor : public ExprVisitor {
    std::ostream &os_;

  public:
    ExprPrintVisitor() : os_(std::cout) { }

    /// \brief Printer constructor.
    ExprPrintVisitor(std::ostream &os) : os_(os) { }

    virtual void visit(Expr *expr)
    {
        // Empty.
    }

    virtual void visit(BinExpr *expr)
    {
        // Empty.
    }

    virtual void visit(VarExpr *expr)
    {
        os_ << expr->name();
    }

    virtual void visit(ValExpr *expr)
    {
        os_ << expr->num();
    }

    virtual void visit(AddExpr *expr)
    {
        os_ << "(";
        expr->lhs()->accept(*this);
        os_ << "+";
        expr->rhs()->accept(*this);
        os_ << ")";
    }

    virtual void visit(SubExpr *expr)
    {
        os_ << "(";
        expr->lhs()->accept(*this);
        os_ << "-";
        expr->rhs()->accept(*this);
        os_ << ")";
    }

    virtual void visit(MulExpr *expr)
    {
        expr->lhs()->accept(*this);
        os_ << "*";
        expr->rhs()->accept(*this);
    }

    virtual void visit(DivExpr *expr)
    {
        expr->lhs()->accept(*this);
        os_ << "/";
        expr->rhs()->accept(*this);
    }

    virtual void visit(ModExpr *expr)
    {
        expr->lhs()->accept(*this);
        os_ << "%";
        expr->rhs()->accept(*this);
    }

    virtual void visit(ShlExpr *expr)
    {
        expr->lhs()->accept(*this);
        os_ << "<<";
        expr->rhs()->accept(*this);
    }

    virtual void visit(ShrExpr *expr)
    {
        expr->lhs()->accept(*this);
        os_ << ">>";
        expr->rhs()->accept(*this);
    }

    virtual void visit(SeqExpr *expr)
    {
        for (auto it=expr->seq_begin(); it!=expr->seq_end(); it++) {
            if (it != expr->seq_begin()) os_ << ",";
            os_ << *it;
        }
    }

    virtual void visit(RngExpr *expr)
    {
        os_ << expr->bindvar();
        expr->from()->accept(*this);
        os_ << "..";
        expr->to()->accept(*this);
    }

    virtual void visit(LogExpr *expr)
    {
        os_ << "log(";
        expr->value()->accept(*this);
        os_ << ",";
        expr->base()->accept(*this);
        os_ << ")";
    }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
#endif

#ifdef __cplusplus
extern "C" {
#endif

void st_expr_print(st_expr *expr);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__UTIL__EXPR_PRINT_H__
