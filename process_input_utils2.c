/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 04:59:21 by marvin            #+#    #+#             */
/*   Updated: 2023/01/12 04:59:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*get_name(char *str)
{
	int			len;
	int			i;
	char		*name;

	len = 0;
	i = 0;
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
	return (name);
}

int	check_if_exists_vars(char *str)
{
	t_env_lst	*temp;
	char		*name;

	temp = com_info()->vars;
	name = get_name(str);
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, ft_strlen(name)))
		{
			free(name);
			return (1);
		}
		temp = temp->next;
	}
	free(name);
	return (0);
}

void	change_value_vars(char *str)
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
	head = com_info()->vars;
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
	while (com_info()->vars->name != name)
	{
		if (!ft_strncmp(name, com_info()->vars->name, (len + 1)))
		{
			com_info()->vars->value = value;
			break ;
		}
		com_info()->vars = com_info()->vars->next;
	}
	com_info()->vars = head;
}