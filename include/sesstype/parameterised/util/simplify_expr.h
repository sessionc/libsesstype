#ifndef SESSTYPE__PARAMETERISED__UTIL__SIMPLIFY_EXPR_H__
#define SESSTYPE__PARAMETERISED__UTIL__SIMPLIFY_EXPR_H__

#include "sesstype/parameterised/util/expr_visitor.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
namespace util {
#endif

#ifdef __cplusplus
class SimplifyExpr : public ExprVisitor {
  public:
    virtual void visit(Expr *expr) override { }
    virtual void visit(VarExpr *expr) override { }
    virtual void visit(ValExpr *expr) override { }
    virtual void visit(AddExpr *expr) override { }
    virtual void visit(SubExpr *expr) override { }
    virtual void visit(MulExpr *expr) override { }
    virtual void visit(DivExpr *expr) override { }
    virtual void visit(ModExpr *expr) override { }
    virtual void visit(ShlExpr *expr) override { }
    virtual void visit(ShrExpr *expr) override { }
    virtual void visit(SeqExpr *expr) override { }
    virtual void visit(RngExpr *expr) override { }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SENDTYPE__PARAMETERISED__UTIL__SIMPLIFY_EXPR_H__
