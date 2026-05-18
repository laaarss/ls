#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // библ точных целых типов (для uintptr_t)

// структ узла односвязного списка
struct Node {
    uintptr_t data;  // поле для хран данных. 
    //оно гарантирует 8 байт на 64-бит, чтобы адрес не обрезался
    struct Node* next;};

// структ узла бин дерева
struct TreeNode {
    int data; // тоже поле для хранения данных. 
    // но тут int достаточно, т.к. храним высоту (целое число)
    struct TreeNode* left;
    struct TreeNode* right;};

// для списков
struct Node* createNode(uintptr_t data); //создаёт новый узел, возвращает указатель на него
void append(struct Node** head, uintptr_t data); //обавляет узел в конец списка
int sorted(struct Node* head); // отсортирован ли список по возрастанию
int get(struct Node* h, int k);  // возвращает значение k-го элемента
void insert(struct Node** h, int k, uintptr_t val); // ставляет узел со значением val на позицию k
void deleteNode(struct Node** h, int k); // удаляет узел с позиции k и освобождает память
void print(struct Node* h); // выводит все элементы списка через пробел
struct Node* inputList(void); // считывает числа с клавиатуры до первой буквы

//для деревьев
struct TreeNode* createTreeNode(int data); // новый узел дерева
struct TreeNode* appendTree(struct TreeNode* cursor, int data); //екурсивно вставляет узел в бин дер поиска
void LNR(struct TreeNode* cursor); // по возрастанию (по св-ву бин деревьев)
void RNL(struct TreeNode* cursor);
void NLR(struct TreeNode* cursor);
void breadthFirstSearchByFlowchart(struct TreeNode* root);  // обход в ширину

#endif