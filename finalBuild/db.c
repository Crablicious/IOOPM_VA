#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_module.h"

char buffer[128]; 
char buffer2[128];

int compare(void *left, void *right) {
  return(strcmp((const char *) left, (const char *) right));
}

comparator cmp = &compare;

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
    if (db == NULL){
      db = create_db(buffer, buffer2);
    }else{
      add_item(buffer, buffer2, &db, cmp);
    }
  }
  fclose(database);
  return db;
}

void query_entry(struct node *db){
  printf("Enter key: ");
  read_line(buffer, 128, stdin);
  puts("Searching database...\n");
  struct node **found= search_entry(buffer, &db, cmp);   
  if (found){
    char *value = extract_value(*found);
    printf("Found entry:\nkey: %s\nvalue: %s\n", buffer, value);   
  }
  else{
    printf("Could not find an entry matching key \"%s\"!\n", buffer); 
  }
}

void update_entry(struct node *db){
  printf("Enter key: ");
  read_line(buffer, 128, stdin);
  puts("Searching database...\n");
  struct node **found= search_entry(buffer, &db, cmp);
  if(found){
    char *old_value = extract_value(*found);
    printf("Matching entry found:\nkey: %s\nvalue: %s\n\n", buffer, old_value);
    puts("Enter new value:");
    read_line(buffer, 128, stdin);
    update_value(found, buffer); 
    printf("The Value: %s updated to %s\n", old_value, buffer);
  }
  else{
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
}


void insert_entry(struct node **db){
  struct node **found;
  //separera till en hjälpfunktion
  do{ 
    puts("Enter key");
    read_line(buffer, 128, stdin);
    puts("Searching database for duplicate keys...");
    found = search_entry(buffer, db, cmp);  
    if(found){
      puts("key already exists, choose another one!\n");
    } 
  } while(found);
  puts("Key is unique!\nEnter value: ");
  read_line(buffer2, 128, stdin);
  add_item(buffer, buffer2, db, cmp);
}

void delete_entry(struct node **db){
  struct node **found = NULL;
  while(!found){ 
    puts("Enter key");
    read_line(buffer, 128, stdin);
    puts("Searching database for the key...");
    found = search_entry(buffer, db, cmp);  
    if(!found){
      puts("Key does not exist, choose another one!\n");
    } 
  }
  char *buffer2 = extract_value(*found);
  printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", buffer, buffer2);
  remove_item(found, db, cmp);
}

void print_database(struct node *db){
  int item_num = node_amount(db);
  char **item_list = (char **)all_items(db);
  if (item_list != NULL){
    int i;
    for (i = 0; i < item_num*2; i+=2){
      printf("Key: %s\n", *(item_list+i));
      printf("Value: %s\n",*(item_list+i+1));
      free(*(item_list+i));
      free(*(item_list+i+1));
    }
    free(item_list);
  }
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
    while(getchar() != '\n'); 
    switch(choice){
    case 1: //query an entry
      query_entry(db);
      break;  
    case 2: //update an existing entry
      update_entry(db);
      break;
    case 3: //insert a new entry
      insert_entry(&db);
      break;
    case 4: //deletes an entry 
      delete_entry(&db);
      break; 
    case 5: //prints the whole database
      print_database(db);
      break;
    case 0: // Exit
      puts("Good bye!");
      destroy_db(db);
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
 
  struct node *db = pull_database (argv[1]);
  
  // Main loop
  main_loop(db);
  return 0;
}
