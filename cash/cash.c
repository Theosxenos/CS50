//#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int calculate_coins(int cents);
int calculate_owed_coins(int cents_owed);

int get_int(char *prompt)
{
    int number;
    char input[100];
    
    printf("%s", prompt);
    fgets(input, sizeof(input), stdin);
    
    // Convert the input char* to an integer
    number = atoi(input);
    
    return number;
}

int main(void)
{
    int cents;

    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // int coins = calculate_owed_coins(cents);
    int coins = calculate_coins(cents);
    printf("%i\n", coins);
}

int calculate_owed_coins(int cents_owed)
{
    int sum_of_coins = 0;

    int quarters = cents_owed / 25;
    cents_owed -= 25 * quarters;
    sum_of_coins += quarters;
    if (cents_owed == 0)
        return sum_of_coins;

    int dimes = cents_owed / 10;
    cents_owed -= 10 * dimes;
    sum_of_coins += dimes;
    if (cents_owed == 0)
        return sum_of_coins;

    int nickels = cents_owed / 5;
    cents_owed -= 5 * nickels;
    sum_of_coins += nickels;
    if (cents_owed == 0)
        return sum_of_coins;

    // Next smallest is only pennies (1c) so just return sum of all
    return sum_of_coins + cents_owed;
}

int calculate_coins(int cents)
{
    int change[] = {25, 10, 5, 1};
    int sum = 0;

    for (int i = 0; i < 4; i++)
    {
        int coin_value = change[i];
        int coin_amount = cents / coin_value;
        sum += coin_amount;
        cents %= coin_value; // equal to cents -= coin_value * coin_amount;
        if (cents == 0)
            break;
    }

    return sum;
}
