#ifndef STACK_H
#define STACK_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Stack {
private:
    T* arr;       // Массив для хранения элементов стека
    int top;      // Индекс верхнего элемента
    int maxSize;  // Максимальный размер стека

public:
    Stack(int size);
    ~Stack();

    void Spush(const T& value);
    void Spop();
    T Speek() const;
    bool SisEmpty() const;
    bool SisFull() const;
    void Sdisplay() const;
    void SreadFromFile(const string& filename);
    void SwriteToFile(const string& filename) const;
};

// Конструктор
template <typename T>
Stack<T>::Stack(int size) : top(-1), maxSize(size) {
    arr = new T[maxSize]; // Выделение памяти для массива
}

// Деструктор
template <typename T>
Stack<T>::~Stack() {
    delete[] arr; // Освобождение памяти
}

// Добавление элемента
template <typename T>
void Stack<T>::Spush(const T& value) {
    if (SisFull()) {
        cout << "Стек переполнен!" << endl;
        return;
    }
    arr[++top] = value; // Увеличение индекса и добавление элемента
}

// Удаление элемента
template <typename T>
void Stack<T>::Spop() {
    if (SisEmpty()) {
        cout << "Стек пуст!" << endl;
        return;
    }
    --top; // Уменьшение индекса верхнего элемента
}

// Чтение элемента
template <typename T>
T Stack<T>::Speek() const {
    if (SisEmpty()) {
        throw runtime_error("Стек пуст!");
    }
    return arr[top]; // Возврат верхнего элемента
}

// Проверка на пустоту
template <typename T>
bool Stack<T>::SisEmpty() const {
    return top == -1; // Если индекс верхнего элемента -1, стек пуст
}

// Проверка на заполненность
template <typename T>
bool Stack<T>::SisFull() const {
    return top == maxSize - 1; // Если индекс верхнего элемента равен maxSize - 1, стек полный
}

// Метод для вывода элементов стека
template <typename T>
void Stack<T>::Sdisplay() const {
    if (SisEmpty()) {
        cout << "Стек пуст." << endl;
        return;
    }
    
    cout << "Элементы стека: ";
    for (int i = top; i >= 0; --i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <typename T>
void Stack<T>::SreadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл для чтения.");
    }

    // Сбрасываем стек
    top = -1;

    T value;
    while (file >> value) {
        if (SisFull()) {
            throw runtime_error("Стек переполнен при считывании из файла.");
        }
        Spush(value); // Добавляем элементы в стек
    }

    file.close();
}

template <typename T>
void Stack<T>::SwriteToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл для записи.");
    }

    if (SisEmpty()) {
        cout << "Стек пуст, ничего не записано." << endl;
        file.close();
        return;
    }

    for (int i = top; i >= 0; --i) {
        file << arr[i] << " \n"; // Записываем элементы в файл
    }

    file.close();
}

#endif