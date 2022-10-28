/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:55:46 by jlebre            #+#    #+#             */
/*   Updated: 2022/10/26 19:25:41 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
	{
		str[i++] = s1[j++];
	}
	j = 0;
	while (s2[j])
	{
		str[i++] = s2[j++];
	}
	str[i] = '\0';
	return (str);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return ((int)i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (!len || ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len > ft_strlen(s))
	{
		len = ft_strlen(s);
		return (ft_substr(s, start, len));
	}
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (s[start + i] != '\0' && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strdup(const char *s1)
{
	char	*p;

	p = malloc(ft_strlen(s1) + 1);
	if (!p)
		return (NULL);
	ft_memmove(p, s1, ft_strlen(s1) + 1);
	return (p);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dr;
	const char	*sr;
	size_t		i;

	sr = src;
	dr = dst;
	i = 0;
	if (!dst && !src)
		return (NULL);
	if (dr < sr)
	{
		while (i < len)
		{
			dr[i] = sr[i];
			i++;
		}
	}
	else
	{
		while (len--)
			dr[len] = sr[len];
	}
	return (dst);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;	
	}
	return (0);
}

void	ft_clear(void)
{
	printf("\033c");
}