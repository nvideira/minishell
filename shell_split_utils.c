/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:00:37 by nvideira          #+#    #+#             */
/*   Updated: 2023/01/25 18:28:33 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_rollback(char const *str, int st)
// {
// 	int	i;

// 	i = 0;
// 	while (st > 0 && (str[st] != '>' && str[st] != '<'))
// 	{
// 		st--;
// 		i++;
// 	}
// 	if (str[st] == '>' || str[st] == '<')
// 		return (i);
// 	return (0);
// }

void	*freematrix(char **ns, int msize)
{
	while (msize--)
		free(ns[msize]);
	free(ns);
	return (NULL);
}

int	ft_space(char s)
{
	if (s == '\n' || s == '\t' || s == '\v'
		|| s == '\f' || s == '\r' || s == ' ')
		return (1);
	else
		return (0);
}

int	ft_ispipe(char s, char c)
{
	if (c == s || s == '\0')
		return (1);
	else
		return (0);
}
