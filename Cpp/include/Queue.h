#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Queue {
private:
    T* arr;       // Массив для хранения элементов очереди
    int front;    // Индекс начала очереди
    int rear;     // Индекс конца очереди
    int maxSize;  // Максимальный размер очереди

public:
    Queue(int size);
    ~Queue();

    void Qpush(const T& value);
    void Qpop();
    T Qpeek() const;
    bool QisEmpty() const;
    bool QisFull() const;
    void Qprint() const;
    void QreadFromFile(const string& filename);
    void QwriteToFile(const string& filename) const;
};

// Конструктор
template <typename T>
Queue<T>::Queue(int size) : front(0), rear(0), maxSize(size) {
    arr = new T[maxSize]; // Выделение памяти для массива
}

// Деструктор
template <typename T>
Queue<T>::~Queue() {
    delete[] arr; // Освобождение памяти
}

// Добавление элемента
template <typename T>
void Queue<T>::Qpush(const T& value) {
    if (QisFull()) {
        cout << "Очередь переполнена!" << endl;
        return;
    }
    arr[rear] = value;
    rear = (rear + 1) % maxSize; // Циклическое увеличение индекса
}

// Удаление элемента
template <typename T>
void Queue<T>::Qpop() {
    if (QisEmpty()) {
        cout << "Очередь пуста!" << endl;
        return;
    }
    front = (front + 1) % maxSize; // Циклическое увеличение индекса
}

// Чтение элемента
template <typename T>
T Queue<T>::Qpeek() const {
    if (QisEmpty()) {
        throw runtime_error("Очередь пуста!");
    }
    return arr[front]; // Возврат переднего элемента
}

// Проверка на пустоту
template <typename T>
bool Queue<T>::QisEmpty() const {
    return front == rear; // Если индексы равны, очередь пуста
}

// Проверка на заполненность
template <typename T>
bool Queue<T>::QisFull() const {
    return (rear + 1) % maxSize == front; // Если следующий индекс rear равен front
}

template <typename T>
void Queue<T>::Qprint() const {
    if (QisEmpty()) {
        cout << "Очередь пуста" << endl;
        return;
    }

    cout << "Элементы очереди: ";
    for (int i = front; i != rear; i = (i + 1) % maxSize) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// чтение с файла
template <typename T>
void Queue<T>::QreadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл для чтения.");
    }

    // Сбрасываем очередь
    front = 0;
    rear = 0;

    T value;
    while (file >> value) {
        if (QisFull()) {
            throw runtime_error("Очередь переполнена при считывании из файла.");
        }
        Qpush(value); // Добавляем элементы в очередь
    }

    file.close();
}

// запись в файл
template <typename T>
void Queue<T>::QwriteToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл для записи.");
    }

    if (QisEmpty()) {
        cout << "Очередь пуста, ничего не записано." << endl;
        file.close();
        return;
    }

    for (int i = front; i != rear; i = (i + 1) % maxSize) {
        file << arr[i] << " "; // Записываем элементы в файл
    }

    file.close();
}

#endif