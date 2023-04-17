/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:10:11 by marvin            #+#    #+#             */
/*   Updated: 2023/02/11 18:10:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_char(char *input, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == c)
		{
			if (input[i + 1] == c)
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

int	check_file_access(char *file, int type)
{
	if (!access(file, F_OK))
	{
		if (access(file, type))
		{
			ft_error("%s: Permission denied\n", file);
			return (1);
		}
	}
	return (0);
}

int	check_file_existence(char *file)
{
	if (access(file, F_OK))
	{
		ft_error("%s: No such file or directory\n", file);
		return (1);
	}
	return (0);
}

int	check_redir_type(char *input)
{
	if (input[0] == '>')
	{
		if (input[1] && input[1] == '>')
			return (1);
		else
			return (2);
	}
	else if (input[0] == '<')
	{
		if (input[1] && input[1] == '<')
			return (3);
		else
			return (4);
	}
	return (0);
}
