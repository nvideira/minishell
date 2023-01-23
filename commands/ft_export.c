/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:33:34 by marvin            #+#    #+#             */
/*   Updated: 2023/01/23 15:43:14 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_export(char **input)
{
	int	i;

	i = 1;
	if (!input[i])
		print_exported(input);
	while (input[i])
	{
		if (ft_strchr(input[i], '='))
			check_export(input[i]);
		i++;
	}
	return (0);
}
