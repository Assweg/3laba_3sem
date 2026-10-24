#include "Stack.h"

int main() {
    Stack<string> stack(10);

    // Заполняем стек
    stack.Spush("Nikita");
    stack.Spush("Andrey");
    stack.Spush("Fedor");

    // Сохраняем в текстовый файл
    stack.SwriteToFile("stack.txt");

    // Сохраняем в бинарный файл
    stack.saveToBinaryFile("stack.bin");

    // Очищаем стек
    while (!stack.SisEmpty()) {
        stack.Spop();
    }

    // Загружаем из текстового файла
    stack.SreadFromFile("stack.txt");
    stack.Sdisplay(); // Выводим стек

    // Очищаем стек
    while (!stack.SisEmpty()) {
        stack.Spop();
    }

    // Загружаем из бинарного файла
    stack.loadFromBinaryFile("stack.bin");
    stack.Sdisplay(); // Выводим стек

    return 0;
}