#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    /* Read rows and cols from the file (assuming the first two numbers are rows and cols) */
    if (fscanf(pf, "%d %d", &rows, &cols) != 2) {
        printf("Error reading matrix dimensions.\n");
        fclose(pf);
        return 1;
    }

    /* Allocate memory for the 2D array */
    int **data = malloc(rows * sizeof(double *));
    for (i = 0; i < rows; i++) {
        data[i] = malloc(cols * sizeof(double));
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (fscanf(pf, "%lf", &data[i][j]) != 1) {
                printf("Error reading matrix data.\n");
                for (int k = 0; k <= i; k++) free(data[k]);
                free(data);
                fclose(pf);
                return 1;
            }

            /* Map numbers to ASCII characters */
            char c;
            switch (data[i][j]) {
                case 0: c = ' '; break; // Map 0 to space
                case 1: c = 'A'; break; // Map 1 to 'A'
                case 2: c = 'B'; break; // Map 2 to 'B'
                case 3: c = '#'; break; // Map 3 to '#'
                case 4: c = '*'; break; // Map 4 to '*'
                default: c = '?'; break; // Map unknown numbers to '?'
            }

            printf("%f ", data[i][j]);
        }
        printf("\n");
    }

    /* Free allocated memory */
    for (i = 0; i < rows; i++) {
        free(data[i]);
    }
    free(data);

    fclose(pf);
    return 0;
}
