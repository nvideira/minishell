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

#include "minishell.h"

// Faz as verificações para saber se o comando echo tem a flag -n
int	check_n(char **input)
{
	int i;

	i = 1;
	while (input[1][i] && input[1][i] != ' ')
	{
		if (input[1][i] != 'n' && input[1][i] != 'e')
			return (0);
		i++;
	}
	return (1);
}

// Recria o comando echo
// Tem as funcionalidades de -n e -e
// Também tem a funcionalidade de imprimir o que é passado como argumento
void	ft_echo(char **input)
{
	if (!input[1])
		write(1, "\n", 1);
	else if (!ft_strncmp(input[1], "-n", 2))
	{
		if (check_n(input))
			do_print(input, 2, 2);
		else
			do_print(input, 1, 1);
	}
	else if (!ft_strncmp(input[1], "-e", 3))
		process_flags(input, 2);
	else
		do_print(input, 1, 1);
	com_info()->exit_value = 0;
}
