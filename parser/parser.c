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

//input = separate_input(input);
// Processa o input e verifica se há erros
char	*parser(char *input, char **env)
{
	char	**args;

	if (parser_checks(input))
		return (NULL);
	if (!parser_checks2(input))
		return (NULL);
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
	char	*old;

	input = check_ds(input);
	old = ft_strdup(input);
	input = process_peliculas(input);
	input = process_quotes(input, old);
	free(old);
	return (input);
}

char	**parse_input3(char **input)
{
	int		i;

	i = 0;
	if (!strncmp(input[0], "export", 6))
		return (input);
	while (input[i])
	{
		input[i] = parse_input2(input[i]);
		i++;
	}
	return (input);
}
