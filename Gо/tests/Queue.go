package main

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// Queue представляет структуру данных очереди
type Queue struct {
	arr     []int // Массив для хранения элементов очереди
	front   int   // Индекс начала очереди
	rear    int   // Индекс конца очереди
	maxSize int   // Максимальный размер очереди
}

// NewQueue создает новую очередь с заданным размером
func NewQueue(size int) *Queue {
	return &Queue{
		arr:     make([]int, size),
		front:   0,
		rear:    0,
		maxSize: size,
	}
}

// Qpush добавляет элемент в конец очереди
func (q *Queue) Qpush(value int) {
	if q.QisFull() {
		fmt.Println("Очередь переполнена!")
		return
	}
	q.arr[q.rear] = value
	q.rear = (q.rear + 1) % q.maxSize // Циклическое увеличение индекса
}

// Qpop удаляет элемент из начала очереди
func (q *Queue) Qpop() {
	if q.QisEmpty() {
		fmt.Println("Очередь пуста!")
		return
	}
	q.front = (q.front + 1) % q.maxSize // Циклическое увеличение индекса
}

// Qpeek возвращает элемент из начала очереди без удаления
func (q *Queue) Qpeek() (int, error) {
	if q.QisEmpty() {
		return 0, errors.New("Очередь пуста!")
	}
	return q.arr[q.front], nil
}

// QisEmpty проверяет, пуста ли очередь
func (q *Queue) QisEmpty() bool {
	return q.front == q.rear
}

// QisFull проверяет, заполнена ли очередь
func (q *Queue) QisFull() bool {
	return (q.rear+1)%q.maxSize == q.front
}

// Qprint выводит элементы очереди
func (q *Queue) Qprint() {
	if q.QisEmpty() {
		fmt.Println("Очередь пуста")
		return
	}

	fmt.Print("Элементы очереди: ")
	for i := q.front; i != q.rear; i = (i + 1) % q.maxSize {
		fmt.Printf("%d ", q.arr[i])
	}
	fmt.Println()
}

// QreadFromFile считывает элементы очереди из файла
func (q *Queue) QreadFromFile(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return errors.New("Не удалось открыть файл для чтения.")
	}
	defer file.Close()

	// Сбрасываем очередь
	q.front = 0
	q.rear = 0

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		values := strings.Fields(scanner.Text())
		for _, valueStr := range values {
			value, err := strconv.Atoi(valueStr)
			if err != nil {
				return errors.New("Не удалось преобразовать строку в число.")
			}
			if q.QisFull() {
				return errors.New("Очередь переполнена при считывании из файла.")
			}
			q.Qpush(value)
		}
	}

	if err := scanner.Err(); err != nil {
		return err
	}

	return nil
}

// QwriteToFile записывает элементы очереди в файл
func (q *Queue) QwriteToFile(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return errors.New("Не удалось открыть файл для записи.")
	}
	defer file.Close()

	if q.QisEmpty() {
		fmt.Println("Очередь пуста, ничего не записано.")
		return nil
	}

	for i := q.front; i != q.rear; i = (i + 1) % q.maxSize {
		_, err := file.WriteString(fmt.Sprintf("%d ", q.arr[i]))
		if err != nil {
			return err
		}
	}

	return nil
}
