/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:27:14 by nvideira          #+#    #+#             */
/*   Updated: 2022/11/14 18:52:43 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**shell_split(char *str)
{
	char	**arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	arr = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	while (str[i])
	{
		while (str[i] && str[i] == 32)
			i++;
		if (str[i] == '"' || str[i] == '\'')
		{
			if (ft_strchr(str + i + 1, str[i]))
			{
				arr[j] = ft_substr(str, i + 1, ft_strchr(str + i + 1, str[i]));
				j++;
			}
			else
			{
				
			}
		}
	}
}