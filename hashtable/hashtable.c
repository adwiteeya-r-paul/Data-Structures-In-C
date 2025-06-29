* 
 * hashtable.c - source file for hashtable module
 *
 * A *hashtable* is a set of (key,item) pairs.  It acts just like a set, 
 * but is far more efficient for large collections.
 *
 * Adwiteeya Rupantee Paul, April 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable.h"
#include "hash.h"
#include "set.h"


/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/

typedef struct setnode {
    char* key;               // key string
    void* item;             // pointer to item
    struct setnode* next;   // next node in the list
} setnode_t;

typedef struct set{
    struct setnode* head;   // head of the list of items in set 
} set_t;


/**************** global types ****************/

typedef struct hashtable{
    int num_slots;      // number of slots in the hashtable
    struct set* slots[]; // array of pointers to hashnodes
} hashtable_t;


/**************** global functions ****************/
/* that is, visible outside this file */
/* see set.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
/* see hashtable.h for comments about exported functions */
static bool slots_check(hashtable_t* ht, int index);



/**************** slots_check() ****************/
/* check if the slots are allocated successfully */
static bool slots_check(hashtable_t* ht, int index) {
    if (ht->slots[index] == NULL) {
        for (int j = 0; j < index; j++) {
            free(ht->slots[j]); // free previously allocated sets
        }
        free(ht->slots); // free the slots array
        free(ht); // free the hashtable structure
        return false; // error allocating memory for set
    }
    return true; // all slots are allocated successfully
}


/**************** hashtable_new() ****************/
/* see hashtable.h for description */
hashtable_t*
hashtable_new(const int num_slots)
{
    hashtable_t* ht = malloc(sizeof(hashtable_t));
    if (ht == NULL) {
        return NULL;              // error allocating hashtable
    } else {
        // initialize contents of hashtable structure
        ht->num_slots = num_slots;
        if (ht->slots == NULL) {
            free(ht); // free the hashtable if slots allocation fails
            return NULL; // error allocating memory for slots
        }
        ht->slots[num_slots]; // initialize slots to NULL

        for (int i = 0; i <= num_slots; i++) {
            ht->slots[i] = set_new(); // create a new set for each slot
            if (slots_check(ht, i) == false) {
                return NULL; // check if sets are allocated successfully
            }
        }
        // check if the hashtable, key, and item are not NULL
        return ht;
    }
}

/**************** hashtable_insert() ****************/
/* see hashtable.h for description */

bool hashtable_insert(hashtable_t* ht, const char* key, void* item){
    // check if the hashtable, key, and item are not NULL
    if (ht != NULL && key != NULL && item != NULL){
        // calculate the hash value for the key
        unsigned long hash = hash_jenkins(key, ht->num_slots);  
        // insert the item into the appropriate slot
        return set_insert(ht->slots[hash], key, item); //if key exists, return false
        } else {
            return false; 
        }
      
    return false; // failure

}

/**************** hashtable_find() ****************/
/* see hashtable.h for description */

void* hashtable_find(hashtable_t* ht, const char* key){
    // check if the hashtable and key are not NULL
    if (ht != NULL && key != NULL) {
        // calculate the hash value for the key
        unsigned long hash = hash_jenkins(key, ht->num_slots);
        // find the item in the appropriate slot
        return set_find(ht->slots[hash], key); //if key exists, return item
    } else {
        return NULL; // failure
    }
}

/**************** hashtable_print() ****************/
/* see hashtable.h for description */

void hashtable_print(hashtable_t* ht, FILE* fp, 
    void (*itemprint)(FILE* fp, const char* key, void* item)){
    // check if the hashtable and file pointer are not NULL
    if (ht != NULL && fp != NULL) {
        // print the hashtable
        for (int i = 0; i < ht->num_slots; i++) {
            set_print(ht->slots[i], fp, itemprint); // print each slot
            if (ht->slots[i] != NULL) {
                fprintf(fp, "\n"); // print newline after each slot
            }
        }
    } else if (fp == NULL) {
        fprintf(fp, "(null)\n"); // print null if hashtable is NULL
    }
}

/**************** hashtable_iterate() ****************/
/*see hashtable.h for description*/

void hashtable_iterate(hashtable_t* ht, void* arg,
    void (*itemfunc)(void* arg, const char* key, void* item) ){
    // check if the hashtable and item function are not NULL
    if (ht != NULL && itemfunc != NULL) {
        // iterate over each slot in the hashtable
        for (int i = 0; i < ht->num_slots; i++) {
            set_iterate(ht->slots[i], arg, itemfunc); // call item function
        }
    }
}

/**************** hashtable_delete() ****************/
/* see hashtable.h for description */


void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item)){
    // check if the hashtable is not NULL
    if (ht != NULL && itemdelete != NULL) {
        // iterate over each slot in the hashtable
        for (int i = 0; i < ht->num_slots; i++) { 
            set_delete(ht->slots[i],itemdelete); // delete each slot
        }
    }
    free(ht->slots);
    free(ht);
}
