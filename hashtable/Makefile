# Makefile for 'hashtable' module
#
# Adwiteeya Rupantee Paul, April 2025


OBJS = hashtabletest.o hashtable.o hash.o set.o ../lib/file.o 
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make

hashtabletest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtabletest.o: hash.h set.h ../lib/file.h
hashtable.o: set.h  ../lib/file.h
hashtable.o: hash.h
hashtable.o: hashtable.h
set.o: set.h
hash.o: hash.h
../lib/file.o: ../lib/file.h


# expects a file `test.names` to exist; it can contain any text.
test: hashtabletest test.names
	./hashtabletest < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f hashtabletest
	rm -f core
