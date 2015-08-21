/**
 * \file test/expr.cc
 * \brief Tests for Expr.
 */

#include "gtest/gtest.h"

#include <iostream>
#include <string>

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
#include "sesstype/parameterised/util/expr_apply.h"
#include "sesstype/parameterised/util/expr_eval.h"
#include "sesstype/parameterised/util/expr_invert.h"
#include "sesstype/parameterised/util/print.h"
#include "sesstype/parameterised/util/empty_visitor.hpp"

namespace sesstype {
namespace parameterised {
namespace tests {

class ExprTest : public ::testing::Test {
  protected:
    ExprTest() {}
};

/**
 * \test VarExpr operations.
 */
TEST_F(ExprTest, TestVarExpr)
{
    auto *expr = new VarExpr("N");
    EXPECT_EQ(expr->type(), ST_EXPR_VAR);
    EXPECT_EQ(expr->name(), "N");
    delete expr;
}

/**
 * \test ValExpr operations.
 */
TEST_F(ExprTest, TestValExpr)
{
    auto *expr = new ValExpr(42);
    EXPECT_EQ(expr->type(), ST_EXPR_CONST);
    EXPECT_EQ(expr->num(), 42);
    delete expr;
}

/**
 * \test AddExpr operations.
 */
TEST_F(ExprTest, TestAddExpr)
{
    auto *l = new ValExpr(42);
    auto *r = new VarExpr("N");
    auto *expr = new AddExpr(l, r);
    EXPECT_EQ(expr->type(), ST_EXPR_ADD);
    EXPECT_EQ(expr->lhs(), l);
    EXPECT_EQ(expr->rhs(), r);
    delete expr;
}

/**
 * \test SubExpr operations.
 */
TEST_F(ExprTest, TestSubExpr)
{
    auto *l = new VarExpr("N");
    auto *r = new ValExpr(42);
    auto *expr = new SubExpr(l, r);
    EXPECT_EQ(expr->type(), ST_EXPR_SUB);
    EXPECT_EQ(expr->lhs(), l);
    EXPECT_EQ(expr->rhs(), r);
    delete expr;
}

/**
 * \test MulExpr operations.
 */
TEST_F(ExprTest, TestMulExpr)
{
    auto *l = new VarExpr("N");
    auto *r = new ValExpr(42);
    auto *expr = new MulExpr(l, r);
    EXPECT_EQ(expr->type(), ST_EXPR_MUL);
    EXPECT_EQ(expr->lhs(), l);
    EXPECT_EQ(expr->rhs(), r);
    delete expr;
}

/**
 * \test DivExpr operations.
 */
TEST_F(ExprTest, TestDivExpr)
{
    auto *l = new VarExpr("N");
    auto *r = new ValExpr(42);
    auto *expr = new DivExpr(l, r);
    EXPECT_EQ(expr->type(), ST_EXPR_DIV);
    EXPECT_EQ(expr->lhs(), l);
    EXPECT_EQ(expr->rhs(), r);
    delete expr;
}

/**
 * \test ModExpr operations.
 */
TEST_F(ExprTest, TestModExpr)
{
    auto *l = new VarExpr("N");
    auto *r = new ValExpr(42);
    auto *expr = new ModExpr(l, r);
    EXPECT_EQ(expr->type(), ST_EXPR_MOD);
    EXPECT_EQ(expr->lhs(), l);
    EXPECT_EQ(expr->rhs(), r);
    delete expr;
}

/**
 * \test ShlExpr operations.
 */
TEST_F(ExprTest, TestShlExpr)
{
    auto *l = new ValExpr(3);
    auto *r = new ValExpr(2);
    auto *expr = new ShlExpr(l, r);
    EXPECT_EQ(expr->type(), ST_EXPR_SHL);
    EXPECT_EQ(expr->lhs(), l);
    EXPECT_EQ(expr->rhs(), r);
    delete expr;
}

/**
 * \test ShrExpr operations.
 */
TEST_F(ExprTest, TestShrExpr)
{
    auto *l = new ValExpr(3);
    auto *r = new ValExpr(2);
    auto *expr = new ShrExpr(l, r);
    EXPECT_EQ(expr->type(), ST_EXPR_SHR);
    EXPECT_EQ(expr->lhs(), l);
    EXPECT_EQ(expr->rhs(), r);
    delete expr;
}

/**
 * \test SeqExpr operations.
 */
TEST_F(ExprTest, TestSeqExpr)
{
    auto *expr = new SeqExpr();
    EXPECT_EQ(expr->type(), ST_EXPR_SEQ);
    EXPECT_EQ(expr->num_values(), 0);
    expr->append_value(1);
    EXPECT_EQ(expr->num_values(), 1);
    expr->append_value(2);
    EXPECT_EQ(expr->num_values(), 2);
    expr->append_value(3);
    EXPECT_EQ(expr->num_values(), 3);
    expr->append_value(4);
    EXPECT_EQ(expr->num_values(), 4);
    expr->append_value(5);
    EXPECT_EQ(expr->num_values(), 5);

    int i=1;
    for (auto it=expr->seq_begin(); it!=expr->seq_end(); it++, i++) {
        EXPECT_EQ(*it, i);
        EXPECT_EQ(i, expr->value(i-1));
    }
    delete expr;
}

/**
 * \test RngExpr operations.
 */
TEST_F(ExprTest, TestRngExpr)
{
    auto *from = new ValExpr(1);
    auto *to = new ValExpr(10);
    auto *expr = new RngExpr(from, to);
    EXPECT_EQ(expr->from(), from);
    EXPECT_EQ(expr->to(), to);
    EXPECT_EQ(expr->bindvar(), "");

    expr->set_bindvar("BBB");
    EXPECT_EQ(expr->from(), from);
    EXPECT_EQ(expr->to(), to);
    EXPECT_EQ(expr->bindvar(), "BBB");

    auto *from2 = new ValExpr(2);
    auto *to2 = new SubExpr(
        new VarExpr("N"),
        new ValExpr(1));

    expr->set_from(from2);
    EXPECT_EQ(expr->from(), from2);
    EXPECT_EQ(expr->to(), to);
    EXPECT_EQ(expr->bindvar(), "BBB");

    expr->set_to(to2);
    EXPECT_EQ(expr->from(), from2);
    EXPECT_EQ(expr->to(), to2);
    EXPECT_EQ(expr->bindvar(), "BBB");
    delete expr;

    auto *expr_setbind = new RngExpr("A",
        new ValExpr(1),
        new ValExpr(100));
    delete expr_setbind;
}

/**
 * \test Basic usage of Expr.
 */
TEST_F(ExprTest, ComplexExpr)
{
  // 1 * 2 + (3 / N - 10) % 100

  auto *expr = new AddExpr(
      new MulExpr(
          new ValExpr(1),
          new ValExpr(2)),
      new ModExpr(
        new SubExpr(
          new DivExpr(
            new ValExpr(3),
            new VarExpr("N")),
          new ValExpr(10)),
        new ValExpr(100)));
  delete expr;
}

/**
 * \test Expression reverse.
 */
TEST_F(ExprTest, InvertExpr)
{
    // 1 * N - 1
    util::ExprInvert inverter("i");

    auto expr = new SubExpr(
            new MulExpr(new ValExpr(3), new VarExpr("i")),
            new ValExpr(2));

    expr->accept(inverter);
    Expr *inverted = inverter.invert();

    EXPECT_EQ(inverted->type(), ST_EXPR_DIV);
    DivExpr *de = dynamic_cast<DivExpr *>(inverted);
    EXPECT_EQ(de->lhs()->type(), ST_EXPR_ADD);
    EXPECT_EQ(de->rhs()->type(), ST_EXPR_CONST);
    EXPECT_EQ(dynamic_cast<ValExpr *>(de->rhs())->num(), 3);
    AddExpr *ae = dynamic_cast<AddExpr *>(de->lhs());
    EXPECT_EQ(ae->lhs()->type(), ST_EXPR_VAR);
    EXPECT_EQ(ae->rhs()->type(), ST_EXPR_CONST);
    EXPECT_EQ(dynamic_cast<VarExpr *>(ae->lhs())->name(), "i");
    EXPECT_EQ(dynamic_cast<ValExpr *>(ae->rhs())->num(), 2);

    delete expr;
    delete inverted;
}

/**
 * \test Expression apply.
 */
TEST_F(ExprTest, ApplyExpr)
{
    // Apply i:1..10 --> i+1

    auto rng = new RngExpr("i", new ValExpr(1), new ValExpr(10));
    util::ExprApply apply(rng);
    auto expr = new AddExpr(new VarExpr("i"), new ValExpr(1));
    expr->accept(apply);
    auto applied = apply.apply();
    util::Print p;
    applied->accept(p);
    util::ExprEval eval;
    applied->accept(eval);
    auto eval_applied = eval.eval();
    std::cout << "eval applied: " << *eval_applied << "\n";

    delete rng;
    delete applied;
}

TEST_F(ExprTest, CloneExpr)
{
    util::EmptyVisitor v;
    auto rng = new RngExpr(
            "__",
            new ValExpr(1),
            new AddExpr(
                new SubExpr(
                    new DivExpr(new ValExpr(1), new VarExpr("G")),
                    new MulExpr(
                        new ShlExpr(new ValExpr(1), new VarExpr("K")),
                        new ShrExpr(new ValExpr(2), new ValExpr(3))
                    )
                ),
                new ModExpr(new ValExpr(1), new ValExpr(42))
            ));
    rng->accept(v);
    auto rng2 = rng->clone();
    rng2->accept(v);
    delete rng;
    rng2->accept(v);
    delete rng2;
}

} // namespace tests
} // namespace parameterised
} // namespace sesstype

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
