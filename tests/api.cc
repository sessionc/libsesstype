/**
 * \file test/api.cc
 * \brief Tests for C API.
 */

#include "gtest/gtest.h"

#include <string>

#include <sesstype/sesstype.h>

namespace sesstype {
namespace tests {

class APITest : public ::testing::Test {
  protected:
    APITest() {}
};

/**
 * \test Basic usage of C API.
 */
TEST_F(APITest, BasicUsage)
{
    st_module *module = st_module_mk_init("default");
    const char *name = st_module_get_name(module);
    EXPECT_STREQ(name, "default");
}

} // namespace tests
} // namespace sesstype

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
