/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:49:58 by nvideira          #+#    #+#             */
/*   Updated: 2023/02/13 01:00:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *limiter)
{
	char	*file;
	int		fd;
	int		fd_in;

	fd = open("./.tmp/tmpfile.txt", O_TRUNC | O_CREAT | O_WRONLY, 0666);
	write(1, "> ", 2);
	file = get_next_line(STDIN_FILENO);
	while (1)
	{
		if (ft_strncmp(file, limiter, ft_strlen(file) - 1) == 0
			&& ft_strlen(file) > 1)
			break ;
		write(fd, file, ft_strlen(file));
		free(file);
		write(1, "> ", 2);
		file = get_next_line(STDIN_FILENO);
	}
	free(file);
	close(fd);
	fd_in = open("./.tmp/tmpfile.txt", O_RDONLY, 0777);
	return (fd_in);
}
