#include <stdio.h>

int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    // check if argc >= 3

    FILE *log = fopen(argv[1], "r");
    //FILE *output = fopen(argv[2], "w");

    if (log == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    char zMonth[4];
    int date, hour, minute, seconds;
    char buffer[100];
    char zProcessName[51];
    int nRead;

    while (!feof(log)) {
        fscanf(log, "fail");
        nRead = fscanf(log, "%3s %d %d:%d:%d %50s", zMonth, &date, &hour, &minute, &seconds, zProcessName);
        char* c = fgets(buffer, sizeof(buffer), log);
        printf("%s %d %d:%d:%d %s\n", zMonth, date, hour, minute, seconds, zProcessName);
        printf("%s", c);  // Print each line from the file
        //fputs(c, output);  // Write each character to the destination file
    }

    fclose(log);
    //fclose(output);
    return 0;
}