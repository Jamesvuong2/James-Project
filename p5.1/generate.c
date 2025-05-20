// generate.c
// Created 19/05/2025
// Worksheet 5
// ID: 23180228
// Created by James Vuong

// This program creates a 2D array and then fills it with random values.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "randomarray.h"
#include "randomarray.c"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <filename> <rows> <cols>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    int rows = atoi(argv[2]);
    int cols = atoi(argv[3]);

    if (rows <= 0 || cols <= 0) {
        printf("Rows and columns must be positive integers.\n");
        return 1;
    }

    // Allocate memory for 2D array
    double** array = malloc(rows * sizeof(double*));
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        array[i] = malloc(cols * sizeof(double));
        if (array[i] == NULL) {
            printf("Memory allocation failed.\n");
            for (int k = 0; k < i; k++) free(array[k]);
            free(array);
            return 1;
        }
    }

    // Fill the array with random values using randomArray()
    srand((unsigned int)time(NULL));
    randomArray(array, rows, cols, 0);

    FILE* file;
    if (strcmp(filename, "-") == 0) {
        file = stdout;
    } else {
        file = fopen(filename, "w");
        if (file == NULL) {
            printf("Error opening file for writing.\n");
            for (int i = 0; i < rows; i++) free(array[i]);
            free(array);
            return 1;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%f", array[i][j]);
            if (j < cols - 1) {
                fputc(' ', file);
            }
        }
        fputc('\n', file);
    }

    if (file != stdout) {
        fclose(file);
    }

    for (int i = 0; i < rows; i++) free(array[i]);
    free(array);

    printf("File '%s' generated with %d rows and %d columns.\n", filename, rows, cols);
    return 0;
}