set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${libsesstype_VERSION})

# Debian package.
set(CPACK_DEBIAN_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_DEBIAN_PACKAGE_VERSION ${libsesstype_VERSION})
set(CPACK_DEBIAN_PACKAGE_SECTION "libdevel")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Nicholas Ng <nickng@imperial.ac.uk>")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION_SUMMARY "Session Types programming library")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Session Types programming library for C/C++.
 This library is a collection of data structures for representing and APIs for manipulating Multiparty Session Types (MPST) for programming.
 A C API is provided for FFI interoperation with other programming languages.
 Developed for Imperial College London, see http://mrg.doc.ic.ac.uk/ for details about Session Types research.")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "http://www.doc.ic.ac.uk/~cn06/pabble")
set(CPACK_DEBIAN_PACKAGE_LICENSE "${CMAKE_HOME_DIRECTORY}/LICENSE.md")
set(CPACK_DEBIAN_PACKAGE_LICENSE "mit")
set(CPACK_DEBIAN_PACKAGE_RECOMMENDS "")
set(CPACK_DEBIAN_PACKAGE_SUGGESTS "")

include(CPack)
