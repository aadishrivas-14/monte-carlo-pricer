CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -Iinclude
LDFLAGS = -pthread

SRC_DIR = src
BUILD_DIR = build
EXAMPLES_DIR = examples

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Examples
EXAMPLE1 = $(BUILD_DIR)/01_basic_pricer
EXAMPLE2 = $(BUILD_DIR)/02_parallel_pricer
EXAMPLE3 = $(BUILD_DIR)/03_variance_reduction

.PHONY: all clean examples

all: $(BUILD_DIR) examples

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build examples
$(EXAMPLE1): $(EXAMPLES_DIR)/01_basic_pricer.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(EXAMPLE2): $(EXAMPLES_DIR)/02_parallel_pricer.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(EXAMPLE3): $(EXAMPLES_DIR)/03_variance_reduction.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

examples: $(EXAMPLE1) $(EXAMPLE2) $(EXAMPLE3)

clean:
	rm -rf $(BUILD_DIR)

# Run examples
run1: $(EXAMPLE1)
	./$(EXAMPLE1)

run2: $(EXAMPLE2)
	./$(EXAMPLE2)

run3: $(EXAMPLE3)
	./$(EXAMPLE3)
