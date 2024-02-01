#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define directive
#define MAX_RED_CUBES 12
#define MAX_GREEN_CUBES 13
#define MAX_BLUE_CUBES 14

#define FILE_NAME "input.txt" // .txt input file to be read

// function prototype
void string_parser(const char *line, char *games[static 100]);
int get_game_number();
void *safe_malloc(size_t n);
FILE *getfile();

void main()
{
    FILE *fp = getfile(); // open file

    int sum_of_ids = 0; // sum of the IDs of the games possible
    int game_id = 1;    // tracking the game ID to be potentially added to sum_of_ids for the final answer
    const int max_string_length = 256;
    char *line = safe_malloc(max_string_length + 1);

    while (fgets(line, max_string_length, fp) != NULL)
    {
        // printf("Game %i results:\n", game_id); // WIP tracking
        // printf("%s\n", line);                  // WIP tracking

        int game_valid = 0;    // flag to track validity of each game
        char *games[100] = {}; // initialize array where games will be added to

        string_parser(line, games);

        /*
        ##########################
        FINAL ANSWER
        If game is valid, incriment sum_of_ids by the current game_id
        ##########################,
        */
        if (game_valid == 1)
        {
            sum_of_ids += game_id;
        }

        // printf("\nThe sum of game IDs for those that were valid is %i.\n", sum_of_ids);

        game_id++; // incriment game_id
    }

    fclose(fp); // close file
    free(line);
}

/**
 * @brief Takes the current line, parses it, and returns an array containing the cube results grouped by throw
 * @details Initially parses the first part of the line - which is the same for each line aside from the game number.
 * The result from the initial parse is that where the first character is (should be!) the first number of the line.
 * With this newly parsed string, the function iterates through each character until a delimeter is found.
 * Each character processed prior to that delimeter is added to a block within the games array. The block will
 * therefore contain a single throws' worth of information. The program then continues to iterate through the line
 * from where it left off at the delimeter, doing the same process onto the next block within the array.
 * What is returned it the games array, which contains blocks for each throw.
 * @param line: pointer to the current line
 * @param games: the array where each block represents a throw.
 * @return void, updates the games array via pointer to reflect groupings of each throw for further parsing
 */
//Game 15532: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
void string_parser(const char *line, char *games[static 100])
{
    // variable declaration with definition
    static const char *game_delimeter = ";"; // delimeter indicating new hand of cubes within a game
    static const char *junk_delimeter = ":"; // delimeter indicating the split of where the content we want begins (to the right)
    
    const int length_of_unparsed_line = strlen(line);
    const char *parsed_line_excluding_game_number = strstr(line, junk_delimeter); // passes line and junk_delimeter to strstr, returns all to the right of delim
    
    
    // char game_number[] = "0"; // create memory destination, can be modified as it is a Character Array


    int game_number = get_game_number(line, parsed_line_excluding_game_number, length_of_unparsed_line);

    printf("game_number %i\n", game_number);



    // printf("\n\n%c\n\n", first);

    // printf("PARSED STRING: %s\n\n", parsed_line_excluding_game_number);         // retreives all to the right of "Game <number>: "

    // printf("%i\n", length_of_unparsed_line);
    
    // printf("%s\n", game_number);
}


int get_game_number(const char *line, const char *parsed_line_excluding_game_number, const int length_of_unparsed_line)
{
    static const int length_of_word_and_space_prefacing_game_number = 5;
    const int length_of_parsed_line_excluding_game_number = strlen(parsed_line_excluding_game_number);

    const int idx_end_of_number = length_of_unparsed_line - length_of_parsed_line_excluding_game_number;
    const int idx_number_start = idx_end_of_number - length_of_word_and_space_prefacing_game_number; // index begins one value to the left of the first digit
    const int idx_number_end_inclusive = idx_end_of_number; // index ends on the last digit
    const int game_number_length = idx_number_end_inclusive - idx_number_start + 1;


    // printf("idx_number_start:\n%i\n\n", idx_number_start);  
    // printf("idx_number_end_inclusive:\n%i\n\n\n", idx_number_end_inclusive);
    // printf("game_number_length:\n%i\n\n\n", game_number_length);  

    char *str_number = safe_malloc(game_number_length + 1);

    int i = idx_number_start;
    int x = 0;


    while (i < idx_number_end_inclusive)
    {
        str_number[x] = line[i];
        i++;
        x++;
    }

    int int_number = strtol(str_number, NULL, 0);

    free(str_number);

    return int_number;






    // printf("\nline\n%s\n\nparsed_line_excluding_game_number\n%s\n\n", line, parsed_line_excluding_game_number);
    // printf("length_of_parsed_line_excluding_game_number:\n%i\n\n", length_of_parsed_line_excluding_game_number);  
    // printf("length_of_unparsed_line:\n%i\n\n", length_of_unparsed_line);
    // printf("length_of_word_and_space_prefacing_game_number:\n%i\n\n\n", length_of_word_and_space_prefacing_game_number);  
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