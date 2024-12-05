#include "LinkedList.h"

int main() {
    LinkedList<string> list;

    // Заполняем список
    list.LpushBack("sister");
    list.LpushBack("dad");
    list.LpushBack("mom");

    // Сохраняем в текстовый файл
    list.writeToFile("Llist.txt");

    // Сохраняем в бинарный файл
    list.saveToBinaryFile("Llist.bin");

    // Очищаем список
    while (list.Lfind("sister") || list.Lfind("dad") || list.Lfind("mom")) {
        list.Ldel("sister");
        list.Ldel("dad");
        list.Ldel("mom");
    }

    // Загружаем из текстового файла
    list.readFromFile("Llist.txt");
    list.Lprint(); // Выводим список

    // Очищаем список
    while (list.Lfind("sister") || list.Lfind("dad") || list.Lfind("mom")) {
        list.Ldel("sister");
        list.Ldel("dad");
        list.Ldel("mom");
    }

    // Загружаем из бинарного файла
    list.loadFromBinaryFile("Llist.bin");
    list.Lprint(); // Выводим список

    return 0;
}