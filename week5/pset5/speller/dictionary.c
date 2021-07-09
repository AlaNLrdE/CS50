// Implements a dictionary's functionality

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// Holds the number of words in the dictionary
unsigned int dictionarySize;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

void freeMem(node *dictionaryEntry);
bool searchWord(const char *word, node *linkedList);
void allLowerCase(const char *word, char *tmpWord);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    bool boRet = false;
    unsigned int hashIndex = hash(word);
    unsigned int index = 0;
    char tmpWord[LENGTH + 1];

    if (table[hashIndex] != NULL)
    {
        for (int i = 0; i < LENGTH; i++)
        {
            tmpWord[i] = '\0';
        }
        allLowerCase(word, tmpWord);
        boRet = searchWord(tmpWord, table[hashIndex]);
    }
    else
    {
        /* table in hash = hashIndex contains nothing (NULL) */
    }

    return boRet;
}
// Search an specific word in a linkedList
bool searchWord(const char *word, node *linkedList)
{
    bool boRet = false;
// return true if the word is in the linked list
    if (0 == strcmp(word, linkedList->word))
    {
        boRet = true;
    }
    else
    {
        if (linkedList->next != NULL)
        {
            boRet = searchWord(word, linkedList->next);
        }
        else
        {
            boRet = false;
        }
    }
    return boRet;
}

// this functions change any upper case letter in a string to lower case
void allLowerCase(const char *word, char *tmpWord)
{
    int i = 0;

    while (word[i] != '\0')
    {
        if (word[i] >= 65 && word[i] <= 90)
        {
            tmpWord[i] = word[i] + 32;
        }
        else
        {
            tmpWord[i] = word[i];
        }
        i++;
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    /* Hash algorithm JDB2 by Dan Bernstein from: https://stackoverflow.com/questions/64699597/how-to-write-djb2-hashing-function-in-c
    djb2: this algorithm (k=33) was first reported by dan bernstein many years ago in comp.lang.c.
    another version of this algorithm (now favored by bernstein) uses
    xor: hash(i) = hash(i - 1) * 33 ^ str[i];
    the magic of number 33 (why it works better than many other constants, prime or not)
    has never been adequately explained.*/
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))        // *str++ is going to the next address in memory, where the next char in the string is stored
    {
        if (isupper(c))
        {
            c = c + 32;
        }

        hash = ((hash << 5) + hash) + c; // hash * 33 + c   // hash << 5 = hash * 2^5
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    bool boRet = true;
    char word[LENGTH];
    unsigned int hashIndex;
    // Open dictionary file
    FILE *inptr = fopen(dictionary, "r");
    // "reset" the dictionary size variable
    dictionarySize = 0;

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        boRet = false;
    }
    else
    {
        // Read strings from one file one at a time
        while (EOF != fscanf(inptr, "%s", word))
        {
            // increase the dictionary size variable
            dictionarySize++;
            // Create a new node for each word
            node *wordEntry = (node *)malloc(sizeof(node));
            if (NULL != wordEntry)
            {
                strcpy(wordEntry->word, word);
                // Hash word to obtain a hash value
                hashIndex = hash(wordEntry->word);
                // Insert node into hash table at that location
                if (table[hashIndex] == NULL)
                {
                    wordEntry->next = NULL;
                    table[hashIndex] = wordEntry;
                }
                else
                {
                    wordEntry->next = table[hashIndex];
                    table[hashIndex] = wordEntry;
                }
            }
            else
            {
                boRet = false;
            }
        }
        fclose(inptr);
    }

    return boRet;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionarySize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    bool boRet = false;

    for (int i = 0; i < (N - 1); i ++)
    {
        if (table[i] != NULL)
        {
            freeMem(table[i]);
            boRet = true;
        }
    }
    return boRet;
}
// this function destroys a linked list, freeing the memory
void freeMem(node *dictionaryEntry)
{
    if (dictionaryEntry->next == NULL)
    {
        free(dictionaryEntry);
    }
    else
    {
        freeMem(dictionaryEntry->next);
        free(dictionaryEntry);
    }
}
