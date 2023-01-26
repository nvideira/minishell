/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:41:42 by nvideira          #+#    #+#             */
/*   Updated: 2023/01/26 18:06:31 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_redir(char **before, char **after)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		redirections(after, com_info()->redir_type);
		commands(before, com_info()->env, 1);
	}
	else
		waitpid(pid, &com_info()->exit_value, 0);
	// E preciso dar close?
	//fd_close(com_info()->cmds_done_redir);
	unlink(".heredoc");
}

// Executa as redireções.
// Se i for impar, é o tipo de redireção.
// Se i for par, é o arquivo.
void	execute_redir(char **input)
{
	char	***new;
	int 	i;

	i = 1;
	new = split_redir(input);
	if (com_info()->redir_no > 1)
	{
		while (i < com_info()->redir_no * 2 - 2)
		{
			if (check_redir_type(new[i][0]) <= 2)
				close(open(new[i + 1][0], O_CREAT, 0644));
			else
			{
				if (check_file_access(new[i + 1][0]))
					return ;
				else
				{	
					com_info()->redir_type = check_redir_type(new[i][0]);
					do_redir(new[0], new[i + 1]);
				}
			}
			i += 2;
		}
	}
	com_info()->redir_type = check_redir_type(new[i][0]);
	do_redir(new[0], new[i + 1]);
	
	// while (i < com_info()->redir_no * 2)
	// {
	// 	com_info()->redir_type = check_redir_type(new[i][0]);
	// 	do_redir(new[i - 1], new[i + 1]);
	// 	i += 2;
	// }
}

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