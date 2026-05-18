#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "mylibrary.h"

#pragma pack(push, 1)
typedef struct {
   uint32_t timestamp_ms;     // время в миллисек 
    float    lat_rad;          // широта в рад
    float    lon_rad;          // долгота в рад
    float    alt_m;            // высота в м
} Record;
#pragma pack(pop)

typedef struct {
   uint32_t timestamp_ms;  
    double   lat_deg;          // широта в град
    double   lon_deg;          // долгота в град
    double   alt_m;        
} FlightPoint;

typedef struct {
    int    pointCount;         // кол-во точек маршрута
    double duration;           // общ длительность полёта в сек
    double maxHeight;          // макс высота
    double minHeight;          // мин высота
} FlightStats;

struct Node* readFlightData(const char* filename);  // чтен бин файла( теперь принимает имя файла как параметр)
struct TreeNode* buildHeightTree(struct Node* list);        // строит дерево высот из списка
double findMinHeight(struct TreeNode* root);                // нахожд мин в дереве (идёт влево)
double findMaxHeight(struct TreeNode* root);                // нахожд макв дереве (идёт вправо)
FlightStats calcStats(struct Node* list, struct TreeNode* tree); // собираем статистику в структуру
void printStats(FlightStats* stats);                        // вывод статистики
int saveStatsToFile(FlightStats* stats, const char* filename); // сохр в txt-файл
void freeFlightList(struct Node* head);                     // освобождает память списка
void freeHeightTree(struct TreeNode* root);                 // освобождает память дерева

#endif