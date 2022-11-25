/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:18 by jlebre            #+#    #+#             */
/*   Updated: 2022/11/24 15:57:37 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(char **env)
{
	char		*username;
	
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, recieve);
	com_info()->env_lst = env_to_lst(env);
	com_info()->args = lst_to_env(com_info()->env_lst);
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
