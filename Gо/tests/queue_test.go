package main

import (
	"bytes"
	"io"
	"os"
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
)

// TestQueueCreation проверяет создание очереди
func TestQueueCreation(t *testing.T) {
	q := NewQueue(5)
	assert.Equal(t, 5, q.maxSize, "Ожидаемый размер очереди: 5")
	assert.True(t, q.QisEmpty(), "Новая очередь должна быть пустой")
}

// TestQueuePush проверяет добавление элементов в очередь
func TestQueuePush(t *testing.T) {
	q := NewQueue(3)
	q.Qpush(1)
	q.Qpush(2)
	q.Qpush(3)

	assert.False(t, q.QisEmpty(), "Очередь не должна быть пустой после добавления элементов")
	assert.True(t, q.QisFull(), "Очередь должна быть заполнена после добавления трех элементов")
}

// TestQueuePop проверяет удаление элементов из очереди
func TestQueuePop(t *testing.T) {
	q := NewQueue(3)
	q.Qpush(1)
	q.Qpush(2)
	q.Qpush(3)

	q.Qpop()
	q.Qpop()

	assert.False(t, q.QisEmpty(), "Очередь не должна быть пустой после удаления двух элементов")

	q.Qpop()
	assert.True(t, q.QisEmpty(), "Очередь должна быть пустой после удаления всех элементов")
}

// TestQueuePeek проверяет чтение элемента из начала очереди
func TestQueuePeek(t *testing.T) {
	q := NewQueue(3)
	q.Qpush(1)
	q.Qpush(2)

	value, err := q.Qpeek()
	require.NoError(t, err, "Ошибка при чтении элемента")
	assert.Equal(t, 1, value, "Ожидаемое значение: 1")

	q.Qpop()
	value, err = q.Qpeek()
	require.NoError(t, err, "Ошибка при чтении элемента")
	assert.Equal(t, 2, value, "Ожидаемое значение: 2")
}

// TestQueueFull проверяет, что очередь корректно определяет заполненность
func TestQueueFull(t *testing.T) {
	q := NewQueue(2)
	q.Qpush(1)
	q.Qpush(2)

	assert.True(t, q.QisFull(), "Очередь должна быть заполнена")

	q.Qpop()
	assert.False(t, q.QisFull(), "Очередь не должна быть заполнена после удаления элемента")
}

// TestQueueEmpty проверяет, что очередь корректно определяет пустоту
func TestQueueEmpty(t *testing.T) {
	q := NewQueue(2)
	assert.True(t, q.QisEmpty(), "Очередь должна быть пустой")

	q.Qpush(1)
	assert.False(t, q.QisEmpty(), "Очередь не должна быть пустой после добавления элемента")

	q.Qpop()
	assert.True(t, q.QisEmpty(), "Очередь должна быть пустой после удаления элемента")
}

// TestQueueReadWriteFile проверяет чтение и запись очереди в файл
func TestQueueReadWriteFile(t *testing.T) {
	q := NewQueue(3)
	q.Qpush(1)
	q.Qpush(2)
	q.Qpush(3)

	err := q.QwriteToFile("test_queue.txt")
	require.NoError(t, err, "Ошибка при записи в файл")

	q.Qpop()
	q.Qpop()
	q.Qpop()

	err = q.QreadFromFile("test_queue.txt")
	require.NoError(t, err, "Ошибка при чтении из файла")

	assert.False(t, q.QisEmpty(), "Очередь не должна быть пустой после чтения из файла")

	value, err := q.Qpeek()
	require.NoError(t, err, "Ошибка при чтении элемента")
	assert.Equal(t, 1, value, "Ожидаемое значение: 1")

	// Удаляем тестовый файл
	err = os.Remove("test_queue.txt")
	require.NoError(t, err, "Ошибка при удалении тестового файла")
}

// TestQueueFullError проверяет, что очередь корректно обрабатывает переполнение
func TestQueueFullError(t *testing.T) {
	q := NewQueue(2)
	q.Qpush(1)
	q.Qpush(2)

	err := q.QreadFromFile("test_queue.txt")
	assert.Error(t, err, "Ожидалась ошибка переполнения очереди")
	assert.EqualError(t, err, "Очередь переполнена при считывании из файла.", "Ожидаемая ошибка: Очередь переполнена при считывании из файла.")
}

