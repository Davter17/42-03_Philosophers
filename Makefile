NAME = philo

SRCS_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRCS = $(SRCS_DIR)/main.c \
       $(SRCS_DIR)/utils.c \
       $(SRCS_DIR)/philo_utils.c \
       $(SRCS_DIR)/start.c \
       $(SRCS_DIR)/routine.c \
       $(SRCS_DIR)/watchers.c

OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I$(INC_DIR)

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@printf "  \033[33m⚙\033[0m  Compiling %d files...\n" $(words $(OBJS))
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@printf "  \033[32m✓\033[0m Compiled %d files → $(NAME)\n" $(words $(OBJS))
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@printf "  \033[31m✗\033[0m  Removing object files...\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "  \033[31m✗\033[0m  Removing $(NAME)...\n"
	@rm -f $(NAME)

re: fclean all
