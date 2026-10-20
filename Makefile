
CC ?= arm-linux-gnueabihf-gcc
CFLAGS = -Wall -Wextra -O0 -g -DDEBUG
TARGET = mem_utility

SOURCES = mem_utility.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build complete: $(TARGET)"

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
	chmod +x /usr/local/bin/$(TARGET)

strip: $(BUILD_DIR)/$(TARGET)
	$(STRIP) $<
