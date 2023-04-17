/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:34:43 by marvin            #+#    #+#             */
/*   Updated: 2022/12/15 18:34:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Imprime o que foi passado para o comando echo
void	do_print(char **input, int start, int type)
{
	while (start < com_info()->nb_args)
	{
		write(1, input[start], ft_strlen(input[start]));
		if ((com_info()->nb_args - start) != 1)
			write(1, " ", 1);
		start++;
	}
	if (type != 2)
		write(1, "\n", 1);
}

//com_info()->exit_value = 0;

// Verifica qual flag foi passada para o comando echo -e
void	check_flag(char c)
{
	if (c == 'a')
		write(1, "\a", 1);
	else if (c == 'b')
		write(1, "\b", 1);
	else if (c == 't')
		write(1, "\t", 1);
	else if (c == 'n')
		write(1, "\n", 1);
	else if (c == 'v')
		write(1, "\v", 1);
	else if (c == 'f')
		write(1, "\f", 1);
	else if (c == 'r')
		write(1, "\r", 1);
	return ;
}

// Processa as flags para o comando echo -e
void	process_flags(char **input, int start)
{
	int	i;

	i = 0;
	while (start < com_info()->nb_args)
	{
		while (input[start][i])
		{
			if (input[start][i] == '\\')
			{
				i++;
				if (ft_strchr("abtnvfr", input[start][i]))
					check_flag(input[start][i]);
			}
			else
				printf("%c", input[start][i]);
			i++;
		}
		if ((com_info()->nb_args - start) != 1)
			printf(" ");
		start++;
	}
	printf("\n");
	com_info()->exit_value = 0;
}
