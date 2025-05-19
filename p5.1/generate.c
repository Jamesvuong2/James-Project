#include <stdio.h>
#include <stdlib.h>
#include "plot.h"

int main(int argc, char* argv[])
{
        for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    int i, j;
    FILE *inputfile;
    FILE* scriptFile;

    double **data;
    const char* filename = argv[1];
    int rows = atoi(argv[2]);
    int cols = atoi(argv[3]);
    char command[250];
    char* scriptFilename;

    if (inputfile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    /* Write the 2D data to file. */
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            fprintf(inputfile, "%f ", data[i][j]);
        }
        fputc('\n', inputfile);
    }

    /* Write the gnuplot script file. */
    fprintf(scriptFile, 
        "set pm3d\n"
        "splot \"%s\" matrix with pm3d notitle\n"
        "pause -1 \"Press Enter\"\n", 
        filename);

    /* Ensure the data is actually written to disk prior to running gnuplot. */
    fflush(inputfile);
    fflush(scriptFile);

    /* Run gnuplot itself. */
    sprintf(command, "gnuplot %s </dev/tty", scriptFilename);
    return system(command);

    return 0;
}