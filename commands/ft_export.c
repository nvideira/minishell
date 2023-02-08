/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:33:34 by marvin            #+#    #+#             */
/*   Updated: 2023/02/07 14:33:11 by marvin           ###   ########.fr       */
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
void	*ft_export(char **input)
{
	int	i;

	i = 1;
	if (!input[i])
	{
		print_exported(input);
		return (0);
	}
	while (input[i])
	{
		if (ft_strchr(input[i], '='))
			check_export(input[i]);
		else
			check_export_without_value(input[i]);
		i++;
	}
	return (0);
}
