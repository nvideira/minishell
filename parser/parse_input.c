/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:04:12 by marvin            #+#    #+#             */
/*   Updated: 2023/01/29 23:04:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == '\n' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\0'
		|| c == ' ')
		return (1);
	return (0);
}

int	count_words(char *input)
{
	int	i;
	int	count;
	int	words;

	i = 0;
	count = 0;
	words = 0;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (input[i] && !is_space(input[i]))
		{
			words++;
			while (input[i] && !is_space(input[i]))
			{
				count++;
				i++;
			}	
		}
	}
	return (count + words);
}

char	*put_spaces(char *input)
{
	int		i;
	int		j;
	char	*new;
	int		words;

	i = 0;
	j = 0;
	words = count_words(input);
	new = malloc(sizeof(char) * (words));
	if (!new)
		return (NULL);
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		while (input[i] && !is_space(input[i]))
			new[j++] = input[i++];
		while (input[i] && is_space(input[i]))
			i++;
		if (input[i])
			new[j++] = ' ';
	}
	new[j] = '\0';
	return (new);
}
