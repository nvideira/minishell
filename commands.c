/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:02:49 by jlebre            #+#    #+#             */
/*   Updated: 2022/11/14 15:25:36 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commands(char **input, char **env)
{
	if (input[0])
	{
		if (!ft_strncmp(input[0], "cd", 3))
			change_dir(input);
		else if (!ft_strncmp(input[0], "pwd", 4))
			printf("%s\n", print_dir());
		else if (!ft_strncmp(input[0], "echo", 5))
			printf("%s\n", input[1]);
		else 
			env_commands(input, env);
	}
	
}

void	env_commands(char **input, char **env)
{
	char	*arr[2];
	int		cenas;

	arr[0] = find_path(input[0], env);
	if (!arr[0])
	{
		printf("\033[0;31mcommand not found: %s\033[0m\n", input[0]);
		return ;
	}
	arr[1] = input[1];
	arr[2] = 0;
	cenas = fork();
	if (!cenas)
	{
		if (execve(arr[0], arr, env) == -1)
		{
			ft_error("Failed", env);
		}
	}
	waitpid(cenas, NULL, 0);
}

char	*find_path(char *cmd, char **env)
{
	int		j;
	char	*path;
	char	*ret_path;

	j = 0;
	while (env[j] && ft_strncmp(env[j], "PATH=", 5))
		j++;
	path = env[j];
	while (path[j] && ft_strichr(path, j, ':') > -1)
	{
		ret_path = join_strings(path, j, cmd);
		if (!access(ret_path, F_OK))
			return (ret_path);
		free(ret_path);
		j += ft_strichr(path, j, ':') - j + 1;
	}
	if (path[j] && ft_strichr(path, j, ':') < 0)
	{
		ret_path = join_strings(path, j, cmd);
		if (!access(ret_path, F_OK))
			return (ret_path);
		free(ret_path);
	}
	return (0);
}

void	change_dir(char **input)
{
	if (input[1])
		chdir(input[1]);
	else
		chdir(ft_strjoin("/nfs/homes/", getenv("USER")));
}
