
EXEC = refuge


SRCS = main.c fonction.c recherche.c


OBJS = $(SRCS:.c=.o)


CC = gcc
CFLAGS = -Wall -Wextra -std=c99


all: $(EXEC)

# Lier les objets pour créer l'exécutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f *.o


fclean: clean
	rm -f $(EXEC)


re: fclean all
