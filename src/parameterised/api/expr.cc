#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>

#include "sesstype/parameterised/cond.h"
#include "sesstype/parameterised/expr.h"
#include "sesstype/parameterised/util.h"

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
    case ST_EXPR_ADD: return new AddExpr(lhs, rhs);
    case ST_EXPR_SUB: return new SubExpr(lhs, rhs);
    case ST_EXPR_MUL: return new MulExpr(lhs, rhs);
    case ST_EXPR_DIV: return new DivExpr(lhs, rhs);
    case ST_EXPR_MOD: return new ModExpr(lhs, rhs);
    case ST_EXPR_SHL: return new ShlExpr(lhs, rhs);
    case ST_EXPR_SHR: return new ShrExpr(lhs, rhs);

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

st_expr *st_expr_eval(st_expr *const e)
{
    sesstype::parameterised::util::ExprEval s;
    e->accept(s);
    return s.eval();
}

st_expr *st_expr_apply(st_expr *const b, st_expr *const e)
{
    if (auto b_rng = dynamic_cast<RngExpr *>(b)) {
        sesstype::parameterised::util::ExprApply applier(b_rng);
        e->accept(applier);
        return applier.apply();
    }
    return nullptr;
}

st_expr *st_expr_inv(st_expr *const e, st_expr *const var_expr)
{
    std::string var;
    if (auto ve = dynamic_cast<VarExpr *>(var_expr)) {
        var = ve->name();
    }
    sesstype::parameterised::util::ExprInvert inverter(var);
    e->accept(inverter);
    return inverter.invert();
}

void st_expr_free(st_expr *e)
{
    delete e;
}

std::ostream &operator<<(std::ostream &os, Expr &expr)
{
    sesstype::parameterised::util::PrintVisitor printer(os);
    expr.accept(printer);
    return os;
}

} // namespace parameterised
} // namespace sesstype
