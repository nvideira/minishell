/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:44:22 by jlebre            #+#    #+#             */
/*   Updated: 2022/12/16 17:48:38 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_error()
{
	printf("unset: not enough arguments\n");
	return ;
}

void	ft_unset(char **input)
{
	int			i;
	t_env_lst	*head;

	if (!input[1])
		unset_error();
	i = 1;
	head = com_info()->env_lst;
	while (input[i])
	{
		//printf("INPUT: %s\n", input[i]);
		while (com_info()->env_lst)
		{
			//printf("NAMEI: %s\nNAMEL: %s\nSIZE: %i\n\n", input[i], com_info()->env_lst->name, ft_strlen(com_info()->env_lst->name));
			if (!ft_strncmp(input[i], com_info()->env_lst->name,
				(ft_strlen(com_info()->env_lst->name) - 1))
				&& ft_strncmp(com_info()->env_lst->name, "_=", 2))
			{
				//printf("NAME: %s\nVALUE: %s\n", com_info()->env_lst->name, com_info()->env_lst->value);
				free(com_info()->env_lst->name);
				free(com_info()->env_lst->value);
				if (!com_info()->env_lst->next)
					com_info()->env_lst->prev->next = NULL;
				else
				{
					com_info()->env_lst->prev->next = com_info()->env_lst->next;
					com_info()->env_lst->next->prev = com_info()->env_lst->prev;
				}
				break ;
			}
			com_info()->env_lst = com_info()->env_lst->next;
		}
		com_info()->env_lst = head;
		i++;
	}
	//com_info()->env_lst = head;
	com_info()->exit_value = 0;
}

/*
export a=3 b=5 c=7
*/