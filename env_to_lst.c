/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:25:45 by nvideira          #+#    #+#             */
/*   Updated: 2023/03/22 18:32:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst	*ft_lstlast(t_env_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	lst_add_back(t_env_lst **lst, t_env_lst *new)
{
	t_env_lst	*last;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
	new->prev = last;
}

int	find_es_or_eol(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' || str[i] == '\0')
			return (i);
		i++;
	}
	return (i);
}

t_env_lst	*new_node(char *env)
{
	t_env_lst	*env_node;

	env_node = malloc(sizeof(t_env_lst));
	if (!env_node)
		return (NULL);
	env_node->name = ft_substr(env, 0, find_es_or_eol(env) + 1);
	env_node->value = ft_substr(env, find_es_or_eol(env) + 1, ft_strlen(env));
	env_node->next = NULL;
	env_node->prev = NULL;
	return (env_node);
}

t_env_lst	*env_to_lst(char **env)
{
	int			i;
	t_env_lst	*env_lst;

	i = 0;
	env_lst = NULL;
	while (env[i])
	{
		lst_add_back(&env_lst, new_node(env[i]));
		i++;
	}
	return (env_lst);
}
