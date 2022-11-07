/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:02:49 by jlebre            #+#    #+#             */
/*   Updated: 2022/11/05 13:03:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commands(char **input, char **env)
{
	if (!ft_strcmp(input[0], "cd"))
		change_dir(input, env);
	else if (!ft_strcmp(input[0], "pwd"))
		printf("%s\n", print_dir());
	else if (!ft_strcmp(input[0], "echo"))
		printf("%s\n", input[1]);
	else if (!ft_strcmp(input[0], "clear"))
		printf("\033c");
}

void	change_dir(char **input, char **env)
{
	if (!opendir(input[1]))
		ft_error("Directory not found!\n", env);
}
