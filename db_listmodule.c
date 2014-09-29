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
Node current_list = NULL; 

Node empty_node(){
  Node empty = malloc(sizeof(struct node));
  return empty;
}


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
char *search_entry(char *input_key){
  cursor = current_list
  while(strcmp(input_key, cursor->key) != 0){
    if (cursor->next){
    cursor = cursor->next;
    }
    else{
      return NULL;
    }
  }
  return cursor->value;  
}


 
//case 2 
void update_value(char *old_value, char *new_value){
  strcpy(old_value, new_value);
}
  


//case 4
void remove_node(char *input_key, char *output_buffer){
  int found = 0;
  cursor = current_list;
  Node prev = NULL;
  while(!found && cursor != NULL){
    if(strcmp(input_key, cursor->key) == 0){
      if(prev == NULL){ // Delete first node
        current_list = cursor->next;
      }else{
        prev->next = cursor->next;
      }
      found = 1;
      strcpy(output_buffer, cursor->value);
    }else{
      prev = cursor;
      cursor = cursor->next;
    }
  }
}


// case 5
void print_database(){
  cursor = current_list;
  while(cursor != NULL){
    puts(cursor->key);
    puts(cursor->value);
    cursor = cursor->next;
  }
}



