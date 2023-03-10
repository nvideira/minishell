/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:13:10 by jlebre            #+#    #+#             */
/*   Updated: 2023/03/10 17:04:19 by nvideira         ###   ########.fr       */
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
	new = malloc(sizeof(char) * (ft_strlen(input) - 1));
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
	//free(input);
	return (new);
}

int	find_quote(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			quote++;
		i++;
	}
	return (quote);
}

int	find_pelicula(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			quote++;
		i++;
	}
	return (quote);
}
