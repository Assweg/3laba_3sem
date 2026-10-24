#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void LpushFront2(const T& element);
    void LpushBack2(const T& element);
    void LdelFront2();
    void LdelBack2();
    void Ldel2(const T& value);
    bool Lfind2(const T& value) const;
    void Lprint2() const;
    void LreadFromFile2(const string& filename);
    void LwriteToFile2(const string& filename) const;
};

// Конструктор инициализирует список с нулевыми указателями на начало и конец, и нулевым размером
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

// Деструктор последовательно удаляет все элементы из списка, освобождая память
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (head) {
        LdelFront2(); // Удаление первого элемента до тех пор, пока список не станет пустым
    }
}

// Добавляет новый элемент в начало списка
template <typename T>
void DoublyLinkedList<T>::LpushFront2(const T& element) {
    Node* newNode = new Node(element); // Создаём новый узел с значением element
    if (!head) { // Если список пустой, голова и хвост указывают на новый элемент
        head = tail = newNode;
    } else { // Иначе, добавляем новый элемент перед текущей головой
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

// Добавляет новый элемент в конец списка
template <typename T>
void DoublyLinkedList<T>::LpushBack2(const T& element) {
    Node* newNode = new Node(element);
    if (!tail) { // Если список пустой, голова и хвост указывают на новый элемент
        head = tail = newNode;
    } else { // Иначе, добавляем новый элемент после текущего хвоста
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

// Удаляет первый элемент из списка
template <typename T>
void DoublyLinkedList<T>::LdelFront2() {
    if (!head) {
        throw std::runtime_error("Список пуст, невозможно удалить элемент.");
    }
    Node* temp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
    size--;
}

template <typename T>
void DoublyLinkedList<T>::LdelBack2() {
    if (!tail) {
        throw std::runtime_error("Список пуст, невозможно удалить элемент.");
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
    size--;
}

template <typename T>
void DoublyLinkedList<T>::Ldel2(const T& value) {
    if (!head) {
        throw std::runtime_error("Список пуст, невозможно удалить элемент.");
    }
    Node* curr = head;
    while (curr) {
        if (curr->data == value) {
            if (curr == head) {
                LdelFront2();
            } else if (curr == tail) {
                LdelBack2();
            } else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                delete curr;
                size--;
            }
            return;
        }
        curr = curr->next;
    }
    throw std::runtime_error("Элемент не найден в списке.");
}

// Поиск по значению
template <typename T>
bool DoublyLinkedList<T>::Lfind2(const T& value) const {
    Node* curr = head;
    while (curr) {
        if (curr->data == value) return true; // Если элемент найден, возвращаем true
        curr = curr->next; // Переходим к следующему элементу
    }
    return false; // Если элемент не найден, возвращаем false
}

// Печатает все элементы списка
template <typename T>
void DoublyLinkedList<T>::Lprint2() const {
    Node* curr = head;
    while (curr) {
        cout << curr->data << " "; // Печатаем значение текущего элемента
        curr = curr->next; // Переходим к следующему элементу
    }
    cout << endl;
}

// Считывает элементы двусвязного списка из файла
template <typename T>
void DoublyLinkedList<T>::LreadFromFile2(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл для чтения.");
    }
    
    T value;
    while (file >> value) {
        LpushBack2(value); // Добавляем элементы в конец списка
    }
    
    file.close();
}

// Записывает элементы двусвязного списка в файл
template <typename T>
void DoublyLinkedList<T>::LwriteToFile2(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл для записи.");
    }
    
    Node* curr = head;
    while (curr) {
        file << curr->data << " "; // Записываем значение элемента
        curr = curr->next; // Переходим к следующему элементу
    }
    
    file.close();
}

#endif