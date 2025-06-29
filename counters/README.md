# Counters

A `counter` set is a set of counters, each distinguished by an integer key. It's a set - each `key` can only occur once in the set - and it tracks a counter for each key. It starts empty. Each time `counters_add` is called on a given key, the corresponding `counter` is incremented. The current `counter` value can be retrieved by asking for the relevant `key`.

### Usage

The *counter* module, defined in `counter.h` and implemented in `counter.c`, implements a counter of `const int count`, for `const int key` and exports the following functions:

```c
counters_t* counters_new(void);
int counters_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_print(counters_t* ctrs, FILE* fp);
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count));
void counters_delete(counters_t* ctrs);
```

### Implementation

We implement this counter as a linked list.
The *counter* itself is represented as a `struct counter` containing a pointer to the head of the list; the head pointer is NULL when the counter is empty.

Each node in the list is a `struct counternode`, a type defined internally to the module.
Each counternode includes a `const int key` for an integer, a `const int count` keeping count of that integer and a pointer to the next counternode on the list.


The `counters_add` method is used to increment the counter indicated by key. To add a new integer in the counterset we create a new counternode to hold the integer as the `key`, and insert it at the head of the list with a `count` of 1. If the `key` already exists, then we do not add a node, but only increase its `count` by 1. The integer has to be zero or positive as the counterset only accepts zero or positive keys. The method returns the current `count` for that `key`.


The `counters_get` method is used to return current value of counter associated with the given key. To get the `count` of an integer `key` in the counterset, we find the `key` and check its `count`. Of course, if the key does not exist or no key is passed or the set is empty, we return NULL instead.

The `counters_set` method is used to set the current value of counter associated with the given key. To add a new integer in the counterset we create a new counternode to hold the integer as the `key`, and insert it at the head of the list with a `count` of 1. If the `key` already exists, then we do not add a node, but only set its `count` to the given `count` value by the caller.
The `key` has to be zero or positive as the counterset only accepts zero or positive keys. The method returns a boolean value true if it's successful and otherwise false if it's not. 

The `counters_print` method prints a little syntax around the list, and between items -- a comma separated list of key=counter pairs. If the `counterset` passed is not a valid pointer, we return "null". And if the output file provided is NULL, we return nothing.

The `counters_iterate` method calls the `itemfunc` function on each item by scanning the linked list.

The `counters_delete` method scans the linked list and frees counternodes as it proceeds.
It concludes by freeing the `struct counter`.

### Assumptions

No assumptions beyond those that are clear from the spec. Counter only accepts zero or positive keys. 

Because of the semantics of a *counters*, we have great freedom in our implementation. Our linked-list approach keeps it similar to the implementation of set. 

### Files

* `Makefile` - compilation procedure
* `counters.h` - the interface
* `counters.c` - the implementation
* `counterstest.c` - unit test driver
* `test.names` - test data
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make counters.o`.

### Testing

The `counterstest.c` program reads integers from stdin and stuffs them into a counterset, then increases the counter everytime there is a repetition.
It tests a few error and edge cases.
This test is somewhat minimal.
A lot more could be done!

To test, simply `make test`.
See `testing.out` for details of testing and an example test run.
