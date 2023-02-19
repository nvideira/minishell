/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:28:38 by marvin            #+#    #+#             */
/*   Updated: 2023/02/15 13:28:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special(char *input, char c)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == c)
		{
			if (!special_quote(input, i)
				&& !surround_quote(input, i, '"'))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_before(char *input, int index, int quote)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < index)
	{
		if (input[i] == quote)
			count++;
		i++;
	}
	return (count);
}

int	check_after(char *input, int index, int quote)
{
	int	count;

	count = 0;
	while (input[index])
	{
		if (input[index] == quote)
			count++;
		index++;
	}
	return (count);
}

int	surround_quote(char *input, int index, int quote)
{
	int	quote_before;
	int	quote_after;

	quote_before = check_before(input, index, quote);
	quote_after = check_after(input, index, quote);
	if (quote_before != 0 && quote_before % 2 == 0)
		return (0);
	if (quote_after != 0 && quote_after % 2 == 0)
		return (0);
	if ((quote_before != 0 && quote_before % 2 != 0)
		&& (quote_after != 0 && quote_after % 2 == 0))
		return (1);
	return (0);
}

int	special_quote(char *input, int i)
{
	int	a;
	int	b;
	int	count;

	if (i == -1)
		return (0);
	a = 0;
	b = 0;
	count = i;
	while (count >= 0)
	{
		if (input[count] == '\"' && count >= 1
			&& input[count - 1] != '\\')
			a++;
		else if (input[count] == '\'' && count >= 1
			&& input[count - 1] != '\\')
			b++;
		count--;
	}
	if (a % 2 == 0 && b % 2 == 0)
		return (0);
	return (1);
}
