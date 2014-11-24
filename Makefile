
CC=gcc
FLAGS=-Wall -ggdb -std=c99
COMPILE= $(CC) $(FLAGS)

tree: db_treemodule.o db_tree

list: db_listmodule.o db_list

db_tree: db.c db_tree.o db.h
	$(COMPILE) db_tree.o db.h db.c -o db_test 		

db_list: db.c db_list.o db.h
	$(COMPILE) db_list.o db.h db.c -o db_test 

db_listmodule.o: db_list.c
	$(COMPILE) -c db_list.c  

db_treemodule.o: db_tree.c
	$(COMPILE) -c db_tree.c

clean:
	rm -rf *o

