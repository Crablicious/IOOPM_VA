#include <stdio.h>

//Struct of implementation
struct node;

// empty();

//Adds an entry (key, value) into the database. 
void add_node(char input_key[], char input_value[]);

//Searches for a matching key in the database and returns whether it is found or not and writes the result to output_buffer.
int search_entry(char input_buffer[], char *output_buffer);

//Changes the value of a specified key in an entry
void update_entry_mod(char buffer); 

//
/* void insert_entry(); */

//
/* void delete_entry(); */

//
void print_database();
