/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:08:21 by marvin            #+#    #+#             */
/*   Updated: 2023/01/11 18:08:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		com_info()->exit_value = 130;
	}
}

void	catch_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c);
}

void	ctrl_c_block(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		com_info()->exit_value = 130;
	}
	if (sig == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 19);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

/*
static void	ctrl_s_block(int sig)
{
	(void) sig;
	write(1, "Quit (core dumped)\n", 19);
	rl_on_new_line();
	rl_replace_line("", 0);
}
*/

//Para não dar prompt várias vezes
//Ctrl + C
//Ctrl + /
void	signal_block(void)
{
	signal(SIGQUIT, ctrl_c_block);
	signal(SIGINT, ctrl_c_block);
}
