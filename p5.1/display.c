#include <stdio.h>
#include <stdlib.h>
#include "plot.h"

static int plotActual(double **data, int rows, int cols, char* dataFilename, char* scriptFilename, FILE* dataFile, FILE* scriptFile)
{
    int i, j;
    char command[250];

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            fprintf(dataFile, "%f ", data[i][j]);
        }
        fputc('\n', dataFile);
    }

    // Write the gnuplot script file.
    fprintf(scriptFile, 
        "set pm3d\n"
        "splot \"%s\" matrix with pm3d notitle\n"
        "pause -1 \"Press Enter\"\n", 
        dataFilename);

    // Ensure the data is actually written to disk prior to running gnuplot.
    fflush(dataFile);
    fflush(scriptFile);

    // Run gnuplot itself.
    sprintf(command, "gnuplot %s </dev/tty", scriptFilename);
    return system(command);
}

void plot(double **data, int rows, int cols)
{
    char dataFilename[] = "/tmp/ucpplotdataXXXXXX";
    char scriptFilename[] = "/tmp/ucpplotscriptXXXXXX";
    int dataFd, scriptFd;
    FILE* dataFile;
    FILE* scriptFile;
    int ret;

    // Open temporary files, based on template filenames.
    dataFd = mkstemp(dataFilename);
    scriptFd = mkstemp(scriptFilename);
    if(dataFd == -1 || scriptFd == -1)
    {
        perror("Plotting failed - unable to create temporary files");
    }
    else
    {
        // Convert the OS-level file descriptors to C-level FILE pointers.
        dataFile = fdopen(dataFd, "w");
        scriptFile = fdopen(scriptFd, "w");
        if(dataFile == NULL || scriptFile == NULL)
        {
            perror("Plotting failed - unable to open temporary file stream");
        }
        else
        {
            // Perform the actual plotting.
            ret = plotActual(data, rows, cols, 
                             dataFilename, scriptFilename,
                             dataFile, scriptFile);
            if(ret % 256 != 0)
            {
                perror("Plotting failed - unable to run gnuplot");
            }
            fclose(dataFile);
            fclose(scriptFile);
        }
    }
}

int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    // check if argc >= 3

    FILE *pf = fopen(argv[1], "r");

    if (pf == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    //char buffer[100];

    while (!feof(pf)) {
        char c = fgetc(pf);
        printf("%c", c);  // Print each line from the file
        //fputs(c, output);  // Write each character to the destination file
    }

    fclose(pf);
    return 0;
}