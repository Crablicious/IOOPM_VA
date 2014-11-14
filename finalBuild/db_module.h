#ifndef DB_MODULE_H
#define DB_MODULE_H
#include <stdio.h>

/**
Database consists of this type.
 */
struct node;

/**
You have to create a comparator that compares the keys of your database.
As follows: some_comparator(left, right), that returns <0 if left < right, 0 if left ==right, 0< if left > right. 
 */
typedef int (*comparator)(void *, void *);

/**
Input: Key and value of the first item you want to store in the database. 
Effect: Starts the database and returns a pointer to it's first element.
*/
struct node *create_db(void *input_key, void *input_value);

/**
Input: A pointer to a database created by create_db.
Effect: Returns a pointer to the value of the item pointed at.
*/
void *extract_value(struct node *db);

/**
Input: A new entry's key, value and pointer to the database you want the new entry in, (key, value, databasepointer). Start a new database by sending in a NULL-pointer as database.
Effect: Returns a pointer to the specified database with your entry added.
*/
void add_item(void *input_key, void *input_value, struct node **db, comparator cmp);

/**
Input: A key and a pointer to the database you want to search for key in.
Effect: Searches for a matching key in the database. Returns a pointer to the found item if found, else NULL.
*/
struct node **search_entry(void *input_key, struct node **db, comparator cmp);

/**
Input: A pointer to the item with the "old" value and a pointer to the new value.
Effect: Changes old value into new value. 
*/
void update_value(struct node **old_value_item, void *new_value); 

/**
Input: A pointer to the unwanted item and the database.
Effect. The unwanted item is deleted from the database.
 */ 
void remove_item(struct node **unwanted_item, struct node **db, comparator cmp);

/**
Input: A pointer to the database you want to destroy.
Effect: Database is removed and memory freed.
*/
void destroy_db(struct node *db);

/**
Input: A pointer to the database you want to print.
Effect: All items in database is returned as an unsorted char* list with "END_OF_ITEMS" in last spot. You're responsible for freeing all elements and also the returned pointer. 
(key(1), value(1), key(2), value(2).... key(n), value(n), "END_OF_ITEMS")
 */
void **all_items(struct node *db);

/**
Input: A pointer to the database.
Effect: An int displying the number of elements in the db.
*/ 
int node_amount(struct node *db);

#endif
