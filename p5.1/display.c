#include <stdio.h>
#include <stdlib.h>
#include "plot.h"

int main(int argc, char* argv[])
{
        for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    int rows, cols;
    int i, j;

    FILE *pf = fopen(argv[1], "r");

    if (pf == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read rows and cols from the file (assuming the first two numbers are rows and cols)
    if (fscanf(pf, "%d %d", &rows, &cols) != 2) {
        printf("Error reading matrix dimensions.\n");
        fclose(pf);
        return 1;
    }

    // Allocate memory for the matrix
    double **data = malloc(rows * sizeof(double *));
    for (i = 0; i < rows; i++) {
        data[i] = malloc(cols * sizeof(double));
    }

    // Read the matrix data
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (fscanf(pf, "%lf", &data[i][j]) != 1) {
                printf("Error reading matrix data.\n");
                // Free allocated memory before returning
                for (int k = 0; k <= i; k++) free(data[k]);
                free(data);
                fclose(pf);
                return 1;
            }
            printf("%f ", data[i][j]);
        }
        printf("\n");
        plot(data, rows, cols);
    }

    // Free allocated memory
    for (i = 0; i < rows; i++) {
        free(data[i]);
    }
    free(data);

    fclose(pf);
    return 0;
}