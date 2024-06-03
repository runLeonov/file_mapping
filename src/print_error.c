#include <windows.h>
#include <stdio.h>
#include "print_error.h"

void print_last_error(const char *message) {
    DWORD errorMessageID = GetLastError();
    if (errorMessageID == 0) {
        printf("%s: No error message has been recorded\n", message);
        return;
    }

    LPSTR messageBuffer = NULL;
    size_t size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    printf("%s: %s\n", message, messageBuffer);

    LocalFree(messageBuffer);
}
