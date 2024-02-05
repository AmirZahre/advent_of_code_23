#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// #define directives
#define MAX_RED_CUBES 12
#define MAX_GREEN_CUBES 13
#define MAX_BLUE_CUBES 14
#define FILE_NAME "input.txt" // .txt input file to be read

// function prototypes
void string_parser(const char *line, int *sum_of_ids);
int validate_cube_toss(char *parsed_line_excluding_game_number);
int get_game_number(const char *line, const char *parsed_line_excluding_game_number, const int length_of_unparsed_line);
void *safe_malloc(size_t n);
FILE *getfile();

void main()
{
    FILE *fp = getfile(); // open file

    int sum_of_ids = 0; // sum of the IDs of the games possible
    const int max_string_length = 256;
    char *line = safe_malloc(max_string_length + 1);


    while (fgets(line, max_string_length, fp) != NULL) // for each line
    {
        string_parser(line, &sum_of_ids);

    }
    printf("sum_of_ids %i\n", sum_of_ids);

    fclose(fp); // close file
    free(line);
}

// Game 15532: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
void string_parser(const char *line, int *sum_of_ids)
{
    // variable declaration with definition
    static const char *junk_delimeter = ":"; // delimeter indicating the split of where the content we want begins (to the right)

    char *parsed_line_excluding_game_number = strstr(line, junk_delimeter) + 2; // passes line and junk_delimeter to strstr, returns all to the right of delim

    /*
    ##########################
    FINAL ANSWER
    If game is valid, incriment sum_of_ids by the current game_id
    ##########################,
    */
    if (validate_cube_toss(parsed_line_excluding_game_number) == 1)
    {
        const int length_of_unparsed_line = strlen(line);
        int game_number = get_game_number(line, parsed_line_excluding_game_number, length_of_unparsed_line);
        *sum_of_ids += game_number;
    }
}

/*
Takes the cube count to validate
The first letter of the colour to validate against
The current position within the for loop (i) so that this function will bump the for loop forward past the characters of the respective colour
*/
int validate_cube_toss(char *parsed_line_excluding_game_number)
{
    int x = 0;                                       // index for the tmp_current_cube_count array
    char *tmp_current_cube_count = safe_malloc(100); // resets t

    int is_game_valid = 1;

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
                if (int_current_cube_count > MAX_BLUE_CUBES){
                    is_game_valid = 0;
                    // printf("Toss is not valid due to the colour Blue appearing %i times.\n\n", int_current_cube_count);
                    return is_game_valid;
                }
                i += 5;
                break;
            case 'r':
                if (int_current_cube_count > MAX_RED_CUBES){
                    is_game_valid = 0;
                    // printf("Toss is not valid due to the colour Red appearing %i times.\n\n", int_current_cube_count);
                    return is_game_valid;
                }
                i += 4;
                break;
            case 'g':
                if (int_current_cube_count > MAX_GREEN_CUBES){
                    is_game_valid = 0;
                    // printf("Toss is not valid due to the colour Green appearing %i times.\n\n", int_current_cube_count);
                    return is_game_valid;
                }
                i += 6;
                break;
            }
            memset(tmp_current_cube_count, 0, 100);
            x = 0;
        }
    }
    return 1;

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

    // printf("idx_end_of_number:\n%i\n\n", idx_end_of_number);
    // printf("idx_number_start:\n%i\n\n", idx_number_start);
    // printf("idx_number_end_inclusive:\n%i\n\n\n", idx_number_end_inclusive);
    // printf("game_number_length:\n%i\n\n\n", game_number_length);
}

/**
 * @brief Wrapper around standard malloc function that handles memory allocation gracefully
 * @details https://stackoverflow.com/a/35027099
 * If malloc fails to allocate memory (which would cause it to return NULL),
 * rather than returning NULL to the caller, safe_malloc prints an error message to
 * stderr and then calls abort() to terminate the program.
 * @return Returns a pointer to the memory where the read file is stored.
 */
void *safe_malloc(size_t n)
{
    void *p = malloc(n);
    if (p == NULL)
    {
        fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", n);
        abort();
    }
    return p;
}

/**
 * @brief This function reads the file "input.txt" from within the same directory.
 * @return Returns a pointer to the memory where the read file is stored.
 */
FILE *getfile()
{
    char *filename = FILE_NAME;
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }
    return fp;
}