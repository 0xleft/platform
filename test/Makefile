CXX = g++
Q = @

# Directories
SRC_DIR = ../src
TEST_DIR = .
BUILD_DIR = target

$(shell mkdir -p $(BUILD_DIR)/chess)

# Source files
SRC = $(wildcard $(SRC_DIR)/chess/*.cpp)
TEST_SRC = $(wildcard $(TEST_DIR)/*.cpp)

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Compiler flags
CPPFLAGS = -std=c++11 -fno-exceptions -Os -Wall -I../include -I$(SRC_DIR) -I$(SRC_DIR)/engine -I$(SRC_DIR)/chess -ffunction-sections -fdata-sections

# Linker flags
LDFLAGS = -Wl,--gc-sections

# Targets
.PHONY: all clean

all: $(BUILD_DIR)/test


$(BUILD_DIR)/test: $(OBJ) $(TEST_OBJ)
	$(Q) $(CXX) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

run: $(BUILD_DIR)/test
	$(Q) $(BUILD_DIR)/test

clean:
	rm -rf $(BUILD_DIR)