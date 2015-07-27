/**
 * \file test/module.cc
 * \brief Tests for sesstype::Module and sesstype::Import.
 */

#include <stdexcept>
#include <string>

#include "gtest/gtest.h"

#include "sesstype/module.h"
#include "sesstype/session.h"
#include "sesstype/parameterised/module.h"

namespace sesstype {
namespace tests {

class ModuleTest : public ::testing::Test {
 protected:
  ModuleTest() {}
};

/**
 * \test Test default settings of Module.
 */
TEST_F(ModuleTest, EmptyModule)
{
  sesstype::Module anon_module;
  EXPECT_EQ(anon_module.name(), "default");
  ASSERT_THROW(anon_module.session(""), std::out_of_range);
  anon_module.set_name("ANON");
  EXPECT_EQ(anon_module.name(), "ANON");
}

/**
 * \test Test adding Sessions to Module.
 */
TEST_F(ModuleTest, Module_AddSession)
{
  sesstype::Module module("M");
  auto *p = new sesstype::Session("P");
  EXPECT_EQ(module.num_session(), 0);
  module.add_session(p); // Do this, then hand over pointer to module.
  EXPECT_EQ(module.num_session(), 1);

  sesstype::Session pp("PP");
  module.add_session(&pp); // pp will be gone at the end of this function.
  EXPECT_EQ(module.num_session(), 2);

  EXPECT_EQ(module.session("P"), p);
  EXPECT_EQ(module.session("PP"), &pp);

  delete p;
}

/**
 * \test Test adding Import to Module.
 */
TEST_F(ModuleTest, Module_AddImport)
{
  sesstype::Module empty;
  auto *int_import = new sesstype::Import("int");
  auto *java_string_import = new sesstype::Import("String", "java.lang", "");

  // Test adding import really works.
  EXPECT_EQ(empty.num_import(), 0);
  EXPECT_EQ(empty.has_import(std::string("int")), false);
  empty.add_import(int_import);
  EXPECT_EQ(empty.num_import(), 1);
  EXPECT_EQ(empty.has_import(std::string("int")), true);
  EXPECT_EQ(empty.import("int"), int_import);

  empty.add_import(java_string_import);
  EXPECT_EQ(empty.num_import(), 2);
  EXPECT_EQ(empty.has_import("String"), true);
  EXPECT_EQ(empty.import("String"), java_string_import);

  ASSERT_THROW(empty.import("int2"), std::out_of_range);
}

/**
 * \test Test adding constant to Module.
 */
TEST_F(ModuleTest, Module_AddConstant)
{
  sesstype::parameterised::Module empty;
  auto *constant = new sesstype::parameterised::ValueConstant("N", 1);
  auto *constant2 = new sesstype::parameterised::BoundedConstant("M", 1, 10);
  EXPECT_EQ(empty.num_constant(), 0);
  empty.add_constant(constant);
  EXPECT_EQ(empty.num_constant(), 1);
  EXPECT_EQ(empty.constant("N"), constant);
  empty.add_constant(constant2);
  EXPECT_EQ(empty.num_constant(), 2);
  EXPECT_EQ(empty.constant("M"), constant2);
}

/**
 * \test Import alias works like normal Import but points to original Import.
 */
TEST_F(ModuleTest, Module_Alias)
{
  sesstype::Module empty;
  sesstype::Import *long_alias_import = new sesstype::Import("long", "C", "cint");
  empty.add_import(long_alias_import);
  EXPECT_EQ(empty.has_import(std::string("long")), true);
  EXPECT_EQ(empty.has_import(std::string("cint")), true); // Alias
  EXPECT_EQ(empty.import("cint"), empty.import("long"));
  ASSERT_THROW(empty.import("C"), std::out_of_range);
}

} // namespace tests
} // namespace sesstype

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
