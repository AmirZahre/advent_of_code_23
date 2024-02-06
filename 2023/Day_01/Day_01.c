#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>

#include "safe_malloc.h"
#include "get_file.h"

int parse_string(char *string, int *total);
void get_number_words(char *string, int *min_left_index, int *max_right_index, int *min_left_number, int *max_right_number);
void left_index(char *string, const char *number_word, int *min_left_index, char *min_index_word, int i);
void right_index(char *string, const char *number_word, int *max_right_index, char *max_right_word, int i);
void reverse_string(const char *string, char *reversed_string);
void convert_word_to_number(char *number_word, int *converted_number);
void get_numbers(const char *string, int *min_left_index, int *max_right_index, int *min_left_number, int *max_right_number);
int concat_first_last(int *first_digit, int *last_digit);

const char *number_word_array[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

/**
 * @brief This program is for Day 1 of the 2023 Advent of Code
 * @details Iterates through each row from the text file and parses the respective string
 * to find the minimum and maximum number-word or number, based on their index.
 * It then contatonates these two (after converting the number-word to a number, if needed) and
 * then sums the 2-digit value into a rolling total, int total.
 * @return Returns int total.
 */
int main()
{
    char *filename = "/workspaces/advent_code_23/2023/Day_01/input.txt";    // Specify .txt file
    FILE *fp = getFile(filename);

    int total = 0;

    int max_string_length = 256;
    char *line = (char *)safe_malloc(sizeof(char) * max_string_length); // Use safe_malloc instead of malloc to allocate memory for each line

    // Begin cycling through each line from within fp
    while (fgets(line, max_string_length, fp) != NULL)
    {
        parse_string(line, &total);
    }
    printf("%i\n", total);
    free(line);
    fclose(fp);

}

/**
 * @brief Where all the string parsing occurs for both num word and nums
 * @return Returns concatonated int.
 */
int parse_string(char *string, int *total)
{
    // allocate memory for min and max ints and their indexes
    int *min_left_index = safe_malloc(sizeof(int));
    int *max_right_index = safe_malloc(sizeof(int));
    int *min_left_number = safe_malloc(sizeof(int));
    int *max_right_number = safe_malloc(sizeof(int));

    *min_left_index = INT_MAX;
    *max_right_index = -1;

    get_number_words(string, min_left_index, max_right_index, min_left_number, max_right_number);
    get_numbers(string, min_left_index, max_right_index, min_left_number, max_right_number);

    *total += concat_first_last(min_left_number, max_right_number);

    free(min_left_index);
    free(max_right_index);
    free(min_left_number);
    free(max_right_number);
}

/**
 * @brief Organizes the retreival of the first and last number words and their conversions into numeric
 */
void get_number_words(char *string, int *min_left_index, int *max_right_index, int *min_left_number, int *max_right_number)
{
    // allocates memory for min and max number words
    char *min_index_word = (char *)safe_malloc(sizeof(char) * 7);
    char *max_index_word = (char *)safe_malloc(sizeof(char) * 7);

    // for each number word
    for (int i = 0; i < sizeof(number_word_array) / sizeof(number_word_array[0]); i++)
    {
        // find and return left index
        left_index(string, number_word_array[i], min_left_index, min_index_word, i);

        // find and return right index
        right_index(string, number_word_array[i], max_right_index, max_index_word, i);
    }
    // convert minimum number word to int
    convert_word_to_number(min_index_word, min_left_number);
    convert_word_to_number(max_index_word, max_right_number);

    free(min_index_word);
    free(max_index_word);
}

/**
 * @brief Retrieves the left-most number-word
 */
void left_index(char *string, const char *number_word, int *min_left_index, char *min_index_word, int i)
{
    // searches first occurance of number word in line
    char *first_occurance = strstr(string, number_word);

    // if first occurance exists
    if (first_occurance)
    {
        int index = (int)(strlen(string) - strlen(first_occurance)); // get the index of the first occurance
        if (index < *min_left_index)
        {                                        // if index is less than current minimum index
            *min_left_index = index;             // promote as new minimum index
            strcpy(min_index_word, number_word); // promote minimum index word to reflect current num word
        }
    }
}

/**
 * @brief Retrieves the right-most number-word
 */
void right_index(char *string, const char *number_word, int *max_right_index, char *max_right_word, int i)
{
    int original_length = strlen(string);                                             // Save the original string length
    char *reversed_string = (char *)safe_malloc(sizeof(char) * (strlen(string) + 1)); // +1 for null terminator
    char *reversed_number_word = (char *)safe_malloc(sizeof(char) * (strlen(number_word) + 1));
    reverse_string(string, reversed_string);
    reverse_string(number_word, reversed_number_word);

    // searches first occurance of number word in line
    char *first_occurance = strstr(reversed_string, reversed_number_word);

    // if first occurrence exists
    if (first_occurance)
    {
        int reversed_index = (int)(first_occurance - reversed_string);               // Index in the reversed string
        int original_index = original_length - reversed_index - strlen(number_word); // Correct index in the original string

        if (original_index > *max_right_index) // if the index is greater than the current maximum index
        {
            *max_right_index = original_index;   // update the maximum index
            strcpy(max_right_word, number_word); // update the maximum index word
        }
    }
    free(reversed_string);
    free(reversed_number_word);
}

/**
 * @brief Assisting the right_index, reverses the string so that the methods from left_index may also be applied to right_index
 */
void reverse_string(const char *string, char *reversed_string)
{
    int len = strlen(string);

    for (int i = 0; i < len; i++)
    {
        reversed_string[len - i - 1] = string[i];
    }
    reversed_string[len] = '\0'; // Null-terminate the reversed string
}

/**
 * @brief Converts a number word to its corresponding integer value.
 * @param number_word The number word deemed as being either the first or last within the string
 * @param converted_number The pointer assigned to either min_left_number or right_max_number
 * @details
 * This function takes a string representing a number word (e.g., "one", "two", etc.)
 * and a pointer to an integer. It looks up the number word in a global array of number words,
 * finds the corresponding index, and then stores the integer equivalent (index + 1) in the location
 * pointed to by the given integer pointer. This is because the number words start at "one" which
 * corresponds to the index 0 in the array.
 */
void convert_word_to_number(char *number_word, int *converted_number)
{
    // Cycle through each number word within an array
    for (int i = 0; i < sizeof(number_word_array) / sizeof(number_word_array[0]); i++)
    {
        // If the number word matches the input, assign the corresponding integer (index + 1) to converted_number
        if (strcmp(number_word_array[i], number_word) == 0)
        {
            *converted_number = i + 1;
            break; // Exit loop after finding the match
        }
    }
}

/**
 * @brief Finds first and last number in string, updates min/max if required.
 */
void get_numbers(const char *string, int *min_left_index, int *max_right_index, int *min_left_number, int *max_right_number)
{
    int i;                    // initialize i
    int len = strlen(string); // length of char
                              // printf("%c", string[5]);
    for (i = 0; i < len; i++)
    {
        // printf("%i", i);
        // printf("%c", string[4]);
        if (isdigit((string)[i]) && i < *min_left_index)
        {
            // printf("%i\n", *min_left_number);
            *min_left_index = i;
            *min_left_number = (string[i] - '0');
            // printf("%i\n", *min_left_number);
            // printf("%c %i\n", string[i], i);
            break;
        }
    }

    for (i = len - 1; i >= 0; i--)
    {
        if (isdigit((string)[i]) && i > *max_right_index)
        {
            *max_right_index = i;
            *max_right_number = (string[i] - '0');
        }
    }
}

/**
 * @brief Concatonates first and last digit
 */
int concat_first_last(int *first_digit, int *last_digit)
{
    if (*first_digit == 0)
    {
        printf("No numbers present within string \n");
        return 0;
    }
    int concatenated = (*first_digit * 10) + *last_digit;
    return concatenated;
}