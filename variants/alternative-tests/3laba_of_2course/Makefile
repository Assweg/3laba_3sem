# Путь к Google Test 
GTEST_DIR = /path/to/googletest
GMOCK_DIR = /path/to/gmock

# Флаги компиляции
CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Isrc -I$(GTEST_DIR)/include -I$(GMOCK_DIR)/include -fprofile-instr-generate -fcoverage-mapping
LDFLAGS = -lgtest -lgmock -pthread

# Директории
SRC_DIR = src
TEST_DIR = test
COVERAGE_DIR = coverage

# Находим все тестовые файлы автоматически
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

# Создаем список исполняемых файлов для тестов
EXES = $(TEST_FILES:$(TEST_DIR)/%.cpp=%)

# Сборка всех тестов
all: $(EXES)

# Компиляция каждого теста в отдельный исполняемый файл
$(EXES): %: $(TEST_DIR)/%.o
	$(CXX) -o $@ $^ $(LDFLAGS)

# Компиляция объектных файлов
$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Запуск всех тестов
run-tests: all
	@for exe in $(EXES); do ./$$exe; done

# Сбор покрытия
coverage: $(EXES)
	@for exe in $(EXES); do ./$$exe; done  # Запускаем все тесты
	llvm-profdata merge -sparse default.profraw -o default.profdata
	llvm-cov show ./$(EXES) -instr-profile=default.profdata > $(COVERAGE_DIR)/coverage.txt
	llvm-cov show ./$(EXES) -instr-profile=default.profdata -format=html > $(COVERAGE_DIR)/coverage.html
	@echo "Открыть отчет по покрытию в каталоге $(COVERAGE_DIR)"

# Очистка
clean:
	rm -f $(TEST_DIR)/*.o $(EXES)
	rm -rf $(COVERAGE_DIR)/*
	find $(TEST_DIR) -name "*.profraw" -exec rm -f {} \;

.PHONY: all clean run-tests coverage