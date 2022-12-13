/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:44:22 by jlebre            #+#    #+#             */
/*   Updated: 2022/12/13 15:16:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(char **input)
{
	int			i;
	int			k;
	t_env_lst	*head;

	k = 0;
	if (!input[1])
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	i = 1;
	head = com_info()->env_lst;
	while (input[i])
	{
		while (com_info()->env_lst)
		{
			if (!ft_strncmp(input[i], com_info()->env_lst->name,
				(ft_strlen(com_info()->env_lst->name) - 1) - 1))
			{
				free(com_info()->env_lst->name);
				free(com_info()->env_lst->value);
				free(com_info()->env_lst);
				com_info()->env_lst->prev->next = com_info()->env_lst->next;
				k++;
				//break ;
			}
			com_info()->env_lst = com_info()->env_lst->next;
		}
		com_info()->env_lst = head;
		i++;
	}
	if (k == 0)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	com_info()->exit_value = 0;
	com_info()->env_lst = head;
}
