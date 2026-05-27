CXX := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN := bin
SRC_IMPL_LIST := src/MyLinkedList/Implementation
SRC_IMPL_ARRAY := src/MyDynamicArray/Implementation
SRC_STACK_ARRAY := src/MyStack/Implementation/MyStackArrayImpl
SRC_STACK_LLIST := src/MyStack/Implementation/MyStackLListImpl
SRC_MAIN := src/main
SRC_UT_LIST := src/MyLinkedList/Unittests
SRC_UT_ARRAY := src/MyDynamicArray/Unittests
SRC_UT_STACK_ARRAY := src/MyStack/Implementation/MyStackArrayImpl/Unittests
SRC_UT_STACK_LLIST := src/MyStack/Implementation/MyStackLListImpl/Unittests
INCLUDE_DIRS := -I$(SRC_IMPL_LIST) -I$(SRC_IMPL_ARRAY) -I$(SRC_STACK_ARRAY) -I$(SRC_STACK_LLIST) -I$(SRC_UT_LIST) -I$(SRC_UT_ARRAY) -I$(SRC_UT_STACK_ARRAY) -I$(SRC_UT_STACK_LLIST)

LIBRARIES :=
EXECUTABLE := main

OBJS := $(BIN)/main.o $(BIN)/MyLinkedList.o $(BIN)/MyLinkedListUTests.o $(BIN)/MyDynamicArray.o $(BIN)/MyDynamicArrayUTests.o $(BIN)/MyStackArrayImpl.o $(BIN)/MyStackArrayImplUTests.o $(BIN)/MyStackLListImpl.o $(BIN)/MyStackLListImplUTests.o

.PHONY: all run clean

all: $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) $^ -o $@ $(LIBRARIES)

$(BIN)/main.o: $(SRC_MAIN)/main.cpp | $(BIN)
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(BIN)/MyLinkedList.o: $(SRC_IMPL_LIST)/MyLinkedList.cpp | $(BIN)
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(BIN)/MyLinkedListUTests.o: $(SRC_UT_LIST)/MyLinkedListUTests.cpp | $(BIN)
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(BIN)/MyDynamicArrayUTests.o: $(SRC_UT_ARRAY)/MyDynamicArrayUTests.cpp | $(BIN)
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(BIN)/MyDynamicArray.o: $(SRC_IMPL_ARRAY)/MyDynamicArray.cpp | $(BIN)
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(BIN)/MyStackArrayImpl.o: $(SRC_STACK_ARRAY)/MyStackArrayImpl.cpp | $(BIN)
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(BIN)/MyStackArrayImplUTests.o: $(SRC_UT_STACK_ARRAY)/MyStackArrayImplUTests.cpp | $(BIN)
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(BIN)/MyStackLListImpl.o: $(SRC_STACK_LLIST)/MyStackLListImpl.cpp | $(BIN)
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(BIN)/MyStackLListImplUTests.o: $(SRC_UT_STACK_LLIST)/MyStackLListImplUTests.cpp | $(BIN)
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(BIN):
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)
