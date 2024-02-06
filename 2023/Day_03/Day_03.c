#include <stdio.h>
#include <stdlib.h>

#include "get_file.h"
#include "safe_malloc.h"

int main(void){
    printf("Hello\n");

    char *filename = "../2023/Day_03/input.txt";    // Specify .txt file
    FILE *fp = getFile(filename);

    int max_string_length = 256;
    char *line = (char *)safe_malloc(sizeof(char) * max_string_length); // Use safe_malloc instead of malloc to allocate memory for each line

    // Begin cycling through each line from within fp
    while (fgets(line, max_string_length, fp) != NULL)
    {
        printf("%s\n", line);
        // parse_string(line, &total);
    }

    free(line);

}