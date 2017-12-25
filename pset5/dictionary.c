/**
 * Implements a dictionary's functionality.
 * 
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

//Specify size of hash table (dictionaries/large has 143,091 words)
#define hash_size 145000

typedef struct node
{
    char word[LENGTH+1];
    int key;
    struct node *next;
} node;

//Declaration of hashing algorithm
unsigned long hash(char *str);

//Declare hash table; Dictionary size is known to be 143,091 words
node *hashtable[hash_size];

//Create counter to determine size of dictionary
unsigned int counter = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    //Create temp storage for word to check; convert to lower case
    int n = strlen(word);
    char checkword[n];

    for(int i = 0; i < n; i++)
    {
        checkword[i] = tolower(word[i]);
    }

    //Assign last letter to NULL operator
    checkword[n] = '\0';

    //Hash the checkword
    int hash_check = hash(checkword)%hash_size;

    //Assign cursor to point at first node in linked list
    node *cursor = hashtable[hash_check];

    //If cursor is NULL, the word is not in the dictionary
    if(cursor == NULL)
    {
        return false;
    }

    //If the two words match, return true
    if(strcmp(cursor->word,checkword) == 0)
    {
        return true;
    }
     //Check the next node
    else
    {
        //Check next node if not NULL
        while(cursor->next != NULL)
        {
            cursor = cursor->next;
            //printf("%s and %i\n", cursor->word, cursor->key); this prints out every word & hash key of subsequent nodes in the linked list

            if(strcmp(cursor->word,checkword) == 0)
            {
                return true;
                            }
        }
        return false;
    }
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */

/**Procedure for implementing load
* Load dictionary, exit if file could not be found
* Initalize an empty array equal to the length of the dictionary
* Iterate through every word in dictionary (assumes that each word is separated)
* For each word, create a node to store the word and pointer to the next node
* Use djb2 hashing algorithm on the word to determine index position; insert node at the hashed index value
*/

bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if(dict == NULL)
    {
        fprintf(stderr, "Could not open dictionary\n");
        return false;
    }

    //Set each value in hash table to NULL
    for(int n = 0; n < hash_size; n++)
    {
        hashtable[n] = NULL;
    }

    //Create temp storage for word based on maximum length specified
    char word_entry[LENGTH+1];

    //Loop through entire dictionary
    while(fscanf(dict, "%s", word_entry) != EOF)
    {
        //Allocate memory for a new node (i.e. word and pointer);
        node* new_node = malloc(sizeof(node));

        //If malloc returns NULL, there is not enough memory for the new node
        if(new_node == NULL)
        {
            return false;
        }

        //If malloc succeeds, copy the word into the new node
        strcpy(new_node->word, word_entry);

        //Hash string to determine index position
        int hash_key = hash(word_entry)%hash_size;
        new_node->key = hash_key;

        //Sets the pointer of new_node to NULL (if first element) or to the next item in the linked list (in case of collision)
        new_node->next = hashtable[hash_key];

        //Sets pointer of hashtable[hash_key] to new node;
        hashtable[hash_key] = new_node;

        printf("%s and %i\n", new_node->word, new_node->key); //remove comments to print every word in hash table

        counter++;
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return counter;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0; i < hash_size; i++)
    {
        node* cursor = hashtable[i];
        node* next_cursor;
        while(cursor!=NULL)
        {
            next_cursor = cursor->next;
            free(cursor);
            cursor = next_cursor;
        }
    }
    return true;
}


//djb2 hashing algorithm by dan bernstein
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
