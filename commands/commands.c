/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:02:49 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/03 20:49:53 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	commands(char **input, char **env)
{
	int	i;

	if (input[1])
	{
		i = 1;
		while (input[i])
		{
			if (find_quote(input[i]) == 2)
			{
				input[i] = remove_quotes(input[i]);
			}
			i++;
		}
	}
	if (input[0])
	{
		if (!ft_strncmp(input[0], "echo", 5))
			ft_echo(input);
		else if (!ft_strncmp(input[0], "cd", 3))
			ft_cd(input, env);
		else if (!ft_strncmp(input[0], "pwd", 4))
			ft_pwd();
		else if (!ft_strncmp(input[0], "export", 7))
			ft_export(input);
		else if (!ft_strncmp(input[0], "unset", 6))
			ft_unset(input);
		else if (!ft_strncmp(input[0], "env", 4))
			ft_env(input);
		else if (!ft_strncmp(input[0], "exit", 5))
			ft_exit(input);
		else if (!ft_strncmp(input[0], "change_color", 13))
			change_color(input);
		else
			env_commands(input, env);
		// if (com_info()->pid == 0)
		// 	exit(com_info()->exit_value);
	}
}
