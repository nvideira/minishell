/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:49:58 by nvideira          #+#    #+#             */
/*   Updated: 2023/02/08 19:24:54 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_heredoc(char ***mat_array, int i)
{
	pid_t	pid;

	(void)i;
	pid = fork();
	if (pid == 0)
	{
		com_info()->hereflag = 1;
		heredoc(mat_array[1][0]);
		// if (mat_array[i + 2])
		// {
		// 	printf("mat_array[%d] = %s\n", i, mat_array[i][0]);
		// 	commands(mat_array[i + 2], com_info()->env, 1);
		// }
	}
	else
		waitpid(pid, &com_info()->exit_value, 0);
	//unlink(".heredoc");
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
