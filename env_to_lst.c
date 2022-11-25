/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:25:45 by nvideira          #+#    #+#             */
/*   Updated: 2022/11/24 16:00:25 by jlebre           ###   ########.fr       */
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
	//printf("teste2\n");
	return (lst);
}

void	lst_add_back(t_env_lst **lst, t_env_lst *new)
{
	t_env_lst   *last;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	//printf("teste\n");
	last = ft_lstlast(*lst);
	last->next = new;
}

t_env_lst   *new_node(char *env)
{
	t_env_lst   *env_node;

	env_node = malloc(sizeof(t_env_lst));
	if (!env_node)
		return (NULL);
	env_node->name = ft_substr(env, 0, ft_strchr(env, '=') + 1);
	env_node->value = ft_substr(env, ft_strchr(env, '=') + 2, ft_strlen(env));
	//printf("%s\n", env_node->value);
	env_node->next = NULL;
	return (env_node);
}

t_env_lst   *env_to_lst(char **env)
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

char    **lst_to_env(t_env_lst *lst)
{
	static char	**myenv;
	int	i;

	i = 0;
	myenv[i] = malloc(sizeof(char *) * 100);
	if (!myenv)
		return (NULL);
	while (lst->next)
	{
		myenv[i] = lst->value;
		i++;
		lst = lst->next;
	}
	return (myenv);
}
