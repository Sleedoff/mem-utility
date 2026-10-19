TARGET      := mem_utility

SRC         := $(wildcard *.c)
BUILD_DIR   := build
OBJ         := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))

CROSS_COMPILE ?=

CC          := $(CROSS_COMPILE)gcc
STRIP       := $(CROSS_COMPILE)strip
SIZE        := $(CROSS_COMPILE)size
CFLAGS      ?= -O2 -Wall -Wextra -Wpedantic

.PHONY: all clean strip size help

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJ) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
$(BUILD_DIR):
	mkdir -p $@

strip: $(BUILD_DIR)/$(TARGET)
	$(STRIP) $<

size: $(BUILD_DIR)/$(TARGET)
	$(SIZE) $<

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo "Usage:"
	@echo "  make CROSS_COMPILE=<prefix>-        # сборка"
	@echo "  make CROSS_COMPILE=<prefix>- strip  # сборка + strip"
	@echo "  make clean                          # очистка"