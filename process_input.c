/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:05:06 by marvin            #+#    #+#             */
/*   Updated: 2023/02/12 17:05:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_acess_all(char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j] && (arr[i][j] == '<' || arr[i][j] == '>'
		|| arr[i][j] == ' ' || arr[i][j] == '\t' || arr[i][j] == '\n'
		|| arr[i][j] == '\v' || arr[i][j] == '\f' || arr[i][j] == '\r'
		|| arr[i][j] == '\'' || arr[i][j] == '\"' || arr[i][j] == '|'
		|| arr[i][j] == ';' || arr[i][j] == '&' || arr[i][j] == '('
		|| arr[i][j] == ')' || arr[i][j] == '$'))
			j++;
		if (arr[i][j] == '.' || arr[i][j] == '/')
		{
			if (check_file_access(arr[i], W_OK))
			{
				com_info()->exit_value = 1;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

char	*process_input(char **args, char *input, char **env)
{
	int		pid;

	if (find_es(args[0]))
		exported_vars(args);
	else if (check_special(input, '>')
		|| check_special(input, '<'))
	{
		input = parse_input2(input);
		pid = fork();
		if (pid == 0)
			redirections(input, env);
		waitpid(pid, &com_info()->exit_value, 0);
	}
	else
		commands(input, env, 0);
	free_matrix(args);
	return (input);
}
