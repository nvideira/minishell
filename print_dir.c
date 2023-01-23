/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:17:25 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/23 15:49:40 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*print_dir(void)
{
	char	cwd[1024];

	return (getcwd(cwd, sizeof(cwd)));
}
