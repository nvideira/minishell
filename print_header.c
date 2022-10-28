/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:44:30 by jlebre            #+#    #+#             */
/*   Updated: 2022/10/26 18:40:55 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_header(char **env)
{
	int		cols;
	int		lines;

	cols = get_col(env);
	lines = get_lines(env);
	printf("Cols: %i\nLines: %i\n", cols, lines);
}

int	get_col(char **env)
{
	char	*arr[3];
	int		cols;
	int		head;

	head = fork();
	arr[0] = strdup("/bin/tput");
	arr[1] = strdup("cols");
	arr[2] = 0;
	if (!head)
	{
		cols = execve(arr[0], arr, env);
		if (cols != 0)
			ft_error(" ", env);
	}
	else
		wait(0);
	return (cols);
}

int	get_lines(char **env)
{
	char	*arr[3];
	int		lines;
	int		head;

	head = fork();
	arr[0] = strdup("/bin/tput");
	arr[1] = strdup("lines");
	arr[2] = 0;
	if (!head)
	{
		lines = execve(arr[0], arr, env);
		if (lines != 0)
			ft_error(" ", env);
	}
	else
		wait(0);
	return (lines);
}
