// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 32768;

// Hash table
node *table[N];

// Number of words added
unsigned int total_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Index in which we have to search
    unsigned int index = hash(word);

    // traverse through list to check word in the table index
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // Word found in list
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Uses DJB2 hash algorithm, link : "http://www.cse.yorku.ca/~oz/hash.html"
    unsigned long hash = 5381;
    char c;

    // For every letter in word
    while ((c = *word++))
    {
        // hash = hash * 33 + c
        hash = ((hash << 5) + hash) + (int) tolower(c);
    }
    return (hash % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open dictionary file
    FILE *fptr = fopen(dictionary, "r");

    if (fptr == NULL)
    {
        // Couldn't open file
        return false;
    }

    char word[LENGTH + 1];

    // Read through dictionary word by word
    while (fscanf(fptr, "%s", word) != EOF)
    {
        // Make new node pointer, store word on it
        node *nptr = malloc(sizeof(node));
        if (nptr == NULL)
        {
            // Space not allocated
            return false;
        }

        // Copy word in node
        strcpy(nptr->word, word);

        // Use hash function for index
        unsigned int index = hash(word);

        // Insert word into table
        nptr->next = table[index];
        table[index] = nptr;

        // Update total words counter
        total_words++;
    }

    fclose(fptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return total_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Traverse through table for every index
    for (int i = 0; i < N; i++)
    {
        // Make two pointer cursor and temp for traversing in the list
        node *cursor = table[i];
        while (cursor != NULL)
        {
            // Set cursor to next element and free current element
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}