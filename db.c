#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Datatype key * value * next node
typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;

char buffer[128]; // Globala eller inte?
Node list = NULL;

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

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

void copy_database(char *filename){

  printf("Loading database \"%s\"...\n\n", filename);
  FILE *database = fopen(filename, "r");
  
  // Copys the whole file
  //Bygger upp en nodstruktur mha filen vi matar in.
  while(!(feof(database))){
    Node newNode = malloc(sizeof(struct node)); // malloc allocates space in memory
    readline(buffer, 128, database);
    newNode->key = malloc(strlen(buffer) + 1);
    strcpy(newNode->key, buffer); // Saves the key
    readline(buffer, 128, database);
    newNode->value = malloc(strlen(buffer) + 1);
    strcpy(newNode->value, buffer); // Saves the value
    newNode->next = list; // Puts an empty/previous list/s as next
    list = newNode; 
  }
  fclose(database);
}

//case 1
void query_entry(Node cursor){
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database...\n");
  int found = 0;
  cursor = list;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      puts("Found entry:");
      printf("key: %s\nvalue: %s\n", cursor->key, cursor->value);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
}
 
//case 2
void update_entry(Node cursor){
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database...\n");
  int found = 0;
  cursor = list;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      puts("Matching entry found:");
      printf("key: %s\nvalue: %s\n\n", cursor->key, cursor->value);
      found = 1;
    }
    else{
      cursor = cursor->next;
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
  else{
    printf("Enter new value: ");
    readline(buffer, 128, stdin);
    free(cursor->value);
    cursor->value = malloc(strlen(buffer) + 1);
    strcpy(cursor->value, buffer);
    puts("Value inserted successfully!");
  }
}

//case 3
void insert_entry(Node cursor){
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database for duplicate keys...");
  int found = 0;
  cursor = list;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      printf("key \"%s\" already exists!\n", cursor->key);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){ // Insert new node to the front of the list
    puts("Key is unique!\n");
    Node newNode = malloc(sizeof(struct node));
    newNode->key = malloc(strlen(buffer) + 1);
    strcpy(newNode->key, buffer);
    printf("Enter value: ");
    readline(buffer, 128, stdin);
    newNode->value = malloc(strlen(buffer) + 1);
    strcpy(newNode->value, buffer);
    newNode->next = list;
    list = newNode;
    puts("");
    puts("Entry inserted successfully:");
    printf("key: %s\nvalue: %s\n", list->key, list->value);
  }
}

//case 4
void delete_entry(Node cursor){
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database...\n");
  int found = 0;
  cursor = list;
  Node prev = NULL;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      if(prev == NULL){ // Delete first node
        list = cursor->next;
      }else{
        prev->next = cursor->next;
      }
      found = 1;
      printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", cursor->key, cursor->value);
    }else{
      prev = cursor;
      cursor = cursor->next;
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
}

//case 5
void print_database(Node cursor){
  cursor = list;
  while(cursor != NULL){
    puts(cursor->key);
    puts(cursor->value);
    cursor = cursor->next;
  }
}


void main_loop(){
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
    Node cursor = NULL;
    switch(choice){
    case 1: //query an entry
      query_entry(cursor);
      break;  
    case 2: //update an existing entry
      update_entry(cursor);
      break;
    case 3: //insert a new entry
      insert_entry(cursor);
      break;
    case 4: //deletes an entry
      delete_entry(cursor);
      break;
    case 5: //prints the whole database
      print_database(cursor);
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
  //Prints a welcome message
  print_welcome();
  // Read the input file
  copy_database(argv[1]);
  
  // Main loop
  main_loop();
  return 0;
}
