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
  
  count_right = 1 + depth(tree->right);
  count_left = 1 + depth(tree->left);
  
  if (count_left>count_right){
    return count_left;
  }
  else{
    return count_right;
  }
}

//1 is right, 0 is false. Doesn't run when parent == NULL
int check_parent(Node tree, Node parent){
  if (0<(strcmp(tree->key, parent->key))){
    return 1;
  } 
  else{
    return 0;
  }
}

struct node *balance(Node tree, Node parent){
  int r_or_left;
  if (parent){ 
    r_or_left = check_parent(tree, parent);
  }
  
  struct node *new_root;

  struct node *tmp_a;
  struct node *tmp_b;
  struct node *tmp_c;

  
  if (depth(tree->right) > depth(tree->left)){ //if "right heavy"
    if (depth(tree->right->right) > depth(tree->right->left)){ //case 1 right right heavy
      new_root = tree->right;
      tmp_a = tree->right->left; 
      tree->right->left=tree;
      
      if (parent){
        if (r_or_left){
          parent->right=new_root;
        }
        else{
          parent->left=new_root;
        }
      }
      
      tree->right = tmp_a;

      return new_root;
    }
    //case 2 right left heavy
    else{
      new_root = tree->right->left;
      tmp_b = tree->right->left->left;
      tmp_c = tree->right->left->right;
      
      if (parent){      
        if (r_or_left){
          parent->right=tree->right->left;
        }
        else{
          parent->left=tree->right->left;
        }
      }

      tree->right->left = tmp_c;
      new_root->right = tree->right;
      new_root->left = tree;
      tree->right = tmp_b;
      
      return new_root;
    }
  }

  else{ // if left heavy
  //case 3 left left heavy
    if (depth(tree->left->left) > depth(tree->left->right)){
      
      new_root = tree->left;
      tmp_c = tree->left->right;

      if (parent){
        if (r_or_left){
          parent->right=tree->left;
        }
        else{
          parent->left=tree->left;
        }
      }
      new_root->right = tree;
      tree->left = tmp_c;
      
      return new_root;
      }
    //case 4 left right heavy
    else{
      new_root = tree->left->right;
      tmp_c = tree->left->right->right;
      tmp_b = tree->left->right->left;
      
      if (parent){
        if (r_or_left){
          parent->right=new_root;
        }
        else{
          parent->left=new_root;
        }
      }
      
      
      new_root->left = tree->left;
      new_root->right = tree;
      new_root->right->left = tmp_c;
      new_root->left->right = tmp_b;

      return new_root;
    }
  }
}

struct node *insert_node(Node new_node, Node tree, Node parent){
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
    }
  }
  else if (check_parent(new_node, tree)){ 
    insert_node(new_node, tree->right, tree);
      
  }
  else{
    insert_node(new_node, tree->left, tree);
  }
  
  //Undersök om trädet behöver balanseras och gör det isåfall
  if (1 < abs(depth(tree->right) - depth(tree->left))){
    if (!parent){
      tree = balance(tree, parent);
    }else{
      balance(tree, parent);
    }
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

//Parent behövs endast eftersom den minsta hittas genom parent->left. Returnerar parent.
struct node *smallest(struct node *db){
  if (db != NULL && db->left == NULL){
    return NULL; //basfallet. Nu står vi på minsta noden.
  }

  struct node *small;
  small = smallest(db->left);
  if (small == NULL){
    return db;
  }
  return small;
}

//Parent behövs endast eftersom den minsta hittas genom parent->left. Returnerar parent.
struct node *biggest(struct node *db){
  
  if (db != NULL && db->right == NULL){
    return NULL; //basfallet. Nu står vi på största noden.
  }
  
  struct node *big;
  big = biggest(db->right);
  if (big == NULL){ //Nu är vi på största nodens fader.
    return db;
  }
  return big;
}


struct node *dbl_src_node(struct node **src_tree, char *src_key){
  int compare = strcmp(src_key, (*src_tree)->key);
  if (compare == 0){
    *src_tree = NULL;
    return NULL;
  }else if(0<compare){
    dbl_src_node(&((*src_tree)->right), src_key);
    return *src_tree;
  }else{
    dbl_src_node(&((*src_tree)->left), src_key);
    return *src_tree;
  }
}

//Funkar förmodligen inte på löv.
//Searches for input_key, removes the node
struct node *remove_node(struct node *unwanted_node, struct node **db){
  if (depth(*db) == 1){
    *db = NULL;
    return *db;
    } 
    
  if (unwanted_node->right == NULL && unwanted_node->left == NULL){
    *db = dbl_src_node(db, unwanted_node->key);
    //FREEEEEEEE
    return *db;
  }

    //Om unwanted_node har två subträd.
  //Jag vill här ta bort en nod från vänster. biggest
  if (depth(unwanted_node->left) < depth(unwanted_node->right)){
    struct node *big_parent = biggest(unwanted_node);
    struct node *biggest_node = big_parent->right; //Seg fault.
    unwanted_node->key = biggest_node->key;
    unwanted_node->value = biggest_node->value;
    struct node *deleted_node = biggest_node;
    big_parent->right = biggest_node->left;
    //FREEE THE NOOOOOOOOOODE!!!!!!!!!!!!!!

  }else{ //Här vill jag ta bort en nod från höger. Även då depth(right) == depth(left). smallest
    struct node *small_parent = smallest(unwanted_node);
    struct node *smallest_node = small_parent->left;
    
    unwanted_node->key = smallest_node->key;
    unwanted_node->value = smallest_node->value;
    struct node *deleted_node = smallest_node;
    small_parent->left = smallest_node->right;
    //FREE THE NODE!!!!!!!!!!!!!!!!!
  }
  return *db;
}

//Prints out the database to the standard ouput
void print_database_mod(struct node *db){
  //inorder traversal
  if (db){
    print_database_mod(db->left);
    printf("Key: %s Value: %s\n", db->key, db->value);
    print_database_mod(db->right);
  }
}
