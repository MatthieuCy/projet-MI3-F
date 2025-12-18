CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
EXEC = wildwater

# Liste des objets : on utilise les noms de fichiers actuels
OBJ = main.o avl.o leaks.o

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c avl.h
	$(CC) $(CFLAGS) -c main.c -o main.o

avl.o: avl.c avl.h
	$(CC) $(CFLAGS) -c avl.c -o avl.o

leaks.o: leaks.c avl.h
	$(CC) $(CFLAGS) -c leaks.c -o leaks.o

clean:
	rm -f *.o $(EXEC)
