/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:25:19 by nvideira          #+#    #+#             */
/*   Updated: 2023/02/06 18:39:38 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_cleanup(void)
{
	int	i;

	i = 0;
	while (i < com_info()->pipe_no)
	{
		close(com_info()->pip[i][0]);
		close(com_info()->pip[i][1]);
		i++;
	}
	free(com_info()->pip);
}