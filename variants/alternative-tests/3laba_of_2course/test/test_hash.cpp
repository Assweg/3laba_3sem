#include "../src/hash.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Тест конструктора и деструктора
TEST(HashTableTest, ConstructorAndDestructor) {
    HashTable ht;
    // Проверка на отсутствие ошибок при создании и удалении таблицы
}

// Тест метода Hinsert
TEST(HashTableTest, Insert) {
    HashTable ht;
    ht.Hinsert("key1", "value1");
    ht.Hinsert("key2", "value2");
    ht.Hinsert("key3", "value3");

    string value;
    EXPECT_TRUE(ht.Hget("key1", value));
    EXPECT_EQ(value, "value1");
    EXPECT_TRUE(ht.Hget("key2", value));
    EXPECT_EQ(value, "value2");
    EXPECT_TRUE(ht.Hget("key3", value));
    EXPECT_EQ(value, "value3");
}

// Тест метода Hget
TEST(HashTableTest, Get) {
    HashTable ht;
    ht.Hinsert("key1", "value1");
    ht.Hinsert("key2", "value2");

    string value;
    EXPECT_TRUE(ht.Hget("key1", value));
    EXPECT_EQ(value, "value1");
    EXPECT_TRUE(ht.Hget("key2", value));
    EXPECT_EQ(value, "value2");
    EXPECT_FALSE(ht.Hget("key3", value));
}

// Тест метода Hdel
TEST(HashTableTest, Delete) {
    HashTable ht;
    ht.Hinsert("key1", "value1");
    ht.Hinsert("key2", "value2");

    EXPECT_TRUE(ht.Hdel("key1"));
    string value;
    EXPECT_FALSE(ht.Hget("key1", value));
    EXPECT_TRUE(ht.Hget("key2", value));
    EXPECT_EQ(value, "value2");
}

// Тест метода Hprint
TEST(HashTableTest, Print) {
    HashTable ht;
    ht.Hinsert("key1", "value1");
    ht.Hinsert("key2", "value2");

    testing::internal::CaptureStdout();
    ht.Hprint();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("key1: value1"), std::string::npos);
    EXPECT_NE(output.find("key2: value2"), std::string::npos);
}

// Тест метода HreadFromFile
TEST(HashTableTest, ReadFromFile) {
    HashTable ht;
    ht.HreadFromFile("test_hashtable_data.txt");

    string value;
    EXPECT_TRUE(ht.Hget("key1", value));
    EXPECT_EQ(value, "value1");
    EXPECT_TRUE(ht.Hget("key2", value));
    EXPECT_EQ(value, "value2");
}

// Тест метода HwriteToFile
TEST(HashTableTest, WriteToFile) {
    HashTable ht;
    ht.Hinsert("key1", "value1");
    ht.Hinsert("key2", "value2");
    ht.HwriteToFile("test_hashtable_output.txt");

    HashTable ht2;
    ht2.HreadFromFile("test_hashtable_output.txt");

    string value;
    EXPECT_TRUE(ht2.Hget("key1", value));
    EXPECT_EQ(value, "value1");
    EXPECT_TRUE(ht2.Hget("key2", value));
    EXPECT_EQ(value, "value2");
}

// Тест на обработку исключений
TEST(HashTableTest, ExceptionHandling) {
    HashTable ht;
    EXPECT_THROW(ht.HreadFromFile("non_existent_file.txt"), std::runtime_error);
    EXPECT_THROW(ht.HwriteToFile("non_existent_directory/file.txt"), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}