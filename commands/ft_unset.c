/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:44:22 by jlebre            #+#    #+#             */
/*   Updated: 2023/03/23 17:10:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Recria o comando unset
void	ft_unset(char **input)
{
	int	i;

	i = 1;
	if (input[i])
	{
		while (input[i])
		{
			check_unset(input[i]);
			i++;
		}
	}
	com_info()->exit_value = 0;
}
