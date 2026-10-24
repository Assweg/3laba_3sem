#include "Tree.h"

int main() {
    CompleteBinaryTree<int> tree(10);

    // Заполняем дерево
    tree.Tinsert(10);
    tree.Tinsert(25);
    tree.Tinsert(32);

    // Сохраняем в текстовый файл
    tree.TwriteToFile("tree.txt");

    // Сохраняем в бинарный файл
    tree.saveToBinaryFile("tree.bin");

    // Очищаем дерево
    tree.clear();

    // Загружаем из текстового файла
    tree.TreadFromFile("tree.txt");
    tree.Tprint(); // Выводим дерево
    cout << endl;

    // Очищаем дерево
    tree.clear();

    // Загружаем из бинарного файла
    tree.loadFromBinaryFile("tree.bin");
    tree.Tprint(); // Выводим дерево

    return 0;
}