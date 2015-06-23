#
# Tests goes here.
#

add_executable(test_message message.cc)
target_link_libraries(test_message sesstype gtest gtest_main)
add_test(NAME Message COMMAND test_message)

add_executable(test_const constant.cc)
target_link_libraries(test_const sesstype gtest gtest_main)
add_test(NAME Constant COMMAND test_const)

add_executable(test_expr expr.cc)
target_link_libraries(test_expr sesstype gtest gtest_main)
add_test(NAME Expr COMMAND test_expr)
