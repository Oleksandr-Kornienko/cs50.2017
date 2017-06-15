#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include "dictionary.h"
#define HASHTABLE_SIZE 65536
// number of buckets in hash table
#define NUM_BUCKETS 143091


typedef struct node
{
    char word[LENGTH + 1]; // LENGTH is 45 (written in dictionary.h)
    struct node* next;
}
node;

unsigned int dictionary_size = 0;

node* hashtable[NUM_BUCKETS];
 

static int hash_word(const char* word)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
        hash = (hash << 2) ^ word[i];
    return hash % HASHTABLE_SIZE;
}


bool check(const char* word)
{
    // find bucket in hash table where the word should be
    node* bucket = hashtable[hash_word(word)];
    
    // look at all entries in bucket to see if word exists by iterating over linked list at that index
    for (node* entry = bucket; entry != NULL; entry = entry->next)
    {
        // because words are lowercase, use strcasecmp to compare words
        if (strcasecmp(entry->word, word) == 0)
        {
            return true;
        }
    }   
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary file
    FILE* file = fopen(dictionary, "r");
    if(file == NULL)
    {
        fclose(file);
        return false;
    }
    
    // scan file and load the words into hash table
    while(true)
    {
        // create memory for node/word
        node* new_node = malloc(sizeof(node));
        
        // if node is null, unload malloc and close file
        if (new_node == NULL)
        {
            unload();
            fclose(file);
            return false;
        }
        // read word from dictionary into node
        // if word is not successfully read from file, break out of while loop
        if (fscanf(file, "%45s", new_node->word) != 1)
        {
            free(new_node);
            break;
        }
        
        // hashsing word
        int hash = hash_word(new_node->word);
        
        // enter entry into beginning of the linked list in the hash table
        // current entry will point to what the hash table currently points to
        new_node->next =  hashtable[hash];
        
        // store in the hash table at the hash, the current entry
        hashtable[hash] = new_node;
        
        // increment size of hash table
        dictionary_size++; 
    }
    
    // check if program broke out of the while loop from error or end of file
    if(ferror(file))
    {
        unload();
        fclose(file);
        return false;
    }
    
    // close file if successful
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictionary_size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // loop through all buckets in the hash table
    for (int i=0; i < NUM_BUCKETS; i++)
    {
        // for each linked list in hash table, loop over entire linked list and free each node
        node* entry = hashtable[i];
        while (entry != NULL)
        {
            // create temporary variable that stores pointer to next elem. in linked list
            node* next = entry->next;
            // free current element
            free(entry);
            // update current element to point to next element
            entry = next;
        }
    }
    return true;
}