/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:02:49 by jlebre            #+#    #+#             */
/*   Updated: 2023/02/08 04:00:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Esta função é chamada para executar os comandos
// Compara o input com os comandos que temos e chama a função correspondente
// Se não for nenhum dos comandos, chama a função fork_commands
void	commands(char **input, char **env, int is_fork)
{
	if (input[0])
	{
		if (!ft_strncmp(input[0], "echo", 5))
			ft_echo(input);
		else if (!ft_strncmp(input[0], "cd", 3))
			ft_cd(input, env);
		else if (!ft_strncmp(input[0], "pwd", 4))
			ft_pwd();
		else if (!ft_strncmp(input[0], "export", 7))
			ft_export(input);
		else if (!ft_strncmp(input[0], "unset", 6))
			ft_unset(input);
		else if (!ft_strncmp(input[0], "env", 4))
			ft_env(input);
		else if (!ft_strncmp(input[0], "exit", 5))
			ft_exit(input);
		else if (!ft_strncmp(input[0], "change_color", 13))
			change_color(input);
		else
			fork_commands(input, env, is_fork);
	}
}

// Esta função é chamada para executar os comandos que não são builtins
// Verifica se está dentro de um fork ou não (por causa dos pipes)
void	fork_commands(char **input, char **env, int is_fork)
{
	int	pid;

	signal_block();
	if (!is_fork)
	{
		pid = fork();
		if (pid == 0)
			env_commands(input, env);
		else
			waitpid(pid, &com_info()->exit_value, 0);
	}
	else
		env_commands(input, env);
}

/*
void	fork_commands(char **input, char **env, int is_fork)
{
	//int	cenas;

	signal_block();
	if (!is_fork)
	{
		com_info()->pid[com_info()->pid_counter++] = fork();
		if (com_info()->pid[com_info()->pid_counter - 1] == 0)
		{
			env_commands(input, env);
			com_info()->pid_counter++;
		}
		else
			waitpid(com_info()->pid[com_info()->pid_counter - 1], &com_info()->exit_value, 0);
	}
	else
		env_commands(input, env);
}
*/
