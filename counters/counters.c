/* 
 * counters.c - source file for counters module
 *
 * A "counter set" is a set of counters, each distinguished by an integer key.
 * It's a set - each key can only occur once in the set - but instead of
 * storing (key,item) pairs, it tracks a counter for each key.  It starts
 * empty. Each time `counters_add` is called on a given key, that key's
 * counter is incremented. The current counter value can be retrieved by
 * asking for the relevant key.
 * 
 * Adwiteeya Rupantee Paul, April 2025
 */

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "counters.h"


/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct countersnode {
    int key;                 // key 
    int count;                // counter value
    struct countersnode *next;       // link to next node
  } countersnode_t;

  /**************** global types ****************/

typedef struct counters {
    struct countersnode* head;   // head of the list of items in set 
} counters_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see counter.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static countersnode_t* countersnode_new(const int key, int count);

/**************** counter_new() ****************/
/* see counter.h for description */
counters_t*
counters_new(void)
{
    counters_t* ctrs = malloc(sizeof(counters_t));

    if (ctrs == NULL) {
        return NULL;              // error allocating counter
    } else {
        // initialize contents of counter structure
        ctrs->head = NULL;
        return ctrs;
    }
}

/**************** counternode_new() ****************/
/* allocate and initialize a counternode */

static countersnode_t*  // not visible outside this file
countersnode_new(const int key, int count)
{
    countersnode_t* node = malloc(sizeof(countersnode_t));

    if (node == NULL) {
        // error allocating memory for node; return error
        return NULL;
    } else {
        node->key = key;           // set the key 
        node->count = count;       // set the count 
        node->next = NULL;         // initialize next pointer to NULL
        return node;
    }
}

/**************** counter_add() ****************/
/*see counter.h for description */

int counters_add(counters_t* ctrs, const int key)
{
    if (ctrs == NULL || key < 0) {
        return 0; // error
    } else {
        // check if the key already exists
        for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
            if (node->key == key) {
                // key already exists, increment the count
                node->count = node->count + 1;
                return node->count;
            }
        }
        // key does not exist, create a new counternode
        countersnode_t* new_node = countersnode_new(key, 1);
        if (new_node == NULL) {
            return 0; // error allocating memory
        }

        int value = new_node->count; // return the new count
        new_node->next = ctrs->head; // add to the head of the list
        ctrs->head = new_node;
        return value;

    }
}


/**************** counter_get() ****************/
/*see counter.h for description */

int counters_get(counters_t* ctrs, const int key)
{
    if (ctrs == NULL || key < 0) {
        return 0; // error
    } else {
        // check if the key already exists
        for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
            if (node->key == key) {                
                return node->count; // found the item
            }
        }
        return 0;              // key not found
    }
}


/**************** counter_set() ****************/
/*see counter.h for description */

bool counters_set(counters_t* ctrs, const int key, const int count)
{
    if (ctrs == NULL || key < 0 || count < 0) {
        return false; // error
    } else {
        // check if the key already exists
        for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
            if (node->key == key) {
                // key already exists, update the count
                node->count = count;
                return true;
            }
        }
        // key does not exist, create a new counternode
        countersnode_t* new_node = countersnode_new(key, count);
        if (new_node == NULL) {
            return false; // error allocating memory
        }
        new_node->next = ctrs->head; // add to the head of the list
        ctrs->head = new_node;
        return true; // success
    }
}

/**************** counter_print() ****************/
/*see counter.h for description */

void counters_print(counters_t* ctrs, FILE* fp)
{
    if (ctrs != NULL && fp != NULL) {
        // print each node in the list
        fputc('{', fp);
        for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
            fprintf(fp, "%d", node->key);
            fputc('=', fp);
            fprintf(fp, "%d", node->count);
            if (node->next != NULL) {
                fputc(',', fp);
            }
        }
        fputc('}', fp);
    }
    else if (ctrs == NULL) {
        fputs("(null)", fp);
    }
}


/**************** counter_iterate() ****************/
/*see counter.h for description */

void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count))
{
    if (ctrs != NULL && itemfunc != NULL) {
        // call itemfunc with arg, on each item
        for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
            (*itemfunc)(arg, node->key, node->count);
        }
    }
}
/**************** counter_delete() ****************/
/*see counter.h for description */

void counters_delete(counters_t*ctrs){
    if (ctrs != NULL) {
        // delete each node in the list
        for (countersnode_t* node = ctrs->head; node != NULL; ) {
            countersnode_t* next = node->next; // save the next node
            free(node);                  // free the current node
            node = next;                    // move to the next node
        }
        free(ctrs);                    // free the counter set itself
    }
}















  
