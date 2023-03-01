/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:15:07 by marvin            #+#    #+#             */
/*   Updated: 2023/03/01 05:02:33 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_commands(char **input, char **env)
{
	int	count;

	count = 0;
	com_info()->pid = malloc(sizeof(int) * count_args(input));
	while (input[count])
	{
		if (parent_commands(input[count], env))
			com_info()->pid[count] = 1;
		else
		{
			if (pipe(com_info()->fd) == -1)
				return ;
			com_info()->pid[count] = fork();
			if (com_info()->pid[count] < 0)
				return ;
			if (com_info()->pid[count] == 0)
				execute_pipe(input, count, env);
			close(com_info()->fd[1]);
			com_info()->pipe_fd = com_info()->fd[0];
		}
		count++;
	}
	free_matrix(input);
	ft_wait_pid(count);
}

// Executa os pipes
void	execute_pipe(char **input, int count, char **env)
{
	int	fd_out;

	child_input(input, count);
	if (!ft_find_char(input[count], '>'))
	{
		if (count != (count_args(input) - 1))
			dup2(com_info()->fd[1], STDOUT_FILENO);
	}
	else
	{
		fd_out = redirect_output(input[count]);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (ft_find_char(input[count], '<') || ft_find_char(input[count], '>'))
		input[count] = ft_strtrim(input[count], " <>");
	commands(input[count], env, 1);
	rl_clear_history();
	exit(com_info()->exit_value);
}

void	child_input(char **input, int count)
{
	int	fd_in;

	if (!ft_find_char(input[count], '<'))
	{
		if (count == 0)
			close(com_info()->fd[0]);
		else if (count > 0)
		{
			dup2(com_info()->pipe_fd, STDIN_FILENO);
			close(com_info()->pipe_fd);
		}
	}
	else
	{
		if (count == 0)
			close(com_info()->fd[0]);
		else if (count > 0)
			close(com_info()->pipe_fd);
		fd_in = redirect_input(input[count]);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
}

// Espera por todos os processos
void	ft_wait_pid(int counter)
{
	int	i;

	i = 0;
	while (i < counter)
	{
		waitpid(com_info()->pid[i], &com_info()->exit_value, 0);
		if (WIFEXITED(com_info()->exit_value))
			com_info()->exit_value = WEXITSTATUS(com_info()->exit_value);
		i++;
	}
}
