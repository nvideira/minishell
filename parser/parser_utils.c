/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:56:15 by jlebre            #+#    #+#             */
/*   Updated: 2022/12/14 16:58:16 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_limiter(char *input, int start)
{
	int		i;
	char	*limiter;

	while (input[start] && (input[start] == ' ' || input[start] == '\t'))
		start++;
	i = start;
	while (input[i] && input[i] != ' ' && input[i] != '\t')
		i++;
	limiter = ft_substr(input, start, i - start);
	return (limiter);
}

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

char	***split_split(char **matrix)
{
	char	***ret;
	int		i;

	i = 0;
	while (matrix[i])
		i++;
	ret = malloc(sizeof(char **) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		ret[i] = ft_split(matrix[i], ' ');
		i++;
	}
	ret[i] = NULL;
	return (ret);
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

int	count_pipes(char *input)
{
	int	i;
	int	pipe_no;

	i = 0;
	pipe_no = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_quotes(input, i, input[i]);
		else if (input[i] == '|')
			pipe_no++;
		i++;
	}
	return (pipe_no);
}
