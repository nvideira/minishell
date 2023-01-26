/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:35:05 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/26 04:58:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Processa o input
// Enquanto houver comandos:
// Se o comando tiver um sinal de '=', chama a função exported_vars
// Se o comando tiver um sinal de redirecionamento, chama a função execute_redir
// Se o comando tiver um sinal de pipe, chama a função execute_pipe
// Se não, chama a função commands
// Incrementa o número de comandos feitos
// Avança para o próximo comando
void	process_input(char **env)
{
	while (com_info()->commands)
	{
		com_info()->commands->nb_args = count_args(com_info()->commands->arg);
		if (find_es(com_info()->commands->arg[0]) == 1)
			exported_vars(com_info()->commands->arg);
		else if (count_redirs(com_info()->commands->arg) > 0)
			execute_redir(com_info()->commands->arg);
		else if (com_info()->pipe_no > 0)
			execute_pipe(com_info()->commands->arg);
		else
			commands(com_info()->commands->arg, env, 0);
		com_info()->cmds_done++;
		com_info()->commands = com_info()->commands->next;
	}
	//free_all();
	catch_signal();
}
