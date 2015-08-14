/**
 * \file sesstype/parameterised/util/expr_visitor.h
 * \brief Utilities for Expr.
 */
#ifndef SESSTYPE__PARAMETERISED__UTIL__EXPR_VISITOR_H__
#define SESSTYPE__PARAMETERISED__UTIL__EXPR_VISITOR_H__

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

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
namespace util {
#endif

#ifdef __cplusplus
/**
 * \brief Abstract class for building Expr visitors.
 */
class ExprVisitor {
  public:
    virtual void visit(Expr    *expr) = 0;
    virtual void visit(VarExpr *expr) = 0;
    virtual void visit(ValExpr *expr) = 0;
    virtual void visit(AddExpr *expr) = 0;
    virtual void visit(SubExpr *expr) = 0;
    virtual void visit(MulExpr *expr) = 0;
    virtual void visit(DivExpr *expr) = 0;
    virtual void visit(ModExpr *expr) = 0;
    virtual void visit(ShlExpr *expr) = 0;
    virtual void visit(ShrExpr *expr) = 0;
    virtual void visit(SeqExpr *expr) = 0;
    virtual void visit(RngExpr *expr) = 0;
    virtual void visit(LogExpr *expr) = 0;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__UTIL__EXPR_VISITOR_H__
