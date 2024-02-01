#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define directive
#define MAX_RED_CUBES 12
#define MAX_GREEN_CUBES 13
#define MAX_BLUE_CUBES 14

#define FILE_NAME "input.txt" // .txt input file to be read

// function prototype
void string_parser(char const *line, char *games[static 100]);
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

        printf("\nThe sum of game IDs for those that were valid is %i.\n", sum_of_ids);

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
// 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
void string_parser(char const *line, char *games[static 100])
{
    // variable declaration with definition
    static const char *game_delimeter = ";"; // delimeter indicating new hand of cubes within a game
    static const char *junk_delimeter = ":"; // delimeter indicating the split of where the content we want begins (to the right)
    int i = 0;
    int n = 0;                                              // initialize index for line walkthrough
    char *parsed_string = strstr(line, junk_delimeter) + 2; // passes line and junk_delimeter to strstr, returns all to the right of delim
    printf("PARSED STRING: %s\n\n", parsed_string);         // retreives all to the right of "Game <number>: "
    // printf("games[n]: %s\n", games[n]);
    printf("LOOP START: \n\n");

    while (strstr(parsed_string, game_delimeter) != NULL)
    {
        char *temp_parsed_string = strstr(parsed_string, game_delimeter);
        int temp_length_remaining_string = strlen(temp_parsed_string);
        int temp_length_original_string = strlen(parsed_string);
        int temp_length_trimmed_string = temp_length_original_string - temp_length_remaining_string;

        printf("temp length of trimmed string\n%i\n\n", temp_length_trimmed_string);
        char *trimmed_string = parsed_string + temp_length_trimmed_string;
        // printf("\n%s\n", trimmed_string);

        char *temp = safe_malloc(sizeof(char) * temp_length_trimmed_string + 1);

        strncat(temp, parsed_string, temp_length_trimmed_string);
        printf("temp\n%s\n\n", temp);

        parsed_string = temp_parsed_string;
        printf("parsed_string:\n%s\n\n", parsed_string);

        parsed_string += 2;

        free(temp);
    }

    /*
    opt 1: iterate through each character until delim is reached?
    * break when the delim is reached
    * do stuff until that delim is reached:
    ** STUFF:
    *** if character is int, add char to temp_num
    NOTE: want to check if the next character also is an int; if so, concatonate to the temp_num
    else character is either empty space or beginning of word
    NOTE: red green blue each begin with a unique first char - can look into memory-optimized approach

    ISSUE:

    */
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