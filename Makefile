# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 20:39:17 by mpico-bu          #+#    #+#              #
#    Updated: 2025/04/22 20:13:51 by mpico-bu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = 	src/main.c \
		src/utils.c \
		src/philo_utils.c \
		src/start.c \
		src/routine.c \
		src/watchers.c
		
OBJDIR = obj

OBJS = 	obj/main.o \
		obj/utils.o \
		obj/philo_utils.o \
		obj/start.o \
		obj/routine.o \
		obj/watchers.o

CFLAGS = -Wall -Wextra -Werror 
# -g3 -fsanitize=thread -pthread

CC = cc

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	chmod +x $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
