/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:46:39 by jlebre            #+#    #+#             */
/*   Updated: 2022/12/09 17:52:53 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **input)
{
	t_env_lst	*temp;

	if (!find_path("env", com_info()->env_lst))
	{
		printf("\033[0;31mCommand not found: env\033[0m\n");
		com_info()->exit_value = 127;
		return ;
	}
	if (input[1])
	{
		printf("\033[0;31mEnv: '%s': No such file or directory\033[0m\n",
			input[1]);
		com_info()->exit_value = 127;
		return ;
	}
	temp = com_info()->env_lst;
	while (temp)
	{
		printf("%s%s\n", temp->name, temp->value);
		temp = temp->next;
	}
	com_info()->exit_value = 0;
}
