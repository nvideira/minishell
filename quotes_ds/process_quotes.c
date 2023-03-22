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

// Processa aspas duplas
char	*process_quotes(char *input)
{
	char	*new;

	if (find_quote(input) % 2 == 0 && find_quote(input) != 0)
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

	if (find_pelicula(input) % 2 == 0 && find_pelicula(input) != 0)
	{
		if (!surround_quote(input, 0, '"'))
		{
			new = remove_quotes(input, '\'');
			free(input);
			input = ft_strdup(new);
			free(new);
		}
	}
	return (input);
}
