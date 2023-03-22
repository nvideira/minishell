/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:49:58 by nvideira          #+#    #+#             */
/*   Updated: 2023/03/21 17:45:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *limiter)
{
	char	*file;
	int		fd;
	int		fd_in;

	fd = open(".tmpfile.txt", O_TRUNC | O_CREAT | O_WRONLY, 0666);
	write(1, "> ", 2);
	file = readline(STDIN_FILENO);
	while (file)
	{
		if (!ft_strncmp(file, limiter, ft_strlen(file) - 1)
			&& ft_strlen(file) > 1)
			break ;
		write(fd, file, ft_strlen(file));
		write(fd, "\n", 1);
		free(file);
		write(1, "> ", 2);
		file = readline(STDIN_FILENO);
	}
	if (file)
		free(file);
	close(fd);
	fd_in = open(".tmpfile.txt", O_RDONLY, 0777);
	return (fd_in);
}
