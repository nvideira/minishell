/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:13:10 by jlebre            #+#    #+#             */
/*   Updated: 2023/04/05 19:30:53 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *input, char quote)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char)
			* (ft_strlen(input) - find_quote(input, quote) + 1));
	if (!new)
		return (NULL);
	while (input[i])
	{
		if (input[i] != quote)
		{
			new[j] = input[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

int	find_quote(char *str, char quote)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == quote)
			counter++;
		i++;
	}
	return (counter);
}
