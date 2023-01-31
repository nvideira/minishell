/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:03:49 by nvideira          #+#    #+#             */
/*   Updated: 2023/01/27 00:22:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Shell_Split não está de acordo com a Norminette

int	find_quotes(const char *str, int i, int type)
{
	int	st;

	st = i;
	i++;
	if (type == 34)
	{
		while (str[i] && str[i] != 34)
			i++;
		if (str[i] == 34)
			return (i);
	}
	else
	{
		while (str[i] && str[i] != 39)
			i++;
		if (str[i] == 39)
			return (i);
	}
	return (st);
}

int	ft_wordcount(const char *str, char c)
{
	int		words;
	size_t	i;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] == 34)
			i = find_quotes(str, i, 34);
		if (str[i] == 39)
			i = find_quotes(str, i, 39);
		if (ft_ispipe(str[i], c) == 0 && ft_ispipe(str[i + 1], c) == 1)
			words++;
		i++;
	}
	return (words);
}

// Norminette
static int	split_it(char const *str, char c, int st, char **ns)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] != '\0' && str[i] == c)
		{
			i++;
			st++;
		}
		if (str[i] == 34)
			i = find_quotes(str, i, 34);
		if (str[i] == 39)
			i = find_quotes(str, i, 39);
		if (str[i] == '\0')
			break ;
		if (ft_ispipe(str[i], c) == 0 && ft_ispipe(str[i + 1], c) == 1)
		{
			while (str[st] && (ft_space(str[st]) || ft_ispipe(str[st], c)))
				st++;
			ns[j] = ft_substr(str, st, (i - st) + 1);
			if (!ns[j++])
				return (0);
			st = i + 1;
		}
		i++;
	}
	ns[j] = NULL;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**ns;
	size_t	st;
	int		matlen;

	st = 0;
	if (!s)
		return (NULL);
	matlen = ft_wordcount(s, c);
	ns = malloc(sizeof(char *) * (matlen + 1));
	if (!ns)
		return (NULL);
	if (!split_it(s, c, st, ns))
		return (freematrix(ns, matlen));
	return (ns);
}
