# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 11:50:04 by nvideira          #+#    #+#              #
#    Updated: 2022/10/17 11:52:23 by nvideira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.c

OBJS	= ${SRCS:.c=.o}

NAME	= minishell

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}
			
re:			fclean all

.PHONY:		all clean fclean re
