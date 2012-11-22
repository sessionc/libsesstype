#
# Common.mk
# Common make configuration options
#

INCLUDE_DIR := $(ROOT)/include
SRC_DIR     := $(ROOT)/src
LIB_DIR     := $(ROOT)/lib
DOCS_DIR    := $(ROOT)/docs
BUILD_DIR   := $(ROOT)/build
BIN_DIR     := $(ROOT)/bin

# Compile options

DEBUG   := -g -D__DEBUG__
RELEASE := -O3
PROFILE := -g -pg

MPICC   := mpicc
CFLAGS  := -Wall -I$(INCLUDE_DIR) -m64 -fPIC $(RELEASE)
LDFLAGS := -L$(LIB_DIR)

# Other options

AR      := ar
ARFLAGS := -cvq
INSTALL := install -p

# Other tools

CP      := cp -i
MV      := mv -i
MAKE    := make
MKDIR   := mkdir -p
DOXYGEN := doxygen
