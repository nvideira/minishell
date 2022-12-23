/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:45:11 by jlebre            #+#    #+#             */
/*   Updated: 2022/12/14 17:49:56 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void   *ft_export(char **input)
{
    int	i;

    i = 1;
	if (!input[i])
		print_exported(input);
    while (input[i])
    {
		if (ft_strchr(input[i], '='))
		{
			if (check_if_exists(input[i]))
				change_value(input[i]);
			else
				lst_add_back(&com_info()->env_lst, new_node(input[i]));
		}
		else
			break ;
		i++;
    }
	return (0);
}

//(export aaa bbb=) (cria aaa= e bbb=)
