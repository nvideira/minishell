/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:18:36 by marvin            #+#    #+#             */
/*   Updated: 2023/02/11 14:18:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Processa o input e verifica se há erros
void	parser(char *input, char **env)
{
	char	**args;

	if (parser_checks(input))
		return ;
	if (!parser_checks2(input))
		return ;
	input = parse_input(input);
	if (check_special(input, '|'))
	{
		input = parse_input2(input);
		args = ft_split(input, '|');
		pipe_commands(args, env);
		free_matrix(args);
		return ;
	}
	args = ft_split(input, ' ');
	process_input(args, input, env);
}
