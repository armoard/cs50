// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dictionary.h"
#include "string.h"
#include "strings.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int size_file = 0;
int* ps = &size_file;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node* cursor = table[hash(word)];

    while(cursor != NULL)
    {
        if((strcasecmp(cursor->word, word)) == 0)
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
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';       //sirve igualmente
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char words[45]; //capacidad hasta la palabra mas larga 
    while (fscanf(dict,"%s",words) != EOF)
    {
        node *n = malloc(sizeof(node)); //memoria para el node 
        int hashvalue = hash(words); 
        strcpy(n->word, words); 
        n->next = table[hashvalue];  // el next del node apunta al primer item del hashtable 
        table[hashvalue] = n; // ahora hacemos nuestro nodo el primer item del hashtable

        *ps = *ps+1; // cuenta el numero de letras
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return *ps; // no hace falta usar pointers pero queda fachero
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
     for (int i = 0; i<N;i++)
    {
        node* temp = table[i];
        node* cursor = table[i];
        while(cursor != NULL)
        {   cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}
