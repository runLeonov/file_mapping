#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "print_error.h"
#include "read_file.h"

#define FILE_SIZE (2LL * 1024 * 1024 * 1024)  // 2 ГБ
#define RECORD_SIZE 128                      // Розмір одного запису

void read_records_from_file(const char *filename) {
    HANDLE hFile = CreateFileA(
        filename,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (hFile == INVALID_HANDLE_VALUE) {
        print_last_error("CreateFile");
        exit(EXIT_FAILURE);
    }

    // Створюємо map-об'єкт файлу
    HANDLE hMap = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMap == NULL) {
        print_last_error("CreateFileMapping");
        CloseHandle(hFile);
        exit(EXIT_FAILURE);
    }

    // Мапуємо файл на пам'ять
    char *mapped = (char *)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, FILE_SIZE);
    if (mapped == NULL) {
        print_last_error("MapViewOfFile");
        CloseHandle(hMap);
        CloseHandle(hFile);
        exit(EXIT_FAILURE);
    }

    // Читаємо записи з файлу відповідно до їхніх індексів
    for (size_t i = 0; i < FILE_SIZE / RECORD_SIZE; i++) {
        size_t offset = i * RECORD_SIZE;
        printf("Record %llu: %.*s\n", i, RECORD_SIZE, mapped + offset);
    }

    // Звільняємо маповану пам'ять
    if (UnmapViewOfFile(mapped) == 0) {
        print_last_error("UnmapViewOfFile");
    }

    CloseHandle(hMap);
    CloseHandle(hFile);
}
