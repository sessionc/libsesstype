/**
 * \file test/expr.cc
 * \brief Tests for sesstype::Expr.
 */

#include "gtest/gtest.h"

#include <iostream>
#include <string>

#include "sesstype/expr.h"

namespace sesstype {
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
    auto *expr = new sesstype::VarExpr("N");
    EXPECT_EQ(expr->type(), ST_EXPR_TYPE_VAR);
    EXPECT_EQ(expr->name(), "N");
    delete expr;
}

/**
 * \test ValExpr operations.
 */
TEST_F(ExprTest, TestValExpr)
{
    auto *expr = new sesstype::ValExpr(42);
    EXPECT_EQ(expr->type(), ST_EXPR_TYPE_CONST);
    EXPECT_EQ(expr->num(), 42);
    delete expr;
}

/**
 * \test AddExpr operations.
 */
TEST_F(ExprTest, TestAddExpr)
{
    auto *l = new sesstype::ValExpr(42);
    auto *r = new sesstype::VarExpr("N");
    auto *expr = new sesstype::AddExpr(l, r);
    EXPECT_EQ(expr->type(), ST_EXPR_TYPE_ADD);
    EXPECT_EQ(expr->lhs(), l);
    EXPECT_EQ(expr->rhs(), r);
    delete expr;
}

/**
 * \test SubExpr operations.
 */
TEST_F(ExprTest, TestSubExpr)
{
    auto *l = new sesstype::VarExpr("N");
    auto *r = new sesstype::ValExpr(42);
    auto *expr = new sesstype::SubExpr(l, r);
    EXPECT_EQ(expr->type(), ST_EXPR_TYPE_SUB);
    EXPECT_EQ(expr->lhs(), l);
    EXPECT_EQ(expr->rhs(), r);
    delete expr;
}

/**
 * \test MulExpr operations.
 */
TEST_F(ExprTest, TestMulExpr)
{
    auto *l = new sesstype::VarExpr("N");
    auto *r = new sesstype::ValExpr(42);
    auto *expr = new sesstype::MulExpr(l, r);
    EXPECT_EQ(expr->type(), ST_EXPR_TYPE_MUL);
    EXPECT_EQ(expr->lhs(), l);
    EXPECT_EQ(expr->rhs(), r);
    delete expr;
}

/**
 * \test DivExpr operations.
 */
TEST_F(ExprTest, TestDivExpr)
{
    auto *l = new sesstype::VarExpr("N");
    auto *r = new sesstype::ValExpr(42);
    auto *expr = new sesstype::DivExpr(l, r);
    EXPECT_EQ(expr->type(), ST_EXPR_TYPE_DIV);
    EXPECT_EQ(expr->lhs(), l);
    EXPECT_EQ(expr->rhs(), r);
    delete expr;
}

/**
 * \test ModExpr operations.
 */
TEST_F(ExprTest, TestModExpr)
{
    auto *l = new sesstype::VarExpr("N");
    auto *r = new sesstype::ValExpr(42);
    auto *expr = new sesstype::ModExpr(l, r);
    EXPECT_EQ(expr->type(), ST_EXPR_TYPE_MOD);
    EXPECT_EQ(expr->lhs(), l);
    EXPECT_EQ(expr->rhs(), r);
    delete expr;
}

/**
 * \test ShlExpr operations.
 */
TEST_F(ExprTest, TestShlExpr)
{
    auto *l = new sesstype::ValExpr(3);
    auto *r = new sesstype::ValExpr(2);
    auto *expr = new sesstype::ShlExpr(l, r);
    EXPECT_EQ(expr->type(), ST_EXPR_TYPE_SHL);
    EXPECT_EQ(expr->lhs(), l);
    EXPECT_EQ(expr->rhs(), r);
    delete expr;
}

/**
 * \test ShrExpr operations.
 */
TEST_F(ExprTest, TestShrExpr)
{
    auto *l = new sesstype::ValExpr(3);
    auto *r = new sesstype::ValExpr(2);
    auto *expr = new sesstype::ShrExpr(l, r);
    EXPECT_EQ(expr->type(), ST_EXPR_TYPE_SHR);
    EXPECT_EQ(expr->lhs(), l);
    EXPECT_EQ(expr->rhs(), r);
    delete expr;
}

/**
 * \test SeqExpr operations.
 */
TEST_F(ExprTest, TestSeqExpr)
{
    auto *expr = new sesstype::SeqExpr();
    EXPECT_EQ(expr->type(), ST_EXPR_TYPE_SEQ);
    EXPECT_EQ(expr->num_value(), 0);
    expr->append_value(1);
    EXPECT_EQ(expr->num_value(), 1);
    expr->append_value(2);
    EXPECT_EQ(expr->num_value(), 2);
    expr->append_value(3);
    EXPECT_EQ(expr->num_value(), 3);
    expr->append_value(4);
    EXPECT_EQ(expr->num_value(), 4);
    expr->append_value(5);
    EXPECT_EQ(expr->num_value(), 5);

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
    auto *from = new sesstype::ValExpr(1);
    auto *to = new sesstype::ValExpr(10);
    auto *expr = new sesstype::RngExpr(from, to);
    EXPECT_EQ(expr->from(), from);
    EXPECT_EQ(expr->to(), to);
    EXPECT_EQ(expr->bindvar(), "");

    expr->set_bindvar("BBB");
    EXPECT_EQ(expr->from(), from);
    EXPECT_EQ(expr->to(), to);
    EXPECT_EQ(expr->bindvar(), "BBB");

    auto *from2 = new sesstype::ValExpr(2);
    auto *to2 = new sesstype::SubExpr(
        new sesstype::VarExpr("N"),
        new sesstype::ValExpr(1));

    expr->set_from(from2);
    EXPECT_EQ(expr->from(), from2);
    EXPECT_EQ(expr->to(), to);
    EXPECT_EQ(expr->bindvar(), "BBB");

    expr->set_to(to2);
    EXPECT_EQ(expr->from(), from2);
    EXPECT_EQ(expr->to(), to2);
    EXPECT_EQ(expr->bindvar(), "BBB");
    delete expr;

    auto *expr_setbind = new sesstype::RngExpr("A",
        new sesstype::ValExpr(1),
        new sesstype::ValExpr(100));
    delete expr_setbind;
}

/**
 * \test Basic usage of Expr.
 */
TEST_F(ExprTest, ComplexExpr)
{
  // 1 * 2 + (3 / N - 10) % 100

  auto *expr = new sesstype::AddExpr(
      new sesstype::MulExpr(
          new sesstype::ValExpr(1),
          new sesstype::ValExpr(2)),
      new sesstype::ModExpr(
        new sesstype::SubExpr(
          new sesstype::DivExpr(
            new sesstype::ValExpr(3),
            new sesstype::VarExpr("N")),
          new sesstype::ValExpr(10)),
        new sesstype::ValExpr(100)));
  delete expr;
}

} // namespace tests
} // namespace sesstype

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
