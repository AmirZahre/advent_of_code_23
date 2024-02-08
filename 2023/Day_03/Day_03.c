#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "get_file.h"
#include "safe_malloc.h"

#define FILE_NAME "input.txt" // .txt input file to be read
#define MAX_STRING_LENGTH 256
#define MAX_NUMBERS 1000

// function prototypes
void capture_number(char *line, int row_index);

struct number
{
    int number;
    int idx_left;
    int idx_right;
    int valid_number;
} number_list[MAX_NUMBERS];

int main(void)
{

    char *filename = "/workspaces/advent_code_23/2023/Day_03/" FILE_NAME; // Specify .txt file
    FILE *fp = getFile(filename);

    int max_string_length = MAX_STRING_LENGTH;
    char *line = (char *)safe_malloc(sizeof(char) * max_string_length); // Use safe_malloc instead of malloc to allocate memory for each line

    int row_index = 0;
    // Begin cycling through each line from within fp
    while (fgets(line, max_string_length, fp) != NULL)
    {
        // printf("row %i\n", row_index);
        capture_number(line, row_index++);

    }

    // int lineNumber = 0;

    // // Iterate through each line in the file using fgets
    // for (; fgets(line, sizeof("fsdfatrtsfdsf"), fp) != NULL ;) {
    //     // Process the line (e.g., print it with the line number)
    //     printf("Line %d: %s\n", lineNumber++, line);
    // }

    fclose(fp);
    free(line);
}

void capture_number(char *line, int row_index)
{
    int x = 0;
    char *tmp_number = safe_malloc(100);


    for (int i = 0; i < strlen(line); i++)
    {
        char current_character = line[i];

    if (current_character != '.' && current_character != '\n') {

        while (isdigit(current_character)){
            tmp_number[x++] = current_character;
            current_character = line[++i];
        }

        
        int idx_left = i - strlen(tmp_number);
        int idx_right = i;
        int int_current_num = atoi(tmp_number);
        printf("%i: ", int_current_num);
        printf("right %i left %i\n", idx_left, idx_right);
    }

        // if (isdigit(current_character))
        // {

        //     tmp_number[x++] = current_character;

        //     // printf("left %c\n",  line[i-1]);


             
        //     // printf("left %c\n",  line[i+1]);
        // }
        // else 
        // {           
        //     int int_current_num = atoi(tmp_number);
        //     printf("%i\n", int_current_num);



            memset(tmp_number, 0, 100);
            x = 0;
        // // }
        // }
    }
}
