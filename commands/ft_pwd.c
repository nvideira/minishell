/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:46:02 by jlebre            #+#    #+#             */
/*   Updated: 2023/03/22 18:56:41 by nvideira         ###   ########.fr       */
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
