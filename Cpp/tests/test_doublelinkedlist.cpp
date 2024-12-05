#include "../include/DoubleLinkedList.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Тест конструктора и деструктора
TEST(DoublyLinkedListTest, ConstructorAndDestructor) {
    DoublyLinkedList<int> list;
    EXPECT_EQ(list.Lfind2(1), false);
}

// Тест метода LpushFront2
TEST(DoublyLinkedListTest, PushFront) {
    DoublyLinkedList<int> list;
    list.LpushFront2(1);
    list.LpushFront2(2);
    list.LpushFront2(3);
    EXPECT_EQ(list.Lfind2(1), true);
    EXPECT_EQ(list.Lfind2(2), true);
    EXPECT_EQ(list.Lfind2(3), true);
}

// Тест метода LpushBack2
TEST(DoublyLinkedListTest, PushBack) {
    DoublyLinkedList<int> list;
    list.LpushBack2(1);
    list.LpushBack2(2);
    list.LpushBack2(3);
    EXPECT_EQ(list.Lfind2(1), true);
    EXPECT_EQ(list.Lfind2(2), true);
    EXPECT_EQ(list.Lfind2(3), true);
}

// Тест метода LdelFront2
TEST(DoublyLinkedListTest, DelFront) {
    DoublyLinkedList<int> list;
    list.LpushBack2(1);
    list.LpushBack2(2);
    list.LpushBack2(3);
    list.LdelFront2();
    EXPECT_EQ(list.Lfind2(1), false);
    EXPECT_EQ(list.Lfind2(2), true);
    EXPECT_EQ(list.Lfind2(3), true);
}

// Тест метода LdelBack2
TEST(DoublyLinkedListTest, DelBack) {
    DoublyLinkedList<int> list;
    list.LpushBack2(1);
    list.LpushBack2(2);
    list.LpushBack2(3);
    list.LdelBack2();
    EXPECT_EQ(list.Lfind2(1), true);
    EXPECT_EQ(list.Lfind2(2), true);
    EXPECT_EQ(list.Lfind2(3), false);
}

// Тест метода Ldel2
TEST(DoublyLinkedListTest, Del) {
    DoublyLinkedList<int> list;
    list.LpushBack2(1);
    list.LpushBack2(2);
    list.LpushBack2(3);
    list.Ldel2(2);
    EXPECT_EQ(list.Lfind2(1), true);
    EXPECT_EQ(list.Lfind2(2), false);
    EXPECT_EQ(list.Lfind2(3), true);
}

// Тест метода Lfind2
TEST(DoublyLinkedListTest, Find) {
    DoublyLinkedList<int> list;
    list.LpushBack2(1);
    list.LpushBack2(2);
    list.LpushBack2(3);
    EXPECT_EQ(list.Lfind2(1), true);
    EXPECT_EQ(list.Lfind2(2), true);
    EXPECT_EQ(list.Lfind2(3), true);
    EXPECT_EQ(list.Lfind2(4), false);
}

// Тест метода Lprint2
TEST(DoublyLinkedListTest, Print) {
    DoublyLinkedList<int> list;
    list.LpushBack2(1);
    list.LpushBack2(2);
    list.LpushBack2(3);
    testing::internal::CaptureStdout();
    list.Lprint2();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1 2 3 \n");
}

// Тест метода LreadFromFile2
TEST(DoublyLinkedListTest, ReadFromFile) {
    DoublyLinkedList<int> list;
    list.LreadFromFile2("test_list_data.txt");
    EXPECT_EQ(list.Lfind2(1), true);
    EXPECT_EQ(list.Lfind2(2), true);
    EXPECT_EQ(list.Lfind2(3), true);
}

// Тест метода LwriteToFile2
TEST(DoublyLinkedListTest, WriteToFile) {
    DoublyLinkedList<int> list;
    list.LpushBack2(1);
    list.LpushBack2(2);
    list.LpushBack2(3);
    list.LwriteToFile2("test_list_output.txt");
    
    DoublyLinkedList<int> list2;
    list2.LreadFromFile2("test_list_output.txt");
    EXPECT_EQ(list2.Lfind2(1), true);
    EXPECT_EQ(list2.Lfind2(2), true);
    EXPECT_EQ(list2.Lfind2(3), true);
}

// Тест на обработку исключений
TEST(DoublyLinkedListTest, ExceptionHandling) {
    DoublyLinkedList<int> list;
    EXPECT_THROW(list.LdelFront2(), std::runtime_error);
    EXPECT_THROW(list.LdelBack2(), std::runtime_error);
    EXPECT_THROW(list.Ldel2(1), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}