#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "LinkedList.h"

// File IO complemented with linked list allocation and data storing.
int main() {
    FILE *fp;
    LinkedList *list = createLinkedList();
    if (list == NULL) {
        perror("Failed to create linked list");
        return 1;
    }

    char temp[10];
    char topic[100];
    double **data;
    int day, month, year, week;

    // Open the file for reading
    fp = fopen("logfile.txt", "r");
    if (fp == NULL) {
        perror("Cannot open file");
        freeLinkedList(list, free);
        return 1;
    }

    // Read each log entry from the file
    while (fscanf(fp, "%d-%d-%d\n", &day, &month, &year) == 3) {
        if (fscanf(fp, "%s %d : ", temp, &week) != 2) {
            fprintf(stderr, "Error reading week for entry.\n");
            break;
        }
        if (fgets(topic, sizeof(topic), fp) == NULL) {
            fprintf(stderr, "Error reading topic for entry.\n");
            break;
        }

        // Allocate memory for a Log struct and populate it
        Log *entry = (Log *)malloc(sizeof(Log));
        if (entry == NULL) {
            perror("Memory allocation failed");
            break;
        }
        entry->day = day;
        entry->month = month;
        entry->year = year;
        entry->week = week;
        strncpy(entry->topic, topic, sizeof(entry->topic));

        // Insert the entry into the linked list
        insertLast(list, entry);
    }

    fclose(fp);

    // Print the log entries
    printf("Log Entries:\n");
    // Function to print a single log entry
    void printLogEntry(void *data);
    {
        Log *entry = (Log *)data;
        printf("%02d/%02d/%d (Week %d) : %s", entry->day, entry->month, entry->year, entry->week, entry->topic);
    }
    
    // Call printLinkedList with the printLogEntry function
        printLinkedList(list, printLogEntry);

    // Free the linked list
    freeLinkedList(list, free);

    return 0;
}