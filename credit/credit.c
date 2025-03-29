#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

bool validate_creditcard(long cardNumber);

int main(void)
{
    long cardNumber = get_long("Number: ");

    if (!validate_creditcard(cardNumber))
    {
        printf("%s", "INVALID\n");
    }
    else
    {
        printf("%s", "VALID\n");
    }
}

bool validate_creditcard(long cardNumber)
{
    long cardNumberShortened = cardNumber;
    int counter = 0;
    long digitSequenceSum = 0;
    long evenDigitSequence = 0;
    long unevenDigitSequence = 0;

    while (cardNumberShortened > 0)
    {
        long lastDigit = cardNumberShortened % 10;

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

        cardNumberShortened /= 10;
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
            digitSequenceSum += lastDigitProduct % 10;
            lastDigitProduct /= 10;
        }

        digitSequenceSum += lastDigitProduct;
        evenDigitSequence /= 10;
    }

    while (unevenDigitSequence > 0)
    {
        long lastDigit = unevenDigitSequence % 10;
        digitSequenceSum += lastDigit;
        unevenDigitSequence /= 10;
    }

    return digitSequenceSum % 10 == 0;
}
