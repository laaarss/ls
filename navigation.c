#include "navigation.h"  
#include <stdint.h>      // для типа uintptr_t
#include <dirent.h>      // для работы с директориями 

// чтение бин файла и создание односвязного списка
struct Node* readFlightData(const char* filename) { //ф-я приним имя файла 
    FILE* file = fopen(filename, "rb");
    if (!file) { //есои не открылся
        printf("Oshibka: ne udalos otkryt fayl %s\n", filename);
        return NULL;}

    struct Node* head = NULL;  // голова списка пока пустая
    Record rec;  //временная пер
    int count = 0;  

    while (fread(&rec, sizeof(Record), 1, file) == 1) {  // читаем запись, пока есть данные
        FlightPoint* p = malloc(sizeof(FlightPoint));  // выделяем память под точку
        if (!p) {  // если памяти не хватило
            printf("Oshibka: ne hvatilo pamyati\n");  
            fclose(file);
            return NULL;  }

        //  копируем поля из rec в p
        p->timestamp_ms = rec.timestamp_ms;  
        p->alt_m = rec.alt_m; 
        p->lat_deg = rec.lat_rad * (180.0 / 3.14159265358979);  // радианы в градусы
        p->lon_deg = rec.lon_rad * (180.0 / 3.14159265358979); 
        append(&head, (uintptr_t)p);  // добавляем указатель в список (uintptr_t для 64 бит)
        count++;  }
    fclose(file);  
        printf("Prochitano %d zapisey iz fayla %s\n", count, filename);  
    return head;  }

// построение бинарного дерева высот 
struct TreeNode* buildHeightTree(struct Node* list) {  // функция принимает список точек
    struct TreeNode* root = NULL;  // корень дерева пока пустой
    struct Node* cur = list;  // указатель для прохода по списку
    int count = 0;  
    
    while (cur) {  // пока есть узлы в списке
        FlightPoint* p = (FlightPoint*)cur->data;  // получаем указатель на точку
        int hInt = (int)(p->alt_m * 100);  //  * 100 для сохранения точности в int
        root = appendTree(root, hInt);  // используем готовую функцию из mylibrary
        count++;
        cur = cur->next;  }
    printf("Derevo postroeno: %d tochek\n", count);  
    return root; }

// поиск мин высоты (движение влево по бин дереву поиска)
double findMinHeight(struct TreeNode* root) {  // функция принимает корень дерева
    if (!root) return 0.0;  // если дерево пустое - 0
    while (root->left) root = root->left;  // идём влево, пока есть что то слева
    return root->data / 100.0; } //высота в исх масштабе

// поиск макс высоты 
double findMaxHeight(struct TreeNode* root) {  
    if (!root)
        return 0.0;  
    while (root->right) 
        root = root->right;  
    return root->data / 100.0;  }

// итоговая статистика маршрута
FlightStats calcStats(struct Node* list, struct TreeNode* tree) {  
    FlightStats s = {0};  // обнуляем все поля структуры статистики
    if (!list) 
        return s;  // если список пустой - возвращаем пустую статистику
    struct Node* cur = list;  // указатель для прохода по списку
    FlightPoint* first = NULL;  // указатель на 1ую точку
    FlightPoint* last = NULL;  // указатель на последнюю точку

    while (cur) {  // пока есть узлы в списке
        FlightPoint* p = (FlightPoint*)cur->data;  //  указатель на точку
        if (!first) first = p;  // запоминаем 1ую
        last = p;  // обновляем последнюю 
        s.pointCount++; 
        cur = cur->next;  }

    if (first && last) {  
        s.duration = last->timestamp_ms - first->timestamp_ms;  } // длит в мс
    s.minHeight = findMinHeight(tree);  // берём мин из дерева
    s.maxHeight = findMaxHeight(tree);  // берём макс из дерева
    return s; }  

// вывод в консоль
void printStats(FlightStats* s) {  
    printf("Kol-vo tochek: %d\n", s->pointCount);  //  количество точек
    printf("Dlitelnost: %.0f ms\n", s->duration);    // длительность 
    printf("Max vysota: %.2f m\n", s->maxHeight);  // макс высота
    printf("Min vysota:  %.2f m\n", s->minHeight);  // минвысота
}

// запись статистики 
int saveStatsToFile(FlightStats* s, const char* filename) {  
    FILE* f = fopen(filename, "w");  
    if (!f) { printf("Oshibka: ne udalos sozdat fayl\n"); return 0; }  
    fprintf(f, "Statistika poleta:\n");  
    fprintf(f, "Kol-vo tochek: %d\n", s->pointCount);  
    fprintf(f, "Dlitelnost: %.0f ms\n", s->duration); 
    fprintf(f, "Max vysota: %.2f m\n", s->maxHeight);  
    fprintf(f, "Min vysota: %.2f m\n", s->minHeight);  
    fclose(f);  
    return 1;  }

// освоб памяти односвязного списка
void freeFlightList(struct Node* head) {  
    struct Node* cur = head;  
    while (cur) {  
        FlightPoint* p = (FlightPoint*)cur->data;  
        if (p) free(p);  
        struct Node* next = cur->next;  
        free(cur);  
        cur = next; }}

// освобождение памяти бинарного дерева 
void freeHeightTree(struct TreeNode* root) {  
    if (!root)
        return;  
    freeHeightTree(root->left);  
    freeHeightTree(root->right);  
    free(root);  
}