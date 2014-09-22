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


void clone_string(char point, char *input_key){
  *point = malloc(strlen(input_key)+1);
  strcpy(*point, input_key);
} 

void add_node(char *input_key, char *input_value){
  Node new_node = empty_node();
  
  clone_string((new_node->key), input_key);

  clone_string((new_node->value), input_value);

  new_node->next = current_list; //errorrad
  current_list = new_node; //spars vår data på stacken eller heapen? -HEAPEN!
}


//case 1
int search_entry(char input_buffer[]){
  int found = 0;
  cursor = current_list;
  while(!found && cursor != NULL){
    if(strcmp(input_buffer, cursor->key) == 0){
      found = 1;
      char *node_key = cursor->key;
      char *node_value = cursor->value;
      printf("Found entry:\nkey: %s\nvalue: %s\n", node_key, node_value); //Få ut till db.c istället. Hur?
      return 1;
    }else{
      cursor = cursor->next;
    }
  }
  return 0;
}


 
/* //case 2 */
/* void update_entry_mod(char buffer){ */
  
/*   int found = 0; */
/*   cursor = list; */
/*   while(!found && cursor != NULL){ */
/*     if(strcmp(buffer, cursor->key) == 0){ */
      
/*       printf("key: %s\nvalue: %s\n\n", cursor->key, cursor->value); */
/*       found = 1; */
/*     } */
/*     else{ */
/*       cursor = cursor->next; */
/*     } */
/*   } */
/*   if(!found){ */
    
/*   } */
/*   else{ */
/*     printf("Enter new value: "); */
/*     read_line(buffer, 128, stdin); */
/*     free(cursor->value); */
/*     cursor->value = malloc(strlen(buffer) + 1); */
/*     strcpy(cursor->value, buffer); */
/*     puts("Value inserted successfully!"); */
/*   } */
/* } */


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



