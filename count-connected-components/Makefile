CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -O2

BIN      := bin
SRC      := src
INCLUDE  := include

CPPFLAGS := -I$(INCLUDE)

all: $(BIN)/main

run: all
	./$(BIN)/main

test: $(BIN)/test $(BIN)/solver_test $(BIN)/inputreader_test $(BIN)/logger_test

run-tests: test
	./$(BIN)/solver_test
	./$(BIN)/inputreader_test
	./$(BIN)/logger_test
	./$(BIN)/test

$(BIN)/main: | $(BIN)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) \
		$(SRC)/main.cpp \
		$(SRC)/ConnectedComponentsSolver.cpp \
		$(SRC)/InputReader.cpp \
		$(SRC)/Logger.cpp \
		-o $@

$(BIN)/solver_test: | $(BIN)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) \
		$(SRC)/ConnectedComponentsSolver.cpp \
		$(SRC)/InputReader.cpp \
		$(SRC)/Logger.cpp \
		$(SRC)/ConnectedComponentsSolver_UTests.cpp \
		$(SRC)/SolverTestMain.cpp \
		-o $@

$(BIN)/inputreader_test: | $(BIN)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) \
		$(SRC)/ConnectedComponentsSolver.cpp \
		$(SRC)/InputReader.cpp \
		$(SRC)/InputReader_UTests.cpp \
		$(SRC)/InputReaderTestMain.cpp \
		-o $@

$(BIN)/logger_test: | $(BIN)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) \
		$(SRC)/Logger.cpp \
		$(SRC)/Logger_UTests.cpp \
		$(SRC)/LoggerTestMain.cpp \
		-o $@

$(BIN)/test: | $(BIN)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) \
		$(SRC)/ConnectedComponentsSolver.cpp \
		$(SRC)/InputReader.cpp \
		$(SRC)/Logger.cpp \
		$(SRC)/ConnectedComponentsSolver_UTests.cpp \
		$(SRC)/InputReader_UTests.cpp \
		$(SRC)/Logger_UTests.cpp \
		$(SRC)/AllUnitTests.cpp \
		-o $@

$(BIN):
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)

.PHONY: all run test run-tests clean
