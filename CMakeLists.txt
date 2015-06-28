project(libsesstype CXX C)
cmake_minimum_required(VERSION 2.8)

#
# Version.
#
set(libsesstype_VERSION_MAJOR 2)
set(libsesstype_VERSION_MINOR 0)
set(libsesstype_VERSION_PATCH 0)
set(libsesstype_VERSION ${libsesstype_VERSION_MAJOR}.${libsesstype_VERSION_MINOR}.${libsesstype_VERSION_PATCH})


#
# Directories.
#
set(libsesstype_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(libsesstype_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(libsesstype_BINARY_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(libsesstype_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(libsesstype_TESTS_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(libsesstype_DOCS_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/docs)


# Copy the version to main header file.
configure_file(
    ${libsesstype_INCLUDE_DIR}/sesstype/sesstype.h.in
    ${PROJECT_BINARY_DIR}/include/sesstype/sesstype.h
)


#
# Build configurations.
#
set(CMAKE_C_FLAGS   "-std=c99   -O3 -Wall -Werror")
set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -Wall -Werror")


#
# Sources: libsesstype
#
include_directories(${libsesstype_INCLUDE_DIR} ${PROJECT_BINARY_DIR}/include)
add_subdirectory(${libsesstype_SOURCE_DIR})
add_library(sesstype SHARED ${libsesstype_SOURCE})


#
# Documentation.
#
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(
        ${libsesstype_DOCS_DIR}/Doxyfile.in
        ${PROJECT_BINARY_DIR}/docs/Doxyfile @ONLY
    )
    add_custom_target(docs
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
endif(DOXYGEN_FOUND)


#
# Tests.
#
if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/third_party/gtest)
  enable_testing(true)
  add_subdirectory(third_party/gtest)
  message(STATUS "Looking for gtest (unit test) - found")
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
  link_directories(${LIBRARY_OUTPUT_PATH})
  add_subdirectory(${libsesstype_TESTS_DIR})
else()
  message(WARNING "Looking for gtest (unit test) - not found (no unit test will be run).")
endif()


#
# Install and Packaging.
#
install(DIRECTORY ${libsesstype_INCLUDE_DIR}/
        DIRECTORY ${PROJECT_BINARY_DIR}/include/
        DESTINATION include
        FILES_MATCHING PATTERN *.h)
install(TARGETS sesstype
        EXPORT sesstype
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
include(package.cmake)
