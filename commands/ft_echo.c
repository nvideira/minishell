/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:31:01 by marvin            #+#    #+#             */
/*   Updated: 2022/11/17 23:31:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Recria o comando echo
// Tem as funcionalidades de -n e -e
// Também tem a funcionalidade de imprimir o que é passado como argumento
void	ft_echo(char **input)
{
	if (!input[1])
		printf("\n");
	else if (!ft_strncmp(input[1], "-n", 3))
		do_print(input, 2, 2);
	else if (!ft_strncmp(input[1], "-e", 3))
		process_flags(input, 2);
	else
		do_print(input, 1, 1);
	com_info()->exit_value = 0;
}
