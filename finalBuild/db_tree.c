#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef int (*comparator)(void *, void *);

typedef struct node{
  void *key;
  void *value;
  struct node *right;
  struct node *left;
} *Node;

/**
Allocates memory for an empty node. 
 */
struct node *empty_node(void){
  struct node *empty = malloc(sizeof(struct node));
  assert(empty);
  return empty;
}

void insert_node(struct node *new_node, struct node **tree, comparator cmp);


/**
Copies the input to another memory location and returns a pointer to that location.
*/
void *clone_values(void *input){
  void *copy = malloc(sizeof(input));
  assert(copy);
  memcpy(copy, input, (sizeof(input)));
  return copy;
}

/**
Creates a node with no children and the params as key and value.
 */
struct node *create_db(void *input_key, void *input_value){
  struct node *new_node = empty_node();
  new_node->key = clone_values(input_key);
  new_node->value = clone_values(input_value);
  new_node->right = NULL;
  new_node->left = NULL;
  return new_node;
}

/**
Frees the whole specified node, including key and values.
 */
void destroy(struct node **bad_node){
  free((*bad_node)->key);
  free((*bad_node)->value);
  free(*bad_node);
  *bad_node = NULL;
}

/**
Frees only the memory of the key and value in the specified node.
 */
void destroy_k_v(struct node *bad_node){
  free(bad_node->key);
  free(bad_node->value);
}

/**
Adds a newly created node to the database.
 */
void add_item(void *input_key, void *input_value, struct node **db, comparator cmp){
  if (db != NULL){
    struct node *new_node = create_db(input_key, input_value);
    insert_node(new_node, db, cmp);  
  }
}

/**
Returns value of node
 */
void *extract_value(struct node *db){
  if (db == NULL){
    return NULL;
  }
  return db->value;
}

/**
Searches for a key in the database. Returns a double pointer to it.
 */
struct node **search_entry(void *input_buffer, struct node **db, comparator cmp){
  if (db != NULL){
    struct node **cursor = db;
    int compare;
    while ((*cursor) != NULL){
      compare = cmp(input_buffer, (*cursor)->key);
      if (compare == 0){
        return cursor;
      }else if(compare > 0){
        cursor = &((*cursor)->right);
      }else{
        cursor = &((*cursor)->left);
      }
    }
  }
  return NULL;
}

/**
Updates the nodes value with attached value andalso frees the old value.
 */
void update_value(struct node **old_node, void *new_value){
  if (old_node != NULL && *old_node != NULL){
    free((*old_node)->value);
    (*old_node)->value = clone_values(new_value);
  }
}

/**
Calculates the greatest depth in tree and returns that value. 
 */
/* int depth(struct node *tree){ */
/*   int count_right = 0; */
/*   int count_left = 0; */
/*   if (tree == NULL){ */
/*     return 0; */
/*   } */
  
/*   count_right = 1 + depth(tree->right); */
/*   count_left = 1 + depth(tree->left); */
  
/*   if (count_left>count_right){ */
/*     return count_left; */
/*   } */
/*   else{ */
/*     return count_right; */
/*   } */
/* } */

int max(int a, int b){
  if (a>b) return a;
  return b;
}

int depth(struct node *tree){
  if (tree) return 1+max(depth(tree->right), depth(tree->left));
  return 0;
}

/**
Will balance tree. Should only be called when tree needs to be balanced (depthdifference > 1).
 */
void balance(struct node **tree){
 
  struct node *new_root;
  struct node *old_root;
  struct node *tmp_a;
  struct node *tmp_b;
  struct node *tmp_c;

  
  if (depth((*tree)->right) > depth((*tree)->left)){ //if "right heavy"
    if (depth((*tree)->right->right) > depth((*tree)->right->left)){ //case 1 right right heavy
      new_root = (*tree)->right;
      tmp_a = (*tree)->right->left; 
      (*tree)->right->left=(*tree);
      (*tree)->right = tmp_a;
      *tree = new_root;
    }
    //case 2 right left heavy
    else{
      old_root = *tree;
      *tree = (*tree)->right->left;
      tmp_b = old_root->right->left->left;
      tmp_c = old_root->right->left->right;
      
      
      old_root->right->left = tmp_c;
      (*tree)->right = old_root->right;
      (*tree)->left = old_root;
      old_root->right = tmp_b;
    }
  }

  else{ // if left heavy
  //case 3 left left heavy
    if (depth((*tree)->left->left) > depth((*tree)->left->right)){
      old_root = *tree;
      tmp_c = (*tree)->left->right;

      (*tree)=(*tree)->left;
        
      (*tree)->right = old_root;
      (old_root)->left = tmp_c;
    }
    //case 4 left right heavy
    else{
      old_root = (*tree);
      tmp_c = (*tree)->left->right->right;
      tmp_b = (*tree)->left->right->left;
      
      (*tree) = (*tree)->left->right;
      
      (*tree)->left = old_root->left;
      (*tree)->right = old_root;
      (*tree)->right->left = tmp_c;
      (*tree)->left->right = tmp_b;
    }
  }
}


