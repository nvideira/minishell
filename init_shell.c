/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:18 by jlebre            #+#    #+#             */
/*   Updated: 2023/02/11 17:56:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cenas_do_env(char *str)
{
	char		*user;
	t_env_lst	*temp;

	temp = com_info()->env_lst;
	while (temp)
	{
		if (!ft_strncmp(temp->name, str, sizeof(str)))
		{
			user = ft_strdup(temp->value);
			return (user);
		}
		temp = temp->next;
	}
	return (NULL);
}

// Função que inicializa a shell
void	init_shell(char **env)
{
	char	*username;

	com_info()->env_lst = env_to_lst(env);
	com_info()->vars = NULL;
	com_info()->color = "\033[1;32m:";
	com_info()->env = env;
	if (check_if_exists("USER", com_info()->env_lst))
		username = getenv("USER");
	else
	{
		write(1, "USER not found, setting to 'user'\n", 35);
		lst_add_back(&com_info()->env_lst, new_node("USER=user"));
		username = get_cenas_do_env("USER=");
	}
	write(1, "\n\nUSER is: @", 12);
	write(1, username, ft_strlen(username));
	write(1, "\n", 1);
}
