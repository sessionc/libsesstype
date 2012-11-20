# 
# src/Makefile
#

ROOT := ..
include $(ROOT)/Common.mk

all: sharedlib objs

objs: $(BUILD_DIR)/st_expr.o $(BUILD_DIR)/st_node.o $(BUILD_DIR)/st_normalise.o

sharedlib: $(BUILD_DIR)/st_expr.so $(BUILD_DIR)/st_node.so $(BUILD_DIR)/st_normalise.so

include $(ROOT)/Rules.mk
