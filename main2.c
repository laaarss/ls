#include <stdio.h>
#include "navigation.h"

int main(int argc, char* argv[]) {
    const char* txtFile = "flight_stats.txt";
    char* filename;

    printf("Navigacionnyy analizator\n");

    // Проверка аргументов командной строки
    if (argc < 2) { 
        printf("Oshibka: ne ukazano imya fayla!\n");
        printf("Ispolzovanie: %s <imya_binarnogo_fayla>\n", argv[0]);
        return 1;}
    
    filename = argv[1];  // берём имя файла из аргумента командной строки
    printf("Vybranny fayl: %s\n", filename);

    // 1. Чтение
    struct Node* list = readFlightData(filename); 
    if (!list) {
        printf("Oshibka: net dannyh.\n");
        return 1;}

    // 2. Дерево
    struct TreeNode* tree = buildHeightTree(list);

    // 3. Статистика
    FlightStats stats = calcStats(list, tree);

    // 4. Вывод
    printf("Rezultat:\n");
    printStats(&stats);

    // 5. Сохранение в файл 
    if (saveStatsToFile(&stats, txtFile)) {
        printf("Statistika sohranena v fayl %s\n", txtFile);
    }

    // 6. Очистка памяти 
    freeFlightList(list);
    freeHeightTree(tree);

    return 0;
}