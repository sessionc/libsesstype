# 
# Makefile
#

ROOT := .
include $(ROOT)/Common.mk

all: libsesstype

libsesstype:
	$(MAKE) --dir=src

libsesstype.a: libsesstype
	$(RM) $(LIB_DIR)/$@
	$(AR) $(ARFLAGS) $(BUILD_DIR)/$@ $(BUILD_DIR)/*.o
	$(CP) -v $(BUILD_DIR)/$@ $(LIB_DIR)/$@

include $(ROOT)/Rules.mk
