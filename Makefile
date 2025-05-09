# Nom de l'exécutable
EXEC = refuge

# Répertoires
SRC_DIR = .
OBJ_DIR = obj

# Fichiers sources et objets
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I.

# Règle par défaut
all: $(EXEC)

# Création de l'exécutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compilation des fichiers .o à partir des .c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	rm -rf $(OBJ_DIR)

# Nettoyage complet (objets + exécutable)
fclean: clean
	rm -f $(EXEC)

# Recompiler depuis zéro
re: fclean all


