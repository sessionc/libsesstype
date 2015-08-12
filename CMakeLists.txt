project(libsesstype CXX C)
cmake_minimum_required(VERSION 2.8)
set(PROJECT_DESCRIPTION "Session Types programming library for C/C++")

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
# Build type.
#
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)
message(STATUS "Build mode: ${CMAKE_BUILD_TYPE}")

#
# Build configurations.
#
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -Werror")
set(CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS_DEBUG} -D__DEBUG__")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -D__DEBUG__")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
# Install.
#
set(CMAKE_INSTALL_PREFIX "/usr")
install(DIRECTORY ${libsesstype_INCLUDE_DIR}/
        DIRECTORY ${PROJECT_BINARY_DIR}/include/
        DESTINATION include
        FILES_MATCHING PATTERN *.h)
install(TARGETS sesstype
        EXPORT sesstype
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc"
        DESTINATION lib/pkgconfig)

#
# pkg-config.
# Generate a .pc file for other to find
#
set(PKG_CONFIG_REQUIRES "")
set(PKG_CONFIG_LIBDIR "\${prefix}/lib")
set(PKG_CONFIG_INCLUDEDIR "\${prefix}/include")
set(PKG_CONFIG_LIBS "-L\${libdir} -lsesstype")
set(PKG_CONFIG_CFLAGS "-I\${includedir}")
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/pkg-config.pc.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc")

#
# Packaging.
#
include(package.cmake)
