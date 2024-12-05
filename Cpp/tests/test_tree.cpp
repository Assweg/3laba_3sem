#include "../include/Tree.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Тест конструктора и деструктора
TEST(CompleteBinaryTreeTest, ConstructorAndDestructor) {
    CompleteBinaryTree<int> tree(10);
    EXPECT_EQ(tree.TisComplete(), true);
}

// Тест метода Tinsert
TEST(CompleteBinaryTreeTest, Insert) {
    CompleteBinaryTree<int> tree(10);
    tree.Tinsert(1);
    tree.Tinsert(2);
    tree.Tinsert(3);
    EXPECT_EQ(tree.Tsearch(1), true);
    EXPECT_EQ(tree.Tsearch(2), true);
    EXPECT_EQ(tree.Tsearch(3), true);
}

// Тест метода Tsearch
TEST(CompleteBinaryTreeTest, Search) {
    CompleteBinaryTree<int> tree(10);
    tree.Tinsert(1);
    tree.Tinsert(2);
    tree.Tinsert(3);
    EXPECT_EQ(tree.Tsearch(1), true);
    EXPECT_EQ(tree.Tsearch(2), true);
    EXPECT_EQ(tree.Tsearch(3), true);
    EXPECT_EQ(tree.Tsearch(4), false);
}

// Тест метода TisComplete
TEST(CompleteBinaryTreeTest, IsComplete) {
    CompleteBinaryTree<int> tree(10);
    tree.Tinsert(1);
    tree.Tinsert(2);
    tree.Tinsert(3);
    EXPECT_EQ(tree.TisComplete(), true);
}

// Тест метода Tprint
TEST(CompleteBinaryTreeTest, Print) {
    CompleteBinaryTree<int> tree(10);
    tree.Tinsert(1);
    tree.Tinsert(2);
    tree.Tinsert(3);
    testing::internal::CaptureStdout();
    tree.Tprint();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

// Тест метода TreadFromFile с несуществующим файлом
TEST(CompleteBinaryTreeTest, ReadFromFile_FileNotFound) {
    CompleteBinaryTree<int> tree(10);
    testing::internal::CaptureStdout();
    tree.TreadFromFile("non_existent_file.txt");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Не удалось открыть файл для чтения!"), std::string::npos);
}

// Тест метода TwriteToFile с невозможностью записи
TEST(CompleteBinaryTreeTest, WriteToFile_FileNotWritable) {
    CompleteBinaryTree<int> tree(10);
    tree.Tinsert(1);
    tree.Tinsert(2);
    tree.Tinsert(3);
    testing::internal::CaptureStdout();
    tree.TwriteToFile("/root/test_tree_output.txt"); // Предположим, что у нас нет прав на запись в /root
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Не удалось открыть файл для записи!"), std::string::npos);
}

// Тест метода TreadFromFile
TEST(CompleteBinaryTreeTest, ReadFromFile) {
    CompleteBinaryTree<int> tree(10);
    tree.TreadFromFile("test_tree_data.txt");
    EXPECT_EQ(tree.Tsearch(1), true);
    EXPECT_EQ(tree.Tsearch(2), true);
    EXPECT_EQ(tree.Tsearch(3), true);
}

// Тест метода TwriteToFile
TEST(CompleteBinaryTreeTest, WriteToFile) {
    CompleteBinaryTree<int> tree(10);
    tree.Tinsert(1);
    tree.Tinsert(2);
    tree.Tinsert(3);
    tree.TwriteToFile("test_tree_output.txt");
    
    CompleteBinaryTree<int> tree2(10);
    tree2.TreadFromFile("test_tree_output.txt");
    EXPECT_EQ(tree2.Tsearch(1), true);
    EXPECT_EQ(tree2.Tsearch(2), true);
    EXPECT_EQ(tree2.Tsearch(3), true);
}

// Тест на обработку исключений
TEST(CompleteBinaryTreeTest, ExceptionHandling) {
    CompleteBinaryTree<int> tree(3);
    tree.Tinsert(1);
    tree.Tinsert(2);
    tree.Tinsert(3);
    EXPECT_THROW(tree.Tinsert(4), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}