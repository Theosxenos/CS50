// #include <cs50.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char *get_card_carrier(int digits); 
int get_first_two_digits(long number);
bool validate_creditcard_number(long card_number);

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

    if (!validate_creditcard_number(card_number))
    {
        printf("%s", "INVALID\n");
        return 0;
    }
    
    int first_two_digits = get_first_two_digits(card_number);
    printf("%s", get_card_carrier(first_two_digits));
}

bool validate_creditcard_number(long card_number)
{
    long card_number_shortened = card_number;
    int counter = 0;
    long digit_sequence_sum = 0;

    while (card_number_shortened > 0)
    {
        long last_digit = card_number_shortened % 10;

        // Uneven digits
        if (counter % 2 == 0)
        {
            digit_sequence_sum += last_digit;
        }
        // Even digits
        else
        {
            int last_digit_product = last_digit * 2;

            // Products of the every other digit needs to be counted as individual digits not its sum
            if(last_digit_product >= 10)
            {
                int split_product_digit = last_digit_product % 10;
                digit_sequence_sum += split_product_digit;
                // Make it single digit
                last_digit_product /= 10;
            }

            digit_sequence_sum += last_digit_product;
        }

        card_number_shortened /= 10;
        counter++;
    }

    printf("Sum %i", digit_sequence_sum);

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

   if (digits >= 51 && digits <= 55) 
{
       return "MASTERCARD\n";
   }

    if(digits / 10 == 4)
    {
        return "VISA\n";
    }

    return "INVALID\n";
}