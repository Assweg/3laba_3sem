#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

// Константа для определения размера таблицы
const int TABLE_SIZE = 10;

// Структура для представления узла в хеш-таблице
struct NodeH {
    string key;     // Ключ узла
    string value;   // Значение узла
    NodeH* next;    // Указатель на следующий узел (для цепочечного разрешения коллизий)

    // Конструктор для инициализации узла с заданным ключом и значением
    NodeH(const string &k, const string &v) : key(k), value(v), next(nullptr) {}
};

// Класс для реализации хеш-таблицы
class HashTable {
public:
    // Конструктор хеш-таблицы
    HashTable();
    
    // Деструктор хеш-таблицы для очистки ресурсов
    ~HashTable();
    
    void Hinsert(const string &key, const string &value);   // Метод для добавления или обновления элемента в хеш-таблице
    bool Hget(const string &key, string &value);    // Метод для получения значения по ключу
    bool Hdel(const string &key);   // Метод для удаления элемента по ключу
    void Hprint() const;    // Метод для отображения всех элементов в хеш-таблице
    void HreadFromFile(const std::string &filename);
    void HwriteToFile(const std::string &filename) const;

    void saveToBinaryFile(const string& filename) const;
    void loadFromBinaryFile(const string& filename);

private:
    // Хеш-функция для получения индекса по ключу
    size_t hash(const string &key) const;

    // Массив указателей на узлы для представления хеш-таблицы
    NodeH* table[TABLE_SIZE];
};

// Конструктор хеш-таблицы
HashTable::HashTable() {
    // Инициализируем каждый элемент массива таблицы указателем NULL
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

// Деструктор хеш-таблицы
HashTable::~HashTable() {
    // Освобождаем память, выделенную для каждого узла в таблице
    for (int i = 0; i < TABLE_SIZE; ++i) { 
        NodeH* current = table[i]; // Указатель на текущий узел
        while (current) {
            NodeH* temp = current; // Временный указатель на удаляемый узел
            current = current->next; // Переходим на следующий узел
            delete temp; // Удаляем текущий узел
        }
    }
}

// Хеш-функция для получения индекса в таблице по ключу
size_t HashTable::hash(const string &key) const {
    size_t hashValue = 0; // Начальное значение хеша
    for (char ch : key) {
        // Применяем простой алгоритм хеширования
        hashValue = (hashValue * 31 + ch) % TABLE_SIZE;
    }
    return hashValue; // Возвращаем рассчитанный индекс
}

// Функция для добавления или обновления элемента в хеш-таблице
void HashTable::Hinsert(const string &key, const string &value) {
    size_t index = hash(key); // Вычисляем индекс для данного ключа
    NodeH* newNode = new NodeH(key, value); // Создаем новый узел

    // Если в таблице нет узла по этому индексу, добавляем новый узел
    if (!table[index]) {
        table[index] = newNode;
    } else {
        NodeH* current = table[index]; // Начинаем с первого узла в цепочке
        while (current->next) {
            // Проверяем, существует ли уже ключ
            if (current->key == key) {
                current->value = value; // Обновляем значение
                delete newNode; // Избегаем утечки памяти
                return; // Завершаем выполнение функции
            }
            current = current->next; // Переходим к следующему узлу
        }
        // Проверяем последний узел (если у нас несколько узлов в цепочке)
        if (current->key == key) {
            current->value = value; // Обновляем значение
            delete newNode;         // Избегаем утечки памяти
        } else {
            current->next = newNode;  // Добавляем новый узел в конец цепочки
        }
    }
}

// Функция для получения значения по ключу
bool HashTable::Hget(const string &key, string &value) {
    size_t index = hash(key); // Вычисляем индекс для данного ключа
    NodeH* current = table[index]; // Начинаем с первого узла в цепочке
    while (current) {
        // Проверяем, совпадает ли ключ
        if (current->key == key) {
            value = current->value; // Возвращаем значение
            return true; // Успешно найдено
        }
        current = current->next; // Переходим к следующему узлу
    }
    return false; // Ключ не найден
}

// Функция для удаления элемента по ключу
bool HashTable::Hdel(const string &key) {
    size_t index = hash(key); // Вычисляем индекс для данного ключа
    NodeH* current = table[index]; // Начинаем с первого узла
    NodeH* previous = nullptr; // Предыдущий узел для отслеживания ссылок

    while (current) {
        // Проверяем, совпадает ли ключ
        if (current->key == key) {
            if (previous) {
                previous->next = current->next; // Удаляем узел, если он не первый
            } else {
                table[index] = current->next; // Удаляем первый узел (голову)
            }
            delete current; // Освобождаем память
            return true; // Успешно удалено
        }
        previous = current; // Обновляем предыдущий узел
        current = current->next; // Переходим к следующему узлу
    }
    return false; // Ключ не найден
}

// Функция для отображения всех элементов таблицы
void HashTable::Hprint() const {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        cout << i << ": "; // Печатаем индекс
        NodeH* current = table[i]; // Указатель на текущий узел
        while (current) {
            cout << "{" << current->key << ": " << current->value << "} "; // Печатаем ключ-значение
            current = current->next; // Переходим к следующему узлу
        }
        cout << endl; // Переходим на новую строку
    }
}

