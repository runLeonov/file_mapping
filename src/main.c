#include <stdio.h>
#include "create_file.h"
#include "read_file.h"

int main() {
    const char *filename = "largefile.dat";
    create_and_initialize_file(filename);
    printf("File '%s' created and initialized.\n", filename);
    read_records_from_file(filename);
    return 0;
}
