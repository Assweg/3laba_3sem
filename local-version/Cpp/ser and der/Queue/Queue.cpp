#include "Queue.h"

int main() {
    Queue<string> queue(10);

    // Заполняем очередь
    queue.Qpush("brother");
    queue.Qpush("parents");
    queue.Qpush("sister");

    // Сохраняем в текстовый файл
    queue.QwriteToFile("queue.txt");

    // Сохраняем в бинарный файл
    queue.saveToBinaryFile("queue.bin");

    // Очищаем очередь
    while (!queue.QisEmpty()) {
        queue.Qpop();
    }

    // Загружаем из текстового файла
    queue.QreadFromFile("queue.txt");
    queue.Qprint(); // Выводим очередь

    // Очищаем очередь
    while (!queue.QisEmpty()) {
        queue.Qpop();
    }

    // Загружаем из бинарного файла
    queue.loadFromBinaryFile("queue.bin");
    queue.Qprint(); // Выводим очередь

    return 0;
}