/**
Checks if balancing is needed at the current subroot and does balancing if needed. 
 */
void do_balance(struct node **tree){
  if (*tree != NULL){
    if (1 < abs(depth((*tree)->right) - depth((*tree)->left))){
      balance(tree);
    }
  }
}

/**
Inserts a node into the tree at the right place. 
 */
void insert_node(struct node *new_node, struct node **tree, comparator cmp){
  if(*tree == NULL){
    *tree = new_node;
  }
  else if (0 < cmp(new_node->key, (*tree)->key)){ 
    insert_node(new_node, &((*tree)->right), cmp);
  }
  else{
    insert_node(new_node, &((*tree)->left), cmp);
  }
  do_balance(tree);
}


/**
Finds the smallest node in the tree.
 */
struct node **smallest(struct node **db){
  if (((*db) != NULL) && ((*db)->left == NULL)){
    return db; //basfallet. Nu står vi på minsta noden.
  }
  struct node **small;
  small = smallest(&((*db)->left));
  return small;
}

/**
Finds the biggest node in the tree.
 */
struct node **biggest(struct node **db){
  if ((*db) != NULL && (*db)->right == NULL){
    return db; //basfallet. Nu står vi på största noden.
  }
  struct node **big;
  big = biggest(&((*db)->right));
  return big;
}

/**
Looks for unbalance in whole specified tree.
 */
void check_balance(struct node **db){
  if (*db){
    check_balance(&((*db)->right));
    check_balance(&((*db)->left));
    if (1 < abs(depth((*db)->right) - depth((*db)->left))){
      balance(db);
    }
  }
}

/**
Removes the node from the tree. Balances if needed.
 */
void remove_item(struct node **unwanted_node, struct node **db, comparator cmp){
  if (unwanted_node != NULL && *unwanted_node != NULL && db != NULL && *db != NULL){
    int compare = cmp((*unwanted_node)->key, (*db)->key);
    if ((*unwanted_node)->right == NULL && (*unwanted_node)->left == NULL){
      destroy(unwanted_node);
    
    }else if (depth((*unwanted_node)->left) >= depth((*unwanted_node)->right)){
      struct node **biggest_node;
        
      biggest_node = biggest(&((*unwanted_node)->left));
    
      destroy_k_v((*unwanted_node));
    
      (*unwanted_node)->key = (*biggest_node)->key;
      (*unwanted_node)->value = (*biggest_node)->value;
    
      if ((*biggest_node)->left != NULL){
        *biggest_node = (*biggest_node)->left;        
      }
      else{
        free(*biggest_node);
        *biggest_node = NULL;
      }
    
    }else{
  
      struct node **smallest_node;
    
      smallest_node = smallest(&((*unwanted_node)->right));
      
      destroy_k_v(*unwanted_node);
    
      (*unwanted_node)->key = (*smallest_node)->key;
      (*unwanted_node)->value = (*smallest_node)->value;
      if ((*smallest_node)->right != NULL){
        *smallest_node = (*smallest_node)->right;        
      }
      else{
        free(*smallest_node);
        *smallest_node = NULL;
      }
    }
    if (db != NULL && *db != NULL)
      {
        do_balance(db);
        if (compare > 0){
          check_balance(&((*db)->right));
        }else{
          check_balance(&((*db)->left));
        }
      }
  }
}

/**
Frees the whole tree. 
 */
void destroy_db(struct node *db){ 
  if (db != NULL){
    destroy_db(db->left);
    destroy_db(db->right);
    destroy(&db);
  }  
}

/**
Returns amount of nodes in the tree.
 */
int node_amount(struct node *db){
  if (db == NULL){
    return 0;
  }
  return 1+node_amount(db->right)+node_amount(db->left);
}

/**
Saves every node's key and value to an array. Unsorted.
 */
void save_kv(struct node *db, void **item_list){
  if (db != NULL){
    save_kv(db->left, item_list+2);
    *(item_list) = clone_values(db->key);
    *(item_list+1) = clone_values(db->value);      
    save_kv(db->right, item_list+node_amount(db->left)*2+2);
  }
}

/**
Returns an array of all keys and values in the tree as follows: [key(1), value(1), key(2), value(2)... key(n), value(n)]
 */
void **all_items(struct node *db){
  if (db == NULL){ 
    return NULL;
  }
  int num = node_amount(db);
  void **item_list = malloc(sizeof(void**) * (num+1) * 2);
  assert(item_list);
  save_kv(db, item_list);
  return item_list;
}

