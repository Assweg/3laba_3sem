#include "../include/Queue.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <fstream>

// Тест конструктора и деструктора
TEST(QueueTest, ConstructorAndDestructor) {
    Queue<int> q(5);
    EXPECT_TRUE(q.QisEmpty());
}

// Тест метода Qpush
TEST(QueueTest, Push) {
    Queue<int> q(5);
    q.Qpush(1);
    q.Qpush(2);
    q.Qpush(3);
    EXPECT_EQ(q.Qpeek(), 1);
}

// Тест метода Qpop
TEST(QueueTest, Pop) {
    Queue<int> q(5);
    q.Qpush(1);
    q.Qpush(2);
    q.Qpush(3);
    q.Qpop();
    EXPECT_EQ(q.Qpeek(), 2);
}

// Тест метода Qpeek
TEST(QueueTest, Peek) {
    Queue<int> q(5);
    q.Qpush(1);
    q.Qpush(2);
    q.Qpush(3);
    EXPECT_EQ(q.Qpeek(), 1);
}

// Тест метода QisEmpty
TEST(QueueTest, IsEmpty) {
    Queue<int> q(5);
    EXPECT_TRUE(q.QisEmpty());
    q.Qpush(1);
    EXPECT_FALSE(q.QisEmpty());
}

// Тест метода QisFull
TEST(QueueTest, IsFull) {
    Queue<int> q(3);
    q.Qpush(1);
    q.Qpush(2);
    EXPECT_FALSE(q.QisFull());
    q.Qpush(3);
    EXPECT_TRUE(q.QisFull());
}

// Тест метода Qprint
TEST(QueueTest, Print) {
    Queue<int> q(5);
    q.Qpush(1);
    q.Qpush(2);
    q.Qpush(3);
    testing::internal::CaptureStdout();
    q.Qprint();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Элементы очереди: 1 2 3 \n");
}

// Тест метода QreadFromFile
TEST(QueueTest, ReadFromFile) {
    Queue<int> q(5);
    q.QreadFromFile("test_queue_data.txt");
    EXPECT_EQ(q.Qpeek(), 1);
}

// Тест метода QwriteToFile
TEST(QueueTest, WriteToFile) {
    Queue<int> q(5);
    q.Qpush(1);
    q.Qpush(2);
    q.Qpush(3);
    q.QwriteToFile("test_queue_output.txt");
    
    Queue<int> q2(5);
    q2.QreadFromFile("test_queue_output.txt");
    EXPECT_EQ(q2.Qpeek(), 1);
}

// Тест на обработку исключений
TEST(QueueTest, ExceptionHandling) {
    Queue<int> q(3);
    EXPECT_THROW(q.Qpeek(), std::runtime_error);
    q.Qpush(1);
    q.Qpush(2);
    q.Qpush(3);
    EXPECT_THROW(q.Qpush(4), std::runtime_error);
}

// Тест на переполнение очереди
TEST(QueueTest, Overflow) {
    Queue<int> q(3);
    q.Qpush(1);
    q.Qpush(2);
    q.Qpush(3);
    testing::internal::CaptureStdout();
    q.Qpush(4);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Очередь переполнена!\n");
}

// Тест на пустую очередь
TEST(QueueTest, EmptyQueue) {
    Queue<int> q(3);
    testing::internal::CaptureStdout();
    q.Qpop();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Очередь пуста!\n");
}

// Тест на чтение из несуществующего файла
TEST(QueueTest, ReadFromNonExistentFile) {
    Queue<int> q(5);
    EXPECT_THROW(q.QreadFromFile("non_existent_file.txt"), std::runtime_error);
}

// Тест на запись в несуществующий файл
TEST(QueueTest, WriteToNonExistentFile) {
    Queue<int> q(5);
    q.Qpush(1);
    q.Qpush(2);
    q.Qpush(3);
    EXPECT_THROW(q.QwriteToFile("non_existent_directory/output.txt"), std::runtime_error);
}

// Тест на циклическое поведение очереди
TEST(QueueTest, CircularBehavior) {
    Queue<int> q(3);
    q.Qpush(1);
    q.Qpush(2);
    q.Qpush(3);
    q.Qpop();
    q.Qpush(4);
    EXPECT_EQ(q.Qpeek(), 2);
}

// Тест на пустую очередь при записи в файл
TEST(QueueTest, WriteEmptyQueueToFile) {
    Queue<int> q(5);
    testing::internal::CaptureStdout();
    q.QwriteToFile("test_queue_output.txt");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Очередь пуста, ничего не записано.\n");
}

// Тест на переполнение очереди при чтении из файла
TEST(QueueTest, ReadOverflowFromFile) {
    Queue<int> q(3);
    std::ofstream file("test_queue_data.txt");
    file << "1 2 3 4";
    file.close();
    EXPECT_THROW(q.QreadFromFile("test_queue_data.txt"), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}