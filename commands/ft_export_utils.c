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
	char		*temp;
	char		*value;
	t_env_lst	*head;

	head = curr;
	while (curr->next)
	{
		if (cmp_name(curr->name, curr->next->name) == 1)
		{
			temp = ft_strdup(curr->name);
			value = ft_strdup(curr->value);
			curr->name = ft_strdup(curr->next->name);
			curr->value = ft_strdup(curr->next->value);
			curr->next->name = ft_strdup(temp);
			curr->next->value = ft_strdup(value);
			curr = head;
		}
		else
			curr = curr->next;
	}
	curr = head;
	return (curr);
}

// Imprime as variaveis exportadas
void	print_exported(char **input)
{
	t_env_lst	*temp;

	(void)input;
	temp = sort_list(com_info()->env_lst);
	while (temp)
	{
		if (ft_strncmp(temp->value, "", 1))
			printf("declare -x %s\"%s\"\n", temp->name, temp->value);
		else
			printf("declare -x %s\n", temp->name);
		temp = temp->next;
	}
	com_info()->exit_value = 0;
}
