/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:27:52 by marvin            #+#    #+#             */
/*   Updated: 2023/02/11 16:27:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (!s1 || !set)
		return (0);
	while (*s1 && ft_str1chr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_str1chr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}

char	*trim_redir(char *input)
{
	int		len;
	char	*trimmed;

	if (!input)
		return (NULL);
	while (input[len] != '<' && input[len] != '>')
		len++;
	trimmed = ft_substr(input, 0, len);
	return (trimmed);
}
