#include "../include/HashTable.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <fstream>

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

// Тест на обновление значения по существующему ключу
TEST(HashTableTest, UpdateExistingKey) {
    HashTable ht;
    ht.Hinsert("key1", "value1");
    ht.Hinsert("key1", "newValue1");

    string value;
    EXPECT_TRUE(ht.Hget("key1", value));
    EXPECT_EQ(value, "newValue1");
}

// Тест на удаление несуществующего ключа
TEST(HashTableTest, DeleteNonExistentKey) {
    HashTable ht;
    EXPECT_FALSE(ht.Hdel("nonExistentKey"));
}

// Тест на получение значения несуществующего ключа
TEST(HashTableTest, GetNonExistentKey) {
    HashTable ht;
    string value;
    EXPECT_FALSE(ht.Hget("nonExistentKey", value));
}

// Тест на запись пустой таблицы в файл
TEST(HashTableTest, WriteEmptyTableToFile) {
    HashTable ht;
    ht.HwriteToFile("test_hashtable_output.txt");

    ifstream file("test_hashtable_output.txt");
    EXPECT_FALSE(file.peek() != ifstream::traits_type::eof());
    file.close();
}

// Тест на чтение из пустого файла
TEST(HashTableTest, ReadFromEmptyFile) {
    ofstream file("test_hashtable_data.txt");
    file.close();

    HashTable ht;
    ht.HreadFromFile("test_hashtable_data.txt");

    string value;
    EXPECT_FALSE(ht.Hget("key1", value));
}

// Тест на коллизии
TEST(HashTableTest, CollisionHandling) {
    HashTable ht;
    ht.Hinsert("key1", "value1");
    ht.Hinsert("key11", "value11"); // Предположим, что key1 и key11 имеют одинаковый хеш

    string value;
    EXPECT_TRUE(ht.Hget("key1", value));
    EXPECT_EQ(value, "value1");
    EXPECT_TRUE(ht.Hget("key11", value));
    EXPECT_EQ(value, "value11");
}

// Тест на удаление элемента из цепочки коллизий
TEST(HashTableTest, DeleteFromCollisionChain) {
    HashTable ht;
    ht.Hinsert("key1", "value1");
    ht.Hinsert("key11", "value11"); // Предположим, что key1 и key11 имеют одинаковый хеш

    EXPECT_TRUE(ht.Hdel("key11"));
    string value;
    EXPECT_TRUE(ht.Hget("key1", value));
    EXPECT_EQ(value, "value1");
    EXPECT_FALSE(ht.Hget("key11", value));
}

// Тест на вставку большого количества элементов
TEST(HashTableTest, InsertManyElements) {
    HashTable ht;
    for (int i = 0; i < 100; ++i) {
        ht.Hinsert("key" + to_string(i), "value" + to_string(i));
    }

    string value;
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(ht.Hget("key" + to_string(i), value));
        EXPECT_EQ(value, "value" + to_string(i));
    }
}

// Тест на удаление всех элементов
TEST(HashTableTest, DeleteAllElements) {
    HashTable ht;
    for (int i = 0; i < 100; ++i) {
        ht.Hinsert("key" + to_string(i), "value" + to_string(i));
    }

    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(ht.Hdel("key" + to_string(i)));
    }

    string value;
    for (int i = 0; i < 100; ++i) {
        EXPECT_FALSE(ht.Hget("key" + to_string(i), value));
    }
}

// Тест на вставку и удаление элементов в цикле
TEST(HashTableTest, InsertDeleteCycle) {
    HashTable ht;
    for (int i = 0; i < 100; ++i) {
        ht.Hinsert("key" + to_string(i), "value" + to_string(i));
    }

    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(ht.Hdel("key" + to_string(i)));
    }

    for (int i = 0; i < 100; ++i) {
        ht.Hinsert("key" + to_string(i), "value" + to_string(i));
    }

    string value;
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(ht.Hget("key" + to_string(i), value));
        EXPECT_EQ(value, "value" + to_string(i));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}