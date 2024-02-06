#include <stdio.h>
#include <stdlib.h>

#include "get_file.h"

/**
 * @brief This function reads the file "input.txt" from within the same directory.
 * @return Returns a pointer to the memory where the read file is stored.
 */
FILE *getFile(char *filename)
{
    FILE *fp = fopen(filename, "r"); // Open .txt file, assign to variable file

    // Error handling to gracefully handle cases where the file cannot be opened
    if (fp == NULL)
    {
        printf("Error: could not open the file %s\n", filename);
        exit(1);
    }

    return fp;
}