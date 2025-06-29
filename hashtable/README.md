# Hashtable
A `hashtable` is a set of `(key,item)` pairs. It acts just like a `set`, but is far more efficient for large collections.


### Usage

The *hashtable* module, defined in `hashtable.h` and implemented in `hashtable.c`, implements a set of `void*` with `char* keys` based on the hash function defined in `hash.h` and implemented in `hash.c`. The hashtable module exports the following functions:

```c
hashtable_t* hashtable_new(const int num_slots);
bool hashtable_insert(hashtable_t* ht, const char* key, void* item);
void* hashtable_find(hashtable_t* ht, const char* key);
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) );
``` 

### Implementation

We implement this hashtable as a set.
The *hashtable* itself is represented as a `struct hashtable` containing an array. It has the number of slots `num_slots` and an array of pointers to `struct set`s called `struct set* slots`.

Each slot in the array points to a `struct set`, a type declared in `set.h` and defined in `hashtable.c`. The index of the slots for a specific `key` is accessed by the hash function in `hash.h`.  Each `struct set` is a set of `struct setnodes` -- which accumulates any `key`s that have the same index resulting from the hash funciton. 


The `hashtable_insert` method is used to insert a `key` to its appropriate index based on the `hash` function. If the `key` already exists, it returns false, but if it does not exist, it is copied and inserted into the appropriate index.

The `hashtable_find` method returns the item associated with the given key from the hashtable.

The `hashtable_print` method prints (key,item) pairs of a slot, one line per hash slot. If the `hashtable` passed is not a valid pointer, we return "null". And if the output file provided is NULL, we return nothing.

The `hashtable_iterate` method calls the `itemfunc` function on each (key,item) pair by scanning the array slots.

The `hashtable_delete` method scans the array slots and frees the key strings as it proceeds. 

It concludes by freeing the memory allocated in `hashtable_insert`.

### Assumptions

No assumptions beyond those that are clear from the spec.  

Because of the semantics of a *hashtable*, we have great freedom in our implementation. Our set approach keeps it simple.

### Files

* `Makefile` - compilation procedure
* `hashtable.h` - the interface
* `hashtable.c` - the implementation
* `hash.h` - the interface of hash function
* `hash.c` - the implementation of hash function
* `set.h` - the interface of set
* `hashtabletest.c` - unit test driver
* `test.names` - test data
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make hashtable.o`.

### Testing

The `hashtabletest.c` program reads lines from stdin and stuffs them into a hashtable.
It tests a few error and edge cases.
This test is somewhat minimal.
A lot more could be done!

To test, simply `make test`.
See `testing.out` for details of testing and an example test run.
