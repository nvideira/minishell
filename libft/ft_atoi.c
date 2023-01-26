/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:06:15 by marvin            #+#    #+#             */
/*   Updated: 2023/01/04 01:06:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	val;
	int	sinal;

	i = 0;
	val = 0;
	sinal = 1;
	while ((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\t')
		|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == ' '))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sinal *= -1;
		i++;
	}
	while ((str[i] >= 48) && (str[i] <= 57))
	{	
		val *= 10;
		val += str[i] - 48;
		i++;
	}
	return (sinal * val);
}
