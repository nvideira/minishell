/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 02:22:13 by nvideira          #+#    #+#             */
/*   Updated: 2023/01/03 21:26:33 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	use_pipe(void)
{
	if (pipe(com_info()->pip) < 0)
		{
			write(2, "Pipe error\n", 10);
			return ;
		}
		com_info()->pid = fork();
		if (com_info()->pid == 0)
		{
			
			if (com_info()->fd_in > 0)
			{
				close(com_info()->pip[1]);
				dup2(com_info()->pip[0], STDIN_FILENO);
				//se houver redirecoes
					//dup2(output, STDOUT_FILENO);
				//dup2(com_info()->pip[1], STDOUT_FILENO);
			}
			else
			{
				close(com_info()->pip[0]);
				//se nao houver redirecoes
				dup2(com_info()->pip[1], STDOUT_FILENO);
			}
			write(2, com_info()->commands->arg[0], ft_strlen(com_info()->commands->arg[0]));
			write(2, "\n", 1);
			com_info()->fd_in++;
			if (com_info()->commands->next)
			{
				dup2(com_info()->pip[1], STDOUT_FILENO);
			}
		}
}
