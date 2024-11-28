#toolchain path for glibc 2.27
TOOLCHAIN_PATH= ./toolchains/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin

# CC - specifies the compiler
#CC = gcc
CC = ${TOOLCHAIN_PATH}/arm-linux-gnueabihf-gcc
# Compiler flags
## -Wall - enables all compiler's wanrnings
## -Wextra - enables extra warnings
## -Iinclude - add include/ directory to search for headers
CFLAGS = -Wall -Wextra -Icomponents/server -Icomponents/temperature -Icomponents/light
LDFLAGS := -lm

BUILD_DIR := build
TEST_DIR := test
SRC_DIR := main

COMPONENTS := components/server \
				components/temperature \
				components/light 
#components/server \
			  components/temperature \


COMPONENT_LIBS = $(wildcard $(BUILD_DIR)/components/*.a)

#Finds .c files in src/
SOURCES = $(wildcard $(SRC_DIR)/*.c)

#Converts .c files to .o files in build/
##Ex. src/main.c -> build/main.o
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

#Final executable path
TARGET = $(BUILD_DIR)/greenhouse

.PHONY = all test clean

#Target that builds executable
all: build_components build_app

build_components $(BUILD_DIR):
	@echo "Building components..."
	@for comp in $(COMPONENTS); do \
		$(MAKE) -C $$comp CC=$(CC); \
	done

build_app: $(TARGET)

#COMPILING
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

#LINKING (combining object files into executable)
## $@ - target
## $^ - prerequisities (object files)
$(TARGET): $(OBJECTS) $(COMPONENT_LIBS)
	@echo "Linking in progress..."
	@echo "Component libraries: $(COMPONENT_LIBS)"
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(COMPONENT_LIBS) $(LDFLAGS)

#BUILDING TESTS
test: $(BUILD_DIR)/greenhouse_test

$(BUILD_DIR)/greenhouse_test: $(wildcard $(TEST_DIR)/*.c) | $(BUILD_DIR)
	@echo "Building tests..."
	$(CC) $(CFLAGS) -Iinclude -o $@ $^ $(LDFLAGS)

run_test: test
	@echo "Running tests..."
	$(BUILD_DIR)/greenhouse_test

#CLEAN
clean:
	@echo "Cleaning build directory..."
	rm -rf $(BUILD_DIR)