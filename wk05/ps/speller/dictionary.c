// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// TODO
#include <stdio.h>      // fopen
#include <stdlib.h>     // malloc
#include <string.h>     // strcpy
#include <strings.h>  // strcasecmp

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
int word_count = 0;  // num words in hash table

// Returns true if word is in dictionary, else false
// Case insensitive
bool check(const char *word)
{
    // TODO
    // hash word to obtain hash value
    unsigned int hash_index;
    hash_index = hash(word);

    // access linked list at that index in the hash table
    node *cursor = table[hash_index];

    // traverse linked list, looking for the word (strcasecmp)
    while (cursor != NULL)
        if (!strcasecmp(cursor->word, word))
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("The dictionary cannot be opened for reading.\n");
        return false;
    }

    char dict_entry[LENGTH];
    unsigned int hash_index;

    // Read strings from file one at a time
    // Returns 1 (success) or -1 (error)
    while (fscanf(fp, "%s", dict_entry) > 0)
    {
        // Create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Not enough memory to store node.\n");
            return false;
        }

        // Copy dictionary word into node
        strcpy(n->word, dict_entry);

        // Hash word to obtain a hash value
        hash_index = hash(n->word);

        // Insert node into hash table at that location
        n->next = table[hash_index];
        table[hash_index] = n;

        // Increment word count for size()
        word_count += 1;
    }
    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // iterate over hash table
    for (int i = 0; i < N; i++)
    {
        // access linked list at index in hash table
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
            word_count -= 1;
        }
    }

    if (word_count == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}