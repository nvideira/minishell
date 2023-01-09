/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:18 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/08 22:19:09 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(char **env)
{
	char	*username;
	
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, recieve);
	com_info()->env_lst = env_to_lst(env);
	com_info()->vars = NULL;
	com_info()->fd_in = 0;
	com_info()->cmds_done = 0;
	com_info()->color = "\033[1;32m:";
	username = getenv("USER");
	printf("\n\nUSER is: @%s", username);
	ft_clear();
}

void	recieve(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();	
	}
}
