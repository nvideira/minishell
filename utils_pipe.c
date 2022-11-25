/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:58:53 by jlebre            #+#    #+#             */
/*   Updated: 2022/11/21 17:18:31 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strichr(const char *s, int start, int c)
{
	while (s[start] != (char )c && s[start] != '\0')
		start++;
	if (s[start] == (char )c)
		return (start);
	else
		return (-1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] && str2[i] && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (i < n)
		return (str1[i] - str2[i]);
	return (0);
}

char	*join_strings(char *path, int j, char *cmd)
{
	char	*dir;
	char	*ret_path;

	dir = ft_substring(path, j, ft_strichr(path, j, ':') - j);
	ret_path = ft_strjoin(dir, cmd);
	free(dir);
	return (ret_path);
}

char	*ft_substring(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (!len || (unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len > (size_t)ft_strlen(s))
	{
		len = ft_strlen(s);
		return (ft_substr(s, start, len));
	}
	sub = malloc((len + 2) * sizeof(char));
	if (!sub)
		return (NULL);
	while (s[start + i] != '\0' && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '/';
	i++;
	sub[i] = '\0';
	return (sub);
}
