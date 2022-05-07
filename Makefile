CC = gcc
CFLAGS = -Wall -Werror -pedantic -ansi
MAIN = tree
OBJ = main.o directory.o list.o
all: $(MAIN)

$(MAIN): $(OBJ)
	$(CC) $(CLFAGS) -g -o $(MAIN) $(OBJ)

main.o: main.c directory.h list.h
	$(CC) $(CFLAGS) -g -c main.c

directory.o: directory.c list.c
	$(CC) $(CFLAGS) -g -c directory.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -g -c list.c

debug:
	gcc -g main.c directory.c list.c

clean:
	rm *.o $(MAIN)
