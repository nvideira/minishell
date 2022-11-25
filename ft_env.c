/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:29:02 by marvin            #+#    #+#             */
/*   Updated: 2022/11/18 12:29:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env()
{
	while (com_info()->env_lst)
	{
		printf("%s%s\n", com_info()->env_lst->name, com_info()->env_lst->value);
		com_info()->env_lst = com_info()->env_lst->next;
	}
	com_info()->exit_value = 0;
}

void	ft_unset()
{
	free_env(&com_info()->env_lst);
	com_info()->args = lst_to_env(com_info()->env_lst);
	com_info()->exit_value = 0;
}