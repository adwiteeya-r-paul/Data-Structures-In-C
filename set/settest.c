/* 
 * settest.c - test program for set module
 *
 * usage: read key item pairs from stdin separated by whitespace, each pair on one line 
 *
 * This program is a "unit test" for the set module.
 * It does a decent job of testing the module, but is
 * not a complete test; it should test more corner cases.
 *
 * CS50, April 2025
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "set.h"
 #include "file.h"


 static void nameprint(FILE* fp, const char* key, void* item) ;
 static void namedelete(void* item);
 static void itemcount(void* arg, const char* key, void* item);
 

 int main() 
 {
   set_t* set1;           // one set
   set_t* set2;           // another set
   char* key = NULL;            // a key in the bag
   int keycount = 0;            // number of names put in the set
   int setcount = 0;             // number of names found in a set
 

   //create first two sets
   printf("Create first two sets...\n");
   set1 = set_new();
   set2 = set_new();
   if (set1 == NULL) {
     fprintf(stderr, "set_new failed for set1\n");
     return 1;
   }
   if (set2 == NULL) {
    fprintf(stderr, "set_new failed for set2\n");
    return 1;
  }


   // test the set with unacceptable parameters
 
   printf("\nTest with null set, good key, good item...\n");
   set_insert(NULL, "Dartmouth", "College");
   printf("test with null key...\n");
   set_insert(set1, NULL, "College"); 
   printf("test with null item...\n");
   set_insert(set1, "Dartmouth", NULL); 
   printf("test with null set, null key, null item...\n");
   set_insert(NULL, NULL, NULL);
 

   //Count the number of items in the set

   printf("\nCount (should be zero): ");
   setcount = 0;
   set_iterate(set1, &setcount, itemcount);
   printf("%d\n", setcount);
 
   printf("\nTesting set_insert...\n");

   FILE* fp = fopen("fp", "w"); //copy the keys in a different file
   char* keys;
   char* items;
    while(scanf("%s %s", &keys, &items) != EOF) {
      set_insert(set1, &keys, &items); //inserting from the test file
      fprintf(fp, "%s\n", &keys);
      keycount++;   
    }
    fclose(fp);

  //count the number of items in the set
 
   printf("\nCount (should be %d): ", keycount);
   setcount = 0;
   set_iterate(set1, &setcount, itemcount);
   printf("%d\n", setcount);

   //print the set
 
   printf("\nThe set:\n");
   set_print(set1, stdout, nameprint);
   printf("\n");

   FILE *fs = fopen("fp", "r");
   char* value;

   //copy the set to another set
   while(fscanf(fs, "%s", &key) != EOF) {
     value = set_find(set1, &key);
     set_insert(set2, &key, value);
   }

   fclose(fs);

   //count the number of items in the new set
  
   printf("\nThe new set:\n");
   printf("Count (should be %d): ", keycount);
   setcount = 0;
   set_iterate(set2, &setcount, itemcount);
   printf("%d\n", setcount);  

   //print the new set
   set_print(set2, stdout, nameprint);
   printf("\n");

   //delete the sets

   printf("\ndelete the sets...\n");
   set_delete(set1, namedelete);
   set_delete(set2, namedelete); 
   return 0;
  }
  


  
 
 
 /* count the non-null items in the bag.
  * note here we don't care what kind of item is in bag.
  */

 static void itemcount(void* arg, const char* key, void* item)
{
   int* nitems = arg;
 
   if (nitems != NULL && key != NULL && item != NULL) {
     (*nitems)++;
 }
}
 
 // print a key, item pair
 void nameprint(FILE* fp, const char* key, void* item)
 {
   const char* name1 = key;
   char* name2 = item; 
   if (name1 == NULL|| name2 == NULL) {
     fprintf(fp, "(null key or item)");
   }
   else {
     fprintf(fp, "(%s,%s)", name1, name2); 
   }
 }
 
 // delete an item 
 void namedelete(void* item)
 {
     free(item);    
 }
 
