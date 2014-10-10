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

char *extract_value(struct node *db){
  return db->value;
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

//1 is right, 0 is false.
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

struct node *insert_node(Node new_node, Node tree, Node parent){
  struct node *tmp;
  
  if(tree == NULL){
    tree = new_node;
    
    if (parent){
      int r_or_left = check_parent(tree, parent);
      if (r_or_left){
        parent->right = new_node;
      }
      else{
        parent->left = new_node;
      }
      printf("Rekursion key: %s, value: %s\n", tree->key, tree->value);
    }
  }
  else if (check_parent(new_node, tree)){ 
    tmp = insert_node(new_node, tree->right, tree);
      
  }
  else{
    tmp = insert_node(new_node, tree->left, tree);
  }
  
  //Undersök om trädet behöver balanseras och gör det isåfall
  if (1 < abs(depth(tree->right) - depth(tree->left))){
    balance(tree, parent);
  }
 
  if(parent){
    return parent;
  }
  else{
    return tree;
  } 
}



//Adds an entry (key, value) into the database. 
struct node *add_node(char *input_key, char *input_value, struct node *db){
  Node new_node = create_node(input_key, input_value);
  db = insert_node(new_node, db, NULL);
  printf("Det här är rooten ANNA, %s, %s \n", db->key, db->value);
  return db;
}

//Searches for a matching key in the database and returns a pointer to it's value, NULL if not found.
struct node *search_entry(char *input_buffer, struct node *db){
  struct node *cursor = db;
  while (strcmp(input_buffer, cursor->key) != 0){
    if (0 < strcmp(input_buffer, cursor->key)){
      if (cursor->right != NULL){
        cursor = cursor->right;
      }
      else{
        return NULL;
      }
    }
    else{
      if (cursor->left != NULL){
          cursor = cursor->left;
        }
      else{
        return NULL;
      }
    }
  }
  printf("search_entry:\nkey: %s\nvalue: %s\n", cursor->key, cursor->value);   
  return cursor;
}

//recursive search entry
struct node *rec_search_entry(char *input_buffer, struct node *db){
  if (strcmp(input_buffer, db->key) != 0){
    if (0 < strcmp(input_buffer, db->key)){
      if (!(db->right)){
        rec_search_entry(input_buffer, db->right);
      }
    }
    else{
      if (!(db->left)){
        rec_search_entry(input_buffer, db->left);
      }
    }
  }
  return db;
}
 

//Changes the value of a specified key in an entry
void update_value(char *old_value, char *new_value){
  strcpy(old_value, new_value);
} 


//Searches for input_key, removes the node
void remove_node(char *input_key, char *output_buffer);

//Prints out the database to the standard ouput
void print_database_mod(struct node *db){
  if (db){
    printf("Key: %s Value: %s\n", db->key, db->value);
    print_database_mod(db->left);
    print_database_mod(db->right);
  }
}
