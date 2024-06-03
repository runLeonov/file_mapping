#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "print_error.h"
#include "create_file.h"

#define FILE_SIZE (2LL * 1024 * 1024 * 1024)  // 2 ГБ
#define RECORD_SIZE 128                      // Розмір одного запису

void create_and_initialize_file(const char *filename) {
    HANDLE hFile = CreateFileA(
        filename,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (hFile == INVALID_HANDLE_VALUE) {
        print_last_error("CreateFile");
        exit(EXIT_FAILURE);
    }

    // Збільшимо розмір файлу до 2 ГБ
    LARGE_INTEGER liSize;
    liSize.QuadPart = FILE_SIZE;
    if (SetFilePointerEx(hFile, liSize, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR) {
        print_last_error("SetFilePointerEx");
        CloseHandle(hFile);
        exit(EXIT_FAILURE);
    }

    if (SetEndOfFile(hFile) == 0) {
        print_last_error("SetEndOfFile");
        CloseHandle(hFile);
        exit(EXIT_FAILURE);
    }

    // Створюємо map-об'єкт файлу
    HANDLE hMap = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, liSize.HighPart, liSize.LowPart, NULL);
    if (hMap == NULL) {
        print_last_error("CreateFileMapping");
        CloseHandle(hFile);
        exit(EXIT_FAILURE);
    }

    // Мапуємо файл на пам'ять
    char *mapped = (char *)MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, FILE_SIZE);
    if (mapped == NULL) {
        print_last_error("MapViewOfFile");
        CloseHandle(hMap);
        CloseHandle(hFile);
        exit(EXIT_FAILURE);
    }

    // Ініціалізуємо записами з фіксованою довжиною
    for (size_t i = 0; i < FILE_SIZE / RECORD_SIZE; i++) {
        size_t offset = i * RECORD_SIZE;
        memset(mapped + offset, 0, RECORD_SIZE);
        snprintf(mapped + offset, RECORD_SIZE, "%llu", i);  // записуємо індекс у перше поле
    }

    // Звільняємо маповану пам'ять
    if (UnmapViewOfFile(mapped) == 0) {
        print_last_error("UnmapViewOfFile");
    }

    CloseHandle(hMap);
    CloseHandle(hFile);
}
