/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:18 by marvin            #+#    #+#             */
/*   Updated: 2023/01/04 00:51:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_first_quote_pos(char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (0);
}

// Processa aspas duplas
char	*process_quotes(char *input, char *old)
{
	char	*new;

	if (find_quote(old, '"') % 2 == 0 && find_quote(old, '"') != 0
		&& !surround_quote(old, get_first_quote_pos(old, '"'), '\''))
	{
		new = remove_quotes(input, '"');
		free(input);
		input = ft_strdup(new);
		free(new);
	}
	return (input);
}

// Processa aspas simples
char	*process_peliculas(char *input)
{
	char	*new;

	if (find_quote(input, '\'') % 2 == 0 && find_quote(input, '\'') != 0
		&& !surround_quote(input, get_first_quote_pos(input, '\''), '"'))
	{
		new = remove_quotes(input, '\'');
		free(input);
		input = ft_strdup(new);
		free(new);
	}
	return (input);
}
