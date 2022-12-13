/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:31 by jlebre            #+#    #+#             */
/*   Updated: 2022/10/25 15:59:31 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*com_info(void)
{
	static t_command	a;

	return (&a);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;

	(void)argc;
	(void)argv;
	init_shell(env);
	while (1)
	{
		input = readline(print_info());
		if (!input)
		{
			rl_clear_history();
			free (input);
			exit(com_info()->exit_value);
		}
		process_input(input, env);
	}
	free (input);
	return (com_info()->exit_value);
}
