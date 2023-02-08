/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:49:58 by nvideira          #+#    #+#             */
/*   Updated: 2023/02/07 19:00:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_heredoc(char *limiter)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		heredoc(limiter);
		com_info()->hereflag = 1;
	}
	else
		waitpid(pid, &com_info()->exit_value, 0);
	unlink(".heredoc");
}

int	heredoc(char *limiter)
{
	int		fd;
	char	*tmp;

	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		perror("minishell: error opening heredoc file");
	while (1)
	{
		tmp = readline("> ");
		if (ft_strncmp(tmp, limiter, ft_strlen(limiter)) == 0)
			break ;
		ft_putstr_fd(tmp, fd);
		free(tmp);
	}
	free(tmp);
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	if (fd < 0)
	{
		unlink(".heredoc");
		perror("minishell: error opening heredoc file");
	}
	return (fd);
}
