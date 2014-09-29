#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  char *key;
  char *value;
  struct node *right;
  struct node *left;
} *Node;

Node cursor = NULL;
Node current_tree = NULL; 

//Creates an empty tree/node
Node empty(){
  Node empty = malloc(sizeof(struct node));
  return empty;
}

char *clone_string(char *input_string){
  char *copy = malloc(strlen(input_string)+1);
  strcpy(copy, input_string);
  return copy;
}


//Searches for a matching key in the database and returns a pointer to it's value, NULL if not found.
Node *search_entry(char *input_key, Node *tree){
    while (tree != NULL){
      int compare = strcmp(input_key, (*tree)->key);
    if (compare == 0){
      return tree;
    }else{
     *tree = compare > 0 ? (*tree)->right: (*tree)->left;
    }
    }
  return &*tree;
}


Node create_node(char *input_key, char *input_value){
  Node new_node = empty();
r  new_node->key = clone_string(input_key);
  new_node->value = clone_string(input_value);
  new_node->right = empty();
  new_node->left = empty();
  return new_node;
}
//Funkar kanske
int depth(Node tree){
  int count_right = 0;
  int count_left = 0;
  if (tree->right == NULL){
    return 1;
  }
  else{
    count_right = 1 + depth(tree->right);
  }
  if (tree->left == NULL){
    return 1;
  }
  else{
    count_left = 1 + depth(tree->left);
  }
  if (count_left>count_right){
    return count_left;
  }
  else{
    return count_right;
  }
}


int check_parent(Node tree, Node parent){
  if (0<(strcmp(tree->key, parent->key))){
    return 1;
  } 
  else{
    return 0;
  }
}

void balance(Node tree, Node parent){
  int r_or_left = check_parent(tree, parent);
 
  if (tree->left == NULL){
    //case 1
    if (tree->right->left == NULL){
      tree->right->left=tree;

      if (r_or_left){
        parent->right=tree->right;
      }
      else{
        parent->left=tree->right;
      }

      tree->right=NULL;
      tree->left=NULL;
    }
    //case 2tr
    else{
      tree->right->right=tree->right->left;
      tree->right->left=tree;
      
      if (r_or_left){
        parent->right=tree->right;
      }
      else{
        parent->left=tree->right;
      }
      
      tree->right=NULL;
      tree->left=NULL;
    }
  }
  else{
  //case 3
    if (tree->left->right == NULL){
      tree->left->right=tree;

      if (r_or_left){
        parent->right=tree->left;
      }
      else{
        parent->left=tree->left;
      }
      
      tree->right=NULL;
      tree->left=NULL;
      }
    //case 4
    else{
      tree->left->left=tree->left->right;
      tree->left->right=tree;

      if (r_or_left){
        parent->right=tree->left;
      }
      else{
        parent->left=tree->left;
      }
      tree->right=NULL;
      tree->left=NULL;
    }
  }
}

void insert_node(Node new_node, Node tree, Node parent){
  if(tree == NULL){
    tree = new_node;
  }
  else{
    if(0 < strcmp(new_node->key, tree->key)){
      insert_node(new_node, tree->left, tree);
    }
    else{
      insert_node(new_node, tree->right, tree);
    }
  }
  printf("Hej: %s, %s,\n", tree->key, tree->value);
  if (1 < abs(depth(tree->right) - depth(tree->left))){
    balance(tree, parent);
  }
}

//Adds an entry (key, value) into the database. 
void add_node(char *input_key, char *input_value){
  Node new_node = create_node(input_key, input_value);
  printf("Hej: %s, %s,\n", new_node->key, new_node->value);
  insert_node(new_node, current_tree, NULL);
}


//Changes the value of a specified key in an entry
void update_value(char *old_value, char *new_value){
  strcpy(old_value, new_value);
} 


//Searches for input_key, removes the node
void remove_node(char *input_key, char *output_buffer);

//Prints out the database to the standard ouput
void print_database();
