#include <sesstype/expr.h>
#include <sesstype/utils.h>

namespace sesstype {

void VarExpr::accept(utils::ExprVisitor &v)
{
  v.visit(this);
}

void ValExpr::accept(utils::ExprVisitor &v)
{
  v.visit(this);
}

void AddExpr::accept(utils::ExprVisitor &v)
{
  v.visit(this);
}

void SubExpr::accept(utils::ExprVisitor &v)
{
  v.visit(this);
}

void MulExpr::accept(utils::ExprVisitor &v)
{
  v.visit(this);
}

void DivExpr::accept(utils::ExprVisitor &v)
{
  v.visit(this);
}

void ModExpr::accept(utils::ExprVisitor &v)
{
  v.visit(this);
}

void ShlExpr::accept(utils::ExprVisitor &v)
{
  v.visit(this);
}

void ShrExpr::accept(utils::ExprVisitor &v)
{
  v.visit(this);
}

void SeqExpr::accept(utils::ExprVisitor &v)
{
  v.visit(this);
}

void RngExpr::accept(utils::ExprVisitor &v)
{
  v.visit(this);
}

} // namespace sesstype
