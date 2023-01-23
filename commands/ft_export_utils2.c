/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:40:48 by marvin            #+#    #+#             */
/*   Updated: 2022/12/28 00:40:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_export(char *input)
{
	int	exist1;
	int	exist2;

	exist1 = check_if_exists(input);
	exist2 = check_if_exists2(input);
	if (exist1)
	{
		if (exist2)
			change_value2(input);
		change_value(input);
	}
	else if (!exist1)
	{
		if (exist2)
			change_value2(input);
		lst_add_back(&com_info()->env_lst, new_node(input));
	}
}

int	check_if_exists(char *str)
{
	t_env_lst	*temp;
	char		*name;
	int			len;

	if (!str)
		return (0);
	len = 0;
	temp = com_info()->env_lst;
	while (str[len] != '=')
		len++;
	name = get_name_export(str, len);
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

int	check_if_exists2(char *str)
{
	t_env_lst	*temp;
	char		*name;
	int			len;

	if (!str)
		return (0);
	len = 0;
	temp = com_info()->vars;
	while (str[len] != '=')
		len++;
	name = get_name_export(str, len);
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

	len = 0;
	head = com_info()->env_lst;
	while (str[len] != '=')
		len++;
	name = get_name_change_export(str, len);
	value = get_value_export(str, len + 1);
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

void	change_value2(char *str)
{
	t_env_lst	*head;
	char		*name;
	char		*value;
	int			len;

	len = 0;
	head = com_info()->vars;
	while (str[len] != '=')
		len++;
	name = get_name_change_export(str, len);
	value = get_value_export(str, len + 1);
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
