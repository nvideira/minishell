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

#include "../minishell.h"

void	exit_errors(int error, char **input)
{
	if (error == 1)
	{
		ft_error("exit\nexit: %s: numeric argument required\n", input[1]);
		rl_clear_history();
		free (input);
		exit(2);
	}
	else if (error == 2)
	{
		ft_error("exit\nexit: too many arguments\n");
		com_info()->exit_value = 1;
		return ;
	}
	else if (error == 3)
	{
		ft_error("exit\nexit: %s: numeric argument required\n", input[1]);
		rl_clear_history();
		free (input);
		exit(2);
	}
}

void	do_exit(int exit_value, char **input)
{
	printf("exit\n");
	rl_clear_history();
	free (input);
	exit(exit_value);
}

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

void	check_error_3(char *arg, char **input)
{
	if (!ft_isdigit(arg))
		exit_errors(3, input);
	else
		do_exit(ft_atoi(arg), input);
}

void	ft_exit(char **input)
{
	int		i;
	char	*value;

	i = 0;
	while (input[i])
		i++;
	if (i > 2)
	{
		if (!ft_isdigit(input[1]))
			exit_errors(1, input);
		else
			exit_errors(2, input);
	}
	else if (i == 2)
	{
		if (input[1][0] == '$' && ft_strlen(input[1]) > 1)
		{
			value = print_vars_exit(input);
			check_error_3(value, input);
		}
		check_error_3(input[1], input);
	}
	else
		do_exit(com_info()->exit_value, input);
}
