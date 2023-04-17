/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:33:34 by marvin            #+#    #+#             */
/*   Updated: 2023/04/05 19:29:08 by jlebre           ###   ########.fr       */
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

int	errors_export(char *input)
{
	if (ft_str1chr(input, '-')
		&& (!surround_quote(input, ft_strchr(input, '-'), '"')
			&& !surround_quote(input, ft_strchr(input, '-'), '\'')))
		return (1);
	if (ft_isdigit(input))
		return (1);
	if (!ft_strncmp(input, "=", 1))
		return (1);
	return (0);
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
		if (errors_export(input[i]))
		{
			ft_error("export: %s: not a valid identifier\n", input[i]);
			com_info()->exit_value = 1;
			return (0);
		}
		if (ft_strchr(input[i], '='))
			check_export(input[i]);
		else
			check_export_without_value(input[i]);
		i++;
	}
	return (0);
}
