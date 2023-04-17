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

#include "minishell.h"

// Compara o nome das variaveis
int	cmp_name(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i] && s1[i] > s2[i])
			return (1);
		else if (s1[i] != s2[i] && s1[i] < s2[i])
			return (0);
		i++;
	}
	return (0);
}

// Ordena a lista de variaveis
t_env_lst	*sort_list(t_env_lst *curr)
{
	t_env_lst	*head;
	int			i;

	head = curr;
	i = 0;
	while (i == 0)
	{
		i = 1;
		while (curr->next)
		{
			if (cmp_name(curr->name, curr->next->name) == 1)
			{
				do_sort(curr, head);
				i = 0;
			}
			else
				curr = curr->next;
		}
		curr = head;
	}
	return (curr);
}

void	do_sort(t_env_lst *curr, t_env_lst *head)
{
	char		*temp;
	char		*value;

	temp = ft_strdup(curr->name);
	value = ft_strdup(curr->value);
	free(curr->name);
	curr->name = ft_strdup(curr->next->name);
	free(curr->value);
	curr->value = ft_strdup(curr->next->value);
	free(curr->next->name);
	curr->next->name = ft_strdup(temp);
	free(curr->next->value);
	curr->next->value = ft_strdup(value);
	curr = head;
	free(temp);
	free(value);
}
