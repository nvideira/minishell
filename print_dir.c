/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:17:25 by jlebre            #+#    #+#             */
/*   Updated: 2023/02/16 16:42:04 by nvideira         ###   ########.fr       */
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
	char	*new;

	dir = getcwd(cwd, sizeof(cwd));
	username = gce("USER=");
	new = ft_strjoin(username, com_info()->color);
	free(username);
	str = ft_strjoin(new, dir);
	free(new);
	new = ft_strjoin(str, "$ \033[0m");
	free(str);
	return (new);
}

// Função para imprimir o diretório atual
char	*print_dir(void)
{
	char	cwd[1024];

	return (getcwd(cwd, sizeof(cwd)));
}
