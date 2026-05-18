#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint32_t timestamp_ms;
    float lat_rad;
    float lon_rad;
    float alt_m;
} Record;
#pragma pack(pop)

int main() {
    FILE* f = fopen("flight_data3.bin", "wb");
    if (!f) { printf("Oshibka sozdaniya fayla\n"); return 1; }

    Record r;
    uint32_t start = 1700000000000; // пример времени в мс
    srand(123);

    for (int i = 0; i < 50; i++) {
        r.timestamp_ms = start + i * 60000; // каждую минуту
        r.lat_rad = (55.75 + (rand() % 1000)/10000.0) * 3.14159265/180.0;
        r.lon_rad = (37.61 + (rand() % 1000)/10000.0) * 3.14159265/180.0;
        r.alt_m = 100.0f + (rand() % 9900);
        fwrite(&r, sizeof(Record), 1, f);
    }
    fclose(f);
    printf("Fayl flight_data3.bin sozdan (50 tochek).\n");
    return 0;
}