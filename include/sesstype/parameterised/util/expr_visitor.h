/**
 * \file sesstype/parameterised/util/expr_visitor.h
 * \brief Utilities for Expr.
 */
#ifndef SESSTYPE__PARAMETERISED__UTIL__EXPR_VISITOR_H__
#define SESSTYPE__PARAMETERISED__UTIL__EXPR_VISITOR_H__

#include "sesstype/parameterised/expr.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {

class VarExpr;
class ValExpr;
class AddExpr;
class SubExpr;
class MulExpr;
class DivExpr;
class ModExpr;
class ShlExpr;
class ShrExpr;
class SeqExpr;
class RngExpr;

} // namespace parameterised
} // namespace sesstype
#endif

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
    virtual void visit(sesstype::parameterised::VarExpr *expr) = 0;
    virtual void visit(sesstype::parameterised::ValExpr *expr) = 0;
    virtual void visit(sesstype::parameterised::AddExpr *expr) = 0;
    virtual void visit(sesstype::parameterised::SubExpr *expr) = 0;
    virtual void visit(sesstype::parameterised::MulExpr *expr) = 0;
    virtual void visit(sesstype::parameterised::DivExpr *expr) = 0;
    virtual void visit(sesstype::parameterised::ModExpr *expr) = 0;
    virtual void visit(sesstype::parameterised::ShlExpr *expr) = 0;
    virtual void visit(sesstype::parameterised::ShrExpr *expr) = 0;
    virtual void visit(sesstype::parameterised::SeqExpr *expr) = 0;
    virtual void visit(sesstype::parameterised::RngExpr *expr) = 0;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__UTIL__EXPR_VISITOR_H__
