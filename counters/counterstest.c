/* 
 * counterstest.c - test program for counters module
 *
 * usage: read integers from stdin, each on one line
 *
 * This program is a "unit test" for the counters module.
 * It does a decent job of testing the module, but is
 * not a complete test; it should test more corner cases.
 *
 * Adwiteeya Rupantee Paul, April 2025
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "counters.h"
 #include "file.h"

 
 static void itemcount(void* arg, const int key, const int count);
 
 /* **************************************** */
 int main() 
 {
  counters_t* ctrs1 = NULL;           // one counter
  counters_t* ctrs2 = NULL;           // another counter
   int num;           // a number in the counter
   int number;        // a number in the counter
   int numcount = 0;         // number of (not unique) integers put in the counter
   int ctrscount = 0;       // number of (not unique) integers found in a counter


   //create first counter
   printf("Create first counter...\n");
   ctrs1 = counters_new();
   if (ctrs1 == NULL) {
     fprintf(stderr, "counters_new failed for ctrs1\n");
     return 1;
   }

   // test the counter with unacceptable parameters
 
   printf("\nTest with null counters, good key...\n");
   counters_add(NULL, 1);
   printf("test with negative key...\n");
   counters_add(ctrs1, -3); 
   printf("test with null counter, negative key...\n");
   counters_add(NULL, -3);
 
   //Count the number of items in the counter
   printf("\nCount (should be zero): ");
   ctrscount = 0;
   counters_iterate(ctrs1, &ctrscount, itemcount);
   printf("%d\n", ctrscount);
 
   printf("\nTesting counters_insert...\n");
   // read integers from stdin
   numcount = 0;
   while(scanf("%d ", &num) != EOF){
      int count = counters_add(ctrs1, num);  //inserting from the test file   
        numcount++;
   }

   // count the number of items in the counter
   printf("\nCount (should be %d): ", numcount);
   counters_iterate(ctrs1, &ctrscount, itemcount);
   printf("%d\n", ctrscount);

   // print the counter
   printf("\nThe counter:\n");
   counters_print(ctrs1, stdout);
   printf("\n");


  // copy keys to a new counter
   printf("\nMove items to a new counter...\n");
   ctrs2 = counters_new();
   if (ctrs2 == NULL) {
     fprintf(stderr, "counters_new failed for ctrs2\n");
     return 2;
   }

   FILE *file;         
   file = fopen("test.names", "r");
 
   // read from the file
     while (fscanf(file, "%d ", &number) != EOF) {
     int value = counters_get(ctrs1, number); //get the value of the key
     counters_set(ctrs2, number, value); //enter the key and value in the new counter
   }
   

   // delete the first counter
    counters_delete(ctrs1);
    ctrs1 = NULL;

   //number of items in the old counter
    printf("\nThe old counter:\n");
    printf("Count (should be 0): ");
    ctrscount = 0;
    counters_iterate(ctrs1, &ctrscount, itemcount);
    printf("%d\n", ctrscount); 
    
    //print the old counter
    printf("\nPrinting old counter:\n");
    counters_print(ctrs1, stdout);
    printf("\n");


   // count the number of items in the new counter
   printf("\nThe new counter:\n");
   printf("Count should be %d", numcount);
   printf("\n");
   ctrscount = 0;
   counters_iterate(ctrs2, &ctrscount, itemcount);
   printf("%d\n", ctrscount);

   //print the new counter
   printf("\nPrinting new counter:\n");  
   counters_print(ctrs2, stdout);
   printf("\n");
 
   //delete the counters
   printf("\ndelete the counters...\n");
   counters_delete(ctrs1);
   counters_delete(ctrs2);
 
   return 0;
 }
 
 
 /* count the non-null items in the bag.
  * note here we don't care what kind of item is in bag.
  */

 static void itemcount(void* arg, const int key, const int count)
 {
   int* nitems = arg;

   if (nitems != NULL){
   (*nitems)++;
 }

   else {
     fprintf(stderr, "itemcount: null argument\n");
   }
  }
 


 
