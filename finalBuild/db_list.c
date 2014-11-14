#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef int (*comparator)(void *, void *);

typedef struct node{
  void *key;
  void *value;
  struct node *next;
} *Node;



struct node *empty_node(){
  struct node *empty = malloc(sizeof(struct node));
  assert(empty);
  return empty;
}


void *clone_values(void *input){
  void *copy = malloc(sizeof(input));
  assert(copy);
  memcpy(copy, input, (sizeof(input)));
  return copy;
}  

void *create_db(void *input_key, void *input_value){
  struct node *new_node = empty_node();
  new_node->key = clone_values(input_key);
  new_node->value = clone_values(input_value);
  new_node->next = NULL;
  return new_node;
}

void add_item(void *input_key, void *input_value, struct node **db, comparator cmp){
  if (db != NULL){
    struct node *new_node = create_db(input_key, input_value);
    new_node->next = *db; 
    *db = new_node; 
  }
}


void destroy(struct node **bad_node){
  free((*bad_node)->key);
  free((*bad_node)->value);
  free(*bad_node);
  *bad_node = NULL;
}

void *extract_value(struct node *db){
  return db->value;
}

struct node **search_entry(void *input_buffer, struct node **db, comparator cmp){
  if (db != NULL){
    struct node **cursor = db;
    int compare;
    while ((*cursor) != NULL){
      compare = cmp(input_buffer, (*cursor)->key);
      if (compare == 0){
        return cursor;
      }else{
        cursor = &((*cursor)->next);
      }
    }
  }
  return NULL; 
}

void destroy_k_v(struct node *bad_node){
  free(bad_node->key);
  free(bad_node->value);
}
  
void update_value(struct node **old_node, void *new_value){
  if (old_node != NULL && *old_node != NULL){
    free((*old_node)->value);
    (*old_node)->value = clone_values(new_value);
  }
}
 
void remove_item(struct node **unwanted_node, struct node **db, comparator cmp){
  if (unwanted_node != NULL && *unwanted_node != NULL && db != NULL && *db != NULL){
    if ((*unwanted_node)->next == NULL){
      destroy(unwanted_node);
    }else{
      destroy_k_v(*unwanted_node);
      struct node *tmp;
      (*unwanted_node)->key = (*unwanted_node)->next->key;
      (*unwanted_node)->value = (*unwanted_node)->next->value;
      tmp = (*unwanted_node)->next->next;
      free((*unwanted_node)->next);
      (*unwanted_node)->next = tmp;
    }
  }
}

int node_amount(struct node *db){
  if (db != NULL){
    return 1 + node_amount(db->next);
      }else{
    return 0;
  }
}

void **all_items(struct node *db){
  if (db == NULL){ 
    return NULL;
  }
  int num = node_amount(db);
  void **item_list = malloc(sizeof(void**) * (num+1) * 2);
  assert(item_list);
  struct node *cursor = db;
  for (int i = 0; cursor != NULL; i+=2){
    *(item_list+i) = clone_values(cursor->key);
    *(item_list+i+1) = clone_values(cursor->value);
    cursor = cursor->next;
  }
  return item_list;
}

void print_database_mod(struct node *db){
  struct node *cursor = db;
  while(cursor != NULL){
    puts(cursor->key);
    puts(cursor->value);
    cursor = cursor->next;
  }
}

void destroy_db(struct node *db){
  if (db != NULL){ 
    destroy_db(db->next);
    destroy(&db);
  }
}

