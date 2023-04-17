/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:18 by jlebre            #+#    #+#             */
/*   Updated: 2023/03/23 15:51:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Get Cenas do Env (Sigle por causa da norminette)
char	*gce(char *str)
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
void	init_shell(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	com_info()->env_lst = env_to_lst(env);
	com_info()->vars = NULL;
	com_info()->color = "\033[1;32m:";
	com_info()->env = env;
	if (!check_if_exists("USER", com_info()->env_lst))
		lst_add_back(&com_info()->env_lst, new_node("USER=user"));
}
