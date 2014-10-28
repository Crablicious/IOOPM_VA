#ifndef DB_TEST_H
#define DB_TEST_H

#include <stdio.h>



//Database consists of this struct.
typedef struct node{
  char *key;
  char *value;
  struct node *right;
  struct node *left;
} *Node;

int depth(struct node *tree);

//Test
struct node *create_node(char *input_key, char *input_value);



void destroy(struct node **bad_node);

/*
Input: A pointer to a database created by add_node.
Effect: Returns a pointer to the value of the node pointed at.
*/
//Test
char *extract_value(struct node *db);

/*
Input: A new entry's key, value and pointer to the database you want the new entry in, (key, value, databasepointer). Start a new database by sending in a NULL-pointer as database.
Effect: Returns a pointer to the specified database with your entry added.
*/
//test
void add_node(char *input_key, char *input_value, struct node **db);

/*
Input: A key and a pointer to the database you want to search for key in.
Effect: Searches for a matching key in the database. Returns a pointer to the found node if found, else NULL.
*/
//test
struct node **search_entry(char *input_buffer, struct node **db);

/*
Input: A pointer to the node with the "old" value and a pointer to the new value.
Effect: Changes old value into new value. 
*/
//test
void update_value(struct node **old_value, char *new_value); 

/*
Input: A pointer to the unwanted node and the database.
Effect. The unwanted node is deleted from the database.
 */ 
void remove_node(struct node **unwanted_node, struct node **db);


void destroy_tree(struct node *db);

//--------------------------Not good----------------------
//Prints out the database to the standard output
void print_database_mod(struct node *db);


#endif
