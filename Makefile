
CC=gcc
FLAGS=-Wall -ggdb -std=c99
COMPILE= $(CC) $(FLAGS)

all: db.o db_listmodule.o db

db: db.c db_listmodule.o db_listmodule.h
	$(COMPILE) db_listmodule.o db_listmodule.h db.c -o db_test 

db_listmodule.o: db_listmodule.c
	$(COMPILE) -c db_listmodule.c  

clean:
	rm -rf *o