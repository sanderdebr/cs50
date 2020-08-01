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
const unsigned int N = 26;

// Hash table
node *table[N];

/*
// 1. Allocate memory for new node
// Allocate some memory (size of node = num of bytes) to store a node
// Store address of node in n
node *n = malloc(sizeof(node));

// 2. Put data into the node
// Copy string from source to destination
// Copy Hello in value (char arr) of node n
strcpy(n->word, "Hello")

// 3. Set next pointer
// Unknown
n->next = NULL;

TODO
1. Open dictonary file (load function)
- fopen
- check if return value is NULL (success) otherwise return false

2. Read strings from file one at a time
- fscanf(file, "%s", word)
- repeat for each word until fscanf returns EOF

3. Create a new node for each word
- malloc
- check if return value is NULL
- copy word into node using strcpy

4. Hash word to obtain a hash value
- use hash function
- takes string and returns an index

5. Insert node into hash table at that location
- index into hash table (array of linked lists)
- set new node next pointer to first element of linked list
- after that reset head to point to the new node

*/

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hashIndex;

    // 1: Hash word to obtain hash value
    hashIndex = hash(word);
    // 2: Traverse the word in the list with strcasecmp - looking at one node at a time
    for (node *tmp = table[hashIndex]; tmp != NULL; tmp = tmp->next)
    {
        // printf("Check %s with %s\n", word, tmp->word);
        if (strcasecmp(word, tmp->word) == 0)
        {
            // printf("In dictionary: %s - %s\n", word, tmp->word);
            return true;
        }
        // printf("Not in dictionary: %s - %s\n", word, tmp->word);
    }

    return false;
}

// Hashes word to a number

char letter;
int num;
bool loaded = false;
int wordCount = 0;

unsigned int hash(const char *word)
{
    // Check word: alphabetically and ' "
    if (isalpha(*word) || (*word == '\''))
    {
        letter = word[0];

        if (letter >= 'A' && letter <= 'Z')
        {
          num = letter - 'A';
        } else if (letter >= 'a' && letter <= 'z')
        {
            num = letter - 'a';
        }

        if (num > 0 && num < N)
        {
            return num;
        }

        // printf("Something went wrong hashing this word: %s with num: %i\n", word, num);
        return 1;
    }

    // FASTER: more buckets

    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open file
    FILE *file = fopen(dictionary, "rb");

    if (file == NULL)
    {
        printf("Failed to open file");
        return false;
    }

    char word[45];
    int index;

    while(fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for each word
       node *n = malloc(sizeof(node));

       if (n == NULL)
       {
           printf("Failed to store memory");
           return false;
       }

       // Store the node value with the word
       strncpy(n->word, word, sizeof(word));
       // Set next pointing to nothing
       n->next = NULL;
       // Get index of hash
       index = hash(word);

        // Update wordcount
        wordCount++;

       // Set new node next pointer to first element of linked list
       n->next = table[index];
       // Reset head to point to the new node
       table[index] = n;

       /* Print list
       for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
       {
           printf("Word: %s\n", tmp->word);
       } */
    }

    fclose(file);

    loaded = true;

    // printf("Size: %i", size());

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        return wordCount;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Call free on any memory used with malloc
    // Return true when finished

    unsigned int cleared = 0;

    // 1. Loop array of linked lists
    for (int i = 0; i < N; i ++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);

            cleared++;
        }
    }

    if (cleared == size())
    {
        // printf("Cleared all tables\n");
        return true;
    }

    return false;

    // 2. Call free each one of those nodes
    // 3. Create cursor and tmp pointer and point to same node
    // 4. Cursor points to next node
    // 5. Then free the current element (free(tmp))
    // 6. Cursor and tmp point at same node
    // 7. Stop when cursor is pointing to NULL
}
