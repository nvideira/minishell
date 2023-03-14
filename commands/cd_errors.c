/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:55:28 by nvideira          #+#    #+#             */
/*   Updated: 2023/03/14 22:55:40 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Função que vê se há erros no comando cd
int	cd_errors(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	if (i > 2)
	{
		ft_error("cd: string not in pwd: %s\n", input[1]);
		return (0);
	}
	if (i == 2)
	{
		if (ft_strlen(input[1]) == 1 && !ft_strncmp(input[1], "-", 2))
			return (1);
		if (i == 1)
			return (1);
		if (access(input[1], F_OK) != 0)
		{
			ft_error("cd: no such file or directory: %s\n", input[1]);
			return (0);
		}
	}
	return (1);
}
