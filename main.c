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

int	main(int ac, char **av, char **env)
{
	char *input;
	t_env_lst *env_lst;

	(void)ac;
	(void)av;
	init_shell(env);
	ft_clear();
	env_lst = env_to_lst(env);
	// while (env_lst)
	// {
	// 	printf("name: %s, value: %s\n", env_lst->name, env_lst->value);
	// 	env_lst = env_lst->next;
	// }
	while (1)
	{
		input = readline(print_info());
		if (!input)
			exit(0);
		process_input(input, env);
	}
	return (0);
}
