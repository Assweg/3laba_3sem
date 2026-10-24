#ifndef LINKEDLIST2_H
#define LINKEDLIST2_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    LinkedList();
    ~LinkedList();

    void LpushFront(const T& element);
    void LpushBack(const T& element);
    void LdelFront();
    void LdelBack();
    void Ldel(const T& value);
    bool Lfind(const T& value) const;
    void Lprint() const;
    void readFromFile(const string& filename);
    void writeToFile(const string& filename) const;
};

// Конструктор класса LinkedList
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {
    // Инициализация: голова и хвост списка пусты, размер равен 0
}

// Деструктор класса LinkedList
template <typename T>
LinkedList<T>::~LinkedList() {
    // Удаляем все элементы списка
    while (head) {
        LdelFront(); // Вызов метода удаления первого элемента
    }
}

// Метод для добавления элемента в начало списка
template <typename T>
void LinkedList<T>::LpushFront(const T& element) {
    Node* newNode = new Node(element); // Создаем новый узел с данными
    if (!head) { // Если список пустой
        head = tail = newNode; // Голова и хвост указывают на новый узел
    } else { // Если список не пустой
        newNode->next = head; // Новый узел указывает на текущую голову
        head = newNode; // Голова теперь указывает на новый узел
    }
    size++;
}

// Метод для добавления элемента в конец списка
template <typename T>
void LinkedList<T>::LpushBack(const T& element) {
    Node* newNode = new Node(element); // Создаем новый узел
    if (!tail) { // Если список пустой
        head = tail = newNode; // Голова и хвост указывают на новый узел
    } else { // Если список не пустой
        tail->next = newNode; // Предыдущий хвост указывает на новый узел
        tail = newNode; // Хвост теперь указывает на новый узел
    }
    size++; // Увеличиваем размер списка
}

// Метод для удаления первого элемента списка
template <typename T>
void LinkedList<T>::LdelFront() {
    if (!head) return; // Если список пуст, ничего не делаем
    Node* temp = head; // Сохраняем текущую голову
    head = head->next; // Перемещаем голову на следующий узел
    delete temp; // Удаляем старую голову
    size--;
    if (!head) { // Если список стал пустым
        tail = nullptr; // Хвост указывает на nullptr
    }
}

// Метод для удаления последнего элемента списка
template <typename T>
void LinkedList<T>::LdelBack() {
    if (!tail) return; // Если список пуст, ничего не делаем
    if (head == tail) { // Если есть только один элемент
        delete tail; // Удаляем элемент
        head = tail = nullptr; // Список становится пустым
    } else { // Если больше одного элемента
        Node* curr = head; // Начинаем с головы
        // Ищем предпоследний элемент
        while (curr->next != tail) {
            curr = curr->next; // Перемещаемся вперед
        }
        delete tail; // Удаляем последний узел
        tail = curr; // Обновляем хвост на предпоследний
        tail->next = nullptr; // Устанавливаем указатель на nullptr
    }
    size--;
}

// Метод для удаления элемента по значению из списка
template <typename T>
void LinkedList<T>::Ldel(const T& value) {
    if (!head) return; // Если список пуст, ничего не делаем
    if (head->data == value) { // Если элемент для удаления - голова
        LdelFront(); // Удаляем голову
        return;
    }
    
    Node* curr = head; // Начинаем с головы
    // Ищем элемент для удаления
    while (curr->next && curr->next->data != value) {
        curr = curr->next; // Перемещаемся вперед
    }
    if (curr->next) { // Если нашли элемент
        Node* temp = curr->next; // Сохраняем элемент для удаления
        curr->next = temp->next; // Пропускаем элемент, который удаляем
        delete temp; // Удаляем его
        size--; // Уменьшаем размер списка
        
        // Если удаленный элемент был хвостом, обновляем хвост
        if (!curr->next) { 
            tail = curr; 
        }
    }
}

// Метод для поиска элемента по значению
template <typename T>
bool LinkedList<T>::Lfind(const T& value) const {
    Node* curr = head; // Начинаем с головы
    while (curr) {
        if (curr->data == value) return true; // Возвращаем true, если нашли элемент
        curr = curr->next; // Продолжаем поиск
    }
    return false;
}

// Метод для вывода всех элементов списка
template <typename T>
void LinkedList<T>::Lprint() const {
    Node* curr = head; // Начинаем с головы
    while (curr) {
        cout << curr->data << " "; // Печатаем текущий элемент
        curr = curr->next; // Перемещаемся к следующему элементу
    }
    cout << endl;
}

// Метод для чтения односвязного списка из файла
template <typename T>
void LinkedList<T>::readFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    T value;
    while (file >> value) { // Читаем значения до конца файла
        LpushBack(value); // Добавляем значения в конец списка
    }

    file.close();
}

// Метод для записи односвязного списка в файл
template <typename T>
void LinkedList<T>::writeToFile(const string& filename) const {
    ofstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    Node* curr = head; // Начинаем с головы
    while (curr) {
        file << curr->data << " "; // Печатаем текущий элемент
        curr = curr->next; // Перемещаемся к следующему элементу
    }

    file.close();
}

#endif