/**
 * \file test/role.cc
 * \brief Tests for sesstype::Role, sesstype::parameterised::Role and
 * sesstype::parameterised::RoleGrp.
 */

#include "gtest/gtest.h"

#include <iostream>
#include <string>

#include "sesstype/role.h"
#include "sesstype/parameterised/expr.h"
#include "sesstype/parameterised/expr/rng.h"
#include "sesstype/parameterised/expr/val.h"
#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/role_grp.h"

namespace sesstype {
namespace tests {

class RoleTest : public ::testing::Test {
  protected:
    RoleTest() {}
};

/**
 * \test Basic usage of Role.
 */
TEST_F(RoleTest, BasicRole)
{
    auto *def = new sesstype::Role();
    EXPECT_EQ(def->name(), "default");
    delete def;

    auto *role = new sesstype::parameterised::Role("R");
    EXPECT_EQ(role->name(), "R");
    EXPECT_EQ(role->num_dimens(), 0);
    auto *param0 = new sesstype::parameterised::RngExpr(
                new sesstype::parameterised::ValExpr(1),
                new sesstype::parameterised::ValExpr(100));
    role->add_param(param0);
    EXPECT_EQ(role->num_dimens(), 1);
    EXPECT_EQ((*role)[0], param0);
    delete role;
}

/**
 * \test Basic usage of RoleGrp.
 */
TEST_F(RoleTest, BasicRolrGrp)
{
    auto *A = new sesstype::parameterised::Role("A");
    auto *B = new sesstype::parameterised::Role("B");
    auto *C = new sesstype::parameterised::Role("C");
    auto *D = new sesstype::parameterised::Role("D");

    auto *grp = new sesstype::parameterised::RoleGrp();
    EXPECT_EQ(grp->name(), "default_grp");
    EXPECT_EQ(grp->num_members(), 0);
    grp->set_name("g");
    EXPECT_EQ(grp->name(), "g");
    grp->add_member(A);
    EXPECT_EQ(grp->num_members(), 1);
    EXPECT_EQ(grp->member(0), A);

    grp->add_member(B);
    EXPECT_EQ(grp->num_members(), 2);
    EXPECT_EQ(grp->member(1), B);

    delete grp;

    auto *grp_withname = new sesstype::parameterised::RoleGrp("GRP");
    EXPECT_EQ(grp_withname->name(), "GRP");
    EXPECT_EQ(grp_withname->num_members(), 0);
    grp_withname->add_member(C);
    EXPECT_EQ(grp_withname->num_members(), 1);
    EXPECT_EQ(grp_withname->member(0), C);
    grp_withname->add_member(D);
    EXPECT_EQ(grp_withname->num_members(), 2);
    EXPECT_EQ(grp_withname->member(1), D);

    for (auto it=grp_withname->member_begin();
              it!=grp_withname->member_end(); it++) {
    }

    delete grp_withname;
}

} // namespace tests
} // namespace sesstype

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
