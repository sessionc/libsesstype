#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>

#include <sesstype/expr.h>
#include <sesstype/utils.h>

namespace sesstype {

st_expr *st_expr_mk_const(int num)
{
  return new ValExpr(num);
}

st_expr *st_expr_mk_var(const char *var)
{
  return new VarExpr(std::string(var));
}

st_expr *st_expr_mk_binary(st_expr *lhs, enum __st_expr_type type, st_expr *rhs)
{
  switch (type) {
    case ST_EXPR_TYPE_ADD:
      return new AddExpr(lhs, rhs);
    case ST_EXPR_TYPE_SUB:
      return new SubExpr(lhs, rhs);
    case ST_EXPR_TYPE_MUL:
      return new MulExpr(lhs, rhs);
    case ST_EXPR_TYPE_DIV:
      return new DivExpr(lhs, rhs);
    case ST_EXPR_TYPE_MOD:
      return new ModExpr(lhs, rhs);
    case ST_EXPR_TYPE_SHL:
      return new ShlExpr(lhs, rhs);
    case ST_EXPR_TYPE_SHR:
      return new ShrExpr(lhs, rhs);

    case ST_EXPR_TYPE_CONST:
    case ST_EXPR_TYPE_VAR:
    case ST_EXPR_TYPE_SEQ:
    case ST_EXPR_TYPE_RNG:
      std::cerr << "Error: Cannot create binary expression from type "
                << type << std::endl;
    default:
      std::cerr << "Error: Unknown expression type "
                << type << std::endl;
      assert(0);
      break;
  }
  return NULL;
}

st_expr *st_expr_mk_range(char *bindvar, st_expr *from, st_expr *to)
{
  if (bindvar == NULL) {
    return new RngExpr(from, to);
  } else {
    return new RngExpr(bindvar, from, to);
  }
}

st_expr *st_expr_copy(const st_expr *e)
{
  return e->clone();
}

bool st_expr_is_identical(st_expr *e0, st_expr *e1)
{
  assert(0 /*TODO*/);
  return false;
}

void st_expr_eval(st_expr *e)
{
  utils::Simplifier s;
  e->accept(s);
}

void st_expr_free(st_expr *e)
{
  delete e;
}

st_expr *st_expr_apply(const st_expr *b, const st_expr *e)
{
  assert(0 /* TODO */);
}

st_expr *st_expr_inv(const st_expr *e)
{
  assert(0 /* TODO */);
}

} // namespace sesstype
