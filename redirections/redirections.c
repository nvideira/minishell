/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:41:42 by nvideira          #+#    #+#             */
/*   Updated: 2023/01/18 21:57:54 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redir_type(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>')
		{
			if (input[i + 1] == '>')
				return (1);
			else
				return (2);
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
				return (3);
			else
				return (4);
		}
		i++;
	}
	return (0);
}

void	redirections(char **input)
{
	int		i;
	int		fd;
	int		type;

	i = 0;
	while (input[i])
	{
		type = check_redir_type(input[i]);
		if (type == 1)
		{
			fd = open(input[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
			dup2(fd, 1);
			close(fd);
		}
		else if (type == 2)
		{
			fd = open(input[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			dup2(fd, 1);
			close(fd);
		}
		else if (type == 3)
		{
			fd = open(input[i + 1], O_CREAT | O_RDONLY, 0644);
			dup2(fd, 0);
			close(fd);
		}
		else if (type == 4)
		{
			fd = open(input[i + 1], O_CREAT | O_RDONLY, 0644);
			dup2(fd, 0);
			close(fd);
		}
		i++;
	}
}

void	check_redir(char **input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			if (input[i][j] == '>' || input[i][j] == '<')
			{
				redirections(input);
				return ;
			}
			j++;
		}
		i++;
	}
	return (0);
}