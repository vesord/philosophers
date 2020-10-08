# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matrus <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/03 13:49:59 by matrus            #+#    #+#              #
#    Updated: 2020/10/06 13:28:14 by matrus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two

INCLUDES = philo_two.h

SRCS = 	initialization.c main_thread.c phil_function.c \
		philo_two.c set_arg.c utils.c philo_thread.c \
		utils2.c

OBJDIR = ./obj

OBJ = $(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))

CC = gcc
FLAGS = -Wall -Wextra -Werror

.PHONY: all
all: $(OBJDIR) $(NAME)
	@echo Philo_one is ready to die!

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ -o $(NAME)

$(OBJ): $(OBJDIR)/%.o: %.c $(INCLUDES)
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJDIR)

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

.PHONY: re
re: fclean all
