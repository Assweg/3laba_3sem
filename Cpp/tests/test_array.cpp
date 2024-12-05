#include "../include/Array.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Тест конструктора и деструктора
TEST(ArrayTest, ConstructorAndDestructor) {
    Array<int> arr;
    EXPECT_EQ(arr.mlength(), 0);
}

// Тест метода mpush
TEST(ArrayTest, Push) {
    Array<int> arr;
    arr.mpush(1);
    arr.mpush(2);
    arr.mpush(3);
    EXPECT_EQ(arr.mlength(), 3);
    EXPECT_EQ(arr.mprint(0), 1);
    EXPECT_EQ(arr.mprint(1), 2);
    EXPECT_EQ(arr.mprint(2), 3);
}

// Тест метода minsert
TEST(ArrayTest, Insert) {
    Array<int> arr;
    arr.mpush(1);
    arr.mpush(3);
    arr.minsert(1, 2);
    EXPECT_EQ(arr.mlength(), 3);
    EXPECT_EQ(arr.mprint(0), 1);
    EXPECT_EQ(arr.mprint(1), 2);
    EXPECT_EQ(arr.mprint(2), 3);
}

// Тест метода mdel
TEST(ArrayTest, Delete) {
    Array<int> arr;
    arr.mpush(1);
    arr.mpush(2);
    arr.mpush(3);
    arr.mdel(1);
    EXPECT_EQ(arr.mlength(), 2);
    EXPECT_EQ(arr.mprint(0), 1);
    EXPECT_EQ(arr.mprint(1), 3);
}

// Тест метода mprint
TEST(ArrayTest, Print) {
    Array<int> arr;
    arr.mpush(1);
    arr.mpush(2);
    arr.mpush(3);
    EXPECT_EQ(arr.mprint(0), 1);
    EXPECT_EQ(arr.mprint(1), 2);
    EXPECT_EQ(arr.mprint(2), 3);
}

// Тест метода mreplace
TEST(ArrayTest, Replace) {
    Array<int> arr;
    arr.mpush(1);
    arr.mpush(2);
    arr.mpush(3);
    arr.mreplace(1, 4);
    EXPECT_EQ(arr.mprint(1), 4);
}

// Тест метода mlength
TEST(ArrayTest, Length) {
    Array<int> arr;
    arr.mpush(1);
    arr.mpush(2);
    arr.mpush(3);
    EXPECT_EQ(arr.mlength(), 3);
}

// Тест метода mget
TEST(ArrayTest, Get) {
    Array<int> arr;
    arr.mpush(1);
    arr.mpush(2);
    arr.mpush(3);
    testing::internal::CaptureStdout();
    arr.mget();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1 2 3 \n");
}

// Тест метода loadFromFile
TEST(ArrayTest, LoadFromFile) {
    Array<int> arr;
    arr.loadFromFile("test_data.txt");
    EXPECT_EQ(arr.mlength(), 3);
    EXPECT_EQ(arr.mprint(0), 1);
    EXPECT_EQ(arr.mprint(1), 2);
    EXPECT_EQ(arr.mprint(2), 3);
}

// Тест метода saveToFile
TEST(ArrayTest, SaveToFile) {
    Array<int> arr;
    arr.mpush(1);
    arr.mpush(2);
    arr.mpush(3);
    arr.saveToFile("test_output.txt");
    
    Array<int> arr2;
    arr2.loadFromFile("test_output.txt");
    EXPECT_EQ(arr2.mlength(), 3);
    EXPECT_EQ(arr2.mprint(0), 1);
    EXPECT_EQ(arr2.mprint(1), 2);
    EXPECT_EQ(arr2.mprint(2), 3);
}

// Тест на обработку исключений
TEST(ArrayTest, ExceptionHandling) {
    Array<int> arr;
    EXPECT_THROW(arr.mprint(0), std::out_of_range);
    EXPECT_THROW(arr.minsert(1, 1), std::out_of_range);
    EXPECT_THROW(arr.mdel(0), std::out_of_range);
    EXPECT_THROW(arr.mreplace(0, 1), std::out_of_range);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 