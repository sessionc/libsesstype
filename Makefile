# 
# Makefile
#

ROOT := .
include $(ROOT)/Common.mk

all: libsesstype libsesstype.a

libsesstype:
	$(MAKE) --dir=src

libsesstype.a: libsesstype
	$(RM) $(LIB_DIR)/$@
	$(AR) $(ARFLAGS) $(BUILD_DIR)/$@ $(BUILD_DIR)/*.o
	$(CP) -v $(BUILD_DIR)/$@ $(LIB_DIR)/$@

install: libsesstype libsesstype.a
	$(MKDIR) $(DESTDIR)/usr/include
	$(MKDIR) $(DESTDIR)/usr/lib
	$(INSTALL) $(INCLUDE_DIR)/*.h $(DESTDIR)/usr/include
	$(INSTALL) $(BUILD_DIR)/*.so $(DESTDIR)/usr/lib
	$(INSTALL) $(LIB_DIR)/*.a $(DESTDIR)/usr/lib

pkg-deb: all
	dpkg-buildpackage -us -uc -rfakeroot

include $(ROOT)/Rules.mk
