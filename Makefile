CXX := g++
INCLUDE_DIR := include
BUILD_DIR := build
INSTALL_DIR ?= /usr/local
CXXFLAGS := -std=c++17 -Wall -Wextra -fPIC -fvisibility=hidden

# Default target
all: static dynamic

# Static library construction
static: $(BUILD_DIR)/libmylib.a

# Dynamic library construction
dynamic: $(BUILD_DIR)/libmylib.so

# Build rules for the static and dynamic libraries
$(BUILD_DIR)/libmylib.a: $(BUILD_DIR)/MyClass.o
	ar rcs $@ $^

$(BUILD_DIR)/libmylib.so: $(BUILD_DIR)/MyClass.o
	$(CXX) -shared $^ -o $@

$(BUILD_DIR)/MyClass.o: src/MyClass.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

install:
	install -d $(INSTALL_DIR)/include/mylib $(INSTALL_DIR)/lib
	install include/IMyClass.h $(INSTALL_DIR)/include/mylib/
	install $(BUILD_DIR)/libmylib.* $(INSTALL_DIR)/lib/
	ldconfig $(INSTALL_DIR)/lib 2>/dev/null || true

clean:
	rm -rf $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@

.PHONY: all static dynamic install clean