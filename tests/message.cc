/**
 * \brief Tests for sesstype::MsgSig and sesstype::MsgPayload.
 */
#include "gtest/gtest.h"

#include <string>

#include "sesstype/msg.h"
#include "sesstype/parameterised/expr.h"
#include "sesstype/parameterised/expr/add.h"
#include "sesstype/parameterised/expr/var.h"
#include "sesstype/parameterised/expr/val.h"
#include "sesstype/parameterised/msg.h"

namespace sesstype {
namespace tests {

class MsgTest : public ::testing::Test {
 protected:
  MsgTest() {}
};

/**
 * \test Check that empty message signature can be constructed.
 */
TEST_F(MsgTest, EmptyMsg)
{
  auto *sig = new sesstype::MsgSig("");
  EXPECT_EQ(sig->label(), "");
  EXPECT_EQ(sig->num_payloads(), 0);
  delete sig;
}

/**
 * \test Check that empty message payload can be constructed.
 */
TEST_F(MsgTest, EmptyPayload)
{
  auto *payload = new sesstype::MsgPayload("T");
  EXPECT_EQ(payload->name(), "");
  EXPECT_EQ(payload->type(), "T");
}

/**
 * \test Check that empty parameterised message payload can be constructed.
 */
TEST_F(MsgTest, EmptyParameterisedPayload)
{
  auto *payload = new sesstype::parameterised::MsgPayload("T");
  EXPECT_EQ(payload->name(), "");
  EXPECT_EQ(payload->type(), "T");
  EXPECT_EQ(payload->num_dimens(), 0);
}

/**
 * \test Check that basic operation with non-empty message works.
 */
TEST_F(MsgTest, BasicMessages)
{
  auto *sig = new sesstype::MsgSig("Label");

  EXPECT_EQ(sig->label(), "Label");
  EXPECT_EQ(sig->num_payloads(), 0);

  auto *pl_typeonly = new sesstype::MsgPayload("float"); // Type only

  EXPECT_EQ(pl_typeonly->name(), "");
  EXPECT_EQ(pl_typeonly->type(), "float");

  sig->add_payload(pl_typeonly);
  EXPECT_EQ(sig->num_payloads(), 1);

  auto *pl_nametype = new sesstype::parameterised::MsgPayload("int", "count");

  EXPECT_EQ(pl_nametype->name(), "count");
  EXPECT_EQ(pl_nametype->type(), "int");
  EXPECT_EQ(pl_nametype->num_dimens(), 0);

  sig->add_payload(pl_nametype);
  EXPECT_EQ(sig->num_payloads(), 2);

  auto *pl_nametypeparam = new sesstype::parameterised::MsgPayload("long", "size");

  EXPECT_EQ(pl_nametypeparam->name(), "size");
  EXPECT_EQ(pl_nametypeparam->type(), "long");
  EXPECT_EQ(pl_nametypeparam->num_dimens(), 0);

  pl_nametypeparam->add_param(new sesstype::parameterised::ValExpr(2));
  EXPECT_EQ(pl_nametypeparam->num_dimens(), 1);

  pl_nametypeparam->add_param(new sesstype::parameterised::AddExpr(
        new sesstype::parameterised::ValExpr(1),
        new sesstype::parameterised::VarExpr("N")));
  EXPECT_EQ(pl_nametypeparam->num_dimens(), 2);

  EXPECT_EQ(sig->num_payloads(), 2);
  sig->add_payload(pl_nametypeparam);
  EXPECT_EQ(sig->num_payloads(), 3);

  EXPECT_EQ(sig->has_payload("name"), false);
  EXPECT_EQ(sig->has_payload(""), true);
  EXPECT_EQ(sig->has_payload("count"), true);
  EXPECT_EQ(sig->has_payload("size"), true);
  EXPECT_EQ(sig->has_payload("long"), false);

  delete sig;
}

} // namespace tests
} // namespace sesstype

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
