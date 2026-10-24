#ifndef ARRAY_H
#define ARRAY_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Array {
private:
    T* data;           // Указатель на массив
    int size;          // Текущий размер массива
    int capacity;      // Вместимость массива

    void resize();     // Метод для изменения размера массива

public:
    Array();           // Конструктор
    ~Array();          // Деструктор

    void mpush(const T& element);                // Добавление элемента в конец
    void minsert(int index, const T& element);   // Добавление элемента по индексу
    void mdel(int index);                        // Удаление элемента по индексу
    T mprint(int index) const;                   // Получение элемента по индексу
    void mreplace(int index, const T& element);  // Замена элемента по индексу
    int mlength() const;                         // Узнать длину массива
    void mget() const;                           // Чтение массива

    void loadFromFile(const std::string& filename); // Считывание массива из файла
    void saveToFile(const std::string& filename) const; // Запись массива в файл
};

// Конструктор класса Array
template <typename T>
Array<T>::Array() : size(0), capacity(10) {
    data = new T[capacity]; // Выделяем память для массива с начальной вместимостью 10.
}

// Деструктор класса Array
template <typename T>
Array<T>::~Array() {
    delete[] data; // Освобождаем память, выделенную для массива
}

// Метод для изменения размера массива
template <typename T>
void Array<T>::resize() {
    capacity *= 2; // Удваиваем текущую вместимость
    T* newData = new T[capacity]; // Создаем новый массив с увеличенной вместимостью
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i]; // Копируем старые данные в новый массив
    }
    delete[] data; // Освобождаем старый массив
    data = newData; // Перенаправляем указатель на новый массив
}

// Метод добавления элемента в конец массива
template <typename T>
void Array<T>::mpush(const T& element) {
    if (size == capacity) { // Проверяем, нужно ли увеличивать размер массива
        resize();
    }
    data[size++] = element; // Добавляем элемент и увеличиваем размер
}

// Метод вставки элемента по указанному индексу
template <typename T>
void Array<T>::minsert(int index, const T& element) {
    if (index < 0 || index > size) {
        throw out_of_range("Index out of range"); // Проверяем, находится ли индекс в допустимых пределах
    }
    if (size == capacity) {
        resize();
    }
    for (int i = size; i > index; --i) {
        data[i] = data[i - 1]; // Сдвигаем элементы вправо, чтобы освободить место для нового элемента
    }
    data[index] = element; // Вставляем новый элемент по заданному индексу
    size++; // Увеличиваем размер массива
}

// Метод удаления элемента по указанному индексу
template <typename T>
void Array<T>::mdel(int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range"); // Проверяем, находится ли индекс в допустимых пределах
    }
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1]; // Сдвигаем элементы влево, чтобы удалить элемент
    }
    size--; // Уменьшаем размер массива
}

// Метод для получения элемента по индексу
template <typename T>
T Array<T>::mprint(int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range"); // Проверяем, находится ли индекс в допустимых пределах
    }
    return data[index]; // Возвращаем элемент по индексу
}

// Метод замены элемента по указанному индексу
template <typename T>
void Array<T>::mreplace(int index, const T& element) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range"); // Проверяем, находится ли индекс в допустимых пределах
    }
    data[index] = element; // Заменяем элемент по индексу
}

// Метод получения текущего размера массива
template <typename T>
int Array<T>::mlength() const {
    return size;
}

// Метод для печати содержимого массива
template <typename T>
void Array<T>::mget() const {
    for (int i = 0; i < size; ++i) {
        cout << data[i] << " "; // Выводим каждый элемент массива
    }
    cout << endl;
}

// Метод для считывания массива из файла
template <typename T>
void Array<T>::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        throw runtime_error("Unable to open file for reading");
    }
    
    T value;
    while (inFile >> value) {
        mpush(value); // Добавляем элементы в массив
    }
    inFile.close(); // Закрываем файл
}

// Метод для записи массива в файл
template <typename T>
void Array<T>::saveToFile(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        throw runtime_error("Unable to open file for writing");
    }
    
    for (int i = 0; i < size; ++i) {
        outFile << data[i] << " "; // Записываем каждый элемент массива в файл
    }
    outFile.close(); // Закрываем файл
}

#endif