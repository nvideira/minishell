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

static void	ctrl_c(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	catch_signal(void)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

static void	ctrl_c_block(int sig)
{
	if (sig == 2)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
	}
}

static void	ctrl_s_block(int sig)
{
	(void) sig;
	write(1, "Quit (core dumped)\n", 19);
	rl_on_new_line();
	rl_replace_line("", 0);
}

//Para não dar prompt várias vezes
//Ctrl + C
//Ctrl + /
void	signal_block(void)
{
	signal(SIGINT, &ctrl_c_block);
	signal(SIGQUIT, &ctrl_s_block);
}
