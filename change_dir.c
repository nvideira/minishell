/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:56:17 by jlebre            #+#    #+#             */
/*   Updated: 2022/11/17 22:25:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(char **input)
{
	if (input[1])
	{
		chdir(input[1]);
		com_info()->exit_value = 0;
	}
	else
	{
		chdir(ft_strjoin("/nfs/homes/", getenv("USER")));
		com_info()->exit_value = 0;
	}
}
