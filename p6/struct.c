#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

// File IO complemented with struct allocation and data storing.
int main() 
{
    FILE *fp;
    Log *list;
    char temp[10];
    int logAmount;
    int i;

    fp = fopen("logfile.txt", "r");

    if (fp == NULL) 
    {
        perror("cannot open file");
    } 
    
    else 
    {
        // The logfile contains one integer at the beginning to indicate the amount of entries.
        // Each entry contains date and the corresponding C programming topic.

        fscanf(fp, "%d", &logAmount);

        list = (Log *)malloc(sizeof(Log) * logAmount); // Create array of Log struct to store data.

        if (list == NULL) 
        {
            perror("Memory allocation failed");
            fclose(fp);
            return 1;
        }

        for (i = 0; i < logAmount; i++) 
        {
            fscanf(fp, "%d-%d-%d\n", &(list[i].day), &(list[i].month), &(list[i].year)); // Read date.
            fscanf(fp, "%s %d : ", temp, &(list[i].week)); // Read week.
            fgets(list[i].topic, 100, fp); // Retrieve the topic and the '\n' char at the end.
        }

        for (i = 0; i < logAmount; i++) 
        {
            printf("%02d/%02d/%d (Week %d) : %s", list[i].day, list[i].month, list[i].year, list[i].week, list[i].topic);
        }
        printf("\n");

        free(list);
        fclose(fp);
    }

    return 0;
}