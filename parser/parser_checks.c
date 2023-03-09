/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:56:15 by jlebre            #+#    #+#             */
/*   Updated: 2023/03/09 01:09:39 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_checks(char *input)
{
	if (empty_prompt(input))
		return (1);
	if (ft_strlen(input))
		add_history(input);
	return (0);
}

int	parser_checks2(char *input)
{
	if (check_quotes(input))
	{
		printf("minishell: syntax error: unclosed quotes\n");
		return (0);
	}
	if (check_xor(input))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	if (check_and(input))
	{
		printf("minishell: syntax error near unexpected token `&'\n");
		return (0);
	}
	if (!verify_redir(input))
	{
		printf("minishell: syntax error near unexpected token `'\n");
		return (0);
	}
	if (!verify_redir_2(input))
		return (0);
	return (1);
}

int	check_quotes(char *commands)
{
	int	i;

	if (find_quote(commands) % 2 != 0 && find_quote(commands) != 0)
	{
		i = find_quote_position(commands, '"');
		if (check_if_inside_quotes(commands, i))
			return (0);
		return (1);
	}
	if (find_pelicula(commands) % 2 != 0 && find_pelicula(commands) != 0)
	{
		i = find_quote_position(commands, '\'');
		if (check_if_inside_quotes(commands, i))
			return (0);
		return (1);
	}
	return (0);
}

int	find_quote_position(char *input, char type)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == type)
			return (i);
		i++;
	}
	return (0);
}

int	check_if_inside_quotes(char *input, int i)
{
	int	j;

	j = i;
	while (j >= 0)
	{
		if (input[j] == '"' || input[j] == '\'')
			break ;
		j--;
	}
	while (input[i])
	{
		if (j >= 0 && input[i] == input[j])
			return (1);
		i++;
	}
	return (0);
}

int	check_xor(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			i++;
			while (input[i] && is_space(input[i]))
				i++;
			if (input[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_and(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '&')
			return (1);
		i++;
	}
	return (0);
}
