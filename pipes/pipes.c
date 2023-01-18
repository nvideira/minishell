/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 02:22:13 by nvideira          #+#    #+#             */
/*   Updated: 2023/01/17 20:52:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_close(int pos)
{
	if (pos == 0)
		close(com_info()->pip[0][1]);
	else if (pos == com_info()->pipe_no)
		close(com_info()->pip[pos - 1][0]);
	else
		close(com_info()->pip[pos][1]);
}

void	execute_pipe(char **input)
{
	int	pid;
	
	pid = fork();
	if (pid == 0)
	{
		fd_dup(com_info()->cmds_done);
		commands(input, com_info()->env, 1);
	}
	else
		waitpid(pid, &com_info()->exit_value, 0);
	fd_close(com_info()->cmds_done);
	unlink(".heredoc");
}

void	init_pipes(void)
{
	int	i;

	i = 0;
	com_info()->cmds_done = 0;
	com_info()->pip = malloc(sizeof(int *) * (com_info()->pipe_no + 1));
	while (i < com_info()->pipe_no)
	{
		com_info()->pip[i] = malloc(sizeof(int) * 2);
		if (pipe(com_info()->pip[i]) < 0)
		{
			ft_error("Pipe error\n");
			return ;
		}
		i++;
	}
	com_info()->pip[i] = NULL;
}

void	fd_dup(int pos)
{
	if (pos == 0)
	{
		close(com_info()->pip[0][0]);
		dup2(com_info()->pip[0][1], 1);
		close(com_info()->pip[0][1]);
	}
	else if (pos == com_info()->pipe_no)
	{
		dup2(com_info()->pip[pos - 1][0], 0);
		close(com_info()->pip[pos - 1][0]);
	}
	else
	{
		close(com_info()->pip[pos][0]);
		dup2(com_info()->pip[pos - 1][0], 0);
		close(com_info()->pip[pos - 1][0]);
		dup2(com_info()->pip[pos][1], 1);
		close(com_info()->pip[pos][1]);
	}
}
