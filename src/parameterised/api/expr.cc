#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>

#include <sesstype/parameterised/cond.h>
#include <sesstype/parameterised/expr.h>
#include <sesstype/parameterised/util.h>

namespace sesstype {
namespace parameterised {

st_expr *st_expr_mk_const(int num)
{
    return new ValExpr(num);
}

st_expr *st_expr_mk_var(const char *var)
{
    return new VarExpr(std::string(var));
}

st_expr *st_expr_mk_binary(st_expr *lhs, int type, st_expr *rhs)
{
    switch (type) {
    case ST_EXPR_ADD:
        return new AddExpr(lhs, rhs);
    case ST_EXPR_SUB:
        return new SubExpr(lhs, rhs);
    case ST_EXPR_MUL:
        return new MulExpr(lhs, rhs);
    case ST_EXPR_DIV:
        return new DivExpr(lhs, rhs);
    case ST_EXPR_MOD:
        return new ModExpr(lhs, rhs);
    case ST_EXPR_SHL:
        return new ShlExpr(lhs, rhs);
    case ST_EXPR_SHR:
        return new ShrExpr(lhs, rhs);

    case ST_EXPR_CONST:
    case ST_EXPR_VAR:
    case ST_EXPR_SEQ:
    case ST_EXPR_RNG:
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
    util::SimplifyExpr s;
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

} // namespace parameterised
} // namespace sesstype
