#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  char *key;
  char *value;
  struct node *right;
  struct node *left;
} *Node;

/* typedef struct tree{ */
/*   Node *root; */
/* }*Tree; */

Node cursor = NULL;
Node current_tree = NULL; 

//Creates an empty node
Node empty_node(){
  Node empty = malloc(sizeof(struct node));
  return empty;
}

/* Tree empty_tree(){ */
/*   Tree empty = malloc(sizeof(struct tree)); */
/*   empty->root = NULL; */
/* }  */

char *clone_string(char *input_string){
  char *copy = malloc(strlen(input_string)+1);
  strcpy(copy, input_string);
  return copy;
}

Node create_node(char *input_key, char *input_value){
  Node new_node = empty_node();
  new_node->key = clone_string(input_key);
  new_node->value = clone_string(input_value);
  new_node->right = NULL;
  new_node->left = NULL;
  return new_node;
}
//Funkar kanske
int depth(Node current_tree){
  int count_right = 0;
  int count_left = 0;
  if (current_tree->right == NULL){
    return 1;
  }
  else{
    count_right = 1 + depth(current_tree->right);
  }
  if (current_tree->left == NULL){
    return 1;
  }
  else{
    count_left = 1 + depth(current_tree->left);
  }

  if (count_left>count_right){
    return count_left;
  }
  else{
    return count_right;
  }
}

void balance(Node tree){
  if (tree->left == NULL){
  //case 1
    if (tree->right->left == NULL){
      
      }
    //case 2
    else{

    }
  
  }
  else{
  //case 3
    if (tree->left->right == NULL){
      
      }
    //case 4
    else{
      
    }
  }
}

void insert_node(Node new_node, Node tree, Node parent){
  if(tree == NULL){
    tree = new_node;
  }
  if(0 < strcmp(new_node->key, tree->key)){
    insert_node(new_node, tree->left, tree);
  }
  else{
    insert_node(new_node, tree->right, tree);
  }
  if (1 < abs(depth(tree->right) - depth(tree->left))){
    balance(tree);
  }
}

//Adds an entry (key, value) into the database. 
void add_node(char *input_key, char *input_value){
  //Lägg noden på rätt plats - check
  //Kolla djupet på "uppåtvägen" om det behöver balanseras
  Node new_node = create_node(input_key, input_value); 
  insert_node(new_node, current_tree, NULL);
  
  if (depth(current_tree));
}

//Searches for a matching key in the database and returns a pointer to it's value, NULL if not found.
char *search_entry(char input_buffer[]){
  cursor = current_tree;
  while (strcmp(input_buffer, cursor->key) != 0){
    if (input_buffer > cursor->key){
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
void update_value(char *old_value, char *new_value){
  strcpy(old_value, new_value);
} 


//Searches for input_key, removes the node
void remove_node(char *input_key, char *output_buffer);

//Prints out the database to the standard ouput
void print_database();
