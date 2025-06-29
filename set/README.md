# Set

A `set` maintains an unordered collection of (key,item) pairs. Any given key can only occur in the set once.
The `set` starts empty, grows as the caller inserts new (key,item) pairs.
The caller can retrieve items by asking for their key, but cannot remove or update pairs. Items are distinguished by their key.

### Usage

The *set* module, defined in `set.h` and implemented in `set.c`, implements a set of `void*` items with `char*` keys, and exports the following functions through `set.h`:

```c
set_t* set_new(void);
bool set_insert(set_t* set, const char* key, void* item);
void* set_find(set_t* bag, const char* key);
void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item) );
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void set_delete(set_t* set, void (*itemdelete)(void* item) );

```

### Implementation

We implement this set as a linked list.
The *set* itself is represented as a `struct set` containing a pointer to the head of the list; the head pointer is NULL when the set is empty.

Each node in the list is a `struct setnode`, a type defined internally to the module.
Each setnode includes a pointer to the `char* key`,the `void* item` and a pointer to the next setnode on the list.

To insert a new item by `set_insert` in the set we create a new setnode to hold the `key` and `item`, and insert it at the head of the list.

To find an item associated with a given key by `set_find`, we look for the key in the setnodes.

Of course, if the list is empty or if the key is not found, we return NULL instead.
We do not remove the item from the set. 

The `set_print` method prints a little syntax around the list, and between items, but mostly calls the `itemprint` function on each item by scanning the linked list.

The `set_iterate` method calls the `itemfunc` function on each item by scanning the linked list.

The `set_delete` method calls the `itemdelete` function on each item by scanning the linked list, freeing setnodes as it proceeds.
It concludes by freeing the `struct set`.

### Assumptions

No assumptions beyond those that are clear from the spec.

The `key` inserted cannot be NULL, and thus a NULL return from `set_find` must indicate either empty set, NULL key passed, or the key does not exist; not simply a NULL `item` coming out of the set.

Because of the semantics of a *set*, we have great freedom in our implementation.
Our linked-list approach follows the bag template, but does not exactly implement a stack as even though `set_insert` pushes a new item on the stack, there is no pop-aligned method that would pop the top item off the stack.

### Files

* `Makefile` - compilation procedure
* `set.h` - the interface
* `set.c` - the implementation
* `settest.c` - unit test driver
* `test.names` - test data
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make set.o`.

### Testing

The `settest.c` program reads lines from stdin and stuffs them into a set.
It tests a few error and edge cases.
This test is somewhat minimal.
A lot more could be done!

To test, simply `make test`.
See `testing.out` for details of testing and an example test run.
