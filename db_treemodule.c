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
Node current_tree; 

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
  Node right = empty_node();
  right = NULL;
  Node left = empty_node();
  left = NULL;
  
  new_node->right = right;
  new_node->left = left;
  return new_node;
}
//Funkar kanske
int depth(Node tree){
  int count_right = 0;
  int count_left = 0;
  if (tree == NULL){
    return 0;
  }
  
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
    
    printf("Hej insert: %s, %s,\n", tree->key, tree->value);
    printf("Hej2: %s, %s,\n", current_tree->key, current_tree->value);
  }
  else{
    if(0 < strcmp(new_node->key, tree->key)){
      insert_node(new_node, tree->left, tree);
    }
    else{
      insert_node(new_node, tree->right, tree);
    }
  }
  
  if (1 < abs(depth(tree->right) - depth(tree->left))){
    balance(tree, parent);
  }
}

//Adds an entry (key, value) into the database. 
void add_node(char *input_key, char *input_value, Node *tree){
  Node new_node = create_node(input_key, input_value);
  insert_node(new_node, *tree, NULL);

  return tree;
}

//Searches for a matching key in the database and returns a pointer to it's value, NULL if not found.
char *search_entry(char *input_buffer, Node *tree){
  if (tree == NULL){
    return NULL;
  } 
  int compare = strcmp(input_buffer, cursor->key);
  if (compare == 0){//ändra till (!compare)
    return &tree;
  }
  else if (0 < compare){
    search_entry(input_buffer, tree->right);
  }
  else{
    search_entry(input_buffer, tree->left);
  }
}

/* char *search_entry(char *input_buffer, Node *tree){ */
/*   cursor = tree; */
/*   int compare = strcmp(input_buffer, cursor->key);  */
/*   while (compare != 0){ */
/*     if (0 < strcmp(input_buffer, cursor->key)){ */
/*       if (cursor->right != NULL){ */
/*         cursor = cursor->right; */
/*       } */
/*       else{ */
/*         return NULL; */
/*       } */
/*     } */
/*     else{ */
/*       if (cursor->left != NULL){ */
/*           cursor = cursor->left; */
/*         } */
/*       else{ */
/*         return NULL; */
/*       } */
/*     } */
/*   }  */
/*   return cursor->value; */
/* } */

//Changes the value of a specified key in an entry
void update_value(char *old_value, char *new_value){
  strcpy(old_value, new_value);
} 


//Searches for input_key, removes the node
void remove_node(char *input_key, char *output_buffer);

//Prints out the database to the standard ouput
void print_database();
