/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:17:25 by jlebre            #+#    #+#             */
/*   Updated: 2022/10/25 17:59:21 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_dir(void)
{
	char	cwd[1024];
	char	*str;
	char	*username;
	char	*dir;
	
	dir = getcwd(cwd, sizeof(cwd));
	username = getenv("USER");
	str = ft_strjoin(username, ":");
	str = ft_strjoin(str, dir);
	str = ft_strjoin(str, "$ ");
	return (str);
}
