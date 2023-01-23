/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:04:30 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/23 16:37:10 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exported_vars_utils(char *input)
{
	if (check_if_exists(input) && !check_if_exists_vars(input))
	{
		change_value(input);
		lst_add_back(&com_info()->vars, new_node(input));
	}
	else if (check_if_exists_vars(input))
		change_value_vars(input);
	else
		lst_add_back(&com_info()->vars, new_node(input));
}

void	exported_vars(char **input)
{
	int	i;

	i = 0;
	if (input[0][i] == '=')
	{
		ft_error("%s not found\n", input[1]);
		return ;
	}
	while (input[i])
	{
		if (ft_strchr(input[i], '='))
			exported_vars_utils(input[i]);
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
