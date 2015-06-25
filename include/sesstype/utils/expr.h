/**
 * \file sesstype/utils/expr.h
 * \brief Utilities for Expr.
 */
#ifndef SESSTYPE__UTILS__EXPR_H__
#define SESSTYPE__UTILS__EXPR_H__

#include "sesstype/parameterised/expr.h"

#ifdef __cplusplus
namespace sesstype {
namespace utils {
#endif

#ifdef __cplusplus
/**
 * \brief Abstract class for building Expr visitors.
 */
class ExprVisitor {
  public:
    virtual void visit(parameterised::VarExpr *expr) = 0;
    virtual void visit(parameterised::ValExpr *expr) = 0;
    virtual void visit(parameterised::AddExpr *expr) = 0;
    virtual void visit(parameterised::SubExpr *expr) = 0;
    virtual void visit(parameterised::MulExpr *expr) = 0;
    virtual void visit(parameterised::DivExpr *expr) = 0;
    virtual void visit(parameterised::ModExpr *expr) = 0;
    virtual void visit(parameterised::ShlExpr *expr) = 0;
    virtual void visit(parameterised::ShrExpr *expr) = 0;
    virtual void visit(parameterised::SeqExpr *expr) = 0;
    virtual void visit(parameterised::RngExpr *expr) = 0;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace utils
} // namespace sesstype
#endif

#endif//SESSTYPE__UTILS__EXPR_H__
