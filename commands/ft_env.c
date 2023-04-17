/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:46:39 by jlebre            #+#    #+#             */
/*   Updated: 2023/03/23 22:19:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ft_env(char *name, char *value)
{
	write(1, name, ft_strlen(name));
	write(1, value, ft_strlen(value));
	write(1, "\n", 1);
}

// Recria o comando env
void	ft_env(char **input)
{
	t_env_lst	*temp;
	char		*path;

	path = find_path("env", com_info()->env_lst);
	if (env_errors(path, input))
		return ;
	temp = com_info()->env_lst;
	while (temp)
	{
		if (ft_strchr(temp->name, '='))
			print_ft_env(temp->name, temp->value);
		temp = temp->next;
	}
	com_info()->exit_value = 0;
	free(path);
}

int	env_errors(char *path, char **input)
{
	if (!path)
	{
		ft_error("command not found: env\n");
		com_info()->exit_value = 127;
		return (1);
	}
	if (input[1])
	{
		ft_error("Env: '%s': No such file or directory\n",
			input[1]);
		com_info()->exit_value = 127;
		free(path);
		return (1);
	}
	return (0);
}
