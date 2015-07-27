/**
 * \file test/session.cc
 * \brief Tests for sesstype::Session.
 */
#include <stdexcept>
#include <string>
#include <iostream>

#include "gtest/gtest.h"

#include "sesstype/session.h"
#include "sesstype/import.h"
#include "sesstype/util.h"

namespace sesstype {
/**
 * \brief Namespace for unit tests.
 */
namespace tests {

class SessionTest : public ::testing::Test {
 protected:
  SessionTest() {}
};

/**
 * \test Test construction of empty session.
 */
TEST_F(SessionTest, EmptySession)
{
  sesstype::Session empty;
  EXPECT_EQ(empty.name(), std::string("default"));
  EXPECT_EQ(NULL, empty.root());
  EXPECT_EQ(empty.type(), ST_TYPE_GLOBAL);
}

} // namespace tests
} // namespace sesstype

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