// TestQueuePrint проверяет вывод элементов очереди
func TestQueuePrint(t *testing.T) {
	q := NewQueue(3)
	q.Qpush(1)
	q.Qpush(2)
	q.Qpush(3)

	// Перехватываем вывод функции Qprint
	old := os.Stdout
	r, w, _ := os.Pipe()
	os.Stdout = w

	q.Qprint()

	w.Close()
	var buf bytes.Buffer
	io.Copy(&buf, r)
	os.Stdout = old // Возвращаем вывод в стандартный поток

	expectedOutput := "Элементы очереди: 1 2 3 \n"
	assert.Equal(t, expectedOutput, buf.String(), "Вывод функции Qprint не соответствует ожидаемому")
}

// TestQueuePrintEmpty проверяет вывод пустой очереди
func TestQueuePrintEmpty(t *testing.T) {
	q := NewQueue(3)

	// Перехватываем вывод функции Qprint
	old := os.Stdout
	r, w, _ := os.Pipe()
	os.Stdout = w

	q.Qprint()

	w.Close()
	var buf bytes.Buffer
	io.Copy(&buf, r)
	os.Stdout = old // Возвращаем вывод в стандартный поток

	expectedOutput := "Очередь пуста\n"
	assert.Equal(t, expectedOutput, buf.String(), "Вывод функции Qprint для пустой очереди не соответствует ожидаемому")
}

// TestQueuePushFull проверяет, что очередь не добавляет элементы, когда она полна
func TestQueuePushFull(t *testing.T) {
	q := NewQueue(2)
	q.Qpush(1)
	q.Qpush(2)

	// Перехватываем вывод функции Qpush
	old := os.Stdout
	r, w, _ := os.Pipe()
	os.Stdout = w

	q.Qpush(3)

	w.Close()
	var buf bytes.Buffer
	io.Copy(&buf, r)
	os.Stdout = old // Возвращаем вывод в стандартный поток

	expectedOutput := "Очередь переполнена!\n"
	assert.Equal(t, expectedOutput, buf.String(), "Вывод функции Qpush не соответствует ожидаемому")
}

// TestQueuePopEmpty проверяет, что очередь не удаляет элементы, когда она пуста
func TestQueuePopEmpty(t *testing.T) {
	q := NewQueue(2)

	// Перехватываем вывод функции Qpop
	old := os.Stdout
	r, w, _ := os.Pipe()
	os.Stdout = w

	q.Qpop()

	w.Close()
	var buf bytes.Buffer
	io.Copy(&buf, r)
	os.Stdout = old // Возвращаем вывод в стандартный поток

	expectedOutput := "Очередь пуста!\n"
	assert.Equal(t, expectedOutput, buf.String(), "Вывод функции Qpop не соответствует ожидаемому")
}

// TestQueuePeekEmpty проверяет, что Qpeek возвращает ошибку, когда очередь пуста
func TestQueuePeekEmpty(t *testing.T) {
	q := NewQueue(2)

	_, err := q.Qpeek()
	assert.Error(t, err, "Ожидалась ошибка при чтении из пустой очереди")
	assert.EqualError(t, err, "Очередь пуста!", "Ожидаемая ошибка: Очередь пуста!")
}

// TestQueueReadWriteFileEmpty проверяет запись и чтение пустой очереди в файл
func TestQueueReadWriteFileEmpty(t *testing.T) {
	q := NewQueue(3)

	err := q.QwriteToFile("test_queue.txt")
	require.NoError(t, err, "Ошибка при записи в файл")

	q.QreadFromFile("test_queue.txt")
	assert.True(t, q.QisEmpty(), "Очередь должна быть пустой после чтения из файла")

	// Удаляем тестовый файл
	err = os.Remove("test_queue.txt")
	require.NoError(t, err, "Ошибка при удалении тестового файла")
}
