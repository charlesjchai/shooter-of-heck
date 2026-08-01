# Configure flags
CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -g -lncurses
TARGET := main

# Set default target
all: $(TARGET)

# Compile target
$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

# Clean build files
clean:
	rm -rf $(TARGET) *.dSYM

# Define phony targets
.PHONY: all clean
