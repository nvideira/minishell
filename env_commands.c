/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:55:34 by jlebre            #+#    #+#             */
/*   Updated: 2022/11/24 15:56:45 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_commands(char **input)
{
	char	*arr[2];
	int		cenas;
	int		temp;

	arr[0] = find_path(input[0], com_info()->env_lst);
	if (!arr[0])
	{
		printf("\033[0;31mCommand not found: %s\033[0m\n", input[0]);
		com_info()->exit_value = 127;
		return ;
	}
	arr[1] = input[1];
	arr[2] = 0;
	cenas = fork();
	if (!cenas)
	{
		if (execve(arr[0], arr, com_info()->args) == -1)
		{
			com_info()->exit_value = 126;
			red("Deu Merda\n");
		}
	}
	waitpid(cenas, &temp, 0);
	com_info()->exit_value = temp / 256;
}

char	*find_path(char *cmd, t_env_lst *env_lst)
{
	int			j;
	t_env_lst	*temp;
	char		*path;
	char		*ret_path;

	j = 0;
	temp = env_lst;
	while (temp && ft_strncmp(temp->name, "PATH=", 5))
	{
		temp = temp->next;
	}
	path = temp->value;
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
