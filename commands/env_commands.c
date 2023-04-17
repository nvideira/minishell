/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:55:34 by jlebre            #+#    #+#             */
/*   Updated: 2023/03/23 22:19:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Executa os comandos que não são builtins
void	env_commands(char **input, char **env)
{
	char	*path;

	path = find_path(input[0], com_info()->env_lst);
	if (!path)
	{
		ft_error("%s: command not found\n", input[0]);
		catch_signal();
		exit(127);
	}
	else if (execve(path, input, env) == -1)
	{
		ft_error("Deu Merda\n");
		exit(126);
	}
	free(path);
}

// Encontra o path do comando
char	*find_path(char *cmd, t_env_lst *env_lst)
{
	int			j;
	t_env_lst	*temp;
	char		*path;

	j = 0;
	temp = env_lst;
	while (temp && ft_strncmp(temp->name, "PATH=", 5))
		temp = temp->next;
	if (temp == NULL)
		return (0);
	path = temp->value;
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (!access(cmd, F_OK))
			return (cmd);
	}
	else
		return (find_return_path(path, j, cmd));
	return (0);
}

// Junta o path com o comando
char	*find_return_path(char *path, int j, char *cmd)
{
	char	*ret_path;
	int		len;

	len = ft_strlen(path);
	while (j < len && path[j] && ft_strichr(path, j, ':') > -1)
	{
		ret_path = join_strings(path, j, cmd);
		if (!access(ret_path, F_OK))
			return (ret_path);
		free(ret_path);
		j += ft_strichr(path, j, ':') - j + 1;
	}
	if (j < len && path[j] && ft_strichr(path, j, ':') < 0)
	{
		ret_path = join_strings(path, j, cmd);
		if (!access(ret_path, F_OK))
			return (ret_path);
		free(ret_path);
	}
	return (0);
}
