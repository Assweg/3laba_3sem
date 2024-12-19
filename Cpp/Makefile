CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -g --coverage
LDFLAGS = -lgtest -lgtest_main -pthread --coverage

GOCMD=go
GOBUILD=$(GOCMD) build
GOCLEAN=$(GOCMD) clean
GOTEST=$(GOCMD) test
GOGET=$(GOCMD) get
GOCOVER=$(GOCMD) tool cover

# C++ targets
CPP_INCLUDE = include
CPP_TESTS = $(wildcard tests/test_*.cpp)
CPP_TARGETS = $(CPP_TESTS:tests/%.cpp=build/%.out)

# Go targets
GO_INCLUDE = include
GO_TESTS = $(wildcard tests/*_test.go)

all: cpp_test coverage

cpp_test: $(CPP_TARGETS)

$(CPP_TARGETS): build/%.out: tests/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -I$(CPP_INCLUDE) $< -o $@ $(LDFLAGS)

go_test:
	$(GOTEST) -v $(GO_TESTS)

coverage: cpp_coverage

cpp_coverage: $(CPP_TARGETS)
	@mkdir -p coverage
	for test in $(CPP_TARGETS); do \
		$$test || true; \
	done
	gcovr --html --html-details -o coverage/cpp_coverage.html --root=. --exclude-directories=tests



clean:
	$(GOCLEAN)
	rm -rf build coverage

.PHONY: all cpp_test go_test coverage cpp_coverage go_coverage clean