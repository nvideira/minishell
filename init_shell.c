/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:18 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/26 23:13:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Função que inicializa a shell
void	init_shell(char **env)
{
	char	*username;

	com_info()->env_lst = env_to_lst(env);
	com_info()->vars = NULL;
	com_info()->cmds_done = 0;
	com_info()->redir_type = 0;
	com_info()->color = "\033[1;32m:";
	com_info()->env = env;
	username = getenv("USER");
	printf("\n\nUSER is: @%s", username);
	ft_clear();
}
