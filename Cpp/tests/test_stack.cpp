#include "../include/Stack.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <fstream>

// Тест конструктора и деструктора
TEST(StackTest, ConstructorAndDestructor) {
    Stack<int> s(5);
    EXPECT_TRUE(s.SisEmpty());
}

// Тест метода Spush
TEST(StackTest, Push) {
    Stack<int> s(5);
    s.Spush(1);
    s.Spush(2);
    s.Spush(3);
    EXPECT_EQ(s.Speek(), 3);
}

// Тест метода Spop
TEST(StackTest, Pop) {
    Stack<int> s(5);
    s.Spush(1);
    s.Spush(2);
    s.Spush(3);
    s.Spop();
    EXPECT_EQ(s.Speek(), 2);
    s.Spop();
    EXPECT_EQ(s.Speek(), 1);
    s.Spop();
    EXPECT_TRUE(s.SisEmpty());
}

// Тест метода Speek
TEST(StackTest, Peek) {
    Stack<int> s(5);
    s.Spush(1);
    s.Spush(2);
    s.Spush(3);
    EXPECT_EQ(s.Speek(), 3);
    s.Spop();
    EXPECT_EQ(s.Speek(), 2);
    s.Spop();
    EXPECT_EQ(s.Speek(), 1);
}

// Тест метода SisEmpty
TEST(StackTest, IsEmpty) {
    Stack<int> s(5);
    EXPECT_TRUE(s.SisEmpty());
    s.Spush(1);
    EXPECT_FALSE(s.SisEmpty());
    s.Spop();
    EXPECT_TRUE(s.SisEmpty());
}

// Тест метода SisFull
TEST(StackTest, IsFull) {
    Stack<int> s(3);
    s.Spush(1);
    s.Spush(2);
    EXPECT_FALSE(s.SisFull());
    s.Spush(3);
    EXPECT_TRUE(s.SisFull());
}

// Тест метода Sdisplay
TEST(StackTest, Display) {
    Stack<int> s(5);
    s.Spush(1);
    s.Spush(2);
    s.Spush(3);
    testing::internal::CaptureStdout();
    s.Sdisplay();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Элементы стека: 3 2 1 \n");
}

// Тест метода SreadFromFile
TEST(StackTest, ReadFromFile) {
    std::ofstream file("test_stack_data.txt");
    file << "1 2 3";
    file.close();

    Stack<int> s(5);
    s.SreadFromFile("test_stack_data.txt");
    EXPECT_EQ(s.Speek(), 3);
    s.Spop();
    EXPECT_EQ(s.Speek(), 2);
    s.Spop();
    EXPECT_EQ(s.Speek(), 1);
}

// Тест метода SwriteToFile
TEST(StackTest, WriteToFile) {
    Stack<int> s(5);
    s.Spush(1);
    s.Spush(2);
    s.Spush(3);
    s.SwriteToFile("test_stack_output.txt");
    
    Stack<int> s2(5);
    s2.SreadFromFile("test_stack_output.txt");
    EXPECT_EQ(s2.Speek(), 3);
    s2.Spop();
    EXPECT_EQ(s2.Speek(), 2);
    s2.Spop();
    EXPECT_EQ(s2.Speek(), 1);
}

// Тест на обработку исключений
TEST(StackTest, ExceptionHandling) {
    Stack<int> s(3);
    EXPECT_THROW(s.Speek(), std::runtime_error);
    s.Spush(1);
    s.Spush(2);
    s.Spush(3);
    EXPECT_THROW(s.Spush(4), std::runtime_error);
    s.Spop();
    s.Spop();
    s.Spop();
    EXPECT_THROW(s.Spop(), std::runtime_error);
}

// Тест на граничные условия
TEST(StackTest, BoundaryConditions) {
    Stack<int> s(1);
    EXPECT_TRUE(s.SisEmpty());
    EXPECT_FALSE(s.SisFull());
    s.Spush(1);
    EXPECT_TRUE(s.SisFull());
    EXPECT_FALSE(s.SisEmpty());
    s.Spop();
    EXPECT_TRUE(s.SisEmpty());
    EXPECT_FALSE(s.SisFull());
}

// Тест на пустой файл
TEST(StackTest, EmptyFile) {
    std::ofstream file("empty_file.txt");
    file.close();

    Stack<int> s(5);
    s.SreadFromFile("empty_file.txt");
    EXPECT_TRUE(s.SisEmpty());
}

// Тест на файл с одним элементом
TEST(StackTest, SingleElementFile) {
    std::ofstream file("single_element.txt");
    file << "42";
    file.close();

    Stack<int> s(5);
    s.SreadFromFile("single_element.txt");
    EXPECT_EQ(s.Speek(), 42);
}

// Тест на переполнение стека при чтении из файла
TEST(StackTest, OverflowOnRead) {
    std::ofstream file("overflow_file.txt");
    file << "1 2 3 4 5 6";
    file.close();

    Stack<int> s(5);
    EXPECT_THROW(s.SreadFromFile("overflow_file.txt"), std::runtime_error);
}

// Тест на запись в файл, когда стек пуст
TEST(StackTest, WriteToFileEmptyStack) {
    Stack<int> s(5);
    testing::internal::CaptureStdout();
    s.SwriteToFile("empty_stack_output.txt");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Стек пуст, ничего не записано.\n");

    // Проверка, что файл пустой
    std::ifstream file("empty_stack_output.txt");
    EXPECT_FALSE(file.is_open());
}

// Тест на обработку ошибки при открытии файла для записи
TEST(StackTest, WriteToFileOpenError) {
    Stack<int> s(5);
    s.Spush(1);
    s.Spush(2);
    s.Spush(3);
    EXPECT_THROW(s.SwriteToFile(""), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}