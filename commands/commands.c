/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:02:49 by jlebre            #+#    #+#             */
/*   Updated: 2023/03/17 20:09:15 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Esta função é chamada para executar os comandos
// Compara o input com os comandos que temos e chama a função correspondente
// Se não for nenhum dos comandos, chama a função fork_commands
void	commands(char *input, char **env, int is_fork)
{
	char	**arg;

	arg = ft_split(input, ' ');
	arg = parse_input3(arg);
	free(input);
	com_info()->nb_args = count_args(arg);
	if (arg[0])
	{
		if (!ft_strncmp(arg[0], "echo", 5))
			ft_echo(arg);
		else if (!ft_strncmp(arg[0], "cd", 3))
			ft_cd(arg, env);
		else if (!ft_strncmp(arg[0], "pwd", 4))
			ft_pwd();
		else if (!ft_strncmp(arg[0], "export", 7))
			ft_export(arg);
		else
			commands2(arg, env, is_fork);
	}
	free_matrix(arg);
}

// Continuação da função commands
void	commands2(char **arg, char **env, int is_fork)
{
	if (!ft_strncmp(arg[0], "unset", 6))
		ft_unset(arg);
	else if (!ft_strncmp(arg[0], "env", 4))
		ft_env(arg);
	else if (!ft_strncmp(arg[0], "exit", 5))
		ft_exit(arg);
	else if (!ft_strncmp(arg[0], "change_color", 13))
		change_color(arg);
	else
		fork_commands(arg, env, is_fork);
}

int	parent_commands(char *input, char **env)
{
	char	**arg;

	arg = ft_split(input, ' ');
	arg = parse_input3(arg);
	if (!ft_strncmp(arg[0], "cd", 3))
		ft_cd(arg, env);
	else if (!ft_strncmp(arg[0], "export", 7))
		ft_export(arg);
	else if (!ft_strncmp(arg[0], "unset", 6))
		ft_unset(arg);
	else if (!ft_strncmp(arg[0], "exit", 5))
		ft_exit(arg);
	else
	{
		free_matrix(arg);
		return (0);
	}
	free_matrix(arg);
	return (1);
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
