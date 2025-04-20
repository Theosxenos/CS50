// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1024;

// Hash table
node *table[N];

// Amount of words in dictionary
unsigned int word_count;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        sum += toupper(word[i]);
    }

    return sum % 1024;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if(source == NULL)
    {
        return false;
    }

    // Read each word in the file
    char buffer[LENGTH + 1];

    node *new_node;

    while(fscanf(source, "%s", buffer) != EOF)
    {
        // Add each word to the hash table
        new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        strcpy(new_node->word, buffer);

        int index = hash(buffer);
        if (table[index] == NULL)
        {
            table[index] = malloc(sizeof(node));
        }

        new_node->next = table[index]->next;
        table[index] = new_node;

        free(new_node);
        //TODO hash etc.

        word_count++;
    }

    // Close the dictionary file
    fclose(source);


    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
