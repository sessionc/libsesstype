libsesstype
===========

Libraries for programming with Session Types in C/C++.
This is a core library for internal tree representation of Session Types.
See [http://mrg.doc.ic.ac.uk/](http://mrg.doc.ic.ac.uk/) for details.

[![Build Status](https://travis-ci.org/sessionc/libsesstype.svg)](https://travis-ci.org/sessionc/libsesstype?branch=dev)

## Build

1. At the project root, fetch the external dependencies with git
   `$ git submodule init && git submodule update`

2. Generate build files with `CMake`
   `$ cd build && cmake ..`

3. While in the `build/` directory, run `make` to build the files,
   then `make test` to run the unit tests to make sure everything is working.
   `$ make && make test`

4. You will find libsesstype.so in the `build/` directory.

## Development

For both C and C++, include `sesstype/sesstype.h` to get started.

    #include <sesstype/sesstype.h>

    int main(int argc, char *argv[])
    {
      // If C++
      sesstype::Protocol protocol("Example");
      // If C
      st_tree *prot = st_tree_mk_init("Example");
      return EXIT_SUCCESS;
    }
