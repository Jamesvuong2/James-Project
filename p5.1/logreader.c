#include <stdio.h>

int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    // check if argc >= 3

    FILE *log = fopen(argv[0], "r");
    //FILE *output = fopen(argv[2], "w");

    //if (log == "fail") {
    //    printf("Contains fail.\n");
    //    return 2;
    //}
    if (log == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
   
    
    char buffer[100];
    while (!feof(log)) {
        char buffer = fgets(buffer, sizeof(buffer), log);
        printf("%d", buffer);  // Print each line from the file
        //fputs(c, output);  // Write each character to the destination file
    }

    fclose(log);
    //fclose(output);
    return 0;
}