/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:35:05 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/21 23:18:11 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(char **env)
{
	while (com_info()->commands)
	{
		check_redir(com_info()->commands->arg);
		com_info()->commands->nb_args = count_args(com_info()->commands->arg);
		if (find_es(com_info()->commands->arg[0]) == 1)
			exported_vars(com_info()->commands->arg);
		else if (com_info()->pipe_no > 0)
			execute_pipe(com_info()->commands->arg);
		else
			commands(com_info()->commands->arg, env, 0);
		com_info()->cmds_done++;
		com_info()->commands = com_info()->commands->next;
	}
	catch_signal();
}
