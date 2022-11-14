/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:02:50 by nvideira          #+#    #+#             */
/*   Updated: 2022/11/14 15:45:06 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *find_command(char *input, int start)
{
    int i;
    char *command;

    i = start;
    while (input[i] != ' ' && input[i] != '\0')
        i++;
    command = ft_substr(input, start, i - start);
    return (command);
}

int	find_pipes(char *input)
{
	int i;
	int pipe_no;

	i = 0;
	pipe_no = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '|')
			pipe_no++;
		i++;
	}
	return (pipe_no);
}

int	heredoc(char *limiter)
{
	char	*here;
	int		file;

	file = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file < 0)
		perror("here_doc");
	while (1)
	{
		write(1, "heredoc> ", 9);
		here = get_next_line(0);
		if (!ft_strncmp(here, limiter, ft_strlen(limiter)))
			break ;
		write(file, here, ft_strlen(here));
		free(here);
	}
	free(here);
	close(file);
	pipex.infile = open(".heredoc_tmp", O_RDONLY);
	if (pipex.infile < 0)
	{
		unlink(".heredoc_tmp");
		perror("here_doc");
	}
	return (pipex.infile);
}

void	parser(char *input)
{
    int i;

    i = 0;
	if (ft_strncmp(input, "<<", 2))
		heredoc();
	find_pipes(input);
    while (input[i])
    {
        if ()
    }
   
}