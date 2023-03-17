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
char	*parser(char *input, char **env)
{
	char	**args;

	if (parser_checks(input))
		return (NULL);
	if (!parser_checks2(input))
		return (NULL);
	input = parse_input(input);
	if (check_special(input, '|'))
	{
		args = ft_split(input, '|');
		args = parse_input3(args);
		pipe_commands(args, env);
		free(input);
		return (NULL);
	}
	args = ft_split(input, ' ');
	return (process_input(args, input, env));
}

char	*parse_input(char *input)
{
	input = separate_input(input);
	return (input);
}

char	*parse_input2(char *input)
{
	input = process_quotes(input);
	input = check_ds(input);
	input = process_peliculas(input);
	return (input);
}

char	**parse_input3(char **input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		input[i] = parse_input2(input[i]);
		i++;
	}
	return (input);
}
