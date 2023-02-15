/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:46:02 by jlebre            #+#    #+#             */
/*   Updated: 2023/02/09 16:54:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Recria o comando pwd
void	ft_pwd(void)
{
	write(1, print_dir(), ft_strlen(print_dir()));
	write(1, "\n", 1);
	com_info()->exit_value = 0;
}
