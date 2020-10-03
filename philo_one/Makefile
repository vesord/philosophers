NAME = philo_one

INCLUDES = philo_one.h philosopher.h 

SRCS = 	initialization.c main_thread.c phil_function.c \
		philo_one.c set_arg.c utils.c

OBJDIR = ./obj

OBJ = $(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))

CC = gcc
#FLAGS = -Wall -Wextra -Werror

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
