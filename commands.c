/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:02:49 by jlebre            #+#    #+#             */
/*   Updated: 2022/11/22 17:38:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commands(char **input)
{
	if (input[0])
	{
		if (!ft_strncmp(input[0], "echo", 5))
			ft_echo(input);
		else if (!ft_strncmp(input[0], "cd", 3))
			change_dir(input);
		else if (!ft_strncmp(input[0], "pwd", 4))
		{
			printf("%s\n", print_dir());
			com_info()->exit_value = 0;
		}
		else if (!ft_strncmp(input[0], "export", 7))
			printf("EXPORT: %s\n", input[1]);
		else if (!ft_strncmp(input[0], "unset", 6))
			ft_unset();
		else if (!ft_strncmp(input[0], "env", 4))
			ft_env();
		else if (!ft_strncmp(input[0], "exit", 5))
			{
			rl_clear_history();
			free (input);
			exit(com_info()->exit_value);
			}
		else
			env_commands(input);
	}
}
