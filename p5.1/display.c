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
    
    char buffer[100];

    //while (!feof(pf)) {
    //    double **data = fgetc(pf);
    //    printf("%f", data[i][j]);  // Print each line from the file
    //}

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            double **data = fgets(buffer, sizeof(buffer), pf);
            printf("%f", data[i][j]);
        }
        //fputc('\n', dataFile);
    }

    fclose(pf);
    return 0;
}