/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:11:00 by nvideira          #+#    #+#             */
/*   Updated: 2023/03/23 01:58:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_xor(char *input)
{
	int	i;

	if (!input)
		return (0);
	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1])
		{
			i++;
			while (input[i] && is_space(input[i]))
				i++;
			if (input[i] == '|' && (!surround_quote(input, i, '"')
					&& !surround_quote(input, i, '\'')))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_and(char *input)
{
	int	i;

	if (!input)
		return (0);
	i = 0;
	while (input[i])
	{
		if (input[i] == '&' && (!surround_quote(input, i, '"')
				&& !surround_quote(input, i, '\'')))
			return (1);
		i++;
	}
	return (0);
}
