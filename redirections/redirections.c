/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:29:35 by marvin            #+#    #+#             */
/*   Updated: 2023/03/17 20:12:28 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_redirections(char *input)
{
	char	**arr;
	char	*new;
	char	*temp;
	int		i;

	i = 0;
	arr = ft_split(input, ' ');
	new = ft_strjoin(arr[0], " ");
	while (arr[++i])
	{
		if (ft_str1chr(arr[i], '<') || ft_str1chr(arr[i], '>'))
			break ;
		temp = ft_strjoin(new, arr[i]);
		free(new);
		new = temp;
		if (!ft_str1chr(arr[i + 1], '<') && !ft_str1chr(arr[i + 1], '>'))
		{
			temp = ft_strjoin(new, " ");
			free(new);
			new = temp;
		}
	}
	free_matrix(arr);
	free(input);
	return (new);
}

// Faz as redireções e as duplicações de file descriptors
// O que se faz quando tem vários argumentos a seguir ao redirecionador?
void	redirections(char *input, char **env)
{
	int	fd_in;
	int	fd_out;

	if (check_special(input, '<'))
	{
		fd_in = redirect_input(input);
		if (fd_in <= -1)
			exit(com_info()->exit_value);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (check_special(input, '>'))
	{
		fd_out = redirect_output(input);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	input = remove_redirections(input);
	commands(input, env, 1);
	exit(com_info()->exit_value);
}
