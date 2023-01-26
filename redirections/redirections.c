/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:41:42 by nvideira          #+#    #+#             */
/*   Updated: 2023/01/26 17:19:42 by nvideira         ###   ########.fr       */
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
	int i;

	i = 1;
	new = split_redir(input);
	//print_matrix_redir(new);
	if (com_info()->redir_no > 1)
	{
		while (i < com_info()->redir_no * 2 - 2)
		{
			close(open(new[i + 1][0], O_CREAT, 0644));
			i += 2;open(new[i + 1][0], O_CREAT, 0644);
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
