// #include <cs50.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char *get_card_carrier(int digits); 
int get_first_two_digits(long number);
bool validate_creditcard(long card_number);

char *get_string(const char *prompt)
{
    printf("%s", prompt); // Print the prompt

    // Allocate initial buffer
    size_t buffer_size = 128;
    char *buffer = malloc(buffer_size);
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    size_t i = 0; // Current position in buffer
    int ch;

    // Read input character by character
    while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r')
    {
        // Resize buffer if necessary
        if (i + 1 >= buffer_size)
        {
            buffer_size *= 2;
            char *new_buffer = realloc(buffer, buffer_size);
            if (new_buffer == NULL)
            {
                free(buffer);
                fprintf(stderr, "Memory reallocation failed\n");
                exit(EXIT_FAILURE);
            }
            buffer = new_buffer;
        }

        buffer[i++] = ch;
    }

    // Handle CRLF (\r\n)
    if (ch == '\r' && (ch = getchar()) != '\n' && ch != EOF)
    {
        ungetc(ch, stdin);
    }

    buffer[i] = '\0'; // Null-terminate the string

    // Resize buffer to fit the exact string size
    char *result = realloc(buffer, i + 1);
    if (result == NULL)
    {
        free(buffer);
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

long get_long(const char *prompt)
{
    while (true)
    {
        char *input = get_string(prompt);  // Changed string to char*
        if (input == NULL)
        {
            continue;
        }

        char *endptr;
        long value = strtol(input, &endptr, 10);

        // Check if the entire input was successfully converted to a long
        if (*endptr == '\0' && !(value == LONG_MIN || value == LONG_MAX))
        {
            free(input);  // Free the allocated memory
            return value;
        }

        free(input);  // Free the allocated memory
        printf("Invalid number. Please try again.\n");
    }
}

int main(void)
{
    long card_number = get_long("Number: ");

    if (!validate_creditcard(card_number))
    {
        printf("%s", "INVALID\n");
        return 1;
    }
    
    int first_two_digits = get_first_two_digits(card_number);
    printf("%s", get_card_carrier(first_two_digits));
}

bool validate_creditcard(long card_number)
{
    long card_number_shortened = card_number;
    int counter = 0;
    long digit_sequence_sum = 0;
    long evenDigitSequence = 0;
    long unevenDigitSequence = 0;

    while (card_number_shortened > 0)
    {
        long lastDigit = card_number_shortened % 10;

        if (counter % 2 == 0)
        {
            unevenDigitSequence *= 10;
            unevenDigitSequence += lastDigit;
        }
        else
        {
            evenDigitSequence *= 10;
            evenDigitSequence += lastDigit;
        }

        card_number_shortened /= 10;
        counter++;
    }

    while (evenDigitSequence > 0)
    {
        long lastDigit = evenDigitSequence % 10;
        long lastDigitProduct = lastDigit * 2;

        /* Because card numbers are based on a decimal system, the highest digit is 9.
         * Therefore the highest possible number is 18, which is 2 digits and starts with 1
         * So if divided by ten equals 1 it means the product is 10 or higher and we need to split
         * it
         */
        if (lastDigitProduct / 10 == 1)
        {
            digit_sequence_sum += lastDigitProduct % 10;
            lastDigitProduct /= 10;
        }

        digit_sequence_sum += lastDigitProduct;
        evenDigitSequence /= 10;
    }

    while (unevenDigitSequence > 0)
    {
        long lastDigit = unevenDigitSequence % 10;
        digit_sequence_sum += lastDigit;
        unevenDigitSequence /= 10;
    }

    return digit_sequence_sum % 10 == 0;
}

int get_first_two_digits(long card_number)
{
	while (card_number >= 100)
	{
        card_number /= 10;
	}

    return card_number;
}

char *get_card_carrier(int digits)
{
    if(digits == 34 || digits == 37)
    {
        return "AMEX\n";
    }

    for(int i = 51; i <= 55; i++)
    {
        if(digits == i)
        {
            return "MASTERCARD\n";
        }
    }

    if(digits / 10 == 4)
    {
        return "VISA\n";
    }

    return "INVALID\n";
}