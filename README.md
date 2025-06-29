# Data structures in C

This program develops some general-purpose data structures that, with modular design, namely `set`, `counters` and `hashtable`. 

### About the data structures

The specific data structures are defined in the sections below. 

### set

A **set** maintains an unordered collection of _(key,item)_ pairs; any given _key_ can only occur in the set once.
It starts out empty and grows as the caller inserts new _(key,item)_ pairs.
The caller can retrieve _items_ by asking for their _key_, but cannot remove or update pairs.
Items are distinguished by their _key_.

Your `set.c` should implement a set of `void*` items with `char*` _keys_, and export exactly the following functions through `set.h` (see that file for more detailed documentation comments):

```c
set_t* set_new(void);
bool set_insert(set_t* set, const char* key, void* item);
void* set_find(set_t* set, const char* key);
void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item) );
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void set_delete(set_t* set, void (*itemdelete)(void* item) );
```

### counters

A **counter set** is a set of counters, each distinguished by an integer _key_.
It's a set - each _key_ can only occur once in the set - and it tracks a *counter* for each _key_.
It starts empty.
Each time `counters_add` is called on a given _key_, the corresponding *counter* is incremented.
The current *counter* value can be retrieved by asking for the relevant _key_.

Your `counters.c` should implement a set of integer counters with `int` _keys_ (where _keys_ must be non-negative) and export exactly the following functions through `counters.h` (see that file for more detailed documentation comments):

```c
counters_t* counters_new(void);
int counters_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_print(counters_t* ctrs, FILE* fp);
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count));
void counters_delete(counters_t* ctrs);
```

### hashtable

A **hashtable** is a set of _(key,item)_ pairs.
It acts just like a *set*, but is far more efficient for large collections.

Your `hashtable.c` should implement a set of `void*` with `char*` _keys_, and export exactly the following functions through `hashtable.h` (see that file for more detailed documentation comments):

```c
hashtable_t* hashtable_new(const int num_slots);
bool hashtable_insert(hashtable_t* ht, const char* key, void* item);
void* hashtable_find(hashtable_t* ht, const char* key);
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) );
```

The starter kit provided code for the hash function and the header files for set and counters.	

### Comparison between the data structures

| Behavior                | **set**| **counters**    | **hashtable** |
|:----------------------- |:------ |:--------------- |:------------- |
| stores an *item*        | yes    | no              | yes           |
| uses a *key*            | yes    | yes             | yes           |
| keeps items in order    | no     | no              | no            |
| retrieval               | by key | by key          | by key        |
| insertion of duplicates | error  | increment count | error         |
	

### General notes for caller

* The caller must pass a pointer to the code; the data structure holds that pointer, and later returns it to the caller in response to an 'extract' or 'find' operation.
* Each of these modules doesn't know, or doesn't care, what kind of things the items are. The module doesn't allocate memory for items, free memory for items, or copy items - it just tracks the *pointer* to the item.
* The caller is responsible for the *item* pointer, which must be allocated by the caller.
The modules' `_delete` function (like a destructor) allows the caller to provide a custom `itemdelete` function that knows how to free any memory consumed by an item.
* For this reason, the caller must avoid inserting the same item (same address) multiple times; later, the `itemdelete` method would be called multiple times on that item... which could lead to trouble.
* Both **set** and **hashtable** work with string-type keys.
* When adding a new item with `set_insert()` or `hashtable_insert()`, both modules make their own copy of the string - presumably in memory allocated by `malloc()`.
* The module is then responsible for this memory - and later freeing it - just like any other memory it allocates.  This 'copy' semantic is convenient for the caller, who need not worry about how to allocate and manage the key string after inserting it into the set or hashtable.

  ### Assumption
* We assume that a non-NULL `key` is a proper C string; that is, it is null-terminated.

 ### Tools used
* We use `valgrind` to test for memory leaks. 

 ### Files in each module
* a header file and a source file. Note: ur **hashtable**, in addition to its header and source file, also has the header and source files of **set** as the **hashtable** uses a **set** struct. 
* a `Makefile` to compile and test the module code.  with the default target building the relevant `.o` file, and two additional "phony" targets: `make clean` that cleans the directory of anything built by Make; and `make test` that compiles and runs a test program with appropriate parameters and inputs.
* a unit-test mechanism as a test driver.
* a `.gitignore`file
* text files used as input for testing.
* `testing.out`, which is the output of running `make test &> testing.out` inside that subdirectory.

## Implementation

We implement the **set** and **counters** as simplified linked lists. The **hashtable** module is an array of pointers to **set**s.
