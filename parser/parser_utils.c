/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:56:15 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/25 16:51:50 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(char *commands)
{
	int	i;
	int	quotes;
	int	dquotes;

	i = 0;
	quotes = 0;
	dquotes = 0;
	while (commands[i])
	{
		if (commands[i] == '\'' && dquotes == 0 && quotes == 0)
			quotes = 1;
		else if (commands[i] == '\'' && dquotes == 0 && quotes == 1)
			quotes = 0;
		else if (commands[i] == '\"' && dquotes == 0 && quotes == 0)
			dquotes = 1;
		else if (commands[i] == '\"' && dquotes == 1 && quotes == 0)
			dquotes = 0;
		i++;
	}
	if (quotes || dquotes)
		return (1);
	return (0);
}

int	skip_quotes(char *input, int i, char quote)
{
	int	j;

	j = ++i;
	while (input[j] && input[j] != quote)
		j++;
	if (!input[j])
		return (i);
	return (j);
}

int	verify_redir(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<' || input[i] == '|')
		{
			j = i + 1;
			while (input[j] && ft_space(input[j]))
				j++;
			if (input[j] != input[i] && (input[j] == '>' || input[j] == '<' || input[j] == '|'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}