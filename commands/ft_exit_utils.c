/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:30:37 by marvin            #+#    #+#             */
/*   Updated: 2023/02/06 18:31:25 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Função que imprime as variáveis de ambiente
char	*print_vars_exit(char **input)
{
	t_env_lst	*temp;
	char		*name;

	name = input[1];
	temp = com_info()->vars;
	name++;
	while (temp)
	{
		if (!ft_strncmp(name, com_info()->vars->name, ft_strlen(name) - 1))
			return (com_info()->vars->value);
		temp = temp->next;
	}
	return (0);
}

// Verifica se o exit tem erros
void	exit_errors(int error, char **input)
{
	if (error == 1)
	{
		write(1, "exit\n", 5);
		write(2, "exit: numeric argument required", 31);
		rl_clear_history();
		free_matrix(input);
		exit(2);
	}
	else if (error == 2)
	{
		write(1, "exit\n", 5);
		write(2, "exit: too many arguments", 24);
		com_info()->exit_value = 1;
		return ;
	}
}

// Verifica se o exit tem erros
void	check_error_3(char *arg, char **input)
{
	if (!ft_strncmp(arg, "-9223372036854775809", 20))
		exit_errors(1, input);
	if (!ft_isdigit(arg) || !check_size_int(arg))
		exit_errors(1, input);
	else
		do_exit(ft_atoi(arg), input);
}

// Verifica se o input é maior que um int64
int	check_size_int(char *str)
{
	char	*max_int;
	int		i;

	i = 0;
	max_int = "9223372036854775807";
	while (str[i] && max_int[i])
	{
		if (str[i] > max_int[i])
			return (0);
		if (str[i] < max_int[i])
			return (1);
		i++;
	}
	return (1);
}

int	convert_return_value(int exit_value)
{
	if (exit_value == 0)
		return (0);
	else if (exit_value == 1)
		return (1);
	else if (exit_value == 2)
		return (2);
	else if (exit_value == 256)
		return (1);
	else
		return ((exit_value >> 8 & 255));
}
