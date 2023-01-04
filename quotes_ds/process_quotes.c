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

char **process_quotes(char **input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (find_quote(input[i]) == 2)
			input[i] = remove_quotes(input[i]);
		i++;
	}
	return (input);
}

char **process_peliculas(char **input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (find_pelicula(input[i]) == 2)
			input[i] = remove_peliculas(input[i]);
		i++;
	}
	return (input);
}
