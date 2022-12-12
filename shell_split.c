/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:03:49 by nvideira          #+#    #+#             */
/*   Updated: 2022/12/12 18:27:30 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_quotes(const char *str, int i, int type)
{
	i++;
	while (str[i] && str[i] != type)
		i++;
	if (str[i] == type)
		return (i);
	return (-1);
}

static int	ft_space(char s, char c)
{
	if (s == c || s == '\0')
		return (1);
	else
		return (0);
}

static int	ft_wordcount(const char *str, char c)
{
	int		words;
	int		i;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			i = find_quotes(str, i, str[i]);
		if (i == -1)
			return (0);
		if (ft_space(str[i], c) == 0 && ft_space(str[i + 1], c) == 1)
			words++;
		i++;
	}
	return (words);
}

static int	split_it(char const *str, char c, int st, char **ns)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		while (str[i] != '\0' && str[i] == c)
		{
			i++;
			st++;
		}
		if (str[i] == 34 || str[i] == 39)
			i = find_quotes(str, i, str[i]);
		if (str[i] == '\0')
			break ;
		if (ft_space(str[i], c) == 0 && ft_space(str[i + 1], c) == 1)
		{
			ns[j] = ft_substr(str, st, (i - st) + 1);
			if (!ns[j++])
				return (0);
			st = i + 1;
		}
	}
	ns[j] = NULL;
	return (1);
}

void	*freematrix(char **ns, int msize)
{
	while (msize--)
		free(ns[msize]);
	free(ns);
	return (NULL);
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
	if (!matlen)
	{
		printf("Error: Unclosed quotes\n");
		return (NULL);
	}
	ns = malloc(sizeof(char *) * (matlen + 1));
	if (!ns)
		return (NULL);
	if (!split_it(s, c, st, ns))
		return (freematrix(ns, matlen));
	return (ns);
}
