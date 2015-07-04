#
# Tests goes here.
#

add_executable(test_message message.cc)
target_link_libraries(test_message sesstype gtest gtest_main)
add_test(NAME Message COMMAND test_message)

add_executable(test_const constant.cc)
target_link_libraries(test_const sesstype gtest gtest_main)
add_test(NAME Constant COMMAND test_const)

add_executable(test_protocol protocol.cc)
target_link_libraries(test_protocol sesstype gtest gtest_main)
add_test(NAME Protocol COMMAND test_protocol)

add_executable(test_module module.cc)
target_link_libraries(test_module sesstype gtest gtest_main)
add_test(NAME Module COMMAND test_module)

add_executable(test_node node.cc)
target_link_libraries(test_node sesstype gtest gtest_main)
add_test(NAME Node COMMAND test_node)

add_executable(test_expr expr.cc)
target_link_libraries(test_expr sesstype gtest gtest_main)
add_test(NAME Expr COMMAND test_expr)

add_executable(test_role role.cc)
target_link_libraries(test_role sesstype gtest gtest_main)
add_test(NAME Role COMMAND test_role)

add_executable(test_projection projection.cc)
target_link_libraries(test_projection sesstype gtest gtest_main)
add_test(NAME Projection COMMAND test_projection)

add_executable(test_api api.cc)
target_link_libraries(test_api sesstype gtest gtest_main)
add_test(NAME API COMMAND test_api)
