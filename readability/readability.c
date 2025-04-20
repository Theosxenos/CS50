#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int get_count(int symbol_amount, char symbols[], string text);
int get_letter_count(string text);
int get_word_count(string text);
int get_sentence_count(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    int letters = get_letter_count(text);
    int words = get_word_count(text);
    int sentences = get_sentence_count(text);

    // Coleman-Liau index is computed using index = 0.0588 * L - 0.296 * S - 15.8
    // L is the average number of letters per 100 words in the text: that is, the number of letters
    // divided by the number of words, all multiplied by 100.
    float L = letters / (float) words * 100;
    // S is the average number of sentences per 100 words in the text: that is, the number of
    // sentences divided by the number of words, all multiplied by 100.
    float S = sentences / (float) words * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1");
    }
    else if (index >= 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i", index);
    }

    printf("\n");
}

int get_count(int symbol_amount, char symbols[], string text)
{
    int count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = tolower(text[i]);

        for (int j = 0; j < symbol_amount; j++)
        {
            if (c == symbols[j])
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
    for (int i = 'a'; i <= 'z'; i++)
    {
        symbols[index] = i;
        index++;
    }

    return get_count(sizeof symbols, symbols, text);
}

int get_word_count(string text)
{
    char symbols[] = {' '};
    return get_count(sizeof symbols, symbols, text) + 1;
}

int get_sentence_count(string text)
{
    char symbols[] = {'?', '!', '.'};

    return get_count(sizeof symbols, symbols, text);
}
