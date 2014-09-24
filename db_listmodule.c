#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//implementationen

extern char buffer[128]; // Globala eller inte?


//Datatype key * value * next node


//gömma typedef och lägga i .h filen.  
typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;


Node list = NULL;
Node cursor = NULL;
Node current_list = NULL; //Varför går det inte att ha den här som pekare eller på heapen?

//Malloc return en pointer
Node empty_node(){
  Node empty = malloc(sizeof(struct node));
  return empty;
}


/* void clone_string(char cloned){ */
/*   malloc(strlen(cloned) + 1); */
/*   strcpy(new_node->key, cloned); */
/*   return new_node; */
/* } */

char *clone_string(char *input_string){
  char *copy = malloc(strlen(input_string)+1);
  strcpy(copy, input_string);
  return copy;
}  

void add_node(char *input_key, char *input_value){
  Node new_node = empty_node();
  new_node->key = clone_string(input_key);
  new_node->value = clone_string(input_value);
  new_node->next = current_list; //errorrad
  current_list = new_node; 
}


//case 1
int search_entry(char input_buffer[],char *output_buffer){
  int found = 0;
  cursor = current_list;
  while(!found && cursor != NULL){
    if(strcmp(input_buffer, cursor->key) == 0){
      found = 1;
      strcpy(output_buffer, cursor->value);
    }else{
      cursor = cursor->next;
    }
  }
  return found;
}


 
//case 2 
void *update_value(char *old_value, char *new_value){
  //cursor = current_list;
  //old_value = clone_string(new_value);
  strcpy(old_value, new_value);
  printf("Updated %s \n with %s", old_value, new_value);
}
  

/* //case 3 */
/* void insert_entry(){ */
/*   printf("Enter key: "); */
/*   read_line(buffer, 128, stdin); */
/*   puts("Searching database for duplicate keys..."); */
/*   int found = 0; */
/*   cursor = list; */
/*   while(!found && cursor != NULL){ */
/*     if(strcmp(buffer, cursor->key) == 0){ */
/*       printf("key \"%s\" already exists!\n", cursor->key); */
/*       found = 1; */
/*     }else{ */
/*       cursor = cursor->next; */
/*     } */
/*   } */
/*   if(!found){ // Insert new node to the front of the list */
/*     puts("Key is unique!\n"); */
/*     Node new_node = malloc(sizeof(struct node)); */
/*     new_node->key = malloc(strlen(buffer) + 1); */
/*     strcpy(new_node->key, buffer); */
/*     printf("Enter value: "); */
/*     read_line(buffer, 128, stdin); */
/*     new_node->value = malloc(strlen(buffer) + 1); */
/*     strcpy(new_node->value, buffer); */
/*     new_node->next = list; */
/*     list = new_node; */
/*     puts(""); */
/*     puts("Entry inserted successfully:"); */
/*     printf("key: %s\nvalue: %s\n", list->key, list->value); */
/*   } */
/* } */


/* //case 4 */
/* void delete_entry(){ */
/*   printf("Enter key: "); */
/*   read_line(buffer, 128, stdin); */
/*   puts("Searching database...\n"); */
/*   int found = 0; */
/*   cursor = list; */
/*   Node prev = NULL; */
/*   while(!found && cursor != NULL){ */
/*     if(strcmp(buffer, cursor->key) == 0){ */
/*       if(prev == NULL){ // Delete first node */
/*         list = cursor->next; */
/*       }else{ */
/*         prev->next = cursor->next; */
/*       } */
/*       found = 1; */
/*       printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", cursor->key, cursor->value); */
/*     }else{ */
/*       prev = cursor; */
/*       cursor = cursor->next; */
/*     } */
/*   } */
/*   if(!found){ */
/*     printf("Could not find an entry matching key \"%s\"!\n", buffer); */
/*   } */
/* } */


// case 5
void print_database(){
  cursor = current_list;
  while(cursor != NULL){
    puts(cursor->key);
    puts(cursor->value);
    cursor = cursor->next;
  }
}



