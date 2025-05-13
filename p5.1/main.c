#include <stdio.h>

int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    // check if argc >= 3

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    if (input == NULL || output == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
   
    
    while (!feof(input)) {
        char c = fgetc(input);
        printf("%c", c);  // Print each line from the file
        fputc(c, output);  // Write each character to the destination file
    }

    fclose(input);
    fclose(output);
    return 0;
}

