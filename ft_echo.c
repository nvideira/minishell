/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:31:01 by marvin            #+#    #+#             */
/*   Updated: 2022/11/17 23:31:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **input)
{
	int	i;

	if (!ft_strncmp(input[1], "$?", 3))
	{
		printf("%d\n", com_info()->exit_value);
		com_info()->exit_value = 0;
	}
	else if (!ft_strncmp(input[1], "-n", 3))
	{
		printf("%s", input[2]);
		com_info()->exit_value = 0;
	}
	else
	{
		i = 1;
		while (i < com_info()->nb_args)
		{
			printf("%s", input[i]);
			i++;
		}
		printf("\n");
		com_info()->exit_value = 0;
	}
}
