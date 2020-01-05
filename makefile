CC=gcc
CFLAGS=-Wall -ansi -g -Iincludes

contactList: contacts.o conFunctions.o
	$(CC) $(CFLAGS) bin/contacts.o bin/conFunctions.o -o bin/contactList

contacts.o: src/contacts.c includes/conFunctions.h
	$(CC) $(CFLAGS) -c src/contacts.c -o bin/contacts.o

conFunctions.o: src/conFunctions.c includes/conFunctions.h
	$(CC) $(CFLAGS) -c src/conFunctions.c -o bin/conFunctions.o

clean:
	rm bin/*
