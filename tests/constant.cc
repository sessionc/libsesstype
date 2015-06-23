/**
 * \file test/constant.cc
 * \brief Tests for sesstype::Constant.
 */

#include "gtest/gtest.h"

#include <string>

#include "sesstype/constant.h"

namespace sesstype {
namespace tests {

class ConstantTest : public ::testing::Test {
  protected:
    ConstantTest() {}
};

/**
 * \test Basic construction and use of Constant.
 */
TEST_F(ConstantTest, BasicConsts)
{
    auto *val = new sesstype::ValueConstant("N", 3);

    EXPECT_EQ(val->name(), "N");
    EXPECT_EQ(val->value(), 3);

    delete val;

    auto *rng = new sesstype::BoundedConstant("M", 3, 5);

    EXPECT_EQ(rng->name(), "M");
    EXPECT_EQ(rng->lbound(), 3);
    EXPECT_EQ(rng->ubound(), 5);

    delete rng;

    auto *inf = new sesstype::ScalableConstant("K", 2);

    EXPECT_EQ(inf->name(), "K");
    EXPECT_EQ(inf->lbound(), 2);

    delete inf;
}

} // namespace tests
} // namespace sesstype

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
