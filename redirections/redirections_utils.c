/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:29:35 by marvin            #+#    #+#             */
/*   Updated: 2023/01/26 23:51:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_redirs(char **input)
{
	int	i;
	int	j;
	int	redir_no;

	i = 0;
	redir_no = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			if (input[i][j] == '>' || input[i][j] == '<')
			{
				if ((input[i][j] == '>' && input[i][j + 1] == '>')
					|| (input[i][j] == '<' && input[i][j + 1] == '<'))
					j++;
				redir_no++;
			}
			j++;
		}
		i++;
	}
	com_info()->redir_no = redir_no;
	return (redir_no);
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

// Faz as redireções e as duplicações de file descriptors
// O que se faz quando tem vários argumentos a seguir ao redirecionador?
void	redirections(char **arquivo, int type)
{
	int		fd;
	char	*file;

	file = arquivo[0];
	if (type == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (type == 2)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == 4)
		fd = open(file, O_RDONLY);
	else if (type == 3)
		fd = heredoc(file);
	if (type == 1 || type == 2)
		dup2(fd, STDOUT_FILENO);
	else if (type == 4 || type == 3)
		dup2(fd, STDIN_FILENO);
	close(fd);
	free(file);
}
