CXX := g++
INCLUDE_DIR := ../include
MYLIB_DIR := ../build
BUILD_DIR := build
CXXFLAGS := -std=c++17 -Wall -O3
LDFLAGS := -L$(MYLIB_DIR) -lmylib

TARGETS = static_demo dynamic_demo
all: $(addprefix $(BUILD_DIR)/, $(TARGETS))

$(BUILD_DIR)/static_demo: $(BUILD_DIR)/static_demo.o | $(BUILD_DIR)
	$(CXX) -o $@ $^ -Wl,-Bstatic $(LDFLAGS) -Wl,-Bdynamic

$(BUILD_DIR)/dynamic_demo: $(BUILD_DIR)/dynamic_demo.o | $(BUILD_DIR)
	$(CXX) -o $@ $^ -Wl,-rpath='../$(MYLIB_DIR)' $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
