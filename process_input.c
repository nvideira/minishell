/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:35:05 by jlebre            #+#    #+#             */
/*   Updated: 2022/11/05 13:04:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(char *input, char **env, t_env_lst *env_lst)
{
	char	**args;
	(void)env_lst;
	//int		i;

	//i = 0;
	add_history(input);
	args = ft_split(input, 32);
	commands(args, env);
}

	/* printf("INPUT: %s\n", input);
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	} 
	*/
	//print_header(env);