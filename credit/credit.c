#include <cs50.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

string get_card_carrier(long card_number);
int get_first_two_digits(long number);
bool validate_creditcard(long card_number);
bool validate_creditcard_number(long card_number);
bool validate_creditcard_number_for_carrier(string carrier, long card_number);

int main(void)
{
    long card_number = get_long("Number: ");
    validate_creditcard(card_number);
}

bool validate_creditcard(long card_number)
{
    string invalid_Carrier = "INVALID";

    if (!validate_creditcard_number(card_number))
    {
        printf("%s\n", invalid_Carrier);
        return false;
    }

    string carrier = get_card_carrier(card_number);
    bool is_card_length_valid = validate_creditcard_number_for_carrier(carrier, card_number);

    if (is_card_length_valid)
    {
        printf("%s\n", carrier);
        return true;
    }

    printf("%s\n", invalid_Carrier);
    return false;
}

bool validate_creditcard_number(long card_number)
{
    long card_number_shortened = card_number;
    bool uneven = true;
    long digit_sequence_sum = 0;

    while (card_number_shortened > 0)
    {
        long last_digit = card_number_shortened % 10;

        // Uneven digits
        if (uneven)
        {
            digit_sequence_sum += last_digit;
        }
        // Even digits
        else
        {
            int last_digit_product = last_digit * 2;

            // Products of the every other digit needs to be counted as individual digits not its
            // sum
            if (last_digit_product >= 10)
            {
                int split_product_digit = last_digit_product % 10;
                digit_sequence_sum += split_product_digit;
                // Make it single digit
                last_digit_product /= 10;
            }

            digit_sequence_sum += last_digit_product;
        }

        card_number_shortened /= 10;
        uneven = !uneven;
    }

    return digit_sequence_sum % 10 == 0;
}

bool validate_creditcard_number_for_carrier(string carrier, long card_number)
{
    string amex = "AMEX";
    string master = "MASTERCARD";
    string visa = "VISA";

    int card_length = 0;
    while (card_number > 0)
    {
        card_number /= 10;
        card_length++;
    }

    if (carrier == amex && card_length == 15)
    {
        return true;
    }
    else if (carrier == master && card_length == 16)
    {
        return true;
    }
    else if (carrier == visa && (card_length == 13 || card_length == 16))
    {
        return true;
    }

    return false;
}

int get_first_two_digits(long card_number)
{
    while (card_number >= 100)
    {
        card_number /= 10;
    }

    return card_number;
}

string get_card_carrier(long card_number)
{
    int digits = get_first_two_digits(card_number);

    if (digits == 34 || digits == 37)
    {
        return "AMEX";
    }

    if (digits >= 51 && digits <= 55)
    {
        return "MASTERCARD";
    }

    if (digits / 10 == 4)
    {
        return "VISA";
    }

    return "INVALID";
}
