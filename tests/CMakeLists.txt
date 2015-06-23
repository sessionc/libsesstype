#
# Tests goes here.
#

add_executable(test_message message.cc)
target_link_libraries(test_message sesstype gtest gtest_main)
add_test(NAME Message COMMAND test_message)

add_executable(test_const constant.cc)
target_link_libraries(test_const sesstype gtest gtest_main)
add_test(NAME Constant COMMAND test_const)
