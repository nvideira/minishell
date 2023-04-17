/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:56:15 by jlebre            #+#    #+#             */
/*   Updated: 2023/03/23 22:19:08 by marvin           ###   ########.fr       */
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
		ft_error("minishell: syntax error: unclosed quotes\n");
		return (0);
	}
	if (check_xor(input))
	{
		ft_error("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	if (check_and(input))
	{
		ft_error("minishell: syntax error near unexpected token `&'\n");
		return (0);
	}
	if (!verify_redir(input))
	{
		ft_error("minishell: syntax error near unexpected token `'\n");
		return (0);
	}
	if (!verify_redir_2(input))
		return (0);
	return (1);
}

int	check_quotes(char *commands)
{
	int	i;

	if (find_quote(commands, '"') % 2 != 0 && find_quote(commands, '"') != 0)
	{
		i = find_quote_position(commands, '"');
		if (check_if_inside_quotes(commands, i))
			return (0);
		return (1);
	}
	if (find_quote(commands, '\'') % 2 != 0 && find_quote(commands, '\'') != 0)
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

	j = i - 1;
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
