/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:46:39 by jlebre            #+#    #+#             */
/*   Updated: 2023/02/07 16:30:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Recria o comando env
void	ft_env(char **input)
{
	t_env_lst	*temp;

	if (!find_path("env", com_info()->env_lst))
	{
		ft_error("Command not found: env\n");
		com_info()->exit_value = 127;
		return ;
	}
	if (input[1])
	{
		ft_error("Env: '%s': No such file or directory\n",
			input[1]);
		com_info()->exit_value = 127;
		return ;
	}
	temp = com_info()->env_lst;
	while (temp)
	{
		if (ft_strchr(temp->name, '='))
			printf("%s%s\n", temp->name, temp->value);
		temp = temp->next;
	}
	com_info()->exit_value = 0;
}
