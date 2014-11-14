
CC=gcc
FLAGS=-Wall -ggdb -std=c99
COMPILE= $(CC) $(FLAGS)

all: db test db_tree

test: unittests.c db_tree.c db_test.h 
	$(COMPILE) unittests.c db_tree.c -o unittests -lcunit
	./unittests

tree: db_tree.o db_tree

db_tree: db.c db_module.h db_tree.o
	$(COMPILE) db_tree.o db_module.h db.c -o db_tree 

db_tree.o: db_tree.c
	$(COMPILE) -c db_tree.c


list: db_list.o db_list

db: db.c db_module.h
	$(COMPILE) -c db.c db_module.h

db_list: db.c db_list.o db_module.h
	$(COMPILE) db_list.o db_module.h db.c -o db_list 

db_list.o: db_list.c
	$(COMPILE) -c db_list.c  

profiling_tree: db.c db_module.h db_tree.o
	$(COMPILE) db_tree.o db_module.h db.c -o db_proftree -pg

clean:
	rm -rf *o
	rm -rf *~

