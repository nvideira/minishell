/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:10:04 by marvin            #+#    #+#             */
/*   Updated: 2023/01/04 01:10:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char )c && s[i] != '\0')
		i++;
	if (s[i] == (char )c)
		return (i);
	return (0);
}

int	ft_str1chr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char )c && s[i] != '\0')
		i++;
	if (s[i] == (char )c)
		return (1);
	return (0);
}