/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:17:25 by jlebre            #+#    #+#             */
/*   Updated: 2023/02/16 19:55:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Função para criar o prompt
char	*print_info(void)
{
	char	cwd[1024];
	char	*str;
	char	*username;
	char	*dir;
	char	*temp;

	dir = getcwd(cwd, sizeof(cwd));
	username = gce("USER=");
	str = ft_strjoin(username, com_info()->color);
	free(username);
	temp = ft_strjoin(str, dir);
	free(str);
	str = ft_strjoin(temp, "$ \033[0m");
	free(temp);
	return (str);
}

// Função para imprimir o diretório atual
char	*print_dir(void)
{
	char	cwd[1024];

	return (getcwd(cwd, sizeof(cwd)));
}
