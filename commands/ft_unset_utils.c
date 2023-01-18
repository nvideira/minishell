/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 04:06:43 by marvin            #+#    #+#             */
/*   Updated: 2022/12/28 04:06:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_error(void)
{
	ft_error("unset: not enough arguments\n");
	return ;
}

void	do_unset(char *input, t_env_lst *lst)
{
	t_env_lst	*head;

	head = lst;	
	while (lst)
	{
		if (!ft_strncmp(input, lst->name, (ft_strlen(lst->name) - 1))
			&& ft_strncmp(lst->name, "_=", 2))
		{
			free(lst->name);
			free(lst->value);
			if (!lst->next && !lst->prev)
				head = NULL;
			else if (!lst->next)
				lst->prev->next = NULL;
			else
			{
				lst->prev->next = lst->next;
				lst->next->prev = lst->prev;
			}
			break ;
		}
		lst = lst->next;
	}
	lst = head;
}

int	check_if_exists_unset(char *input, t_env_lst *temp)
{
	while (temp)
	{
		if (!ft_strncmp(input, temp->name, ft_strlen(input)))
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	check_unset(char *input)
{
	int	exist1;
	int	exist2;

	exist1 = check_if_exists_unset(input, com_info()->env_lst);
	exist2 = check_if_exists_unset(input, com_info()->vars);
	if (exist1)
		do_unset(input, com_info()->env_lst);
	if (exist2)
		do_unset(input, com_info()->vars);
}
