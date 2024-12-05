#include "../include/LinkedList.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Тест конструктора и деструктора
TEST(LinkedListTest, ConstructorAndDestructor) {
    LinkedList<int> list;
    EXPECT_EQ(list.Lfind(1), false);
}

// Тест метода LpushFront
TEST(LinkedListTest, PushFront) {
    LinkedList<int> list;
    list.LpushFront(1);
    list.LpushFront(2);
    list.LpushFront(3);
    EXPECT_EQ(list.Lfind(1), true);
    EXPECT_EQ(list.Lfind(2), true);
    EXPECT_EQ(list.Lfind(3), true);
}

// Тест метода LpushBack
TEST(LinkedListTest, PushBack) {
    LinkedList<int> list;
    list.LpushBack(1);
    list.LpushBack(2);
    list.LpushBack(3);
    EXPECT_EQ(list.Lfind(1), true);
    EXPECT_EQ(list.Lfind(2), true);
    EXPECT_EQ(list.Lfind(3), true);
}

// Тест метода LdelFront
TEST(LinkedListTest, DelFront) {
    LinkedList<int> list;
    list.LpushBack(1);
    list.LpushBack(2);
    list.LpushBack(3);
    list.LdelFront();
    EXPECT_EQ(list.Lfind(1), false);
    EXPECT_EQ(list.Lfind(2), true);
    EXPECT_EQ(list.Lfind(3), true);
}

// Тест метода LdelBack
TEST(LinkedListTest, DelBack) {
    LinkedList<int> list;
    list.LpushBack(1);
    list.LpushBack(2);
    list.LpushBack(3);
    list.LdelBack();
    EXPECT_EQ(list.Lfind(1), true);
    EXPECT_EQ(list.Lfind(2), true);
    EXPECT_EQ(list.Lfind(3), false);
}

// Тест метода Ldel
TEST(LinkedListTest, Del) {
    LinkedList<int> list;
    list.LpushBack(1);
    list.LpushBack(2);
    list.LpushBack(3);
    list.Ldel(2);
    EXPECT_EQ(list.Lfind(1), true);
    EXPECT_EQ(list.Lfind(2), false);
    EXPECT_EQ(list.Lfind(3), true);
}

// Тест метода Lfind
TEST(LinkedListTest, Find) {
    LinkedList<int> list;
    list.LpushBack(1);
    list.LpushBack(2);
    list.LpushBack(3);
    EXPECT_EQ(list.Lfind(1), true);
    EXPECT_EQ(list.Lfind(2), true);
    EXPECT_EQ(list.Lfind(3), true);
    EXPECT_EQ(list.Lfind(4), false);
}

// Тест метода Lprint
TEST(LinkedListTest, Print) {
    LinkedList<int> list;
    list.LpushBack(1);
    list.LpushBack(2);
    list.LpushBack(3);
    testing::internal::CaptureStdout();
    list.Lprint();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1 2 3 \n");
}

// Тест метода readFromFile
TEST(LinkedListTest, ReadFromFile) {
    LinkedList<int> list;
    list.readFromFile("test_list_data.txt");
    EXPECT_EQ(list.Lfind(1), true);
    EXPECT_EQ(list.Lfind(2), true);
    EXPECT_EQ(list.Lfind(3), true);
}

// Тест метода writeToFile
TEST(LinkedListTest, WriteToFile) {
    LinkedList<int> list;
    list.LpushBack(1);
    list.LpushBack(2);
    list.LpushBack(3);
    list.writeToFile("test_list_output.txt");
    
    LinkedList<int> list2;
    list2.readFromFile("test_list_output.txt");
    EXPECT_EQ(list2.Lfind(1), true);
    EXPECT_EQ(list2.Lfind(2), true);
    EXPECT_EQ(list2.Lfind(3), true);
}

// Тест на обработку исключений
TEST(LinkedListTest, ExceptionHandling) {
    LinkedList<int> list;
    EXPECT_THROW(list.LdelFront(), std::runtime_error);
    EXPECT_THROW(list.LdelBack(), std::runtime_error);
    EXPECT_THROW(list.Ldel(1), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}