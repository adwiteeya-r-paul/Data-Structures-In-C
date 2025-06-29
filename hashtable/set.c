/* 
 * set.c - source file for set module
 *
 * A *set* maintains an unordered collection of (key,item) pairs;
 * any given key can only occur in the set once. It starts out empty 
 * and grows as the caller inserts new (key,item) pairs.  The caller 
 * can retrieve items by asking for their key, but cannot remove or 
 * update pairs.  Items are distinguished by their key.
 *
 * Adwiteeya Rupantee Paul, April 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct setnode {
    char* key;               // key string
    void* item;             // pointer to item
    struct setnode* next;   // next node in the list
} setnode_t;

/**************** global types ****************/

typedef struct set {
    struct setnode* head;   // head of the list of items in set 
} set_t;


/**************** global functions ****************/
/* that is, visible outside this file */
/* see set.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
/* see set.h for comments about exported functions */
static setnode_t* setnode_new(const char* key, void* item);


/**************** set_new() ****************/
/* see set.h for description */
set_t*
set_new(void)
{
    set_t* set = malloc(sizeof(set_t));

    if (set != NULL) {
        // initialize contents of set structure
        set->head = NULL;
        return set;
    }
}


/**************** setnode_new() ****************/
/* allocate and initialize a setnode */
static setnode_t*  // not visible outside this file
setnode_new(const char* key, void* item)
{
    setnode_t* node = malloc(sizeof(setnode_t));


    if (node != NULL) {
        node->key = malloc(strlen(key)); // allocate memory for key
        if (node->key == NULL) {
            free(node); // free the node if key allocation fails
            return NULL;    // error allocating memory for key
        }
        strcpy(node->key, key);      // copy the key string
        node->item = item;         // set the item pointer
        node->next = NULL;           // initialize next pointer to NULL
        return node;

    }
}


/**************** set_insert() ****************/
/* see set.h for description */
bool
set_insert(set_t* set, const char* key, void* item)
{
    if (set == NULL) {
        return false;             // bad set
    }
    for (setnode_t* node = set->head; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            return false;         // key already exists
        }
    }
    // check if the set, key, and item are not NULL
    if (set != NULL && key != NULL && item != NULL) {
        // allocate a new node to be added to the list
        setnode_t* new = setnode_new(key, item);
        if (new != NULL) {
            // add it to the head of the list
            new->next = set->head;
            set->head = new;         // success
            return true;
        }
    }
    return false;             // failure
}
/**************** set_find() ****************/
/*see set.h for description*/

void*
set_find(set_t* set, const char* key){
    // check if the set and key are not NULL
    if (set == NULL || key == NULL) {
        return NULL;              // bad set or key
    } else {
        for (setnode_t* node = set->head; node != NULL; node = node->next) {
            if (strcmp(node->key, key) == 0) {
                return node->item; // found the item
            }
        }
        return NULL;              // key not found
    }
}

/**************** set_print() ****************/
/* see set.h for description */
void
set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item) )
{
    if (fp != NULL) {
        if (set != NULL) {
            fputc('{', fp);
            for (setnode_t* node = set->head; node != NULL; node = node->next) {
                // print this node
                if (itemprint != NULL) { // print the node's item 
                    (*itemprint)(fp, node->key, node->item);
                    // check if this is the last node
                    if (node->next == NULL) {
                        break; // last node, don't print a comma
                    }
                    // not the last node, so print a comma
                    fputc(',', fp);
                }
            }
            fputc('}', fp);
        } else {
            fputs("(null)", fp);
        }
    }
}

/**************** set_iterate() ****************/
/* see set.h for description */
void
set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) )
{
    if (set != NULL && itemfunc != NULL) {
        // call itemfunc with arg, on each item
        for (setnode_t* node = set->head; node != NULL; node = node->next) {
            // call the itemfunc with arg, key, and item
            (*itemfunc)(arg, node->key, node->item); 
        }
    }
}
/**************** set_delete() ****************/
/* see set.h for description */
void
set_delete(set_t* set, void (*itemdelete)(void* item) )
{
    if (set != NULL) {
        // delete each node in the list
        for (setnode_t* node = set->head; node != NULL; node = node->next) {
  // delete the item
            if (itemdelete != NULL) {
            node->item = NULL; // set item to NULL
            (*itemdelete)(node->item);
            }
            setnode_t* next = node->next; // save next node
            free(node->key);              // free the key string
            free(node)    ;              // free the node
            node = next;                 // move to next node
        }
        free(set);                      // free the set structure
    }
}
