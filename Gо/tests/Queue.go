package main

import (
	"errors"
	"fmt"
)

// Node представляет элемент очереди
type Node struct {
	data string // Данные, хранящиеся в узле
	next *Node  // Указатель на следующий узел
	prev *Node  // Указатель на предыдущий узел
}

// QUEUE представляет структуру очереди
type QUEUE struct {
	head *Node // Указатель на начало очереди
	tail *Node // Указатель на конец очереди
}

// new_node создает новый узел с заданными данными
func new_node(data string) *Node {
	return &Node{
		data: data,
		next: nil,
		prev: nil,
	}
}

// new_queue создает новую пустую очередь
func new_queue() *QUEUE {
	return &QUEUE{
		head: nil,
		tail: nil,
	}
}

// push добавляет элемент в конец очереди
func (q *QUEUE) push(value string) {
	new_node := new_node(value) // Создаем новый узел

	// Если очередь пуста, устанавливаем head и tail на новый узел
	if q.tail == nil && q.head == nil {
		q.head = new_node
		q.tail = new_node
	} else {
		// Иначе добавляем новый узел в конец очереди
		q.tail.next = new_node
		new_node.prev = q.tail
		q.tail = new_node
	}
}

// is_empty проверяет, пуста ли очередь
func (q *QUEUE) is_empty() bool {
	return q.head == nil
}

// size возвращает количество элементов в очереди
func (q *QUEUE) size() (int, error) {
	// Если очередь пуста, возвращаем ошибку
	if q.head == nil {
		return 0, errors.New("queue is empty")
	}

	temp := q.head // Начинаем с головы очереди
	count := 0     // Счетчик элементов

	// Проходим по всем элементам очереди
	for temp != nil {
		count++
		temp = temp.next
	}
	return count, nil
}

// pop удаляет и возвращает элемент из начала очереди
func (q *QUEUE) pop() string {
	// Если очередь пуста, возвращаем пустую строку
	if q.is_empty() {
		return ""
	}

	temp := q.head.data // Сохраняем данные из головы очереди

	// Если в очереди только один элемент, обнуляем head и tail
	if q.head == q.tail {
		q.head = nil
		q.tail = nil
	} else {
		// Иначе перемещаем head на следующий элемент и обнуляем предыдущий указатель
		q.head = q.head.next
		q.head.prev = nil
	}
	return temp
}

// print выводит содержимое очереди
func (q *QUEUE) print() {
	current := q.head // Начинаем с головы очереди
	for current != nil {
		fmt.Print(current.data, " ") // Выводим данные текущего узла
		current = current.next       // Переходим к следующему узлу
	}
	fmt.Println() // Перевод строки после вывода всех элементов
}
