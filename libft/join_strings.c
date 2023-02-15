/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:53:14 by marvin            #+#    #+#             */
/*   Updated: 2023/02/11 17:53:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Retorna o path do comando
char	*join_strings(char *path, int j, char *cmd)
{
	char	*dir;
	char	*ret_path;

	dir = ft_substring(path, j, ft_strichr(path, j, ':') - j);
	ret_path = ft_strjoin(dir, cmd);
	free(dir);
	return (ret_path);
}
