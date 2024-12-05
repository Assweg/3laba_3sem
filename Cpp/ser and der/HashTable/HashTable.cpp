#include "HashTable.h"

int main() {
    HashTable ht;

    // Заполняем хеш-таблицу
    ht.Hinsert("key1", "value1");
    ht.Hinsert("key2", "value2");
    ht.Hinsert("key3", "value3");

    // Сохраняем в текстовый файл
    ht.HwriteToFile("hashtable.txt");

    // Сохраняем в бинарный файл
    ht.saveToBinaryFile("hashtable.bin");

    // Очищаем хеш-таблицу
    ht = HashTable();

    // Загружаем из текстового файла
    ht.HreadFromFile("hashtable.txt");
    ht.Hprint(); // Выводим хеш-таблицу
    cout << endl;
    
    // Очищаем хеш-таблицу
    ht = HashTable();

    // Загружаем из бинарного файла
    ht.loadFromBinaryFile("hashtable.bin");
    ht.Hprint(); // Выводим хеш-таблицу

    return 0;
}