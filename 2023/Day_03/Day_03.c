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

struct symbol
{
    int idx;
    int row;
};

// function prototypes
void parse_string(char *line, int row_index, struct number *number_list, struct symbol *symbol_list, int *number_count, int *symbol_count);
void validate_numbers(struct number *number_list, struct symbol *symbol_list, int *number_sount, int *symbol_count);

int main(void)
{
    struct number number_list[MAX_NUMBERS];
    struct symbol symbol_list[MAX_NUMBERS];

    char *filename = "/workspaces/advent_code_23/2023/Day_03/" FILE_NAME; // Specify .txt file
    FILE *fp = getFile(filename);

    int max_string_length = MAX_STRING_LENGTH;
    char *line = (char *)safe_malloc(sizeof(char) * max_string_length); // Use safe_malloc instead of malloc to allocate memory for each line

    int number_count = 0; // intention is for n to be incrimented by 1 each time a number or symbol are encountered
    int symbol_count = 0;
    int row_index = 0;
    // Begin cycling through each line from within fp
    while (fgets(line, max_string_length, fp) != NULL)
    {
        parse_string(line, row_index++, number_list, symbol_list, &number_count, &symbol_count);
    }

    validate_numbers(number_list, symbol_list, &number_count, &symbol_count);

    fclose(fp);
    free(line);
}

void parse_string(char *line, int row_index, struct number *number_list, struct symbol *symbol_list, int *number_count, int *symbol_count)
{

    for (int i = 0; i < strlen(line); i++) // for each character within the provided line
    {
        int x = 0; // reset at each for loop - used to track consecutive int's

        char current_character = line[i];

        if (current_character != '.' && current_character != '\n')
        {
            number_list[*number_count].row = row_index;

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

                number_list[*number_count].value = int_current_num;
                number_list[*number_count].idx_left = i - strlen(tmp_number) - 1;
                number_list[*number_count].idx_right = i;
                (*number_count)++;

                free(tmp_number);
                --i;
            }
            else
            { // is symbol
                symbol_list[*symbol_count].idx = i;
                symbol_list[*symbol_count].row = row_index;
                (*symbol_count)++;
            }
        }
    }
}

void validate_numbers(struct number *number_list, struct symbol *symbol_list, int *number_count, int *symbol_count)
{

    printf("NUMBERS:\n");

    int i = 0;
    int row_start = 0;
    int row_end = 1;
    for (int current_row = row_start; current_row < row_end;) // get values only from a specific row
    {

        if (number_list[i].row == current_row)
        {
            printf("pos: %d\n"
                   "row: %i\n"
                   "value: %i\n"
                   "idx_left: %i\n"
                   "idx_right: %i\n\n",
                   current_row, number_list[i].row, number_list[i].value, number_list[i].idx_left, number_list[i].idx_right);


            printf(
                "row: %i\n"
                "idx: %i\n\n",
                symbol_list[i].row, symbol_list[i].idx);


            i++;
        }
        else
        {
            current_row++;
        }
    }



    // printf("\nSYMBOLS:\n");
    // for (int i = 0; i < *symbol_count; i++)
    // {
    //     printf(
    //         "row: %i\n"
    //         "idx: %i\n\n",
    //         symbol_list[i].row, symbol_list[i].idx);
    // }
}



    // int window_start = 0;
    // int window_end = 2;
    // printf("NUMBERS:\n");
    // for (int i = 0; i < *number_count; i++)
    // {
    //     // if (number_list[i].row >= window_start && number_list[i].row <= window_end) // sliding window
    //     // {

    //     printf("pos: %d\n"
    //            "row: %i\n"
    //            "value: %i\n"
    //            "idx_left: %i\n"
    //            "idx_right: %i\n\n",
    //            i, number_list[i].row, number_list[i].value, number_list[i].idx_left, number_list[i].idx_right);
    //     // }
    // }