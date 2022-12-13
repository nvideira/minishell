/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 02:39:27 by marvin            #+#    #+#             */
/*   Updated: 2022/12/13 02:39:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_lst	*sort_list(void)
{
	char		*temp;
	char		*value;
	t_env_lst	*curr;
	t_env_lst	*head;

	curr = com_info()->env_lst;
	head = curr;
	if (curr)
	{
		while(curr && curr->next)
		{
			if (ft_strcmp(curr->name, curr->next->name))
			{
				temp = curr->name;
				value = curr->value;
				curr->name = curr->next->name;
				curr->value = curr->next->value;
				curr->next->name = temp;
				curr->next->value = value;
			}
			curr = curr->next;
		}
	}
	curr = head;
	return (curr);
}