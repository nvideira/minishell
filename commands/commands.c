/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebee <jlebee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:02:49 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/23 29:08:32 by jlebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	commands(char **input, char **env, int is_fork)
{
	if (input[0])
	{
		if (!ft_strncmp(input[0], ">", 1) || !ft_strncmp(input[0], "<", 1))
			check_redir(input);
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
			fork_commands(input, env, is_fork);
	}
}

void	fork_commands(char **input, char **env, int is_fork)
{
	int	cenas;

	signal_block();
	if (!is_fork)
	{
		cenas = fork();
		if (cenas == 0)
			env_commands(input, env);
		else
			waitpid(cenas, &com_info()->exit_value, 0);
	}
	else
		env_commands(input, env);
}
