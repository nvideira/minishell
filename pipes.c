/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 02:22:13 by nvideira          #+#    #+#             */
/*   Updated: 2022/12/19 11:51:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	use_pipe(int *pip)
{
	if (pipe(pip) < 0)
	{
		write(2, "Error creating pipe\n", 20);
		return (1);
	}
	com_info()->pid = fork();
	if (com_info()->pid < 0)
	{
		write(2, "Error creating fork\n", 20);
		return (1);
	}
	else if (com_info()->pid == 0)
	{
		dup2(pip[1], STDOUT_FILENO);
		close(pip[0]);
		close(pip[1]);
	}
	else
	{
		dup2(pip[0], STDIN_FILENO);
		close(pip[0]);
		close(pip[1]);
	}
	return (0);
}
