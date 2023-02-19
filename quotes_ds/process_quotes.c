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
	if (find_quote(input) % 2 == 0 && find_quote(input) != 0)
		input = remove_quotes(input);
	return (input);
}

// Processa aspas simples
char	*process_peliculas(char *input)
{
	if (find_pelicula(input) % 2 == 0 && find_pelicula(input) != 0)
		input = remove_peliculas(input);
	return (input);
}