// Функция для считывания хеш-таблицы из файла
void HashTable::HreadFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл для чтения.");
    }

    string key, value;
    while (file >> key >> value) {
        Hinsert(key, value); // Вставляем каждую пару (ключ, значение) в хеш-таблицу
    }

    file.close(); // Закрываем файл
}

// Функция для записи хеш-таблицы в файл
void HashTable::HwriteToFile(const string &filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл для записи.");
    }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        NodeH* current = table[i];
        while (current) {
            file << current->key << " " << current->value << endl; // Записываем пары ключ-значение
            current = current->next; // Переходим к следующему узлу
        }
    }

    file.close(); // Закрываем файл
}

// Метод для записи хеш-таблицы в бинарный файл
void HashTable::saveToBinaryFile(const string& filename) const {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        throw runtime_error("Не удалось открыть файл для записи.");
    }

    // Записываем количество элементов в хеш-таблице
    int elementCount = 0;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        NodeH* current = table[i];
        while (current) {
            ++elementCount;
            current = current->next;
        }
    }
    outFile.write(reinterpret_cast<const char*>(&elementCount), sizeof(elementCount));

    // Записываем каждую пару ключ-значение
    for (int i = 0; i < TABLE_SIZE; ++i) {
        NodeH* current = table[i];
        while (current) {
            // Записываем длину ключа и значение
            int keyLength = current->key.length();
            int valueLength = current->value.length();
            outFile.write(reinterpret_cast<const char*>(&keyLength), sizeof(keyLength));
            outFile.write(reinterpret_cast<const char*>(&valueLength), sizeof(valueLength));

            // Записываем ключ и значение
            outFile.write(current->key.c_str(), keyLength);
            outFile.write(current->value.c_str(), valueLength);

            current = current->next;
        }
    }

    outFile.close();
}

// Метод для чтения хеш-таблицы из бинарного файла
void HashTable::loadFromBinaryFile(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        throw runtime_error("Не удалось открыть файл для чтения.");
    }

    // Очищаем текущую хеш-таблицу
    for (int i = 0; i < TABLE_SIZE; ++i) {
        NodeH* current = table[i];
        while (current) {
            NodeH* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }

    // Читаем количество элементов в хеш-таблице
    int elementCount;
    inFile.read(reinterpret_cast<char*>(&elementCount), sizeof(elementCount));

    // Читаем каждую пару ключ-значение
    for (int i = 0; i < elementCount; ++i) {
        int keyLength, valueLength;
        inFile.read(reinterpret_cast<char*>(&keyLength), sizeof(keyLength));
        inFile.read(reinterpret_cast<char*>(&valueLength), sizeof(valueLength));

        string key(keyLength, ' ');
        string value(valueLength, ' ');
        inFile.read(&key[0], keyLength);
        inFile.read(&value[0], valueLength);

        Hinsert(key, value); // Вставляем пару ключ-значение в хеш-таблицу
    }

    inFile.close();
}

#endif // HASHTABLE_H