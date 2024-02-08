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
    int is_number;
    int is_symbol;
    int idx_left;
    int idx_right;
    int valid_number;
};

// function prototypes
void parse_string(char *line, int row_index, struct number *number_list);

int main(void)
{
    struct number number_list[MAX_NUMBERS];

    char *filename = "/workspaces/advent_code_23/2023/Day_03/" FILE_NAME; // Specify .txt file
    FILE *fp = getFile(filename);

    int max_string_length = MAX_STRING_LENGTH;
    char *line = (char *)safe_malloc(sizeof(char) * max_string_length); // Use safe_malloc instead of malloc to allocate memory for each line

    int row_index = 0;
    // Begin cycling through each line from within fp
    while (fgets(line, max_string_length, fp) != NULL)
    {
        // printf("row %i\n", row_index);
        parse_string(line, row_index++, number_list);
    }

    // for (int i = 0; i < 15; ){
    //     printf("\n%i\n", number_list[i].value);
    //     i++;
    // };
            // printf("%i\n ", int_current_num);
            // printf("right %i left %i\n ", idx_left, idx_right);

            // printf("is_symbol: %i is_number: %i\n\n", number_list[row_index].is_symbol , number_list[row_index].is_number);


    fclose(fp);
    free(line);
}

void parse_string(char *line, int row_index, struct number *number_list)
{
    int n = 0;
    int x = 0; // reset at each for loop - used to track consecutive int's
    char *tmp_number = safe_malloc(100);

    // struct number number_list[MAX_NUMBERS];
    // number_list[2].idx_left = 5;

    for (int i = 0; i < strlen(line); i++)
    {
        char current_character = line[i];

        if (current_character != '.' && current_character != '\n')
        {

            while (isdigit(current_character))
            {
                tmp_number[x++] = current_character;
                current_character = line[++i];
            }

            int idx_left = i - strlen(tmp_number);
            int idx_right = i;
            int int_current_num = atoi(tmp_number);

            number_list[n].value = int_current_num;

            if (int_current_num == 0) {
                number_list[n].is_symbol = 1;
                number_list[n].is_number = 0;
            } else {
                number_list[n].is_number = 1;
                number_list[n].is_symbol = 0;
            }

            printf("%i\n ", int_current_num);
            printf("right %i left %i\n ", idx_left, idx_right);

            printf("is_symbol: %i is_number: %i\n\n", number_list[n].is_symbol , number_list[n].is_number);

        }

        n++;

        memset(tmp_number, 0, 100);
        x = 0;

    }
    // for (int i = 0; i < 12; i++){
    //     printf("is number: %i is symbol: %i\n", number_list[i].is_number, number_list[i].is_symbol);
    //     }

    }


