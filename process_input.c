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
	{
		input = parse_input2(input);
		commands(input, env, 0);
	}
	free_matrix(args);
	return (input);
}
