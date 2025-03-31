#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int get_count(int symbol_amount, char symbols[], string text);
int get_letter_count(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    printf("Letters: %i\n", get_letter_count(text));

    // Compute the Coleman-Liau index

    // Print the grade level
}

int get_count(int symbol_amount, char symbols[], string text)
{
    int count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = tolower(text[i]);

        for(int j = 0; j < symbol_amount; j++)
        {
            if(c == symbols[j])
            {
                count++;
            }
        }
    }

    return count;
}

int get_letter_count(string text)
{
    char symbols['z' - 'a' + 1];
    int index = 0;
    for(int i = 'a'; i <= 'z'; i++)
    {
        symbols[index] = i;
        index++;
    }

    return get_count(index, symbols, text);
}
