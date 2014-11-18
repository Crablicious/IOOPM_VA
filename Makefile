
CC=gcc
FLAGS=-Wall -ggdb -std=c99
COMPILE= $(CC) $(FLAGS)

new: db_dbl

test: unittests.c db_dbltree.c db_test.h 
	$(COMPILE) unittests.c db_dbltree.c -o unittests -lcunit
	./unittests

db_dbl: db_dbl.c db_dbldb.h db_dbltree.o
	$(COMPILE) db_dbltree.o db_dbldb.h db_dbl.c -o dbl_tree 

db_dbltree.o: db_dbltree.c
	$(COMPILE) -c db_dbltree.c
clean:
	rm -rf *o


list: db_listmodule.o db_list

db: db.c db_listmodule.h
	$(COMPILE) -c db.c db_listmodule.h

db_list: db.c db_listmodule.o db_listmodule.h
	$(COMPILE) db_listmodule.o db_listmodule.h db.c -o db_test 

db_listmodule.o: db_listmodule.c
	$(COMPILE) -c db_listmodule.c  

