CXX = g++
CXXFLAGS := -Iinc -Wall -Wextra -Wpedantic -std=c++17

SRC_DIR := src
INC_DIR := inc
OUT_DIR := out
APP_EXE := app.exe
TEST_EXE := test.exe

APP_OBJS := $(OUT_DIR)/main.o $(OUT_DIR)/array.o $(OUT_DIR)/print.o $(OUT_DIR)/search.o
TEST_OBJS := $(OUT_DIR)/test.o $(OUT_DIR)/search.o

.PHONY: all clean

all: $(APP_EXE)

$(APP_EXE): $(APP_OBJS)
	$(CXX) $(APP_OBJS) -o $@

$(TEST_EXE): $(TEST_OBJS)
	$(CXX) $(TEST_OBJS) -o $@

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR) $(APP_EXE) $(TEST_EXE)