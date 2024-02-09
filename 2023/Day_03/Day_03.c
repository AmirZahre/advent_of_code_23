#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "get_file.h"
#include "safe_malloc.h"

#define FILE_NAME "input.txt" // .txt input file to be read
#define MAX_STRING_LENGTH 256
#define MAX_NUMBERS 1000

struct number
{
    int value;
    int idx_left;
    int idx_right;
    int row;
    int valid_number;
};

// function prototypes
void parse_string(char *line, int row_index, struct number *number_list, int *n);
void validate_numbers(struct number *number_list, int *n);

int main(void)
{
    struct number number_list[MAX_NUMBERS];

    char *filename = "/workspaces/advent_code_23/2023/Day_03/" FILE_NAME; // Specify .txt file
    FILE *fp = getFile(filename);

    int max_string_length = MAX_STRING_LENGTH;
    char *line = (char *)safe_malloc(sizeof(char) * max_string_length); // Use safe_malloc instead of malloc to allocate memory for each line

    int n = 0; // intention is for n to be incrimented by 1 each time a number or symbol are encountered
    int row_index = 0;
    // Begin cycling through each line from within fp
    while (fgets(line, max_string_length, fp) != NULL)
    {
        parse_string(line, row_index++, number_list, &n);
    }

    validate_numbers(number_list, &n);

    fclose(fp);
    free(line);
}

void parse_string(char *line, int row_index, struct number *number_list, int *n)
{
    

    for (int i = 0; i < strlen(line); i++) // for each character within the provided line
    {
        int x = 0; // reset at each for loop - used to track consecutive int's

        char current_character = line[i];

        if (current_character != '.' && current_character != '\n')
        {
            number_list[*n].row = row_index;

            if isdigit (current_character)
            {
                char *tmp_number = safe_malloc(100);
                while (isdigit(current_character))
                {
                    tmp_number[x++] = current_character;
                    current_character = line[++i];
                }

                int idx_left = i - strlen(tmp_number) - 1;
                int idx_right = i;
                int int_current_num = atoi(tmp_number);

                number_list[*n].value = int_current_num;
                number_list[*n].idx_left = i - strlen(tmp_number) - 1;
                number_list[*n].idx_right = i;

                free(tmp_number);
                --i;
            }
            else
            { // is symbol
                number_list[*n].value = -1;
                number_list[*n].idx_left = i;
                number_list[*n].idx_right = i;
            }

            (*n)++;
        }
    }
}

void validate_numbers(struct number *number_list, int *n)
{

    int window_start = 0;
    int window_end = 2;

    for (int i = 0; i < *n; i++)
    {

        printf("pos: %d\n", i);

        printf("row: %i\n"
               "value: %i\n"
               "idx_left: %i\n"
               "idx_right: %i\n\n",
               number_list[i].row, number_list[i].value, number_list[i].idx_left, number_list[i].idx_right);
    }
}