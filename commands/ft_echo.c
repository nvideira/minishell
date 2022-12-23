/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:31:01 by marvin            #+#    #+#             */
/*   Updated: 2022/11/17 23:31:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **input)
{
	if (!input[1])
	{
		printf("\n");
		com_info()->exit_value = 0;
	}
	else if (!ft_strncmp(input[1], "$?", 3))
	{
		printf("%d\n", com_info()->exit_value);
		com_info()->exit_value = 0;
	}
	else if (input[1][0] == '$' && ft_strlen(input[1]) < 2)
		do_print(input, 1, 1);
	else if (input[1][0] == '$')
		print_vars(input);
	else if (!ft_strncmp(input[1], "-n", 3))
		do_print(input, 2, 2);
	else if (!ft_strncmp(input[1], "-e", 3))
		process_flags(input, 2);
	else
		do_print(input, 1, 1);
}

/*
Se tiver uma barra sozinha \, tem de ignorar
Se tiver uma barra com alguma coisa a frente, tem de processar
*/

/*
INPUT: echo a b c
a b c

INPUT: echo "a" "b" "c"
a b c

INPUT: echo a\nb\nc
anbnc

INPUT: echo a \n b \n c
a n b n c

INPUT: echo "a\nb\nc"
a
b
c
*/