/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:35:05 by jlebre            #+#    #+#             */
/*   Updated: 2022/11/09 16:02:26 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(char *input, char **env, t_env_lst *env_lst)
{
	char	**args;
	(void)env_lst;
	//int		i;

	//i = 0;
	//printf("input: /%s/\n", input);
	if(input[0] == '\0')
		return ;
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