/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:18 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/23 18:17:00 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(char **env)
{
	char	*username;

	com_info()->env_lst = env_to_lst(env);
	com_info()->vars = NULL;
	com_info()->fd_in = 0;
	com_info()->cmds_done = 0;
	com_info()->redir_type_prev = 0;
	com_info()->color = "\033[1;32m:";
	com_info()->env = env;
	username = getenv("USER");
	printf("\n\nUSER is: @%s", username);
	ft_clear();
}
