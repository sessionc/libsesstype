#include <sesstype/parameterised/expr.h>
#include <sesstype/parameterised/util/expr_visitor.h>

namespace sesstype {
namespace parameterised {

void VarExpr::accept(util::ExprVisitor &v) { v.visit(this); }

void ValExpr::accept(util::ExprVisitor &v) { v.visit(this); }

void AddExpr::accept(util::ExprVisitor &v) { v.visit(this); }

void SubExpr::accept(util::ExprVisitor &v) { v.visit(this); }

void MulExpr::accept(util::ExprVisitor &v) { v.visit(this); }

void DivExpr::accept(util::ExprVisitor &v) { v.visit(this); }

void ModExpr::accept(util::ExprVisitor &v) { v.visit(this); }

void ShlExpr::accept(util::ExprVisitor &v) { v.visit(this); }

void ShrExpr::accept(util::ExprVisitor &v) { v.visit(this); }

void SeqExpr::accept(util::ExprVisitor &v) { v.visit(this); }

void RngExpr::accept(util::ExprVisitor &v) { v.visit(this); }

} // namespace parameterised
} // namespace sesstype
