/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:17:25 by jlebre            #+#    #+#             */
/*   Updated: 2022/11/07 18:51:58 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_info(void)
{
	char	cwd[1024];
	char	*str;
	char	*tmp;
	char	*username;
	char	*dir;
	
	dir = getcwd(cwd, sizeof(cwd));
	username = getenv("USER");
	tmp = ft_strjoin(username, "\033[0;34m:");
	str = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strjoin(str, dir);
	free(str);
	str = ft_strjoin(tmp, "$ \033[0m");
	free(tmp);
	return (str);
}

char	*print_dir(void)
{
	char	cwd[1024];

	return (getcwd(cwd, sizeof(cwd)));
}
