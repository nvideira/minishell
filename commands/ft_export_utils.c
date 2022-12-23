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

t_env_lst	*sort_list(t_env_lst	*curr)
{
	char		*temp;
	char		*value;
	t_env_lst	*head;

	head = curr;
	while(curr->next)
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

void	print_exported(char **input)
{
	t_env_lst	*temp;
	(void)input;

	temp = sort_list(com_info()->env_lst);
	while (temp)
	{
		printf("declare -x %s\"%s\"\n", temp->name, temp->value);
		temp = temp->next;
	}
	com_info()->exit_value = 0;
}

int	check_if_exists(char *str)
{
	t_env_lst	*temp;
	char		*name;
	int			len;
	int			i;

	len = 0;
	i = 0;
	temp = com_info()->env_lst;
	while (str[len] != '=')
		len++;
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
		return (0);
	while (i < len)
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, len))
		{
			free(name);
			return (1);
		}
		temp = temp->next;
	}
	free(name);
	return (0);
}

void	change_value(char *str)
{
	t_env_lst	*head;
	char		*name;
	char		*value;
	int			len;
	int			len_val;
	int			i;
	int			j;

	len = 0;
	i = 0;
	j = 0;
	head = com_info()->env_lst;
	while (str[len] != '=')
		len++;
	name = malloc(sizeof(char) * (len + 2));
	if (!name)
		return ;
	len_val = (ft_strlen(str) - (len + 1));
	value = malloc(sizeof(char) * (len_val + 1));
	if (!value)
		return ;
	while (i < len && str[i])
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '=';
	i++;
	name[i] = '\0';
	while (str[i])
	{
		value[j] = str[i];
		i++;
		j++;
	}
	while (com_info()->env_lst->name != name)
	{
		if (!ft_strncmp(name, com_info()->env_lst->name, (len + 1)))
		{
			com_info()->env_lst->value = value;
			break ;
		}
		com_info()->env_lst = com_info()->env_lst->next;
	}
	com_info()->env_lst = head;
}
