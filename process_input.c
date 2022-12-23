/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:35:05 by jlebre            #+#    #+#             */
/*   Updated: 2022/12/20 01:21:58 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(char **env)
{
	while (com_info()->commands)
	{
		if (pipe(com_info()->pip) < 0)
		{
			write(2, "Pipe error\n", 10);
			return ;
		}
		com_info()->pid = fork();
		if (com_info()->pid == 0)
		{
			if (com_info()->fd_in > 0)
			{
				dup2(com_info()->fd_in, STDIN_FILENO);
				close(com_info()->fd_in);
			}
			com_info()->fd_in = com_info()->pip[0];
			if (com_info()->commands->next)
			{
				dup2(com_info()->pip[1], STDOUT_FILENO);
				close(com_info()->pip[1]);
			}
			com_info()->commands->nb_args = count_args(com_info()->commands->arg);
			if (find_es(com_info()->commands->arg[0]) == 1)
				exported_vars(com_info()->commands->arg);
			else
				commands(com_info()->commands->arg, env);
		}
		else
		{
			dup2(com_info()->pip[0], STDIN_FILENO);
			close(com_info()->pip[1]);
			close(com_info()->pip[0]);
			// waitpid(com_info()->pid, &com_info()->status, 0);
		}
		com_info()->commands = com_info()->commands->next;
	}
}

/* void	process_input(char **env)
{
	while (com_info()->commands)
	{
		com_info()->commands->nb_args = count_args(com_info()->commands->arg);
		if (find_es(com_info()->commands->arg[0]) == 1)
			exported_vars(com_info()->commands->arg);
		else
			commands(com_info()->commands->arg, env);
		com_info()->commands = com_info()->commands->next;
	}
}

void	process_input(char **env)
{
	while (com_info()->commands)
	{
		if (com_info()->pipe_no % 2 == 1)
			if (use_pipe(com_info()->pipe1))
				return ;
		else
			if (use_pipe(com_info()->pipe2))
				return ;
		com_info()->pipe_no--;
		com_info()->commands->nb_args = count_args(com_info()->commands->arg);
		if (find_es(com_info()->commands->arg[0]) == 1)
			exported_vars(com_info()->commands->arg);
		else
			commands(com_info()->commands->arg, env);
		com_info()->commands = com_info()->commands->next;
	}
}
 */
