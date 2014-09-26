#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  char *key;
  char *value;
  struct node *right;
  struct node *left;
  //color?
} *Node;

Node cursor = NULL;
Node current_list = NULL; 

//Creates an empty node
Node empty_node(){
  Node empty = malloc(sizeof(struct node));
  return empty;
}


char *clone_string(char *input_string){
  char *copy = malloc(strlen(input_string)+1);
  strcpy(copy, input_string);
  return copy;
}

//Adds an entry (key, value) into the database. 
void add_node(char input_key[], char input_value[]);

//Searches for a matching key in the database and returns a pointer to it's value, NULL if not found.
char *search_entry(char input_buffer[]){
  cursor = current_list;
  while (strcmp(input_buffer, cursor->key) != 0){
    if (input_buffer>cursor->key){
      if (cursor->right){
        cursor = cursor->right;
      }
      else{
        return NULL;
      }
    }
    else{
      if (cursor->left)
        {
          cursor = cursor->left;
        }
      else{
        return NULL;
      }
    }
  } 
  return cursor->value;
}

//Changes the value of a specified key in an entry
void update_value(char *old_value, char *new_value); 

//Searches for input_key, removes the node
void remove_node(char *input_key, char *output_buffer);

//Prints out the database to the standard ouput
void print_database();
