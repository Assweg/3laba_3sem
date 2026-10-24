package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestQueue(t *testing.T) {
	// Создаем три очереди для тестирования
	q_fir := new_queue()
	q_sec := new_queue()
	q_thir := new_queue()

	// Добавляем элементы в первую очередь
	q_fir.push("apple")  // Добавляем "apple"
	q_fir.push("banana") // Добавляем "banana"
	q_fir.push("cherry") // Добавляем "cherry"
	q_fir.push("date")   // Добавляем "date"
	q_fir.print()        // Печатаем содержимое первой очереди

	// Проверяем, что вторая очередь пуста
	assert.True(t, q_sec.is_empty(), "QUEUE is empty!!!")
	// Проверяем, что первая очередь не пуста
	assert.False(t, q_fir.is_empty(), "QUEUE is not empty!!!")

	// Добавляем элементы во вторую очередь
	q_sec.push("orange")    // Добавляем "orange"
	q_sec.push("grape")     // Добавляем "grape"
	q_sec.push("pineapple") // Добавляем "pineapple"
	q_sec.push("mango")     // Добавляем "mango"
	q_sec.print()           // Печатаем содержимое второй очереди

	// Проверяем размеры очередей
	size_fir, err := q_fir.size()    // Получаем размер первой очереди
	size_sec, errors := q_sec.size() // Получаем размер второй очереди

	// Проверяем, что размер первой очереди равен 4
	assert.Equal(t, 4, size_fir, "size of q_fir should be 4")
	// Проверяем, что размер второй очереди равен 4
	assert.Equal(t, 4, size_sec, "size of q_sec should be 4")
	// Проверяем, что ошибок нет
	assert.NoError(t, err)
	assert.NoError(t, errors)

	// Удаляем элементы из очередей
	del_fir_value := q_fir.pop() // Удаляем элемент из первой очереди
	del_sec_value := q_sec.pop() // Удаляем элемент из второй очереди

	// Проверяем, что удаленный элемент из первой очереди - "apple"
	assert.Equal(t, "apple", del_fir_value, "The first deleted element should be 'apple'")
	// Проверяем, что удаленный элемент из второй очереди - "orange"
	assert.Equal(t, "orange", del_sec_value, "The first deleted element from q_sec should be 'orange'")

	// Добавляем и удаляем элемент из третьей очереди
	q_thir.push("orange") // Добавляем "orange"
	q_thir.pop()          // Удаляем элемент из третьей очереди
}
