# 
# src/Makefile
#

ROOT := ..
include $(ROOT)/Common.mk

all: sharedlib objs

objs: $(BUILD_DIR)/st_expr.o $(BUILD_DIR)/st_node_print.o $(BUILD_DIR)/st_node.o $(BUILD_DIR)/st_role.o $(BUILD_DIR)/st_role_group.o $(BUILD_DIR)/st_normalise.o $(BUILD_DIR)/st_node_compare.o

sharedlib: $(BUILD_DIR)/st_expr.so $(BUILD_DIR)/st_node_print.so $(BUILD_DIR)/st_node.so $(BUILD_DIR)/st_role.so $(BUILD_DIR)/st_role_group.so $(BUILD_DIR)/st_normalise.so $(BUILD_DIR)/st_node_compare.so

include $(ROOT)/Rules.mk
