# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 15:59:38 by jlebre            #+#    #+#              #
#    Updated: 2022/10/25 15:59:38 by jlebre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
RM = @rm -rf
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address

NAME = minishell

INCLUDE = .

SRC = main.c init_shell.c print_dir.c ft_error.c shell_split.c commands.c \
	process_input.c play_sound.c utils.c utils2.c colors.c print_header.c \
	utils_pipe.c env_to_lst.c free_env.c 
	
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	@$(CC) $(OBJ) $(CFLAGS) -lreadline -o $(NAME)
	@echo " __  __ _      _ ___ _        _ _ "
	@echo "|  \/  (_)_ _ (_) __| |_  ___| | |"
	@echo "| |\/| | | ' \| \__ \ ' \/ -_) | |"
	@echo "|_|  |_|_|_||_|_|___/_||_\___|_|_|"
	@echo "\033[0;32mMiniShell Compiled!\033[0m"
 
.c.o:
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $(<:.c=.o)

valgrind:
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --log-file=valgrind-out.txt \
         ./${NAME}

clean:
	$(RM) $(OBJ)
	@echo "\033[0;31m.o Files Removed!\033[0m"

fclean: clean
	$(RM) $(NAME) 
	@echo "\033[0;31mMiniShell Removed!\033[0m"

re: fclean all

.PHONY: all clean fclean re
