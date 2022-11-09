/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:02:49 by jlebre            #+#    #+#             */
/*   Updated: 2022/11/09 15:33:04 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commands(char **input, char **env)
{
	if (!input)
		return ;
	//printf("test\n");
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
