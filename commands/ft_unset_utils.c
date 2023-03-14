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

#include "minishell.h"

// Verifica se a variável existe na env_lst e na vars
// Executa o unset
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

// Verifica se a variável existe
int	check_if_exists_unset(char *input, t_env_lst *temp)
{
	t_env_lst	*head;

	head = temp;
	while (head)
	{
		if (head->name == NULL)
			return (0);
		if (!ft_strncmp(input, head->name, ft_strlen(input)))
			return (1);
		head = head->next;
	}
	return (0);
}

// Executa o unset
void	do_unset(char *input, t_env_lst *lst)
{
	t_env_lst	*head;

	head = lst;
	while (lst)
	{
		if (!ft_strncmp(input, lst->name, (ft_strlen(lst->name) - 1)))
		{
			if (!lst->next && !lst->prev)
				head = NULL;
			else if (!lst->next)
				lst->prev->next = NULL;
			else if (!lst->prev)
			{
				head = lst->next;
				lst->next->prev = NULL;
			}
			else
			{
				lst->prev->next = lst->next;
				lst->next->prev = lst->prev;
			}
			free(lst->name);
			free(lst->value);
			lst->name = NULL;
			lst->value = NULL;
			if (head != NULL)
				free(lst);
			break ;
		}
		lst = lst->next;
	}
	lst = head;
}
