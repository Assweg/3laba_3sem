#ifndef COMPLETEBINARYTREE_H
#define COMPLETEBINARYTREE_H

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

template <typename T>
class CompleteBinaryTree {
private:
    T* tree;       // Массив для хранения элементов дерева
    int capacity;  // Максимальный размер дерева
    int size;      // Текущий размер дерева

    void printTree(int index, int indent) const; // Вспомогательная функция для печати дерева

public:
    CompleteBinaryTree(int capacity);
    ~CompleteBinaryTree();

    void Tinsert(const T& value);
    bool Tsearch(const T& value) const;
    bool TisComplete() const;
    void Tprint() const;
    void TreadFromFile(const string& filename);
    void TwriteToFile(const string& filename) const;
};

// Конструктор
template <typename T>
CompleteBinaryTree<T>::CompleteBinaryTree(int capacity) : capacity(capacity), size(0) {
    tree = new T[capacity]; // Выделяем память для массива
}

// Деструктор
template <typename T>
CompleteBinaryTree<T>::~CompleteBinaryTree() {
    delete[] tree; // Освобождаем память
}

// Функция для добавления элемента в полное двоичное дерево
template <typename T>
void CompleteBinaryTree<T>::Tinsert(const T& value) {
    if (size >= capacity) {
        cout << "Дерево переполнено!\n";
        return;
    }
    tree[size] = value; // Добавляем элемент в конец массива
    size++;
}

// Функция для поиска элемента в дереве
template <typename T>
bool CompleteBinaryTree<T>::Tsearch(const T& value) const {
    for (int i = 0; i < size; i++) {
        if (tree[i] == value) {
            return true;
        }
    }
    return false; 
}

// Функция для проверки, является ли дерево полным
template <typename T>
bool CompleteBinaryTree<T>::TisComplete() const {
    for (int i = 0; i < size; i++) {
        // Проверяем, что значения для левого и правого детей
        // находятся в пределах размерности дерева
        if ((2 * i + 1 < size && tree[2 * i + 1] == T()) ||
            (2 * i + 2 < size && tree[2 * i + 2] == T())) {
            return false; // Не полное двоичное дерево
        }
    }
    return true; // Полное двоичное дерево
}

// Функция для вывода дерева
template <typename T>
void CompleteBinaryTree<T>::Tprint() const {
    if (size == 0) {
        cout << "Дерево пустое.\n";
        return;
    }
    printTree(0, 0); // Начинаем с корня дерева
}

// Вспомогательная функция для печати дерева
template <typename T>
void CompleteBinaryTree<T>::printTree(int index, int indent) const {
    if (index < size) {
        if (tree[index] != T()) {
            printTree(2 * index + 2, indent + 4); // Правое поддерево
            if (indent) {
                cout << setw(indent) << ' '; // Выравнивание
            }
            cout << tree[index] << "\n"; // Печатаем узел
            printTree(2 * index + 1, indent + 4); // Левое поддерево
        }
    }
}

// Функция для считывания дерева из файла
template <typename T>
void CompleteBinaryTree<T>::TreadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл для чтения!" << endl;
        return;
    }

    T value;
    while (file >> value) {
        if (value != T()) { // Предположим, что значение по умолчанию обозначает пустое значение
            Tinsert(value); // Вставляем элемент в дерево
        }
    }

    file.close();
}

// Функция для записи дерева в файл
template <typename T>
void CompleteBinaryTree<T>::TwriteToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл для записи!" << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        file << tree[i] << "\n"; // Записываем каждый элемент в файл
    }

    file.close();
}

#endif