#include "Array.h"

int main() {
    Array<string> arr;

    // Заполняем массив
    arr.mpush("mom");
    arr.mpush("dad");
    arr.mpush("sister");

    // Сохраняем в текстовый файл
    arr.saveToFile("array.txt");

    // Сохраняем в бинарный файл
    arr.saveToBinaryFile("array.bin");

    // Очищаем массив
    arr.clear();

    // Загружаем из текстового файла
    arr.loadFromFile("array.txt");
    arr.mget(); // Выводим массив

    // Очищаем массив
    arr.clear();

    // Загружаем из бинарного файла
    arr.loadFromBinaryFile("array.bin");
    arr.mget(); // Выводим массив

    return 0;
}