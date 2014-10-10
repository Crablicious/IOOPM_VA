#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bst{
  char *key;
  char *value;
  struct bst *right;
  struct bst *left;
} *Bst;

Bst cursor = NULL;
Bst current_tree = NULL; 

//Creates an empty tree/node
Bst empty(){
  Bst empty = malloc(sizeof(struct bst));
  return empty;
}

<<<<<<< HEAD
=======

>>>>>>> 78bfe15710eca6013f02e13c91771d40728e2740
char *clone_string(char *input_string){
  char *copy = malloc(strlen(input_string)+1);
  strcpy(copy, input_string);
  return copy;
}

Bst create_node(char *input_key, char *input_value){
  Bst new_node = empty();
  new_node->key = clone_string(input_key);
  new_node->value = clone_string(input_value);
  new_node->right = NULL;
  new_node->left = NULL;
  return new_node;
}
<<<<<<< HEAD

int max (int x, int y){
  return x > y ? x : y;
}

int depth(Node tree){
  if (tree == NULL){
    return 0;
  }
  else{
    return 1 + max(depth(tree->left), depth(tree->right));
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
    //case 1 right-right-right
    if (tree->right->left == NULL){
      tree->right->left=tree;

      if (r_or_left){
        parent->right=tree->right;
      }
      else{
        parent->left=tree->right;
      }
      tree->right=NULL;
    }
    //case 2 
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
=======
Bst* search (Bst *tree, char *str)
{
  while(*tree != NULL)
    { 
      int compare = strcmp(str, (*tree)->key);
      if (compare == 0)
	{
	  break;
	}
      else
	{
	  *tree = compare > 0 ? (*tree)->right: (*tree)->left;
	}
>>>>>>> 78bfe15710eca6013f02e13c91771d40728e2740
    }
  return tree;  
}

void insert;

<<<<<<< HEAD
//search_entry kollar redan om noden redan finns
void insert_node(Node new_node, Node *tree, Node parent){
  if(*tree == NULL){
    *tree = new_node;
  }
  else{
    int compare = strcmp(new_node->key, (*tree)->key);
    if(0 < compare){
      insert_node(new_node, &(*tree)->left, *tree);
     }
    else if(0 > compare){
      insert_node(new_node, &(*tree)->right, *tree);
        } 
    if (1 < abs(depth(tree->right) - depth(tree->left))){
      balance(tree, parent);
    }
  }
}
//Adds an entry (key, value) into the database. 
void add_node(char *input_key, char *input_value){
  Node new_node = create_node(input_key, input_value);
  printf("Hej: %s, %s,\n", new_node->key, new_node->value);
  insert_node(new_node, current_tree, NULL);
}
=======

void update;
void delete;
void balance;

>>>>>>> 78bfe15710eca6013f02e13c91771d40728e2740



/* //Funkar kanske */
/* int depth(Bst tree) */
/* { */
/*   return NULL; */
/* } */


/* int check_parent(Bst tree, Bst parent){ */
/*   if (0<(strcmp(tree->key, parent->key))){ */
/*     reif (r_or_left){ */
/*         parent->right=tree->right; */
/*       } */
/*       else{ */
/*         parent->left=tree->right; */
/*       turn 1; */
/*   }  */
/*   else{ */
/*     return 0; */
/*   } */
/* } */

/* void balance */


/*   //få ut i del funktioner? */
/* void balance(Bst tree, Bst parent){ */
/*   int r_or_left = check_parent(tree, parent); */
/*   if (tree->left == NULL){ */
/*     //case 1 */
/*     if (tree->right->left == NULL){ */
/*       tree->right->left=tree; */
      
/*       if (r_or_left){ */
/*         parent->right=tree->right; */
/*       } */
/*       else{ */
/*         parent->left=tree->right; */
/*       } */

/*       tree->right=NULL; */
/*       tree->left=NULL; */
/*     } */
/*     //case 2tr */
/*     else{ */
/*       tree->right->right=tree->right->left; */
/*       tree->right->left=tree; */
      
/*       if (r_or_left){ */
/*         parent->right=tree->right; */
/*       } */
/*       else{ */
/*         parent->left=tree->right; */
/*       } */
      
/*       tree->right=NULL; */
/*       tree->left=NULL; */
/*     } */
/*   } */
/*   else{ */
/*   //case 3 */
/*     if (tree->left->right == NULL){ */
/*       tree->left->right=tree; */

/*       if (r_or_left){ */
/*         parent->right=tree->left; */
/*       } */
/*       else{ */
/*         parent->left=tree->left; */
/*       } */
      
/*       tree->right=NULL; */
/*       tree->left=NULL; */
/*       } */
/*     //case 4 */
/*     else{ */
/*       tree->left->left=tree->left->right; */
/*       tree->left->right=tree; */

/*       if (r_or_left){ */
/*         parent->right=tree->left; */
/*       } */
/*       else{ */
/*         parent->left=tree->left; */
/*       } */
/*       tree->right=NULL; */
/*       tree->left=NULL; */
/*     } */
/*   } */
/* } */



/* void insert_node(Bst new_node, Bst tree, Bst parent){ */
/*   if(tree == NULL){ */
/*     tree = new_node; */
/*   } */
/*   else{ */
/*     if(0 < strcmp(new_node->key, tree->key)){ */
/*       insert_bst(new_bst, tree->left, tree); */
/*     } */
/*     else{ */
/*       insert_bst(new_bst, tree->right, tree); */
/*     } */
/*   } */
/*   printf("Hej: %s, %s,\n", tree->key, tree->value); */
/*   if (1 < abs(depth(tree->right) - depth(tree->left))){ */
/*     balance(tree, parent); */
/*   } */
/* } */

/* //Adds an entry (key, value) into the database.  */
/* void add_bst(char *input_key, char *input_value){ */
/*   Bst new_bst = create_bst(input_key, input_value); */
/*   printf("Hej: %s, %s,\n", new_bst->key, new_bst->value); */
/*   insert_bst(new_bst, current_tree, NULL); */
/* } */


/* Bst *search_entry(char *input_key){ */
/*   cursor = current_tree; */
/*     while (cursor != NULL){ */
/*       int compare = strcmp(input_key, cursor->key); */
/*     if (compare == 0){ */
/*       return NULL; */
/*     }else{ */
/*      cursor = compare > 0 ? cursor->right: cursor->left; */
/*     } */
/*     } */
/*     return cursor->value; */
/* } */




/* //Changes the value of a specified key in an entry */
/* void update_value(char *old_value, char *new_value){ */
/*   strcpy(old_value, new_value); */
/* }  */


/* //Searches for input_key, removes the bst */
/* void remove_bst(char *input_key, char *output_buffer); */

/* //Prints out the database to the standard ouput */
/* void print_database(); */
