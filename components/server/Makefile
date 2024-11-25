TOOLCHAIN_PATH= ../../toolchains/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin


# Compiler and flags
#CC := gcc
CC = ${TOOLCHAIN_PATH}/arm-linux-gnueabihf-gcc
CFLAGS := -Wall -Wextra -I. -I../temperature

SRC_DIR = .
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
BUILD_DIR := build
OUTPUT_DIR := ../../build/components
TARGET := $(OUTPUT_DIR)/server.a

.PHONY: all clean

all: $(TARGET)

#Creating build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

#Linking
$(TARGET): $(OBJ) | $(OUTPUT_DIR)
#	@echo "Linking server component in progress..."
#	$(CC) $(CFLAGS) -o $@ $^
	ar rcs $@ $^

#Compiling
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning component..."
	rm -f $(OBJ) $(TARGET)
