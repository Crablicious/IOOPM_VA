#include <stdio.h>

//Struct of implementation
struct node;

//Creates an empty node
struct node empty_node();

//Adds an entry (key, value) into the database. 
void add_node(char input_key[], char input_value[]);

//Searches for a matching key in the database and returns whether it is found or not and writes the result to output_buffer.
char *search_entry(char *input_key, struct node *tree);

//Changes the value of a specified key in an entry
void update_value(char *old_value, char *new_value); 

//Searches for input_key, removes the node
void remove_node(char *input_key, char *output_buffer);

//Prints out the database to the standard ouput
void print_database();
