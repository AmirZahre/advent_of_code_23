#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_parser(char const *line, char const *game_delimeter, char const *junk_delimeter, char *games[static 100]);
void *safe_malloc(size_t n);
FILE *getfile();

const int max_red_cubes = 12;     // maximum amount of red cubes possible per draw
const int max_green_cubes = 13;   // maximum amount of green cubes possible per draw
const int max_blue_cubes = 14;    // maximum amount of blue cubes possible per draw
const char *game_delimeter = ";"; // delimeter indicating new hand of cubes within a game
const char *junk_delimeter = ":"; // delimeter indicating the split of where the content we want begins (to the right) 

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

        string_parser(line, game_delimeter, junk_delimeter, games);

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
 * @param game_delimeter: the delimeter of each throw, a semi-colon. Used to indicate the end of the current throw and
 * thus beginning of the next throw (if available)
 * @param junk_delimeter: delimeter of the beginning part of the line which is parsed out
 * @param games: the array where each block represents a throw.
 * @return void, updates the games array via pointer to reflect groupings of each throw for further parsing
 */
// 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
void string_parser(char const *line, char const *game_delimeter, char const *junk_delimeter, char *games[static 100])
{
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

        printf("%i\n", temp_length_trimmed_string);
        char *trimmed_string = parsed_string + temp_length_trimmed_string;
        // printf("\n%s\n", trimmed_string);

        char *temp = safe_malloc(sizeof(char) * temp_length_trimmed_string + 1);

        strncat(temp, parsed_string, temp_length_trimmed_string);
        printf("%s\n", temp);
        
        parsed_string = temp_parsed_string;
        printf("parsed_string: %s\n", parsed_string);


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
    char *filename = "input.txt";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: Unable to open file %s\n", filename);
        exit(1);
    }
    return fp;
}