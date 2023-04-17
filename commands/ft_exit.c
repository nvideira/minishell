/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:08:28 by jlebre            #+#    #+#             */
/*   Updated: 2022/11/29 19:08:28 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit2(char **input)
{
	char	*value;

	if (input[1][0] == '$' && ft_strlen(input[1]) > 1)
	{
		value = print_vars_exit(input);
		check_error_3(value, input);
	}
	check_error_3(input[1], input);
}

// Recria a função exit
void	ft_exit(char **input)
{
	int		i;

	i = 0;
	while (input[i])
		i++;
	if (i > 2)
	{
		if (input[2])
			exit_errors(2, input);
		else if (!ft_isdigit(input[1]))
			exit_errors(1, input);
		else
			exit_errors(2, input);
	}
	else if (i == 2)
		ft_exit2(input);
	else
		do_exit(com_info()->exit_value, input);
}

// Função que executa o exit
void	do_exit(int exit_value, char **input)
{
	write(1, "exit\n", 5);
	rl_clear_history();
	free_matrix(input);
	free_list(com_info()->env_lst);
	free_list(com_info()->vars);
	exit(exit_value);
}
