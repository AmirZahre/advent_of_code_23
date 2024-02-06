#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "safe_malloc.h"
#include "get_file.h"

// #define directives

#define FILE_NAME "input.txt" // .txt input file to be read

// function prototypes
int string_parser(const char *line);
int find_cube_max_power(char *parsed_line_excluding_game_number);
int get_game_number(const char *line, const char *parsed_line_excluding_game_number, const int length_of_unparsed_line);


void main()
{
    char *filename = "/workspaces/advent_code_23/2023/Day_02/" FILE_NAME;    // Specify .txt file
    FILE *fp = getFile(filename);


    int power_of_cube_set = 0; // sum of the IDs of the games possible
    const int max_string_length = 256;
    char *line = safe_malloc(max_string_length + 1);

    while (fgets(line, max_string_length, fp) != NULL) // for each line
    {
        power_of_cube_set += string_parser(line);
    }

    printf("power_of_cube_set %i\n", power_of_cube_set);

    fclose(fp); // close file
    free(line);
}

// Game 15532: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
int string_parser(const char *line)
{
    // variable declaration with definition
    static const char *junk_delimeter = ":"; // delimeter indicating the split of where the content we want begins (to the right)

    char *parsed_line_excluding_game_number = strstr(line, junk_delimeter) + 2; // passes line and junk_delimeter to strstr, returns all to the right of delim

    return find_cube_max_power(parsed_line_excluding_game_number);  
}

/*
Takes the cube count to validate
The first letter of the colour to validate against
The current position within the for loop (i) so that this function will bump the for loop forward past the characters of the respective colour
*/
int find_cube_max_power(char *parsed_line_excluding_game_number)
{
    int x = 0;                                       // index for the tmp_current_cube_count array
    char *tmp_current_cube_count = safe_malloc(100); // resets t

    int max_blue = 0;
    int max_red = 0;
    int max_green = 0;

    for (int i = 0; i < strlen(parsed_line_excluding_game_number); i++)
    {
        char current_character = parsed_line_excluding_game_number[i];

        if (isdigit(current_character))
        {
            tmp_current_cube_count[x] = current_character;
            x++;
        }
        else if (current_character == 'b' || current_character == 'r' || current_character == 'g') // if not digit, we assume we have the entire count for the specific colour. now validate.
        {
            int int_current_cube_count = atoi(tmp_current_cube_count); // convert string to int. this is the number for a specific colour of the cube toss.

            switch (parsed_line_excluding_game_number[i])
            {
            case 'b':
                if (int_current_cube_count > max_blue)
                {
                    max_blue = int_current_cube_count;
                }
                i += 5;
                break;
            case 'r':
                if (int_current_cube_count > max_red)
                {
                    max_red = int_current_cube_count;
                }
                i += 4;
                break;
            case 'g':
                if (int_current_cube_count > max_green)
                {
                    max_green = int_current_cube_count;
                }
                i += 6;
                break;
            }
            memset(tmp_current_cube_count, 0, 100);
            x = 0;
        }
    }

    return max_blue * max_red * max_green;
}

int get_game_number(const char *line, const char *parsed_line_excluding_game_number, const int length_of_unparsed_line)
{
    const int length_of_parsed_line_excluding_game_number = strlen(parsed_line_excluding_game_number);
    const int idx_end_of_number = length_of_unparsed_line - length_of_parsed_line_excluding_game_number;
    int idx_number_start = 5;                               // index begins one value to the left of the first digit
    const int idx_number_end_inclusive = idx_end_of_number; // index ends on the last digit
    const int game_number_length = idx_number_end_inclusive - idx_number_start + 1;

    char *str_number = safe_malloc(game_number_length + 1);

    int x = 0; // index for the str array

    while (idx_number_start < idx_number_end_inclusive)
    {
        str_number[x] = line[idx_number_start];
        idx_number_start++;
        x++;
    }
    int int_number = strtol(str_number, NULL, 0);

    free(str_number);

    return int_number;
}