/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:04:30 by jlebre            #+#    #+#             */
/*   Updated: 2022/12/14 17:04:59 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_exists_vars(char *str)
{
	t_env_lst	*temp;
	char		*name;
	int			len;
	int			i;

	len = 0;
	i = 0;
	temp = com_info()->vars;
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

void	exported_vars(char **input)
{
	int	i;

	i = 0;
	if (input[0][i] == '=')
	{
		printf("%s not found\n", input[1]);
		return ;
	}
	while (input[i])
	{
		if (ft_strchr(input[i], '='))
		{
			if (check_if_exists(input[i]) && !check_if_exists_vars(input[i]))
			{
				change_value(input[i]);
				lst_add_back(&com_info()->vars, new_node(input[i]));
			}
			else if (check_if_exists_vars(input[i]))
				change_value_vars(input[i]);
			else
				lst_add_back(&com_info()->vars, new_node(input[i]));
		}
		else
			break ;
		i++;
	}
	return ;
}

//Find Equal Sign
int	find_es(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	count_args(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}
