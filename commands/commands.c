/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:02:49 by jlebre            #+#    #+#             */
/*   Updated: 2023/04/05 19:19:02 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

// Esta função é chamada para executar os comandos
// Compara o input com os comandos que temos e chama a função correspondente
// Se não for nenhum dos comandos, chama a função fork_commands
void	commands(char *input, char **env, int is_fork)
{
	char	**arg;

	arg = ft_split(input, ' ');
	arg = parse_input3(arg);
	free(input);
	if (!arg[0] || !ft_strncmp(arg[0], "", 2) || is_all_space(arg[0]))
	{
		free_matrix(arg);
		return ;
	}
	com_info()->nb_args = count_args(arg);
	if (arg[0])
	{
		if (!ft_strncmp(arg[0], "echo", 5))
			ft_echo(arg);
		else if (!ft_strncmp(arg[0], "cd", 3))
			ft_cd(arg, env);
		else if (!ft_strncmp(arg[0], "pwd", 4))
			ft_pwd(arg);
		else
			commands2(arg, env, is_fork);
	}
	free_matrix(arg);
}

// Continuação da função commands
void	commands2(char **arg, char **env, int is_fork)
{
	if (!ft_strncmp(arg[0], "export", 7))
		ft_export(arg);
	else if (!ft_strncmp(arg[0], "unset", 6))
		ft_unset(arg);
	else if (!ft_strncmp(arg[0], "env", 4))
		ft_env(arg);
	else if (!ft_strncmp(arg[0], "exit", 5))
		ft_exit(arg);
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
