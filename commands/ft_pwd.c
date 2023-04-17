/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:46:02 by jlebre            #+#    #+#             */
/*   Updated: 2023/04/05 19:28:32 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Recria o comando pwd
void	ft_pwd(char **arg)
{
	(void)arg;
	write(1, print_dir(), ft_strlen(print_dir()));
	write(1, "\n", 1);
	com_info()->exit_value = 0;
}

/*
To recreate ZSH's behaviour

if (arg[1])
{
	write(2, "pwd: too many arguments\n", 24);
	com_info()->exit_value = 1;
	return ;
}
*/
