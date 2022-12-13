/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:55:34 by jlebre            #+#    #+#             */
/*   Updated: 2022/12/09 17:53:27 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_commands(char **input, char **env)
{
	char		*arr[2];
	int			i;
	int			cenas;
	int			temp;
	t_env_lst	*temp_lst;

	i = 0;
	temp_lst = com_info()->env_lst;
	arr[0] = find_path(input[0], temp_lst);
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
		while (temp_lst->next)
		{
			while (env[i])
			{
				if (ft_strcmp(ft_strjoin(temp_lst->name, temp_lst->value), env[i]))
				{
					if (execve(arr[0], arr, env) == -1)
					{
						com_info()->exit_value = 126;
						ft_error("Deu Merda");
					}
				}
				i++;
			}
			i = 0;
			temp_lst = temp_lst->next;
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
		j++;
	}
	if (temp == NULL)
		return (0);
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
