// This program reads the contents of a file and displays them on the standard output.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    FILE* file;

    if (strcmp(filename, "-") == 0) {
        file = stdin;
    } else {
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Error opening file for reading.\n");
            return 1;
        }
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    if (file != stdin) {
        fclose(file);
    }

    return 0;
}