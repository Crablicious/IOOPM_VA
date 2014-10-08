
CC=gcc
FLAGS=-Wall -ggdb -std=c99
COMPILE= $(CC) $(FLAGS)

tree: db_treemodule.o db

list: db_listmodule.o db_list

db_tree: db.c db_treemodule.o db_listmodule.h
	$(COMPILE) db_treemodule.o db_listmodule.h db.c -o db_test 		

db: db.c db_listmodule.h
	$(COMPILE) -c db.c db_listmodule.h

db_list: db.c db_listmodule.o db_listmodule.h
	$(COMPILE) db_listmodule.o db_listmodule.h db.c -o db_test 

db_listmodule.o: db_listmodule.c
	$(COMPILE) -c db_listmodule.c  

db_treemodule.o: db_treemodule.c
	$(COMPILE) -c db_treemodule.c

clean:
	rm -rf *o

