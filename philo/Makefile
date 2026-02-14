EXEC = Philo

SRC_DIR = src
OBJ_DIR = obj

SRCS = main.c ft_atoi.c lst.c utils.c init.c free.c
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
LDFLAGS = #-fsanitize=thread -g


# Couleurs (optionnel)
GREEN = \033[0;32m
RESET = \033[0m
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(EXEC)
	@echo "$(GREEN)✔ Compilation réussie !$(RESET)"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(EXEC)

re: fclean all

#.PHONY: all clean fclean re