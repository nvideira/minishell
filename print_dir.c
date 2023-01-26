/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:17:25 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/26 03:10:37 by marvin           ###   ########.fr       */
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

	dir = getcwd(cwd, sizeof(cwd));
	username = getenv("USER");
	str = ft_strjoin(username, com_info()->color);
	str = ft_strjoin(str, dir);
	str = ft_strjoin(str, "$ \033[0m");
	return (str);
}

// Função para imprimir o diretório atual
char	*print_dir(void)
{
	char	cwd[1024];

	return (getcwd(cwd, sizeof(cwd)));
}
