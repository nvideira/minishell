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
		return NULL;
	if (!parser_checks2(input))
		return NULL;
	input = parse_input(input);
	if (check_special(input, '|'))
	{
		input = parse_input2(input);
		args = ft_split(input, '|');
		pipe_commands(args, env);
		free_matrix(args);
		free(input);
		return NULL;
	}
	args = ft_split(input, ' ');
	return (process_input(args, input, env));
}

//input = put_spaces(input);
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
	//char	*tmp;

	i = 0;
	while (input[i])
	{
	//	free(input[i]);
	//	input[i] = ft_strdup(tmp);
		// free(tmp);
		input[i] = process_quotes(input[i]);
		input[i] = check_ds(input[i]);
		input[i] = process_peliculas(input[i]);
		i++;
	}
	return (input);
}
