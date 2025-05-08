# Nom de l'exécutable
EXEC = refuge

# Dossiers
SRC_DIR = .
OBJ_DIR = obj

# Fichiers sources et objets
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Règle par défaut
all: $(EXEC)

# Création de l'exécutable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compilation des .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer les fichiers objets
clean:
	rm -rf $(OBJ_DIR) *.o

# Nettoyer tout (objets + exécutable)
fclean: clean
	rm -f $(EXEC)

# Recompiler tout proprement
re: fclean all

