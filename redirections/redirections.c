/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:41:42 by nvideira          #+#    #+#             */
/*   Updated: 2023/02/08 02:17:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_redir(char **before, char **after)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (com_info()->hereflag == 0)
		{
			redirections(after, com_info()->redir_type);
			commands(before, com_info()->env, 1);
		}
		else
		{
			redirections(after, com_info()->redir_type);
			com_info()->hereflag = 0;
		}
	}
	else
		waitpid(pid, &com_info()->exit_value, 0);
	//unlink(".heredoc");
}

/*
void	fd_dup_redir(int fd, int type)
{
	if (type == 1)
		dup2(fd, 1);
	else if (type == 2)
		dup2(fd, 0);
	else if (type == 3)
		dup2(fd, 1);
	else if (type == 4)
		dup2(fd, 0);
}

void	redirections(char **input, int type)
{
	int	fd;

	if (type == 1)
		fd = open(input[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == 2)
		fd = open(input[0], O_RDONLY);
	else if (type == 3)
		fd = open(input[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == 4)
		fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fd_dup_redir(fd, type);
}
*/

void	options(char ***new, int i)
{
	if (check_redir_type(new[i][0]) <= 2)
		close(open(new[i + 1][0], O_CREAT, 0644));
	else if (check_redir_type(new[i][0]) == 4)
	{
		if (check_file_access(new[i + 1][0]))
			return ;
		else
		{	
			com_info()->redir_type = check_redir_type(new[i][0]);
			do_redir(new[0], new[i + 1]);
		}
	}
	else
	{
		com_info()->hereflag = 1;
		do_heredoc(new[i + 1][0]);
	}
}

// E preciso dar close?
//fd_close(com_info()->cmds_done_redir);

// Executa as redireções.
// Se i for impar, é o tipo de redireção.
// Se i for par, é o arquivo.
void	execute_redir(char **input)
{
	char	***new;
	int		i;

	if (input[0][0] == '<' && input[0][1] == '<')
		i = 0;
	else
		i = 1;
	new = split_redir(input);
	if (com_info()->redir_no > 1)
	{
		while (i < com_info()->redir_no * 2 - 2)
		{
			options(new, i);
			i += 2;
		}
	}
	com_info()->redir_type = check_redir_type(new[i][0]);
	if (com_info()->redir_type != 3)
		do_redir(new[0], new[i + 1]);
	else
	{
		do_heredoc(new[1][0]);
		com_info()->hereflag = 1;
	}
	//free_triple(new);
}

	// while (i < com_info()->redir_no * 2)
	// {
	// 	com_info()->redir_type = check_redir_type(new[i][0]);
	// 	do_redir(new[i - 1], new[i + 1]);
	// 	i += 2;
	// }

int	check_file_access(char *file)
{
	if (access(file, F_OK))
	{
		ft_error("%s: No such file or directory\n", file);
		return (1);
	}
	else if (access(file, R_OK))
	{
		ft_error("%s: Permission denied\n", file);
		return (1);
	}
	return (0);
}
