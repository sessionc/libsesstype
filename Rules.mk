#
# Global rules
#

.PHONY: clean clean-all

$(BUILD_DIR)/%.o: %.c $(INCLUDE_DIR)/%.h
	$(CC) $(CFLAGS) -c $*.c \
	  -o $(BUILD_DIR)/$*.o

$(BUILD_DIR)/%.so: $(BUILD_DIR)/%.o
	$(CC) $(CFLAGS) -shared $(BUILD_DIR)/$*.o \
	  -o $(BUILD_DIR)/$*.so

clean:
	$(RM) -r $(BUILD_DIR)/*
	$(RM) -r $(BIN_DIR)/*

clean-all: clean
	$(RM) $(LIB_DIR)/lib*.a
