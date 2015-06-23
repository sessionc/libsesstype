#
# Tests goes here.
#

add_executable(test_const constant.cc)
target_link_libraries(test_const sesstype gtest gtest_main)
add_test(NAME Constant COMMAND test_const)
