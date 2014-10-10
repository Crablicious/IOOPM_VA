#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_listmodule.h"

//flychecker
// what? ^?
char buffer[128]; // Globala eller inte?
char buffer2[128];

void print_welcome(){
  puts("Welcome to");
  puts(" ____    ____       ");
  puts("/\\  _`\\ /\\  _`\\     ");
  puts("\\ \\ \\/\\ \\ \\ \\L\\ \\   ");
  puts(" \\ \\ \\ \\ \\ \\  _ <\\ ");
  puts("  \\ \\ \\_\\ \\ \\ \\L\\ \\ ");
  puts("   \\ \\____/\\ \\____/ ");
  puts("    \\/___/  \\/___/  ");
  puts("");
}

void read_line(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

struct node *pull_database(char *filename){
  printf("Loading database \"%s\"...\n\n", filename);
  FILE *database = fopen(filename, "r");
  struct node *db = NULL;
  while(!(feof(database))){
    read_line(buffer, 128, database);
    read_line(buffer2, 128, database);
    db = add_node(buffer, buffer2, db);
  }
  fclose(database);
  return db;
}

void query_entry(struct node *db){
  printf("Enter key: ");
  read_line(buffer, 128, stdin);
  puts("Searching database...\n");
  struct node *found = search_entry(buffer, db);   
  if (found){
    char *value = extract_value(found);
    printf("Found entry:\nkey: %s\nvalue: %s\n", buffer, value);   
}
 else{
   printf("Could not find an entry matching key \"%s\"!\n", buffer); 
 }
}

void *update_entry(struct node *db){
  printf("Enter key: ");
  read_line(buffer, 128, stdin);
  puts("Searching database...\n");
  struct node *found = search_entry(buffer, db);
  if(found){
    char *old_value = extract_value(found);
    printf("Matching entry found:\nkey: %s\nvalue: %s\n\n", buffer, old_value);
    puts("Enter new value:");
    read_line(buffer, 128, stdin);
    update_value(old_value, buffer); // (old_value, new_value)
    printf("The Value: %s updated to %s\n", old_value, buffer);
  }
  else{
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
  return db;
}


void *insert_entry(struct node *db){
  struct node *found;
  //separera till en hjälpfunktion
  do{ 
    puts("Enter key");
    read_line(buffer, 128, stdin);
    puts("Searching database for duplicate keys...");
    found = search_entry(buffer, db);  
    if(found){
      puts("key already exists, choose another one!\n");
    } 
  } while(found);
  puts("Key is unique!\nEnter value: ");
  read_line(buffer2, 128, stdin);
  add_node(buffer, buffer2, db);
  return db;
}

void delete_entry(struct node *db){
  struct node *found = NULL;
  while(!found){ //separera till en hjälpfunktion
    puts("Enter key");
    read_line(buffer, 128, stdin);
    puts("Searching database for the key...");
    found = search_entry(buffer, db);  
    if(!found){
      puts("Key does not exist, choose another one!\n");
    } 
  }
  //remove_node(buffer, buffer2);
  printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", buffer, buffer2);
}

void print_database(struct node *db){
  print_database_mod(db);
}

void main_loop(struct node *db){
  int choice = -1;
  while(choice != 0){
    puts("Please choose an operation");
    puts("1. Query a key");
    puts("2. Update an entry");
    puts("3. New entry");
    puts("4. Remove entry");
    puts("5. Print database");
    puts("0. Exit database");
    printf("? ");
    scanf("%d", &choice);
    while(getchar() != '\n'); // Clear stdin
    switch(choice){
    case 1: //query an entry
      query_entry(db);
      break;  
    case 2: //update an existing entry
      update_entry(db);
      break;
    case 3: //insert a new entry
      insert_entry(db);
      break;
    case 4: //deletes an entry 
      delete_entry(db);
      break; 
    case 5: //prints the whole database
      print_database(db);
      break;
    case 0: // Exit
      puts("Good bye!");
      break;
    default:
      // Please try again
      puts("Could not parse choice! Please try again");
    }
    puts("");
  }
}

int main(int argc, char *argv[]){
  if (argc < 2){
    puts("Usage: db [FILE]");
    return -1;
  }
  print_welcome();
  // Read the input file
  //pull_database(argv[1]); //arraynotation
  struct node *db = pull_database (*(argv+1)); //pekarnotation
  // Main loop
  main_loop(db);
  return 0;
}
