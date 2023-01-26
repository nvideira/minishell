/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:44:22 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/26 02:42:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Recria o comando unset
void	ft_unset(char **input)
{
	int			i;

	i = 1;
	if (!input[i])
		unset_error();
	while (input[i])
	{
		check_unset(input[i]);
		i++;
	}
	com_info()->exit_value = 0;
}
