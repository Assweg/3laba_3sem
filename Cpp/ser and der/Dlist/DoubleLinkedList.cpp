#include "DoubleLinkedList.h"

int main() {
    DoublyLinkedList<string> list;

    // Заполняем список
    list.LpushBack2("dad");
    list.LpushBack2("mom");
    list.LpushBack2("sister");

    // Сохраняем в текстовый файл
    list.LwriteToFile2("Dlist.txt");

    // Сохраняем в бинарный файл
    list.saveToBinaryFile("Dlist.bin");

    // Очищаем список
    while (list.Lfind2("dad") || list.Lfind2("mom") || list.Lfind2("sister")) {
        list.Ldel2("dad");
        list.Ldel2("mom");
        list.Ldel2("sister");
    }

    // Загружаем из текстового файла
    list.LreadFromFile2("Dlist.txt");
    list.Lprint2(); // Выводим список

    // Очищаем список
    while (list.Lfind2("dad") || list.Lfind2("mom") || list.Lfind2("sister")) {
        list.Ldel2("dad");
        list.Ldel2("mom");
        list.Ldel2("sister");
    }

    // Загружаем из бинарного файла
    list.loadFromBinaryFile("Dlist.bin");
    list.Lprint2(); // Выводим список

    return 0;
}