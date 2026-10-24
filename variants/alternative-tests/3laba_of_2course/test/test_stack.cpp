#include "../src/Stack.h"
#include <gtest/gtest.h>
#include <stdexcept>

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
}

// Тест метода Speek
TEST(StackTest, Peek) {
    Stack<int> s(5);
    s.Spush(1);
    s.Spush(2);
    s.Spush(3);
    EXPECT_EQ(s.Speek(), 3);
}

// Тест метода SisEmpty
TEST(StackTest, IsEmpty) {
    Stack<int> s(5);
    EXPECT_TRUE(s.SisEmpty());
    s.Spush(1);
    EXPECT_FALSE(s.SisEmpty());
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
    Stack<int> s(5);
    s.SreadFromFile("test_stack_data.txt");
    EXPECT_EQ(s.Speek(), 3);
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
}

// Тест на обработку исключений
TEST(StackTest, ExceptionHandling) {
    Stack<int> s(3);
    EXPECT_THROW(s.Speek(), std::runtime_error);
    s.Spush(1);
    s.Spush(2);
    s.Spush(3);
    EXPECT_THROW(s.Spush(4), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}