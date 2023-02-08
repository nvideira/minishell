/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:15:07 by marvin            #+#    #+#             */
/*   Updated: 2023/02/08 04:01:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Inicializa os pipes
void	init_pipes(void)
{
	int	i;

	i = 0;
	com_info()->pid_counter = 0;
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
	com_info()->pid = malloc(sizeof(int) * (com_info()->pipe_no));
	com_info()->pid[com_info()->pipe_no] = 0;
}

// Executa os pipes
void	execute_pipe(char **input)
{
	signal_block();
	com_info()->pid[com_info()->pid_counter] = fork();
	if (com_info()->pid[com_info()->cmds_done] == 0)
	{
		fd_dup(com_info()->cmds_done);
		commands(input, com_info()->env, 1);
	}
	com_info()->pid_counter++;
	fd_close(com_info()->cmds_done);
	unlink(".heredoc");
}

// Espera por todos os processos
void	ft_wait_pid(void)
{
	int	i;

	i = 0;
	signal_block();
	while (i < (com_info()->pid_counter))
	{
		waitpid(com_info()->pid[i], &com_info()->exit_value, 0);
		i++;
	}
	catch_signal();
}

// Duplica os file descriptors
void	fd_dup(int pos)
{
	if (pos == 0)
	{
		close(com_info()->pip[0][0]);
		dup2(com_info()->pip[0][1], STDOUT_FILENO);
		close(com_info()->pip[0][1]);
	}
	else if (pos == com_info()->pipe_no)
	{
		dup2(com_info()->pip[pos - 1][0], STDIN_FILENO);
		close(com_info()->pip[pos - 1][0]);
	}
	else
	{
		close(com_info()->pip[pos][0]);
		dup2(com_info()->pip[pos][1], STDOUT_FILENO);
		close(com_info()->pip[pos][1]);
		dup2(com_info()->pip[pos - 1][0], STDIN_FILENO);
		close(com_info()->pip[pos - 1][0]);
	}
}

// Fecha os file descriptors
void	fd_close(int pos)
{
	if (pos == 0)
	{
		if (close(com_info()->pip[0][1]) == -1)
			ft_error("Close error 1\n");
	}
	else if (pos == com_info()->pipe_no)
	{
		if (close(com_info()->pip[pos - 1][0]) == -1)
			ft_error("Close error 2\n");
	}
	else
	{
		if (close(com_info()->pip[pos][1]) == -1)
			ft_error("Close error 3\n");
	}
}
