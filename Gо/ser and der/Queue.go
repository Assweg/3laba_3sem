package main

import (
	"bufio"
	"encoding/gob"
	"encoding/json"
	"errors"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// Queue представляет структуру данных очереди
type Queue struct {
	Arr     []int `json:"arr" gob:"arr"`         // Массив для хранения элементов очереди
	Front   int   `json:"front" gob:"front"`     // Индекс начала очереди
	Rear    int   `json:"rear" gob:"rear"`       // Индекс конца очереди
	MaxSize int   `json:"maxSize" gob:"maxSize"` // Максимальный размер очереди
}

// NewQueue создает новую очередь с заданным размером
func NewQueue(size int) *Queue {
	return &Queue{
		Arr:     make([]int, size),
		Front:   0,
		Rear:    0,
		MaxSize: size,
	}
}

// Qpush добавляет элемент в конец очереди
func (q *Queue) Qpush(value int) {
	if q.QisFull() {
		fmt.Println("Очередь переполнена!")
		return
	}
	q.Arr[q.Rear] = value
	q.Rear = (q.Rear + 1) % q.MaxSize // Циклическое увеличение индекса
}

// Qpop удаляет элемент из начала очереди
func (q *Queue) Qpop() {
	if q.QisEmpty() {
		fmt.Println("Очередь пуста!")
		return
	}
	q.Front = (q.Front + 1) % q.MaxSize // Циклическое увеличение индекса
}

// Qpeek возвращает элемент из начала очереди без удаления
func (q *Queue) Qpeek() (int, error) {
	if q.QisEmpty() {
		return 0, errors.New("Очередь пуста!")
	}
	return q.Arr[q.Front], nil
}

// QisEmpty проверяет, пуста ли очередь
func (q *Queue) QisEmpty() bool {
	return q.Front == q.Rear
}

// QisFull проверяет, заполнена ли очередь
func (q *Queue) QisFull() bool {
	return (q.Rear+1)%q.MaxSize == q.Front
}

// Qprint выводит элементы очереди
func (q *Queue) Qprint() {
	if q.QisEmpty() {
		fmt.Println("Очередь пуста")
		return
	}

	fmt.Print("Элементы очереди: ")
	for i := q.Front; i != q.Rear; i = (i + 1) % q.MaxSize {
		fmt.Printf("%d ", q.Arr[i])
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
	q.Front = 0
	q.Rear = 0

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

	for i := q.Front; i != q.Rear; i = (i + 1) % q.MaxSize {
		_, err := file.WriteString(fmt.Sprintf("%d ", q.Arr[i]))
		if err != nil {
			return err
		}
	}

	return nil
}

// QserializeBinary сериализует очередь в бинарный файл
func (q *Queue) QserializeBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return errors.New("Не удалось открыть файл для записи.")
	}
	defer file.Close()

	encoder := gob.NewEncoder(file)
	err = encoder.Encode(q)
	if err != nil {
		return errors.New("Не удалось сериализовать очередь.")
	}

	return nil
}

// QdeserializeBinary десериализует очередь из бинарного файла
func QdeserializeBinary(filename string, size int) (*Queue, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, errors.New("Не удалось открыть файл для чтения.")
	}
	defer file.Close()

	q := NewQueue(size)
	decoder := gob.NewDecoder(file)
	err = decoder.Decode(q)
	if err != nil {
		return nil, errors.New("Не удалось десериализовать очередь.")
	}

	return q, nil
}

// QserializeText сериализует очередь в текстовый файл
func (q *Queue) QserializeText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return errors.New("Не удалось открыть файл для записи.")
	}
	defer file.Close()

	encoder := json.NewEncoder(file)
	err = encoder.Encode(q)
	if err != nil {
		return errors.New("Не удалось сериализовать очередь.")
	}

	return nil
}

// QdeserializeText десериализует очередь из текстового файла
func QdeserializeText(filename string, size int) (*Queue, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, errors.New("Не удалось открыть файл для чтения.")
	}
	defer file.Close()

	q := NewQueue(size)
	decoder := json.NewDecoder(file)
	err = decoder.Decode(q)
	if err != nil {
		return nil, errors.New("Не удалось десериализовать очередь.")
	}

	return q, nil
}

func main() {
	// Создаем очередь
	q := NewQueue(5)
	q.Qpush(1)
	q.Qpush(2)
	q.Qpush(3)

	// Сериализация в бинарный формат
	err := q.QserializeBinary("queue.bin")
	if err != nil {
		fmt.Println("Ошибка при сериализации в бинарный формат:", err)
	}

	// Десериализация из бинарного формата
	q2, err := QdeserializeBinary("queue.bin", 5)
	if err != nil {
		fmt.Println("Ошибка при десериализации из бинарного формата:", err)
	} else {
		q2.Qprint()
	}

	// Сериализация в текстовый формат
	err = q.QserializeText("queue.json")
	if err != nil {
		fmt.Println("Ошибка при сериализации в текстовый формат:", err)
	}

	// Десериализация из текстового формата
	q3, err := QdeserializeText("queue.json", 5)
	if err != nil {
		fmt.Println("Ошибка при десериализации из текстового формата:", err)
	} else {
		q3.Qprint()
	}
}
