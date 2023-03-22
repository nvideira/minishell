/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:33:34 by marvin            #+#    #+#             */
/*   Updated: 2023/03/22 20:04:26 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_without_value(char *name)
{
	t_env_lst	*tmp;
	char		*value;

	tmp = com_info()->env_lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return ;
		tmp = tmp->next;
	}
	value = ft_strdup("");
	lst_add_back(&com_info()->env_lst, new_node(name));
	free(value);
}

void	check_export_without_value(char *name)
{
	int	exist1;
	int	exist2;

	exist1 = check_if_exists(name, com_info()->env_lst);
	exist2 = check_if_exists(name, com_info()->vars);
	if (exist1 || exist2)
		return ;
	else
		export_without_value(name);
}

// Recria o comando export
void	ft_export(char **input)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!input[i])
	{
		print_exported(input);
		return ;
	}
	while (input[i])
	{
		j = check_var_name(input[i]);
		if (j >= 0)
		{
			printf("export: `%c': not a valid identifier\n", input[i][j]);
			com_info()->exit_value = 1;
			return ;
		}
		if (ft_strchr(input[i], '='))
			check_export(input[i]);
		else
			check_export_without_value(input[i]);
		i++;
	}
}

int	check_var_name(char *input)
{
	int	i;

	i = 0;
	if ((input[i] > 'z' || input[i] < 'a')
		&& (input[i] < 'A' || input[i] > 'Z') && input[i] != '_')
		return (0);
	while (input[++i])
	{
		if ((input[i] < 'a' || input[i] > 'z')
			&& (input[i] < 'A' || input[i] > 'Z') && input[i] != '_'
			&& (input[i] < '0' || input[i] > '9'))
			return (i);
	}
	return (-1);
}
