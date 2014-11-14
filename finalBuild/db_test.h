#ifndef DB_TEST_H
#define DB_TEST_H
#include <stdio.h>


typedef struct node{
  char *key;
  char *value;
  struct node *right;
  struct node *left;
} *Node;

typedef int (*comparator)(void *, void *);

int depth(struct node *tree);

struct node *create_db(void *input_key, void *input_value);

void destroy(struct node **bad_node);

void *extract_value(struct node *db);

void add_item(void *input_key, void *input_value, struct node **db, comparator cmp);

struct node **search_entry(char *input_buffer, struct node **db, comparator cmp);

void update_value(struct node **old_value, void *new_value); 
 
void remove_item(struct node **unwanted_node, struct node **db, comparator cmp);

void destroy_db(struct node *db);

void **all_items(struct node *db);


#endif
