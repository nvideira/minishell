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
CFLAGS = -I. -Wall -Werror -Wextra -g -fsanitize=address

NAME = minishell

INCLUDE = .

SRC = \
	main.c init_shell.c signals.c print_dir.c \
	env_to_lst.c free_env.c free_all.c \
	shell_split.c shell_split_utils.c \
	exported_vars.c process_input.c \
	\
	parser/parser.c parser/parser_utils.c parser/parser_checks.c \
	parser/parse_input.c parser/separate_input.c\
	\
	commands/commands.c commands/env_commands.c commands/ft_exit.c \
	commands/ft_echo.c commands/ft_unset.c commands/ft_export.c \
	commands/ft_env.c commands/ft_pwd.c commands/change_color.c \
	commands/ft_export_utils.c commands/ft_export_utils2.c \
	commands/ft_export_utils3.c commands/ft_echo_utils.c commands/cd_errors.c\
	commands/ft_unset_utils.c commands/ft_cd.c commands/ft_exit_utils.c \
	\
	libft/get_next_line.c libft/add_mat_node.c libft/ft_atoi.c \
	libft/ft_clear.c libft/ft_isdigit.c libft/ft_itoa.c libft/ft_strtrim.c \
	libft/ft_memmove.c libft/ft_strchr.c libft/ft_strcmp.c \
	libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlen.c \
	libft/ft_strljoin.c libft/ft_substr.c libft/lst_add_front.c \
	libft/strict_cmp.c libft/ft_putnbr_fd.c libft/ft_putchar_fd.c \
	libft/ft_error.c libft/ft_error_utils.c libft/ft_putstr_fd.c \
	libft/ft_strichr.c libft/ft_strncmp.c libft/ft_substring.c \
	libft/join_strings.c \
	\
	pipes/pipes.c pipes/utils_pipe.c \
	\
	quotes_ds/remove_quote.c quotes_ds/process_ds.c \
	quotes_ds/process_quotes.c quotes_ds/process_ds_utils.c \
	quotes_ds/check_all_quotes.c quotes_ds/utils_extra.c\
	\
	redirections/redirections.c redirections/heredoc.c \
	redirections/redirections_utils.c redirections/verify_redir.c \
	redirections/redirections_input.c redirections/redirections_output.c \
	
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

valgrind: re
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

a:
	make && make clean && ./minishell

.PHONY: all clean fclean re a
