#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int calculate_score(string word);

int main(void)
{
    string input[2];
    input[0] = get_string("Player 1: ");
    input[1] = get_string("Player 2: ");

    int score[2];

    for (int i = 0; i < 2; i++)
    {
        score[i] = calculate_score(input[i]);
    }

    if (score[0] == score[1])
    {
        printf("It's a tie!");
    }
    else if (score[0] > score[1])
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int calculate_score(string word)
{
    int sum = 0;
    for (int j = 0, n = strlen(word); j < n; j++)
    {
        char c = tolower(word[j]);
        sum += POINTS[c - 'a'];
    }

    return sum;
}
