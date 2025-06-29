/* 
 * hashtableest.c - test program for hashtable module
 *
 * usage: read key item pairs from stdin separated by whitespace, each pair on one line 
 *
 * This program is a "unit test" for the hashtable module.
 * It does a decent job of testing the module, but is
 * not a complete test; it should test more corner cases.
 *
 * CS50, Adwiteeya Rupantee Paul, April 2025
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "set.h"
 #include "hashtable.h"
 #include "hash.h"
 #include "file.h"


 static void nameprint(FILE* fp, const char* key, void* item) ;
 static void namedelete(void* item);
 static void itemcount(void* arg, const char* key, void* item);
 

 int main() 
 {
   hashtable_t* hash1;           // one hashtable
   hashtable_t* hash2;           // another hashtable
   char* key = NULL;            // a key in the hashtable
   const int num_slots = 10;       // number of slots put in the bag
   int hashcount = 0;             // number of slots found in a bag
 
   printf("Create first and second hashtables...\n"); //create two hashtables
   hash1 = hashtable_new( num_slots);
   hash2 = hashtable_new( num_slots);
   if (hash1 == NULL) {
     fprintf(stderr, "set_new failed for set1\n");
     return 1;
   }
   if (hash2 == NULL) {
    fprintf(stderr, "set_new failed for set1\n");
    return 1;
  }


  // test the hashtable with unacceptable parameters
   printf("\nTest with null hashtable, good key, good item...\n");
   hashtable_insert(NULL, "Dartmouth", "College");
   printf("test with null key...\n");
   hashtable_insert(hash1, NULL, "College"); 
   printf("test with null item...\n");
   hashtable_insert(hash1, "Dartmouth", NULL); 
   printf("test with null hashtable, null key, null item...\n");
   hashtable_insert(NULL, NULL, NULL);
 
//Count the number of items in the hashtable
   printf("\nCount (should be zero): ");
   hashcount = 0;
   hashtable_iterate(hash1, &hashcount, itemcount);
   printf("%d\n", hashcount);
 
   printf("\nTesting hashtable_insert...\n");
   int keycount = 0;

   FILE* fp = fopen("fp", "w"); //copy the keys in a different file
   char* keys;
   char* items;
    while(scanf("%s %s", &keys, &items) != EOF) { 
      hashtable_insert(hash1, &keys, &items); //inserting from the test file
      fprintf(fp, "%s\n", &keys); 
      keycount = keycount + 1;   
    }
    fclose(fp);

  
 //count the number of items in the hashtable
   printf("\nCount (should be %d): ", keycount);
   hashcount = 0;
   hashtable_iterate(hash1, &hashcount, itemcount);
   printf("%d\n", hashcount);

 //print the hashtable
   printf("\nThe hashtable:\n");
   hashtable_print(hash1, stdout, nameprint);
   printf("\n");

   FILE *fs = fopen("fp", "r");
   char* value;

   //copy the hashtable to another hashtable

   while(fscanf(fs, "%s", &key) != EOF) {
     value = hashtable_find(hash1, &key);
     hashtable_insert(hash2, &key, value);
   }

   fclose(fs);

  //count the number of items in the new hashtable
   printf("\nThe new hashtable:\n");
   printf("Count (should be %d): ", keycount);
   hashcount = 0;
   hashtable_iterate(hash2, &hashcount, itemcount);
   printf("%d\n", hashcount);  

   //print the new hashtable
   hashtable_print(hash2, stdout, nameprint);
   printf("\n");

   //delete the hashtables
   printf("\ndelete the hashtables...\n");
   hashtable_delete(hash1, namedelete);
   hashtable_delete(hash2, namedelete); 
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
 
 // print a key and item, with commas and parentheses.
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
 
