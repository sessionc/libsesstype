/**
 * \file test/protocol.cc
 * \brief Tests for sesstype::Protocol.
 */
#include <stdexcept>
#include <string>
#include <iostream>

#include "gtest/gtest.h"

#include "sesstype/protocol.h"
#include "sesstype/import.h"
#include "sesstype/utils.h"

namespace sesstype {
/**
 * \brief Namespace for unit tests.
 */
namespace tests {

class ProtocolTest : public ::testing::Test {
 protected:
  ProtocolTest() {}
};

/**
 * \test Test construction of empty protocol.
 */
TEST_F(ProtocolTest, EmptyProtocol)
{
  sesstype::Protocol empty;
  EXPECT_EQ(empty.name(), std::string("default"));
  EXPECT_EQ(NULL, empty.root());
  EXPECT_EQ(empty.type(), ST_PROTOCOL_GLOBAL);
}

} // namespace tests
} // namespace sesstype

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

